/*
################################################################################
#
# r8168 is the Linux device driver released for Realtek Gigabit Ethernet
# controllers with PCI-Express interface.
#
# Copyright(c) 2020 Realtek Semiconductor Corp. All rights reserved.
#
# This program is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by the Free
# Software Foundation; either version 2 of the License, or (at your option)
# any later version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
# more details.
#
# You should have received a copy of the GNU General Public License along with
# this program; if not, see <http://www.gnu.org/licenses/>.
#
# Author:
# Realtek NIC software team <nicfae@realtek.com>
# No. 2, Innovation Road II, Hsinchu Science Park, Hsinchu 300, Taiwan
#
################################################################################
*/

/************************************************************************************
 *  This product is covered by one or more of the following patents:
 *  US6,570,884, US6,115,776, and US6,327,625.
 ***********************************************************************************/

#include <linux/pci.h>
#include <linux/etherdevice.h>
#include <linux/skbuff.h>
#include "r8125.h"
#include "r8125_lib.h"

static void
rtl8125_map_to_asic(struct rtl8125_private *tp,
                    struct rtl8125_ring *ring,
                    struct RxDesc *desc,
                    dma_addr_t mapping,
                    u32 rx_buf_sz,
                    const u32 cur_rx)
{
        ring->bufs[cur_rx].dma_addr = mapping;
        if (tp->InitRxDescType == RX_DESC_RING_TYPE_3)
                ((struct RxDescV3 *)desc)->addr = cpu_to_le64(mapping);
        else
                desc->addr = cpu_to_le64(mapping);
        wmb();
        rtl8125_mark_to_asic(tp, desc, rx_buf_sz);
}

static void
rtl8125_lib_tx_fill(struct rtl8125_ring *ring)
{
        struct TxDesc *descs = ring->desc_addr;
        u32 i;

        for (i = 0; i < ring->ring_size; i++) {
                struct TxDesc *desc = &descs[i];

                desc->addr = cpu_to_le64(ring->bufs[i].dma_addr);

                if (i == (ring->ring_size - 1))
                        desc->opts1 = cpu_to_le32(RingEnd);
        }
}

static inline void
rtl8125_mark_as_last_descriptor_8125(struct RxDescV3 *descv3)
{
        descv3->RxDescNormalDDWord4.opts1 |= cpu_to_le32(RingEnd);
}

static inline void
rtl8125_mark_as_last_descriptor(struct rtl8125_private *tp,
                                struct RxDesc *desc)
{
        if (tp->InitRxDescType == RX_DESC_RING_TYPE_3)
                rtl8125_mark_as_last_descriptor_8125((struct RxDescV3 *)desc);
        else
                desc->opts1 |= cpu_to_le32(RingEnd);
}

static void
rtl8125_lib_rx_fill(struct rtl8125_ring *ring)
{
        struct rtl8125_private *tp = ring->private;
        struct RxDesc *desc;
        u32 i;

        for (i = 0; i < ring->ring_size; i++) {
                desc = rtl8125_get_rxdesc(tp, ring->desc_addr, i);
                rtl8125_map_to_asic(tp, ring, desc,
                                    ring->bufs[i].dma_addr, ring->buff_size, i);
        }

        rtl8125_mark_as_last_descriptor(tp,
                                        rtl8125_get_rxdesc(tp, ring->desc_addr, ring->ring_size - 1));
}

struct rtl8125_ring *rtl8125_get_tx_ring(struct rtl8125_private *tp)
{
        int i;

        for (i = tp->num_tx_rings; i < tp->HwSuppNumTxQueues; i++) {
                struct rtl8125_ring *ring = &tp->lib_tx_ring[i];
                if (!ring->allocated) {
                        ring->allocated = true;
                        return ring;
                }
        }

        return NULL;
}

struct rtl8125_ring *rtl8125_get_rx_ring(struct rtl8125_private *tp)
{
        int i;

        for (i = tp->num_rx_rings; i < tp->HwSuppNumRxQueues; i++) {
                struct rtl8125_ring *ring = &tp->lib_rx_ring[i];
                if (!ring->allocated) {
                        ring->allocated = true;
                        return ring;
                }
        }

        return NULL;
}

static void rtl8125_put_ring(struct rtl8125_ring *ring)
{
        if (!ring)
                return;

        ring->allocated = false;
}

