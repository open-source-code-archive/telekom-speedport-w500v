# File: modules/drivers/Makefile
#
# Makefile for the Broadcom Proprietary Linux kernel modules.
#

LN_NAME=bcm9$(BRCM_CHIP)
LN_DRIVER_DIRS =

-include $(KERNEL_DIR)/.config

ifneq ($(CONFIG_BCM_ATMAPI),)
  LN_DRIVER_DIRS +=ln -sn impl$(CONFIG_BCM_BLAA_IMPL) atm/$(LN_NAME);
  LN_DRIVER_DIRS +=ln -sn impl$(CONFIG_BCM_ATMAPI_IMPL) char/atmapi/$(LN_NAME);
  obj-$(CONFIG_BCM_ATMAPI) += atm/$(LN_NAME)/
  obj-$(CONFIG_BCM_ATMAPI) += char/atmapi/$(LN_NAME)/
endif

ifneq ($(CONFIG_BCM_ADSL),)
  LN_DRIVER_DIRS +=ln -sn impl$(CONFIG_BCM_ADSL_IMPL) char/adsl/$(LN_NAME);
  obj-$(CONFIG_BCM_ADSL) += char/adsl/$(LN_NAME)/
endif

ifneq ($(CONFIG_BCM_PROCFS),)
  LN_DRIVER_DIRS +=ln -sn impl$(CONFIG_BCM_PROCFS_IMPL) char/bcmprocfs/$(LN_NAME);
  obj-$(CONFIG_BCM_PROCFS) += char/bcmprocfs/$(LN_NAME)/
endif

ifneq ($(CONFIG_BCM_ENDPOINT),)
  LN_DRIVER_DIRS +=ln -sn impl$(CONFIG_BCM_ENDPOINT_IMPL) char/endpoint/$(LN_NAME);
  obj-$(CONFIG_BCM_ENDPOINT) += char/endpoint/$(LN_NAME)/
endif

ifneq ($(CONFIG_BCM_SECURITY),)
  LN_DRIVER_DIRS +=ln -sn impl$(CONFIG_BCM_SECURITY_IMPL) char/smdrv/$(LN_NAME);
  obj-$(CONFIG_BCM_SECURITY) += char/smdrv/$(LN_NAME)/
endif

ifneq ($(CONFIG_BCM_VDSL),)
  LN_DRIVER_DIRS +=ln -sn impl$(CONFIG_BCM_VDSL_IMPL) char/vdsl/$(LN_NAME);
  obj-$(CONFIG_BCM_VDSL) += char/vdsl/$(LN_NAME)/
endif

ifneq ($(CONFIG_BCM_ATMTEST),)
  LN_DRIVER_DIRS +=ln -sn impl$(CONFIG_BCM_ATMTEST_IMPL) char/test/atm/$(LN_NAME);
  obj-$(CONFIG_BCM_ATMTEST) += char/test/atm/$(LN_NAME)/
endif

ifneq ($(CONFIG_BCM_ENET),)
  LN_DRIVER_DIRS +=ln -sn impl$(CONFIG_BCM_ENET_IMPL) net/enet/$(LN_NAME);
  obj-$(CONFIG_BCM_ENET) += net/enet/$(LN_NAME)/
endif

ifneq ($(CONFIG_BCM_USB),)
  LN_DRIVER_DIRS +=ln -sn impl$(CONFIG_BCM_USB_IMPL) net/usb/$(LN_NAME);
  obj-$(CONFIG_BCM_USB) += net/usb/$(LN_NAME)/
endif

ifneq ($(CONFIG_BCM_WLAN),)
  LN_DRIVER_DIRS +=ln -sn impl$(CONFIG_BCM_WLAN_IMPL) net/wl/$(LN_NAME);
  obj-$(CONFIG_BCM_WLAN) += net/wl/$(LN_NAME)/
endif

ifneq ($(CONFIG_BCM_HPNA),)
  LN_DRIVER_DIRS +=ln -sn impl$(CONFIG_BCM_HPNA_IMPL) net/hpna/$(LN_NAME);
  obj-$(CONFIG_BCM_HPNA) += net/hpna/$(LN_NAME)/
endif

ifneq ($(CONFIG_BCM_NETDEVTEST),)
  LN_DRIVER_DIRS +=ln -sn impl$(CONFIG_BCM_NETDEVTEST_IMPL) net/test/$(LN_NAME);
  obj-$(CONFIG_BCM_NETDEVTEST) += net/test/$(LN_NAME)/
endif

symlinks:
	find . -lname "*" -name "$(LN_NAME)" -print -exec rm -f "{}" ";"
	$(CONFIG_SHELL) -c "$(LN_DRIVER_DIRS)"
