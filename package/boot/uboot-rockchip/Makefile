#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_VERSION:=2024.01-rc2
PKG_RELEASE:=1

PKG_HASH:=7585328ee545bd0566a90965ef02c3a8d1c828f56a92548a03e88e7644dd76bd

PKG_MAINTAINER:=Tobias Maedel <openwrt@tbspace.de>

include $(INCLUDE_DIR)/u-boot.mk
include $(INCLUDE_DIR)/package.mk

define U-Boot/Default
  BUILD_TARGET:=rockchip
  UENV:=default
  HIDDEN:=1
endef


# RK3328 boards

define U-Boot/nanopi-r2s-rk3328
  BUILD_SUBTARGET:=armv8
  NAME:=NanoPi R2S
  BUILD_DEVICES:= \
    friendlyarm_nanopi-r2s
  DEPENDS:=+PACKAGE_u-boot-nanopi-r2s-rk3328:arm-trusted-firmware-rockchip
  PKG_BUILD_DEPENDS:=arm-trusted-firmware-rockchip
  ATF:=rk3328_bl31.elf
endef

define U-Boot/roc-cc-rk3328
  BUILD_SUBTARGET:=armv8
  NAME:=ROC-RK3328-CC
  BUILD_DEVICES:= \
    firefly_roc-rk3328-cc
  DEPENDS:=+PACKAGE_u-boot-roc-cc-rk3328:arm-trusted-firmware-rockchip
  PKG_BUILD_DEPENDS:=arm-trusted-firmware-rockchip
  ATF:=rk3328_bl31.elf
endef


# RK3399 boards


define U-Boot/rock-pi-4-rk3399
  BUILD_SUBTARGET:=armv8
  NAME:=Rock Pi 4
  BUILD_DEVICES:= \
    radxa_rock-pi-4
  DEPENDS:=+PACKAGE_u-boot-rock-pi-4-rk3399:arm-trusted-firmware-rockchip
  PKG_BUILD_DEPENDS:=arm-trusted-firmware-rockchip
  ATF:=rk3399_bl31.elf
endef

define U-Boot/rockpro64-rk3399
  BUILD_SUBTARGET:=armv8
  NAME:=RockPro64
  BUILD_DEVICES:= \
    pine64_rockpro64
  DEPENDS:=+PACKAGE_u-boot-rockpro64-rk3399:arm-trusted-firmware-rockchip
  PKG_BUILD_DEPENDS:=arm-trusted-firmware-rockchip
  ATF:=rk3399_bl31.elf
endef

# RK356x boards

define U-Boot/bpi-r2-pro-rk3568
  BUILD_SUBTARGET:=armv8
  NAME:=BPI-R2-PRO
  BUILD_DEVICES:= \
    rockchip_bpi-r2-pro
  DEPENDS:=+PACKAGE_u-boot-bpi-r2-pro-rk3568:arm-trusted-firmware-rockchip
  PKG_BUILD_DEPENDS:=arm-trusted-firmware-rockchip
  ATF:=rk3568_bl31.elf
  DDR_3568:=$(1)
endef

define U-Boot/quartz64-a-rk3566
  BUILD_SUBTARGET:=armv8
  NAME:=QUARTZ64
  BUILD_DEVICES:= \
    pine64_quartz64-a
  DEPENDS:=+PACKAGE_u-boot-quartz64-a-rk3566:arm-trusted-firmware-rockchip
  PKG_BUILD_DEPENDS:=arm-trusted-firmware-rockchip
  ATF:=rk3568_bl31.elf
  DDR_3568:=$(1)
endef

define U-Boot/nanopi-r5c-rk3568
  BUILD_SUBTARGET:=armv8
  NAME:=NANOPI-R5C
  BUILD_DEVICES:= \
    friendlyelec_nanopi-r5c
  DEPENDS:=+PACKAGE_u-boot-nanopi-r5c-rk3568:arm-trusted-firmware-rockchip
  PKG_BUILD_DEPENDS:=arm-trusted-firmware-rockchip
  ATF:=rk3568_bl31.elf
  DDR_3568:=$(1)
endef

define U-Boot/nanopi-r5s-rk3568
  BUILD_SUBTARGET:=armv8
  NAME:=NANOPI-R5S
  BUILD_DEVICES:= \
    friendlyelec_nanopi-r5s
  DEPENDS:=+PACKAGE_u-boot-nanopi-r5s-rk3568:arm-trusted-firmware-rockchip
  PKG_BUILD_DEPENDS:=arm-trusted-firmware-rockchip
  ATF:=rk3568_bl31.elf
  DDR_3568:=$(1)
endef

define U-Boot/rock-3a-rk3568
  BUILD_SUBTARGET:=armv8
  NAME:=ROCK-3A
  BUILD_DEVICES:= \
    radxa_rock-3a
  DEPENDS:=+PACKAGE_u-boot-rock-3a-rk3568:arm-trusted-firmware-rockchip
  PKG_BUILD_DEPENDS:=arm-trusted-firmware-rockchip
  ATF:=rk3568_bl31.elf
  DDR_3568:=$(1)