static void rtl8125_init_rx_ring(struct rtl8125_ring *ring)
{
        struct rtl8125_private *tp = ring->private;

        if (!ring->allocated)
                return;

        rtl8125_lib_rx_fill(ring);

        RTL_W32(tp, RDSAR_Q1_LOW_8125, ((u64)ring->desc_daddr & DMA_BIT_MASK(32)));
        RTL_W32(tp, RDSAR_Q1_LOW_8125 + 4, ((u64)ring->desc_daddr >> 32));
}

static void rtl8125_init_tx_ring(struct rtl8125_ring *ring)
{
        struct rtl8125_private *tp = ring->private;

        if (!ring->allocated)
                return;

        rtl8125_lib_tx_fill(ring);

        RTL_W32(tp, TNPDS_Q1_LOW_8125, ((u64)ring->desc_daddr & DMA_BIT_MASK(32)));
        RTL_W32(tp, TNPDS_Q1_LOW_8125 + 4, ((u64)ring->desc_daddr >> 32));
}

static void rtl8125_free_ring_mem(struct rtl8125_ring *ring)
{
        unsigned i;
        struct rtl8125_private *tp = ring->private;
        struct pci_dev *pdev = tp->pci_dev;

        if (ring->desc_addr) {
                dma_free_coherent(&pdev->dev, ring->desc_size,
                                  ring->desc_addr, ring->desc_daddr);

                ring->desc_addr = NULL;
        }

        if (ring->flags & RTL8125_CONTIG_BUFS) {
                struct rtl8125_buf *rtl_buf = &ring->bufs[0];
                dma_free_coherent(
                        &pdev->dev,
                        ring->ring_size * ring->buff_size,
                        rtl_buf->addr,
                        rtl_buf->dma_addr);
        } else {
                for (i=0; i<ring->ring_size ; i++) {
                        struct rtl8125_buf *rtl_buf = &ring->bufs[i];
                        if (rtl_buf->addr) {
                                dma_free_coherent(
                                        &pdev->dev,
                                        rtl_buf->size,
                                        rtl_buf->addr,
                                        rtl_buf->dma_addr);

                                rtl_buf->addr = NULL;
                        }
                }
        }

        if (ring->bufs) {
                kfree(ring->bufs);
                ring->bufs = 0;
        }
}

static int rtl8125_alloc_ring_mem(struct rtl8125_ring *ring)
{
        int i;
        struct rtl8125_private *tp = ring->private;
        struct pci_dev *pdev = tp->pci_dev;

        ring->bufs = kzalloc(sizeof(struct rtl8125_buf) * ring->ring_size, GFP_KERNEL);
        if (!ring->bufs)
                return -ENOMEM;

        if (ring->mem_ops == NULL) {
                /* Use dma_alloc_coherent() and dma_free_coherent() below */
                if (ring->direction == RTL8125_CH_DIR_TX)
                        ring->desc_size = ring->ring_size * sizeof(struct TxDesc);
                else if (ring->direction == RTL8125_CH_DIR_RX)
                        ring->desc_size = ring->ring_size * tp->RxDescLength;

                ring->desc_addr = dma_alloc_coherent(
                                          &pdev->dev,
                                          ring->desc_size,
                                          &ring->desc_daddr,
                                          GFP_KERNEL);
                if (!ring->desc_addr)
                        goto error_out;

                memset(ring->desc_addr, 0x0, ring->desc_size);

                if (ring->flags & RTL8125_CONTIG_BUFS) {
                        struct rtl8125_buf *rtl_buf = &ring->bufs[0];

                        rtl_buf->size = ring->buff_size;
                        rtl_buf->addr = dma_alloc_coherent(
                                                &pdev->dev,
                                                ring->ring_size * ring->buff_size,
                                                &rtl_buf->dma_addr,
                                                GFP_KERNEL);
                        if (!rtl_buf->addr)
                                goto error_out;

                        for (i = 1; i < ring->ring_size; i++) {
                                struct rtl8125_buf *rtl_buf = &ring->bufs[i];
                                struct rtl8125_buf *rtl_buf_prev = &ring->bufs[i-1];
                                rtl_buf->size = ring->buff_size;
                                rtl_buf->addr = rtl_buf_prev->addr + ring->buff_size;
                                rtl_buf->dma_addr = rtl_buf_prev->dma_addr + ring->buff_size;
                        }

                } else {
                        for (i = 0; i < ring->ring_size; i++) {
                                struct rtl8125_buf *rtl_buf = &ring->bufs[i];

                                rtl_buf->size = ring->buff_size;
                                rtl_buf->addr = dma_alloc_coherent(
                                                        &pdev->dev,
                                                        rtl_buf->size,
                                                        &rtl_buf->dma_addr,
                                                        GFP_KERNEL);
                                if (!rtl_buf->addr)
                                        goto error_out;

                                memset(rtl_buf->addr, 0x0, rtl_buf->size);
                        }
                }
        }
#if 0
        /* Validate parameters */
        /* Allocate descs */
        mem_ops->alloc_descs(...);

        /* Allocate buffers */
        if (R8125B_CONTIG_BUFS) {
                mem_ops->alloc_buffs(...);
        } else {
                /* Call mem_ops->alloc_buffs(...) for each descriptor. */
        }
#endif

        return 0;

error_out:

        rtl8125_free_ring_mem(ring);

        return -ENOMEM;
}


