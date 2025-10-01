Package/realtek-bluetooth-firmware = $(call Package/firmware-default,RealTek bluetooth firmware)
define Package/realtek-bluetooth-firmware/install
	$(INSTALL_DIR) $(1)/lib/firmware/rtl_bt
	$(CP) \
		$(PKG_BUILD_DIR)/rtl_bt/* \
		$(1)/lib/firmware/rtl_bt
endef
$(eval $(call BuildPackage,realtek-bluetooth-firmware))
