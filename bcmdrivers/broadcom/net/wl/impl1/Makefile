obj-$(CONFIG_BCM_WLAN) += wl.o

wl-objs += wl_dep.o

ifeq "$(BRCM_CHIP)" "6348"
$(obj)/wl_dep.o: $(obj)/shared/bcm4306_map.o $(obj)/shared/bcm4318_map.o
else
$(obj)/wl_dep.o:
endif
	cp $(obj)/wl$(PROFILE).o_save $(obj)/wl_dep.o

ifeq "$(BRCM_CHIP)" "6348"
include $(BRCMDRIVERS_DIR)/broadcom/./net/wl/impl1/Makefile.srom
endif


