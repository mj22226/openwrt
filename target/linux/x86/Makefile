# SPDX-License-Identifier: GPL-2.0-only
#
# Copyright (C) 2006-2011 OpenWrt.org

include $(TOPDIR)/rules.mk

ARCH:=i386
BOARD:=x86
BOARDNAME:=x86
FEATURES:=squashfs ext4 vdi vmdk vhdx pcmcia targz fpu boot-part rootfs-part
SUBTARGETS:=generic legacy geode 64

KERNEL_PATCHVER:=6.18

KERNELNAME:=bzImage

include $(INCLUDE_DIR)/target.mk

DEFAULT_PACKAGES += \
	partx-utils mkf2fs \
	e2fsprogs kmod-button-hotplug \
	grub2-bios-setup block-mount blockd luci luci-app-ttyd fdisk losetup resize2fs bash btop cfdisk collectd-mod-conntrack collectd-mod-cpu collectd-mod-cpufreq collectd-mod-irq collectd-mod-sensors collectd-mod-thermal curl f2fs-tools f2fsck hdparm hfsfsck htop kmod-ata-ahci-dwc kmod-fs-ext4 kmod-fs-f2fs luci-app-diskman luci-app-adblock-fast relayd swap-util kmod-nvme gawk grep sed coreutils-sort luci-app-statistics openssl-util usbutils kmod-usb-storage-extras kmod-usb-storage-uas wget luci-app-filemanager kmod-rtw88-8812au kmod-rtw88-8814au kmod-rtw88-8821au kmod-rtw88-8821cu kmod-rtw88-8822bu kmod-rtw88-8822cu kmod-rtw89-8852ae kmod-rtw88-8822ce usb-modeswitch nano kmod-usb-net-rndis luci-app-pbr luci-app-openvpn openvpn-openssl openvpn-easy-rsa luci-app-ksmbd luci-proto-wireguard ca-bundle ca-certificates  containerd docker docker-compose dockerd kmod-ppp kmod-pppoe kmod-usb-storage-uas kmod-veth kmod-vxlan luci-app-dockerman luci-proto-ppp netifd usign vsftpd luci-app-commands luci-app-nextdns luci-app-nlbwmon luci-app-smartdns luci-app-sqm luci-proto-relay luci-app-irqbalance wget-ssl arp-scan arp-scan-database iperf3-ssl ipset adb lscpu mmc-utils pciutils luci-app-upnp wpad-basic-mbedtls kmod-usb-net-rtl8152 kmod-r8169 kmod-bluetooth bluez-libs bluez-utils kmod-usb-core kmod-usb-uhci kmod-usb2 kmod-hci-uart kmod-btusb realtek-bluetooth-firmware kmod-usb-net-asix-ax88179 kmod-mt76x2u kmod-mt7921u kmod-mt7921e kmod-mt7922-firmware

$(eval $(call BuildTarget))

$(eval $(call $(if $(CONFIG_ISO_IMAGES),SetupHostCommand,Ignore),mkisofs, \
	Please install mkisofs. , \
	mkisofs -v 2>&1 , \
	genisoimage -v 2>&1 | grep genisoimage, \
	xorrisofs -v 2>&1 | grep xorriso \
))