struct rtl8125_ring *rtl8125_request_ring(struct net_device *ndev,
                unsigned int ring_size, unsigned int buff_size,
                enum rtl8125_channel_dir direction, unsigned int flags,
                struct rtl8125_mem_ops *mem_ops)
{
        struct rtl8125_private *tp = netdev_priv(ndev);
        struct rtl8125_ring * ring = 0;

        if (direction == RTL8125_CH_DIR_TX) {
                ring = rtl8125_get_tx_ring(tp);
                if (!ring)
                        goto error_out;
        } else if (direction == RTL8125_CH_DIR_RX) {
                ring = rtl8125_get_rx_ring(tp);
                if (!ring)
                        goto error_out;
        } else
                goto error_out;

        ring->ring_size = ring_size;
        ring->buff_size = buff_size;
        ring->mem_ops = mem_ops;
        ring->flags = flags;

        if (rtl8125_alloc_ring_mem(ring))
                goto error_out;

        /* initialize descriptors to point to buffers allocated */
        if (direction == RTL8125_CH_DIR_TX)
                rtl8125_init_tx_ring(ring);
        else if (direction == RTL8125_CH_DIR_RX)
                rtl8125_init_rx_ring(ring);

        return ring;

error_out:
        rtl8125_free_ring_mem(ring);
        rtl8125_put_ring(ring);

        return NULL;
}
EXPORT_SYMBOL(rtl8125_request_ring);

void rtl8125_release_ring(struct rtl8125_ring *ring)
{
        struct rtl8125_private *tp;

        if (!ring)
                return;

        tp = ring->private;

        rtl8125_free_ring_mem(ring);
        rtl8125_put_ring(ring);
        rtl8125_enable_hw_linkchg_interrupt(tp);
}
EXPORT_SYMBOL(rtl8125_release_ring);

void
rtl8125_hw_config(struct net_device *dev);

int rtl8125_enable_ring(struct rtl8125_ring *ring)
{
        struct rtl8125_private *tp;
        struct net_device *dev;

        if (!ring)
                return -EINVAL;

        if (!(ring->direction == RTL8125_CH_DIR_TX || ring->direction == RTL8125_CH_DIR_RX))
                return -EINVAL;

        tp = ring->private;
        dev = tp->dev;

        /* Start the ring if needed */
        rtl8125_hw_reset(dev);
        rtl8125_tx_clear(tp);
        rtl8125_rx_clear(tp);
        rtl8125_init_ring(dev);

        ring->enabled = true;

        rtl8125_hw_config(dev);
        rtl8125_hw_start(dev);

        return 0;
}
EXPORT_SYMBOL(rtl8125_enable_ring);

void rtl8125_disable_ring(struct rtl8125_ring *ring)
{
        struct rtl8125_private *tp;
        struct net_device *dev;

        /* Stop the ring if possible. IPA do not want to receive or transmit
        packets beyond this point.
        */

        if (!ring)
                return;

        if (!(ring->direction == RTL8125_CH_DIR_TX || ring->direction == RTL8125_CH_DIR_RX))
                return;

        tp = ring->private;
        dev = tp->dev;

        rtl8125_hw_reset(dev);
        //rtl8125_tx_clear(tp);
        //rtl8125_rx_clear(tp);
        //rtl8125_init_ring(dev);

        ring->enabled = false;

        //rtl8125_hw_config(dev);
        //rtl8125_hw_start(dev);
}
EXPORT_SYMBOL(rtl8125_disable_ring);

