Package/brcmfmac-firmware-4339-sdio = $(call Package/firmware-default,Broadcom 4339 FullMAC SDIO firmware,,LICENCE.cypressb)
define Package/brcmfmac-firmware-4339-sdio/install
	$(INSTALL_DIR) $(1)/lib/firmware/cypress
	$(INSTALL_DATA) \
		$(PKG_BUILD_DIR)/cypress/cyfmac4339-sdio.bin \
		$(1)/lib/firmware/cypress/
	$(INSTALL_DIR) $(1)/lib/firmware/brcm
	$(LN) \
		../cypress/cyfmac4339-sdio.bin \
		$(1)/lib/firmware/brcm/brcmfmac4339-sdio.bin
endef
$(eval $(call BuildPackage,brcmfmac-firmware-4339-sdio))

Package/brcmfmac-firmware-43602a1-pcie = $(call Package/firmware-default,Broadcom 43602a1 FullMAC PCIe firmware,,LICENCE.broadcom_bcm43xx)
define Package/brcmfmac-firmware-43602a1-pcie/install
	$(INSTALL_DIR) $(1)/lib/firmware/brcm
	$(INSTALL_DATA) \
		$(PKG_BUILD_DIR)/brcm/brcmfmac43602-pcie.ap.bin \
		$(1)/lib/firmware/brcm/brcmfmac43602-pcie.bin
endef
$(eval $(call BuildPackage,brcmfmac-firmware-43602a1-pcie))

Package/brcmfmac-firmware-4366b1-pcie = $(call Package/firmware-default,Broadcom 4366b1 FullMAC PCIe firmware,,LICENCE.broadcom_bcm43xx)
define Package/brcmfmac-firmware-4366b1-pcie/install
	$(INSTALL_DIR) $(1)/lib/firmware/brcm
	$(INSTALL_DATA) \
		$(PKG_BUILD_DIR)/brcm/brcmfmac4366b-pcie.bin \
		$(1)/lib/firmware/brcm/
endef
$(eval $(call BuildPackage,brcmfmac-firmware-4366b1-pcie))

Package/brcmfmac-firmware-4366c0-pcie = $(call Package/firmware-default,Broadcom 4366c0 FullMAC PCIe firmware,,LICENCE.broadcom_bcm43xx)
define Package/brcmfmac-firmware-4366c0-pcie/install
	$(INSTALL_DIR) $(1)/lib/firmware/brcm
	$(INSTALL_DATA) \
		$(PKG_BUILD_DIR)/brcm/brcmfmac4366c-pcie.bin \
		$(1)/lib/firmware/brcm/
endef
$(eval $(call BuildPackage,brcmfmac-firmware-4366c0-pcie))

Package/brcmfmac-firmware-4329-sdio = $(call Package/firmware-default,Broadcom BCM4329 FullMac SDIO firmware,,LICENCE.broadcom_bcm43xx)
define Package/brcmfmac-firmware-4329-sdio/install
	$(INSTALL_DIR) $(1)/lib/firmware/brcm
	$(INSTALL_DATA) \
		$(PKG_BUILD_DIR)/brcm/brcmfmac4329-sdio.bin \
		$(1)/lib/firmware/brcm/brcmfmac4329-sdio.bin
endef
$(eval $(call BuildPackage,brcmfmac-firmware-4329-sdio))

