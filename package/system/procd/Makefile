#
# Copyright (C) 2014-2016 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=procd
PKG_RELEASE:=1

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL=$(PROJECT_GIT)/project/procd.git
PKG_MIRROR_HASH:=0dccbdbfea96106d1e394cb74a02fa4c7910e06e6d62212d704153bea8dc3024
PKG_SOURCE_DATE:=2025-06-19
PKG_SOURCE_VERSION:=cde025d5baf32e62b485ef9f8ba1e835ba8ece0e
CMAKE_INSTALL:=1

PKG_LICENSE:=GPL-2.0
PKG_LICENSE_FILES:=

PKG_MAINTAINER:=John Crispin <john@phrozen.org>

PKG_BUILD_FLAGS:=lto
PKG_ASLR_PIE_REGULAR:=1
PKG_CONFIG_DEPENDS:= \
	CONFIG_TARGET_INIT_PATH CONFIG_KERNEL_SECCOMP CONFIG_PROCD_SHOW_BOOT \
	CONFIG_KERNEL_NAMESPACES CONFIG_PACKAGE_procd-ujail CONFIG_PACKAGE_procd-seccomp

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

ifeq ($(DUMP),)
  STAMP_CONFIGURED:=$(strip $(STAMP_CONFIGURED))_$(shell echo $(CONFIG_TARGET_INIT_PATH) | $(MKHASH) md5)
endif

CMAKE_OPTIONS += -DEARLY_PATH="$(TARGET_INIT_PATH)"

define Package/procd/Default
  SECTION:=base
  CATEGORY:=Base system
  DEPENDS:=+ubusd +ubus +libjson-script +ubox +libubox +libudebug \
	  +libubus +libblobmsg-json +libjson-c +jshn
  TITLE:=OpenWrt system process manager
  USERID:=:dialout=20 :audio=29
endef

define Package/procd
  $(call Package/procd/Default)
  VARIANT:=default
  CONFLICTS:=procd-selinux
endef

define Package/procd-selinux
  $(call Package/procd/Default)
  DEPENDS += +libselinux
  TITLE += with SELinux support
  PROVIDES:=procd
  VARIANT:=selinux
endef

define Package/procd-ujail
  SECTION:=base
  CATEGORY:=Base system
  DEPENDS:=@KERNEL_NAMESPACES +@KERNEL_UTS_NS +@KERNEL_IPC_NS +@KERNEL_PID_NS \
	  +libubox +libubus +libuci +libblobmsg-json
  TITLE:=OpenWrt process jail helper
endef

define Package/procd-seccomp
  SECTION:=base
  CATEGORY:=Base system
  DEPENDS:=@USE_SECCOMP +libubox +libblobmsg-json
  TITLE:=OpenWrt process seccomp helper + utrace
endef

define Package/uxc
  SECTION:=base
  CATEGORY:=Base system
  DEPENDS:=+procd-ujail +libubus +libubox +libblobmsg-json +blockd +PACKAGE_uxc:rpcd
  TITLE:=OpenWrt container management
  MAINTAINER:=Daniel Golle <daniel@makrotopia.org>
endef

define Package/procd/config
menu "Configuration"
	depends on PACKAGE_procd || PACKAGE_procd-selinux

config PROCD_SHOW_BOOT
	bool
	default n
	prompt "Print the shutdown to the console as well as logging it to syslog"

endmenu
endef

ifeq ($(BUILD_VARIANT),selinux)
  CMAKE_OPTIONS += -DSELINUX=1
endif

ifeq ($(CONFIG_PROCD_SHOW_BOOT),y)
  CMAKE_OPTIONS += -DSHOW_BOOT_ON_CONSOLE=1
endif

ifdef CONFIG_PACKAGE_procd-ujail
  CMAKE_OPTIONS += -DJAIL_SUPPORT=1
endif

SECCOMP=$(if $(CONFIG_PACKAGE_procd-seccomp),1,0)
CMAKE_OPTIONS += -DSECCOMP_SUPPORT=$(SECCOMP) -DUTRACE_SUPPORT=$(SECCOMP)

define Package/procd/install
	$(INSTALL_DIR) $(1)/sbin $(1)/etc $(1)/lib/functions

	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/sbin/{init,procd,askfirst,udevtrigger,upgraded} $(1)/sbin/
	$(INSTALL_DATA) $(PKG_INSTALL_DIR)/usr/lib/libsetlbf.so $(1)/lib
	$(INSTALL_BIN) ./files/reload_config $(1)/sbin/
	$(INSTALL_CONF) ./files/hotplug*.json $(1)/etc/
	$(INSTALL_DATA) ./files/procd.sh $(1)/lib/functions/
	$(INSTALL_BIN) ./files/service $(1)/sbin/service
endef

Package/procd-selinux/install = $(Package/procd/install)

define Package/procd-ujail/install
	$(INSTALL_DIR) $(1)/sbin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/sbin/ujail $(1)/sbin/
endef

define Package/procd-seccomp/install
	$(INSTALL_DIR) $(1)/sbin $(1)/lib
	$(INSTALL_DATA) $(PKG_INSTALL_DIR)/usr/lib/libpreload-seccomp.so $(1)/lib
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/sbin/utrace $(1)/sbin/
	$(LN) utrace $(1)/sbin/seccomp-trace
	$(INSTALL_DATA) $(PKG_INSTALL_DIR)/usr/lib/libpreload-trace.so $(1)/lib
endef

define Package/uxc/conffiles
/etc/uxc
endef

define Package/uxc/install
	$(INSTALL_DIR) $(1)/sbin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/sbin/uxc $(1)/sbin/
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/uxc.init $(1)/etc/init.d/uxc
endef

$(eval $(call BuildPackage,procd))
$(eval $(call BuildPackage,procd-selinux))
$(eval $(call BuildPackage,procd-ujail))
$(eval $(call BuildPackage,procd-seccomp))
$(eval $(call BuildPackage,uxc))