int rtl8125_request_event(struct rtl8125_ring *ring, unsigned long flags,
                          dma_addr_t addr, u64 data)
{
        struct rtl8125_private *tp;
        struct pci_dev *pdev;
        u32 message_id;

        if (!ring)
                return -EINVAL;

        if (!(ring->direction == RTL8125_CH_DIR_TX || ring->direction == RTL8125_CH_DIR_RX))
                return -EINVAL;

        if (ring->event.allocated)
                return -EEXIST;

        if (ring->direction == RTL8125_CH_DIR_TX)
                message_id = (ring->queue_num == 0 ? 16 : 18);
        else
                message_id = ring->queue_num;

        tp = ring->private;
        pdev = tp->pci_dev;

        if (flags & MSIX_event_type) {
                /* Update MSI-X table entry with @addr and @data */
                /* Initialize any MSI-X/interrupt related register in HW */
                u16 reg = message_id * 0x10;

                ring->event.addr = rtl8125_eri_read(tp, reg, 4, ERIAR_MSIX);
                ring->event.addr |= (u64)rtl8125_eri_read(tp, reg + 4, 4, ERIAR_MSIX) << 32;
                ring->event.data = rtl8125_eri_read(tp, reg + 8, 4, ERIAR_MSIX);
                ring->event.data |= (u64)rtl8125_eri_read(tp, reg + 8, 4, ERIAR_MSIX) << 32;

                rtl8125_eri_write(tp, reg, 4, (u64)addr & DMA_BIT_MASK(32), ERIAR_MSIX);
                rtl8125_eri_write(tp, reg + 4, 4, (u64)addr >> 32, ERIAR_MSIX);
                rtl8125_eri_write(tp, reg + 8, 4, data, ERIAR_MSIX);
                rtl8125_eri_write(tp, reg + 12, 4, data >> 32, ERIAR_MSIX);

                ring->event.message_id = message_id;
                ring->event.allocated = 1;
        }

        return 0;
}
EXPORT_SYMBOL(rtl8125_request_event);

void rtl8125_release_event(struct rtl8125_ring *ring)
{
        struct rtl8125_private *tp;
        dma_addr_t addr;
        u64 data;
        u16 reg;

        /* Reverse request_event() */
        if (!ring->event.allocated)
                return;

        if (!(ring->direction == RTL8125_CH_DIR_TX || ring->direction == RTL8125_CH_DIR_RX))
                return;

        if (!ring->event.allocated)
                return;

        tp = ring->private;

        reg = ring->event.message_id * 0x10;

        addr = ring->event.addr;
        data = ring->event.data;
        rtl8125_eri_write(tp, reg, 4, (u64)addr & DMA_BIT_MASK(32), ERIAR_MSIX);
        rtl8125_eri_write(tp, reg + 4, 4, (u64)addr >> 32, ERIAR_MSIX);
        rtl8125_eri_write(tp, reg + 8, 4, data, ERIAR_MSIX);
        rtl8125_eri_write(tp, reg + 12, 4, data >> 32, ERIAR_MSIX);

        ring->event.allocated = 0;

        return;
}
EXPORT_SYMBOL(rtl8125_release_event);

int rtl8125_enable_event(struct rtl8125_ring *ring)
{
        struct rtl8125_private *tp = ring->private;

        if (!ring->event.allocated)
                return -EINVAL;

        /* Set interrupt moderation timer */
        rtl8125_set_ring_intr_mod(ring, ring->event.delay);

        /* Enable interrupt */
        rtl8125_enable_hw_interrupt_v2(tp, ring->event.message_id);

        ring->event.enabled = 1;

        return 0;
}
EXPORT_SYMBOL(rtl8125_enable_event);

int rtl8125_disable_event(struct rtl8125_ring *ring)
{
        struct rtl8125_private *tp = ring->private;

        if (!ring->event.allocated)
                return -EINVAL;

        /* Disable interrupt */
        rtl8125_disable_hw_interrupt_v2(tp, ring->event.message_id);

        ring->event.enabled = 0;

        return 0;
}
EXPORT_SYMBOL(rtl8125_disable_event);