Package/brcmfmac-nvram-43430-sdio = $(call Package/firmware-default,Broadcom BCM43430 SDIO NVRAM,,LICENCE.broadcom_bcm43xx)
define Package/brcmfmac-nvram-43430-sdio/install
	$(INSTALL_DIR) $(1)/lib/firmware/brcm
	$(INSTALL_DATA) \
		$(PKG_BUILD_DIR)/brcm/brcmfmac43430-sdio.AP6212.txt \
		$(1)/lib/firmware/brcm/
	$(LN) \
		brcmfmac43430-sdio.AP6212.txt \
		$(1)/lib/firmware/brcm/brcmfmac43430-sdio.sinovoip,bpi-m2-plus.txt
	$(LN) \
		brcmfmac43430-sdio.AP6212.txt \
		$(1)/lib/firmware/brcm/brcmfmac43430-sdio.sinovoip,bpi-m2-zero.txt
	$(LN) \
		brcmfmac43430-sdio.AP6212.txt \
		$(1)/lib/firmware/brcm/brcmfmac43430-sdio.sinovoip,bpi-m2-ultra.txt
	$(LN) \
		brcmfmac43430-sdio.AP6212.txt \
		$(1)/lib/firmware/brcm/brcmfmac43430-sdio.sinovoip,bpi-m3.txt
	$(LN) \
		brcmfmac43430-sdio.AP6212.txt \
		$(1)/lib/firmware/brcm/brcmfmac43430-sdio.friendlyarm,nanopi-r1.txt
	$(LN) \
		brcmfmac43430-sdio.AP6212.txt \
		$(1)/lib/firmware/brcm/brcmfmac43430-sdio.starfive,visionfive-v1.txt
	$(LN) \
		brcmfmac43430-sdio.AP6212.txt \
		$(1)/lib/firmware/brcm/brcmfmac43430-sdio.beagle,beaglev-starlight-jh7100-a1.txt
	$(LN) \
		brcmfmac43430-sdio.AP6212.txt \
		$(1)/lib/firmware/brcm/brcmfmac43430-sdio.beagle,beaglev-starlight-jh7100-r0.txt
	$(INSTALL_DATA) \
		$(PKG_BUILD_DIR)/brcm/brcmfmac43430-sdio.Hampoo-D2D3_Vi8A1.txt \
		$(1)/lib/firmware/brcm/
	$(INSTALL_DATA) \
		$(PKG_BUILD_DIR)/brcm/brcmfmac43430-sdio.MUR1DX.txt \
		$(1)/lib/firmware/brcm/
	$(INSTALL_DATA) \
		$(PKG_BUILD_DIR)/brcm/brcmfmac43430-sdio.raspberrypi,3-model-b.txt \
		$(1)/lib/firmware/brcm/
	$(LN) \
		brcmfmac43430-sdio.raspberrypi,3-model-b.txt \
		$(1)/lib/firmware/brcm/brcmfmac43430-sdio.raspberrypi,model-zero-w.txt
	$(LN) \
		brcmfmac43430-sdio.raspberrypi,3-model-b.txt \
		$(1)/lib/firmware/brcm/brcmfmac43430-sdio.raspberrypi,model-zero-2-w.txt
endef
$(eval $(call BuildPackage,brcmfmac-nvram-43430-sdio))

Package/brcmfmac-firmware-43430a0-sdio = $(call Package/firmware-default,Broadcom BCM43430a0 FullMac SDIO firmware,,LICENCE.broadcom_bcm43xx)
define Package/brcmfmac-firmware-43430a0-sdio/install
	$(INSTALL_DIR) $(1)/lib/firmware/brcm
	$(INSTALL_DATA) \
		$(PKG_BUILD_DIR)/brcm/brcmfmac43430a0-sdio.bin \
		$(1)/lib/firmware/brcm/brcmfmac43430a0-sdio.bin
endef
$(eval $(call BuildPackage,brcmfmac-firmware-43430a0-sdio))

