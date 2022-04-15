#
#
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=firmware-nonfree
PKG_SOURCE_DATE:=2022-04-11
PKG_SOURCE_VERSION:=fdaf74c780ca7a29b12d62e5b0d37c38c2321e20
PKG_MIRROR_HASH:=ad249767689f83e5b04559c65e5f6043b96a0ae470beee3c20f7ca25918fcc4a
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
		$(PKG_BUILD_DIR)/debian/config/brcm80211/brcm/brcmfmac43456-sdio.bin \
		$(1)/lib/firmware/brcm/brcmfmac43456-sdio.bin
	$(INSTALL_DATA) \
		$(PKG_BUILD_DIR)/debian/config/brcm80211/brcm/brcmfmac43456-sdio.clm_blob \
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
		$(PKG_BUILD_DIR)/debian/config/brcm80211/brcm/brcmfmac43456-sdio.txt \
		$(1)/lib/firmware/brcm/brcmfmac43456-sdio.radxa,rockpi4b.txt
endef

$(eval $(call BuildPackage,brcmfmac-firmware-43456-sdio-rockpi-4))

# brcmfmac-firmware-43456-sdio-rpi-400
define Package/brcmfmac-firmware-43456-sdio-rpi-400
  $(Package/firmware-nonfree-default)
  TITLE:=BCM43456 NVRAM for rpi 400
endef

define Package/brcmfmac-firmware-43456-sdio-rpi-400/install
	$(INSTALL_DIR) $(1)/lib/firmware/brcm
	$(INSTALL_DATA) \
		$(PKG_BUILD_DIR)/debian/config/brcm80211/brcm/brcmfmac43456-sdio.txt \
		$(1)/lib/firmware/brcm/brcmfmac43456-sdio.raspberrypi,400.txt
endef

$(eval $(call BuildPackage,brcmfmac-firmware-43456-sdio-rpi-400))