int rtl8125_set_ring_intr_mod(struct rtl8125_ring *ring, int delay)
{
        struct rtl8125_private *tp = ring->private;

        if (!ring->event.allocated)
                return -EFAULT;

        ring->event.delay = delay;

        /* Set interrupt moderation timer */
        rtl8125_hw_set_timer_int_8125(tp, ring->event.message_id, ring->event.delay);

        return 0;
}
EXPORT_SYMBOL(rtl8125_set_ring_intr_mod);

int rtl8125_rss_redirect(struct net_device *ndev,
                         unsigned long flags,
                         struct rtl8125_ring *ring)
{
        struct rtl8125_private *tp = ring->private;
        int i;

        /* Disable RSS if needed */
        /* Update RSS hash table to set all entries point to ring->queue */
        /* Set additional flags as needed. Ex. hash_type */
        /* Enable RSS */

        for (i = 0; i < rtl8125_rss_indir_tbl_entries(tp); i++)
                tp->rss_indir_tbl[i] = ring->queue_num;

        _rtl8125_config_rss(tp);

        return 0;
}
EXPORT_SYMBOL(rtl8125_rss_redirect);

int rtl8125_rss_reset(struct net_device *ndev)
{
        struct rtl8125_private *tp = netdev_priv(ndev);

        /* Disable RSS */
        /* Reset RSS hash table */
        /* Enable RSS if that is the default config for driver */

        rtl8125_init_rss(tp);
        _rtl8125_config_rss(tp);

        return 0;
}
EXPORT_SYMBOL(rtl8125_rss_reset);

struct net_device *rtl8125_get_netdev(struct device *dev)
{
        struct pci_dev *pdev = to_pci_dev(dev);

        /* Get device private data from @dev */
        /* Retrieve struct net_device * from device private data */

        return pci_get_drvdata(pdev);
}
EXPORT_SYMBOL(rtl8125_get_netdev);

int rtl8125_receive_skb(struct net_device *net_dev, struct sk_buff *skb, bool napi)
{
        /* Update interface stats - rx_packets, rx_bytes */
        skb->protocol = eth_type_trans(skb, net_dev);
        return napi ? netif_receive_skb(skb) : netif_rx(skb);
}
EXPORT_SYMBOL(rtl8125_receive_skb);

int rtl8125_register_notifier(struct net_device *net_dev,
                              struct notifier_block *nb)
{
        struct rtl8125_private *tp = netdev_priv(net_dev);

        return atomic_notifier_chain_register(&tp->lib_nh, nb);
}
EXPORT_SYMBOL(rtl8125_register_notifier);

int rtl8125_unregister_notifier(struct net_device *net_dev,
                                struct notifier_block *nb)
{
        struct rtl8125_private *tp = netdev_priv(net_dev);

        return atomic_notifier_chain_unregister(&tp->lib_nh, nb);
}
EXPORT_SYMBOL(rtl8125_unregister_notifier);

void rtl8125_lib_reset_prepare(struct rtl8125_private *tp)
{
        atomic_notifier_call_chain(&tp->lib_nh,
                                   RTL8125_NOTIFY_RESET_PREPARE, NULL);
}
EXPORT_SYMBOL(rtl8125_lib_reset_prepare);

void rtl8125_lib_reset_complete(struct rtl8125_private *tp)
{
        int i;

        for (i = 0; i < tp->HwSuppNumTxQueues; i++) {
                struct rtl8125_ring *ring = &tp->lib_tx_ring[i];

                if (!ring->allocated)
                        continue;

                if (ring->event.enabled)
                        rtl8125_enable_event(ring);

                rtl8125_init_tx_ring(ring);
        }

        for (i = 0; i < tp->HwSuppNumRxQueues; i++) {
                struct rtl8125_ring *ring = &tp->lib_rx_ring[i];

                if (!ring->allocated)
                        continue;

                if (ring->event.enabled)
                        rtl8125_enable_event(ring);

                rtl8125_init_rx_ring(ring);
        }

        atomic_notifier_call_chain(&tp->lib_nh,
                                   RTL8125_NOTIFY_RESET_COMPLETE, NULL);
}
EXPORT_SYMBOL(rtl8125_lib_reset_complete);