Package/brcmfmac-nvram-43455-sdio = $(call Package/firmware-default,Broadcom BCM43455 SDIO NVRAM,,LICENCE.broadcom_bcm43xx)
define Package/brcmfmac-nvram-43455-sdio/install
	$(INSTALL_DIR) $(1)/lib/firmware/brcm
	$(INSTALL_DATA) \
		$(PKG_BUILD_DIR)/brcm/brcmfmac43455-sdio.acepc-t8.txt \
		$(1)/lib/firmware/brcm/
	$(INSTALL_DATA) \
		$(PKG_BUILD_DIR)/brcm/brcmfmac43455-sdio.raspberrypi,3-model-b-plus.txt \
		$(1)/lib/firmware/brcm/
	$(LN) \
		brcmfmac43455-sdio.raspberrypi,3-model-b-plus.txt \
		$(1)/lib/firmware/brcm/brcmfmac43455-sdio.raspberrypi,3-model-a-plus.txt
	$(INSTALL_DATA) \
		$(PKG_BUILD_DIR)/brcm/brcmfmac43455-sdio.raspberrypi,4-model-b.txt \
		$(1)/lib/firmware/brcm/
	$(LN) \
		brcmfmac43455-sdio.raspberrypi,4-model-b.txt \
		$(1)/lib/firmware/brcm/brcmfmac43455-sdio.raspberrypi,4-compute-module.txt
	$(LN) \
		brcmfmac43455-sdio.raspberrypi,4-model-b.txt \
		$(1)/lib/firmware/brcm/brcmfmac43455-sdio.Raspberry\ Pi\ Foundation-Raspberry\ Pi\ 4\ Model\ B.txt
	$(LN) \
		brcmfmac43455-sdio.raspberrypi,4-model-b.txt \
		$(1)/lib/firmware/brcm/brcmfmac43455-sdio.raspberrypi,5-model-b.txt
	$(LN) \
		brcmfmac43455-sdio.raspberrypi,4-model-b.txt \
		$(1)/lib/firmware/brcm/brcmfmac43455-sdio.Raspberry\ Pi\ Foundation-Raspberry\ Pi\ Compute\ Module\ 4.txt
	$(LN) \
		brcmfmac43455-sdio.raspberrypi,4-model-b.txt \
		$(1)/lib/firmware/brcm/brcmfmac43455-sdio.Raspberry\ Pi\ Foundation-Raspberry\ Pi\ 5\ Model\ B.txt
	$(INSTALL_DATA) \
		$(PKG_BUILD_DIR)/brcm/brcmfmac43455-sdio.MINIX-NEO\ Z83-4.txt \
		$(1)/lib/firmware/brcm/
	$(INSTALL_DATA) \
		$(PKG_BUILD_DIR)/brcm/brcmfmac43455-sdio.AW-CM256SM.txt \
		$(1)/lib/firmware/brcm/
	$(LN) \
		brcmfmac43455-sdio.AW-CM256SM.txt \
		$(1)/lib/firmware/brcm/brcmfmac43455-sdio.beagle,am5729-beagleboneai.txt
	$(LN) \
		brcmfmac43455-sdio.AW-CM256SM.txt \
		$(1)/lib/firmware/brcm/brcmfmac43455-sdio.pine64,pinebook-pro.txt
	$(LN) \
		brcmfmac43455-sdio.AW-CM256SM.txt \
		$(1)/lib/firmware/brcm/brcmfmac43455-sdio.pine64,pinephone-pro.txt
	$(LN) \
		brcmfmac43455-sdio.AW-CM256SM.txt \
		$(1)/lib/firmware/brcm/brcmfmac43455-sdio.pine64,quartz64-b.txt
endef
$(eval $(call BuildPackage,brcmfmac-nvram-43455-sdio))

Package/brcmfmac-nvram-4356-sdio = $(call Package/firmware-default,Broadcom BCM4356 SDIO NVRAM,,LICENCE.broadcom_bcm43xx)
define Package/brcmfmac-nvram-4356-sdio/install
	$(INSTALL_DIR) $(1)/lib/firmware/brcm
	$(INSTALL_DATA) \
		$(PKG_BUILD_DIR)/brcm/brcmfmac4356-sdio.AP6356S.txt \
		$(1)/lib/firmware/brcm/
	$(LN) \
		brcmfmac4356-sdio.AP6356S.txt \
		$(1)/lib/firmware/brcm/brcmfmac4356-sdio.friendlyarm,nanopc-t4.txt
endef
$(eval $(call BuildPackage,brcmfmac-nvram-4356-sdio))

Package/brcmfmac-firmware-usb = $(call Package/firmware-default,Broadcom BCM43xx fullmac USB firmware,,LICENCE.broadcom_bcm43xx)
define Package/brcmfmac-firmware-usb/install
	$(INSTALL_DIR) $(1)/lib/firmware/brcm
	$(INSTALL_DATA) \
		$(PKG_BUILD_DIR)/brcm/brcmfmac43236b.bin \
		$(1)/lib/firmware/brcm/
	$(INSTALL_DATA) \
		$(PKG_BUILD_DIR)/brcm/brcmfmac43143.bin \
		$(1)/lib/firmware/brcm/
endef
$(eval $(call BuildPackage,brcmfmac-firmware-usb))

