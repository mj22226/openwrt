#
# Copyright (C) 2021 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=uboot-friendlyarm
PKG_SOURCE_DATE:=2021-01-05
PKG_SOURCE_VERSION:=c5a1b04b8f35489fa3b0524996e65fd863cf9d79
PKG_MIRROR_HASH:=18efb819e9333f691dfea41317ca36b2f530b1e587084d73eee6288af5a7a83b
PKG_RELEASE:=1
PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/friendlyarm/uboot-rockchip.git

include $(INCLUDE_DIR)/u-boot.mk
include $(INCLUDE_DIR)/package.mk


define U-Boot/Default
  BUILD_TARGET:=rockchip
  UENV:=default
  HIDDEN:=1
endef

define U-Boot/nanopi-r4s-rk3399
  BUILD_SUBTARGET:=armv8
  NAME:=NanoPi R4S
  BUILD_DEVICES:= \
    friendlyarm_nanopi-r4s
  DEPENDS:=+PACKAGE_u-boot-nanopi-r4s-rk3399:arm-trusted-firmware-rockchip
  PKG_BUILD_DEPENDS:=arm-trusted-firmware-rockchip
  ATF:=rk3399_bl31.elf
endef

UBOOT_TARGETS :=nanopi-r4s-rk3399

UBOOT_CONFIGURE_VARS += USE_PRIVATE_LIBGCC=yes

UBOOT_MAKE_FLAGS += \
  BL31=$(STAGING_DIR_IMAGE)/$(ATF)

define Build/Configure
	$(call Build/Configure/U-Boot)

	$(SED) 's#CONFIG_MKIMAGE_DTC_PATH=.*#CONFIG_MKIMAGE_DTC_PATH="$(PKG_BUILD_DIR)/scripts/dtc/dtc"#g' $(PKG_BUILD_DIR)/.config
	echo 'CONFIG_IDENT_STRING=" OpenWrt"' >> $(PKG_BUILD_DIR)/.config
endef

define Build/InstallDev
	$(INSTALL_DIR) $(STAGING_DIR_IMAGE)
	$(CP) $(PKG_BUILD_DIR)/idbloader.img $(STAGING_DIR_IMAGE)/$(BUILD_VARIANT)-idbloader.img
	$(CP) $(PKG_BUILD_DIR)/u-boot.itb $(STAGING_DIR_IMAGE)/$(BUILD_VARIANT)-u-boot.itb
endef

define Package/u-boot/install/default
endef

$(eval $(call BuildPackage/U-Boot))
