/*
################################################################################
#
# r8125 is the Linux device driver released for Realtek 2.5Gigabit Ethernet
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

#ifndef _LINUX_rtl8125_LIB_H
#define _LINUX_rtl8125_LIB_H

/*
IPA SW would like to pass its own memory allocators to
request_ring() to allocate/free the memory for the descriptor ring and buffers.

Private field is needed in allocator.
Private field will be used by IPA offload software, not to be touched by
Realtek driver.

Realtek driver can use the allocators similar to dma_alloc_coherent() and
dma_free_coherent(). Allocator should pass the mem ops as one of the parameters
for us to access our private data.
*/

#include <linux/device.h>
#include <linux/types.h>

struct rtl8125_mem_ops {
        void *(*alloc_descs)(struct device *dev, size_t size, dma_addr_t *daddr,
                             gfp_t gfp, struct rtl8125_mem_ops *ops);
        void *(*alloc_buf)(struct device *dev, size_t size, dma_addr_t *daddr,
                           gfp_t gfp, struct rtl8125_mem_ops *ops);

        void (*free_descs)(void *buf, struct device *dev, size_t size,
                           dma_addr_t daddr, struct rtl8125_mem_ops *ops);
        void (*free_buf)(void *buf, struct device *dev, size_t size,
                         dma_addr_t daddr, struct rtl8125_mem_ops *ops);

        void *private;
};

enum rtl8125_channel_dir {
        RTL8125_CH_DIR_RX,
        RTL8125_CH_DIR_TX,
};

enum rtl8125_ring_flags {
        RTL8125_CONTIG_BUFS = BIT(0), /* Alloc entire ring buffer memory as a contiguous block */
        RTL8125_NO_CLOSE = BIT(1), /* No Close Feature */
        /*...*/
};

/* Represents each buffer allocated */
struct rtl8125_buf {
        /* struct list_head bufs_list; */
        void *addr;
        dma_addr_t dma_addr;
        phys_addr_t phys_addr;
        size_t size;
};

enum rtl8125_event_flags {
        /* If any */
        MSIX_event_type = BIT(0),
};

struct rtl8125_event {
        /* MSI vector information as needed */
        dma_addr_t addr;
        u64 data;
        bool allocated;
        bool enabled;
        u32 message_id;

        /* Moderation parameters */
        int delay;
};

/* Represents ring allocated for IPA */
struct rtl8125_ring {
        bool enabled;
        bool allocated;
        enum rtl8125_channel_dir direction;

        u32 queue_num;
        unsigned long flags;

        unsigned ring_size;
        unsigned desc_size;
        unsigned buff_size;

        void *desc_addr; /* descriptor base virt addr */
        dma_addr_t desc_daddr; /* descriptor base dma addr */
        phys_addr_t desc_paddr; /* descriptor base phys addr */

        /* List or array of buffers allocated. If RTL8125_CONTIG_BUFS was
          requested, then only one entry need to be populated for the one
          contiguous buffer.
         */
        struct rtl8125_buf *bufs; /* OR struct list_head bufs; */

        struct rtl8125_mem_ops *mem_ops; /* store mem ops to use for freeing */

        /* Other driver fields */
        struct rtl8125_event event;

        void *private;
};

enum rtl8125_rss_flags {
        RTL8125_RSS_HASH_IPV4 = BIT(0),
        RTL8125_RSS_HASH_IPV6 = BIT(1),
        /*...*/
};

enum rtl8125_notify {
        RTL8125_NOTIFY_RESET_PREPARE,
        RTL8125_NOTIFY_RESET_COMPLETE,
};

/* Allocate an Rx or Tx ring */
struct rtl8125_ring *rtl8125_request_ring(struct net_device *ndev,
                unsigned int ring_size, unsigned int buff_size,
                enum rtl8125_channel_dir direction, unsigned int flags,
                struct rtl8125_mem_ops *mem_ops);

void rtl8125_release_ring(struct rtl8125_ring *ring);

/* Starts the ring */
int rtl8125_enable_ring(struct rtl8125_ring *ring);

void rtl8125_disable_ring(struct rtl8125_ring *ring);


/* Allocate an event (MSI-X, pointer wrb, etc.). Only one type of event will
be requested from a ring at any point of time.
*/
int rtl8125_request_event(struct rtl8125_ring *ring, unsigned long flags,
                          dma_addr_t addr, u64 data);

void rtl8125_release_event(struct rtl8125_ring *ring);

/* Enables the interrupt */
int rtl8125_enable_event(struct rtl8125_ring *ring);

int rtl8125_disable_event(struct rtl8125_ring *ring);


/* Sets interrupt moderation. Count, Timer, or both. If HW does not suport
ranges for moderation, one parameter for timer and count is sufficient.*/
int rtl8125_set_ring_intr_mod(struct rtl8125_ring *ring, int delay);

/* Redirect Rx RSS hash table to a given ring */
int rtl8125_rss_redirect(struct net_device *ndev,
                         unsigned long flags,
                         struct rtl8125_ring *ring);

/* Reset RSS hash table to driver default. IPA will call this only after Rx ring
 is disabled through disable_ring() API.
*/
int rtl8125_rss_reset(struct net_device *ndev);

/* Get net_device object from struct device. */
struct net_device *rtl8125_get_netdev(struct device *dev);

int rtl8125_receive_skb(struct net_device *net_dev, struct sk_buff *skb,
                        bool napi);

int rtl8125_register_notifier(struct net_device *net_dev,
                              struct notifier_block *nb);

int rtl8125_unregister_notifier(struct net_device *net_dev,
                                struct notifier_block *nb);

void rtl8125_lib_reset_prepare(struct rtl8125_private *tp);

void rtl8125_lib_reset_complete(struct rtl8125_private *tp);

#endif /* _LINUX_rtl8125_LIB_H */
