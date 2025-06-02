# SPDX-License-Identifier: GPL-2.0-only

include $(TOPDIR)/rules.mk

BOARD:=rockchip
BOARDNAME:=Rockchip
FEATURES:=ext4 audio usb usbgadget display gpio fpu pci pcie rootfs-part boot-part squashfs
SUBTARGETS:=armv8

KERNEL_PATCHVER:=6.16

define Target/Description
	Build firmware image for Rockchip SoC devices.
endef

include $(INCLUDE_DIR)/target.mk

DEFAULT_PACKAGES += uboot-envtools partx-utils e2fsprogs mkf2fs kmod-gpio-button-hotplug -hostapd-common -wpad-basic-mbedtls -kmod-brcmfmac -brcmfmac-sdio-firmware-43430-bt - brcmfmac-firmware-ap6255-hugsun-x99 -brcmfmac-nvram-4356-sdio -cypress-firmware-4356-sdio -brcmfmac-firmware-4356-nanopi-m4 -kmod-rtw88-8822ce -rtl8822ce-firmware -kmod-ata-ahci-dwc -kmod-hwmon-pwmfan -kmod-rtw88-8723du -kmod-rtw88-8723ds block-mount blockd luci luci-app-ttyd

KERNELNAME:=Image dtbs

$(eval $(call BuildTarget))