endef

# RK3588 boards

define U-Boot/nanopi-r6c-rk3588
  BUILD_SUBTARGET:=armv8
  NAME:=NANOPI-R6C
  BUILD_DEVICES:= \
    friendlyelec_nanopi-r6c
  DEPENDS:=+PACKAGE_u-boot-nanopi-r6c-rk3588:arm-trusted-firmware-rockchip
  PKG_BUILD_DEPENDS:=arm-trusted-firmware-rockchip
  ATF:=rk3588_bl31.elf
  DDR_3588:=$(1)

endef

define U-Boot/nanopi-r6s-rk3588
  BUILD_SUBTARGET:=armv8
  NAME:=NANOPI-R6C
  BUILD_DEVICES:= \
    friendlyelec_nanopi-r6s
  DEPENDS:=+PACKAGE_u-boot-nanopi-r6c-rk3588:arm-trusted-firmware-rockchip
  PKG_BUILD_DEPENDS:=arm-trusted-firmware-rockchip
  DEVICE_DTS := rk3588-nanopi-r6c.dts
  UBOOT_CONFIG:= nanopi-r6c-rk3588
  ATF:=rk3588_bl31.elf
  DDR_3588:=$(1)

endef

define U-Boot/orangepi-5-plus-rk3588
  BUILD_SUBTARGET:=armv8
  NAME:=ORANGEPI-5-PLUS
  BUILD_DEVICES:= \
    xunlong_orangepi-5-plus
  DEPENDS:=+PACKAGE_u-boot-orangepi-5-plus-rk3588:arm-trusted-firmware-rockchip
  PKG_BUILD_DEPENDS:=arm-trusted-firmware-rockchip
  ATF:=rk3588_bl31.elf
  DDR_3588:=$(1)
endef

define U-Boot/rock-5b-rk3588
  BUILD_SUBTARGET:=armv8
  NAME:=ROCK-5B
  BUILD_DEVICES:= \
    radxa_rock-5b
  DEPENDS:=+PACKAGE_u-boot-rock-5b-rk3588:arm-trusted-firmware-rockchip
  PKG_BUILD_DEPENDS:=arm-trusted-firmware-rockchip
  UBOOT_CONFIG:= rock5b-rk3588
  ATF:=rk3588_bl31.elf
  DDR_3588:=$(1)
  DEFAULT := n
endef

UBOOT_TARGETS := \
  nanopi-r6c-rk3588 \
  nanopi-r6s-rk3588 \
  orangepi-5-plus-rk3588 \
  rock-5b-rk3588 \
  bpi-r2-pro-rk3568 \
  nanopi-r5c-rk3568 \
  nanopi-r5s-rk3568 \
  quartz64-a-rk3566 \
  rock-3a-rk3568 \
  rock-pi-4-rk3399 \
  rockpro64-rk3399 \
  nanopi-r2s-rk3328 \
  roc-cc-rk3328

UBOOT_CONFIGURE_VARS += USE_PRIVATE_LIBGCC=yes

UBOOT_MAKE_FLAGS += \
  PATH=$(STAGING_DIR_HOST)/bin:$(PATH) \
  BL31=$(STAGING_DIR_IMAGE)/$(ATF)
export ROCKCHIP_TPL=./ddr.bin

define Build/Configure
	$(call Build/Configure/U-Boot)

ifneq ($(DDR_3568),)
	$(CP) $(STAGING_DIR_IMAGE)/rk3568_ddr.bin $(PKG_BUILD_DIR)/ddr.bin
endif

ifneq ($(DDR_3588),)
	$(CP) $(STAGING_DIR_IMAGE)/rk3588_ddr.bin $(PKG_BUILD_DIR)/ddr.bin
endif

	$(SED) 's#CONFIG_MKIMAGE_DTC_PATH=.*#CONFIG_MKIMAGE_DTC_PATH="$(PKG_BUILD_DIR)/scripts/dtc/dtc"#g' $(PKG_BUILD_DIR)/.config
	echo 'CONFIG_TOOLS_MKEFICAPSULE=n' >> $(PKG_BUILD_DIR)/.config
	echo 'CONFIG_OF_LIBFDT_OVERLAY=n' >> $(PKG_BUILD_DIR)/.config
endef

define Build/InstallDev
	$(INSTALL_DIR) $(STAGING_DIR_IMAGE)
	$(CP) $(PKG_BUILD_DIR)/idbloader.img $(STAGING_DIR_IMAGE)/$(BUILD_VARIANT)-idbloader.img
	$(CP) $(PKG_BUILD_DIR)/u-boot.itb $(STAGING_DIR_IMAGE)/$(BUILD_VARIANT)-u-boot.itb
endef

define Package/u-boot/install/default
endef

$(eval $(call BuildPackage/U-Boot))
