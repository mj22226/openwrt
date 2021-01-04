#
# Copyright (C) 2012-2016 OpenWrt.org
# Copyright (C) 2016 LEDE-project.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

define Device/dsa-migration
  DEVICE_COMPAT_VERSION := 1.1
  DEVICE_COMPAT_MESSAGE := Config cannot be migrated from swconfig to DSA
endef

define Device/linksys
  $(Device/NAND-128K)
  DEVICE_VENDOR := Linksys
  DEVICE_PACKAGES += kmod-ata-ahci kmod-ata-core kmod-fs-ext4 kmod-scsi-core kmod-scsi-generic  kmod-mwlwifi wpad-basic-wolfssl
  IMAGES += factory.img
  IMAGE/factory.img := append-kernel | pad-to $$$$(KERNEL_SIZE) | \
	append-ubi | pad-to $$$$(PAGESIZE)
  KERNEL_SIZE := 6144k
endef

define Device/linksys_wrt1900ac-v1
  $(call Device/linksys)
  $(Device/dsa-migration)
  DEVICE_MODEL := WRT1900AC
  DEVICE_VARIANT := v1
  DEVICE_ALT0_VENDOR := Linksys
  DEVICE_ALT0_MODEL := Mamba
  DEVICE_DTS := armada-xp-linksys-mamba
  DEVICE_PACKAGES += mwlwifi-firmware-88w8864
  KERNEL_SIZE := 3072k
  SUPPORTED_DEVICES += armada-xp-linksys-mamba linksys,mamba
endef
TARGET_DEVICES += linksys_wrt1900ac-v1

define Device/linksys_wrt32x
  $(call Device/linksys)
  $(Device/dsa-migration)
  DEVICE_MODEL := WRT32X
  DEVICE_ALT0_VENDOR := Linksys
  DEVICE_ALT0_MODEL := Venom
  DEVICE_DTS := armada-385-linksys-venom
  DEVICE_PACKAGES += kmod-btmrvl kmod-mwifiex-sdio mwlwifi-firmware-88w8964
  KERNEL_SIZE := 3072k
  KERNEL := kernel-bin | append-dtb
  SUPPORTED_DEVICES += armada-385-linksys-venom linksys,venom
endef
TARGET_DEVICES += linksys_wrt32x