Package/brcmsmac-firmware = $(call Package/firmware-default,Broadcom BCM43xx softmac PCIe firmware,,LICENCE.broadcom_bcm43xx)
define Package/brcmsmac-firmware/install
	$(INSTALL_DIR) $(1)/lib/firmware/brcm
	$(INSTALL_DATA) \
		$(PKG_BUILD_DIR)/$(PKG_LINUX_FIRMWARE_SUBDIR)/brcm/bcm43xx-0.fw \
		$(PKG_BUILD_DIR)/$(PKG_LINUX_FIRMWARE_SUBDIR)/brcm/bcm43xx_hdr-0.fw \
		$(1)/lib/firmware/brcm/
endef
$(eval $(call BuildPackage,brcmsmac-firmware))

Package/bnx2-firmware = $(call Package/firmware-default,Broadcom BCM5706/5708/5709/5716 firmware)
define Package/bnx2-firmware/install
	$(INSTALL_DIR) $(1)/lib/firmware/bnx2
	$(INSTALL_DATA) \
		$(PKG_BUILD_DIR)/bnx2/* \
		$(1)/lib/firmware/bnx2/
endef
$(eval $(call BuildPackage,bnx2-firmware))

Package/bnx2x-firmware = $(call Package/firmware-default,=QLogic 5771x/578xx firmware)
define Package/bnx2x-firmware/install
	$(INSTALL_DIR) $(1)/lib/firmware/bnx2x
	$(INSTALL_DATA) \
		$(PKG_BUILD_DIR)/bnx2x/* \
		$(1)/lib/firmware/bnx2x/
endef
$(eval $(call BuildPackage,bnx2x-firmware))

BRCMFMAC_43456_URL:=https://raw.githubusercontent.com/RPi-Distro/firmware-nonfree/bookworm/debian/config/brcm80211/brcm/

define Download/brcmfmac43456-sdio.bin
  FILE:=brcmfmac43456-sdio.bin
  URL:=$(BRCMFMAC_43456_URL)
  HASH:=ddf83f2100885b166be52d21c8966db164fdd4e1d816aca2acc67ee9cc28d726
endef

define Download/brcmfmac43456-sdio.clm_blob
  FILE:=brcmfmac43456-sdio.clm_blob
  URL:=$(BRCMFMAC_43456_URL)
  HASH:=2dbd7d22fc9af0eb560ceab45b19646d211bc7b34a1dd00c6bfac5dd6ba25e8a
endef

define Download/brcmfmac43456-sdio.txt
  FILE:=brcmfmac43456-sdio.txt
  URL:=$(BRCMFMAC_43456_URL)
  HASH:=44e0bb322dc1f39a4b0a89f30ffdd28bc93f7d7aaf534d06d229fe56f6198194
endef

$(eval $(call Download,brcmfmac43456-sdio.bin))
$(eval $(call Download,brcmfmac43456-sdio.clm_blob))
$(eval $(call Download,brcmfmac43456-sdio.txt))

Package/brcmfmac-firmware-43456-rockpi-4 = $(call Package/firmware-default,Broadcom Rock Pi 4 firmware)
define Package/brcmfmac-firmware-43456-rockpi-4/install
	$(INSTALL_DIR) $(1)/lib/firmware/brcm
	$(INSTALL_DATA) \
		$(DL_DIR)/brcmfmac43456-sdio.bin \
		$(1)/lib/firmware/brcm/brcmfmac43456-sdio.radxa,rockpi4a.bin
	$(INSTALL_DATA) \
		$(DL_DIR)/brcmfmac43456-sdio.clm_blob \
		$(1)/lib/firmware/brcm/brcmfmac43456-sdio.radxa,rockpi4a.clm_blob
	$(INSTALL_DATA) \
		$(DL_DIR)/brcmfmac43456-sdio.txt \
		$(1)/lib/firmware/brcm/brcmfmac43456-sdio.radxa,rockpi4a.txt
endef
$(eval $(call BuildPackage,brcmfmac-firmware-43456-rockpi-4))

## Broadcom NanoPi M4 firmware

BRCMFMAC_4356_URL:=https://raw.githubusercontent.com/armbian/firmware/master/brcm/

define Download/brcmfmac4356-sdio.bin
  FILE:=brcmfmac4356-sdio.bin
  URL:=$(BRCMFMAC_4356_URL)
  HASH:=cc689fc1b39bd3d1655eff9fcfac60a3bf73fb6a45e77fdbab1e762aeeecf34e
endef

define Download/brcmfmac4356-sdio.clm_blob
  FILE:=brcmfmac4356-sdio.clm_blob
  URL:=$(BRCMFMAC_4356_URL)
  HASH:=e048470d674de8865c30521138af248e5f96a9878ac73b707d834698cbf9a08a
endef

define Download/brcmfmac4356-sdio.txt
  FILE:=brcmfmac4356-sdio.txt
  URL:=$(BRCMFMAC_4356_URL)
  HASH:=81efd86f47fac54596d3c614872b2997ed0079303136e4c675a8eaa1a39db120
endef

$(eval $(call Download,brcmfmac4356-sdio.bin))
$(eval $(call Download,brcmfmac4356-sdio.clm_blob))
$(eval $(call Download,brcmfmac4356-sdio.txt))

Package/brcmfmac-firmware-4356-nanopi-m4 = $(call Package/firmware-default,Broadcom NanoPi M4 firmware)
define Package/brcmfmac-firmware-4356-nanopi-m4/install
	$(INSTALL_DIR) $(1)/lib/firmware/brcm
	$(INSTALL_DATA) \
		$(DL_DIR)/brcmfmac4356-sdio.bin \
		$(1)/lib/firmware/brcm/brcmfmac4356-sdio.friendlyarm,nanopi-m4.bin
	$(INSTALL_DATA) \
		$(DL_DIR)/brcmfmac4356-sdio.clm_blob \
		$(1)/lib/firmware/brcm/brcmfmac4356-sdio.friendlyarm,nanopi-m4.clm_blob
	$(INSTALL_DATA) \
		$(DL_DIR)/brcmfmac4356-sdio.txt \
		$(1)/lib/firmware/brcm/brcmfmac4356-sdio.friendlyarm,nanopi-m4.txt
endef
$(eval $(call BuildPackage,brcmfmac-firmware-4356-nanopi-m4))

## Broadcom AP6255 firmware

AP_6255_URL:=https://raw.githubusercontent.com/RPi-Distro/firmware-nonfree/bookworm/debian/config/brcm80211/cypress/

define Download/cyfmac43455-sdio-minimal.bin
  FILE:=cyfmac43455-sdio-minimal.bin
  URL:=$(AP_6255_URL)
  HASH:=3075cb0bdc4b28ed4f08e01b1a216d0ebc70f4022d9d3272a4a43b3c90456e60
endef

define Download/cyfmac43455-sdio-standard.bin
  FILE:=cyfmac43455-sdio-standard.bin
  URL:=$(AP_6255_URL)
  HASH:=d608f866582519c0a28d86db43040f4f1b98dd1d153e72e9752586546b4a36c3
endef

define Download/cyfmac43455-sdio.clm_blob
  FILE:=cyfmac43455-sdio.clm_blob
  URL:=$(AP_6255_URL)
  HASH:=9823842cae9fb9a5dd1e5fb31f595516ec7deee341354bef30bb3026eee29cc1
endef

$(eval $(call Download,cyfmac43455-sdio-minimal.bin))
$(eval $(call Download,cyfmac43455-sdio-standard.bin))
$(eval $(call Download,cyfmac43455-sdio.clm_blob))

Package/brcmfmac-firmware-ap6255-hugsun-x99 = $(call Package/firmware-default,Broadcom hugsun x99 firmware)
define Package/brcmfmac-firmware-ap6255-hugsun-x99/install
	$(INSTALL_DIR) $(1)/lib/firmware/brcm
	$(INSTALL_DATA) \
		$(DL_DIR)/cyfmac43455-sdio-minimal.bin \
		$(1)/lib/firmware/brcm/brcmfmac43455-sdio.hugsun,x99.bin
	$(INSTALL_DATA) \
		$(DL_DIR)/cyfmac43455-sdio.clm_blob \
		$(1)/lib/firmware/brcm/brcmfmac43455-sdio.hugsun,x99.clm_blob
	$(INSTALL_DATA) \
		$(PKG_BUILD_DIR)/brcm/brcmfmac43455-sdio.acepc-t8.txt \
		$(1)/lib/firmware/brcm/brcmfmac43455-sdio.hugsun,x99.txt
endef
$(eval $(call BuildPackage,brcmfmac-firmware-ap6255-hugsun-x99))
