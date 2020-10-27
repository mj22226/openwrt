#
# Copyright (C) 2020 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=firmware-nonfree
PKG_SOURCE_DATE:=2020-10-16
PKG_SOURCE_VERSION:=5113681d6dcd46581a1882cbeb3d5cf1ddbf7676
PKG_MIRROR_HASH:=5f40e0b9d6a3cc4f6399e8beb603604b18c4515151a3f3da8356f2bb3f467563
PKG_RELEASE:=1
PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/RPi-Distro/firmware-nonfree.git

PKG_MAINTAINER:=

include $(INCLUDE_DIR)/package.mk

define Package/firmware-nonfree-default
  SECTION:=firmware
  CATEGORY:=Firmware
  URL:=https://github.com/RPi-Distro
endef

define Build/Compile
	true
endef

# brcmfmac-firmware-43456-sdio
define Package/brcmfmac-firmware-43456-sdio
  $(Package/firmware-nonfree-default)
  TITLE:=BCM43456 FullMac SDIO firmware
endef

define Package/brcmfmac-firmware-43456-sdio/install
	$(INSTALL_DIR) $(1)/lib/firmware/brcm
	$(INSTALL_DATA) \
		$(PKG_BUILD_DIR)/brcm/brcmfmac43456-sdio.bin \
		$(1)/lib/firmware/brcm/brcmfmac43456-sdio.bin
	$(INSTALL_DATA) \
		$(PKG_BUILD_DIR)/brcm/brcmfmac43456-sdio.clm_blob \
		$(1)/lib/firmware/brcm/brcmfmac43456-sdio.clm_blob
endef

$(eval $(call BuildPackage,brcmfmac-firmware-43456-sdio))

# brcmfmac-firmware-43456-sdio-rockpi-4
define Package/brcmfmac-firmware-43456-sdio-rockpi-4
  $(Package/firmware-nonfree-default)
  TITLE:=BCM43456 NVRAM for rockpi-4
endef

define Package/brcmfmac-firmware-43456-sdio-rockpi-4/install
	$(INSTALL_DIR) $(1)/lib/firmware/brcm
	$(INSTALL_DATA) \
		$(PKG_BUILD_DIR)/brcm/brcmfmac43456-sdio.txt \
		$(1)/lib/firmware/brcm/brcmfmac43456-sdio.radxa,rockpi4b.txt
endef

$(eval $(call BuildPackage,brcmfmac-firmware-43456-sdio-rockpi-4))
