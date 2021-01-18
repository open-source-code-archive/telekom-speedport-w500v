#****************************************************************************
#
#  Copyright (c) 2001, 2002, 2003, 2004  Broadcom Corporation
#  All Rights Reserved
#  No portions of this material may be reproduced in any form without the
#  written permission of:
#          Broadcom Corporation
#          16251 Laguna Canyon Road
#          Irvine, California 92618
#  All information contained in this document is Broadcom Corporation
#  company private, proprietary, and trade secret.
#
#****************************************************************************

# Top-level Makefile for all commengine xDSL platforms

# for TECOM standard version, comment it
# for specific customer, please remove the comment and assign the name
#
# note: platform name must be in lower-case
#       add specific version if necessary
#       copy html directory to html_xxxxxx for specific customer xxxxxx
#
export PLATFORM=t_online_fra

ifeq ($(strip $(PLATFORM)),t_online_fra)

# CUSTOMER is used in "CFM" directory
export CUSTOMER=T_ONLINE
# BRCM_VOICE_GLOBAL_CFLAGS is used in "xChange" directory
BRCM_VOICE_GLOBAL_CFLAGS=$(CUSTOMER)

endif

include version.make

# BRCM_RELEASETAG=$(BRCM_VERSION).$(BRCM_RELEASE)L.$(BRCM_EXTRAVERSION)
BRCM_RELEASETAG=$(BRCM_VERSION).$(BRCM_RELEASE).$(BRCM_EXTRAVERSION)


###########################################
#
# Define Basic Variables
#
###########################################
BUILD_DIR = $(shell pwd)
KERNEL_VER = 2.6
ifeq ($(strip $(KERNEL_VER)),2.6)
INC_KERNEL_BASE = $(BUILD_DIR)/kernel
ORIGINAL_KERNEL = linuxmips.tar.bz2
endif
KERNEL_DIR = $(INC_KERNEL_BASE)/linux
BRCMDRIVERS_DIR = $(BUILD_DIR)/bcmdrivers
USERAPPS_DIR = $(BUILD_DIR)/userapps
LINUXDIR = $(INC_KERNEL_BASE)/linux
HOSTTOOLS_DIR = $(BUILD_DIR)/hostTools
IMAGES_DIR = $(BUILD_DIR)/images
TARGETS_DIR = $(BUILD_DIR)/targets
DEFAULTCFG_DIR = $(TARGETS_DIR)/defaultcfg
XCHANGE_DIR = $(BUILD_DIR)/xChange
FSSRC_DIR = $(TARGETS_DIR)/fs.src
CFE_FILE = $(TARGETS_DIR)/cfe/cfe$(BRCM_CHIP).bin
CONFIG_SHELL := $(shell if [ -x "$$BASH" ]; then echo $$BASH; \
          else if [ -x /bin/bash ]; then echo /bin/bash; \
          else echo sh; fi ; fi)
GENDEFCONFIG_CMD = $(HOSTTOOLS_DIR)/scripts/gendefconfig
RUN_NOISE=1



###########################################
#
# Import Build Profiles
#
###########################################
BRCM_BOARD=bcm963xx
LAST_PROFILE=$(shell find targets -name vmlinux | sed -e "s?targets/??" -e "s?/.*??" -e "q")
ifeq ($(strip $(PROFILE)),)
PROFILE=$(LAST_PROFILE)
export PROFILE
endif
ifneq ($(strip $(PROFILE)),)
include $(TARGETS_DIR)/$(PROFILE)/$(PROFILE)
export BRCM_CHIP
export BRCM_FLASHPSI_SIZE
export BRCM_DRIVER_WIRELESS_PCMCIA_DATASWAP BRCM_DRIVER_WIRELESS_EBI_DMA
export BRCM_DRIVER_USB BRCM_DRIVER_ETHERNET_CONFIG
export BRCM_DEFAULTCFG
export BRCM_KERNEL_NF_FIREWALL BRCM_KERNEL_NF_MANGLE BRCM_KERNEL_NF_NAT
endif

###########################################
#
# Define Toolchain
#
###########################################
ifeq ($(strip $(BRCM_UCLIBC)),y)
NTC=1
ifeq ($(strip $(NTC)),1)
#TOOLCHAIN=/opt/toolchains/uclibc-crosstools
TOOLCHAIN=/opt/toolchains/uclibc-crosstools
CROSS_COMPILE = $(TOOLCHAIN)/bin/mips-linux-uclibc-
else
TOOLCHAIN=/opt/toolchains/uclibc
CROSS_COMPILE = $(TOOLCHAIN)/bin/mips-uclibc-
endif
else
TOOLCHAIN=/usr/crossdev/mips
CROSS_COMPILE = $(TOOLCHAIN)/bin/mips-linux-
endif

AR              = $(CROSS_COMPILE)ar
AS              = $(CROSS_COMPILE)as
LD              = $(CROSS_COMPILE)ld
CC              = $(CROSS_COMPILE)gcc
CXX             = $(CROSS_COMPILE)g++
CPP             = $(CROSS_COMPILE)cpp
NM              = $(CROSS_COMPILE)nm
STRIP           = $(CROSS_COMPILE)strip
SSTRIP          = $(CROSS_COMPILE)sstrip
OBJCOPY         = $(CROSS_COMPILE)objcopy
OBJDUMP         = $(CROSS_COMPILE)objdump
RANLIB          = $(CROSS_COMPILE)ranlib

LIB_PATH        = $(TOOLCHAIN)/mips-linux/lib
LIBDIR          = $(TOOLCHAIN)/mips-linux/lib
LIBCDIR         = $(TOOLCHAIN)/mips-linux

###########################################
#
# Application-specific settings
#
###########################################
INSTALL_DIR = $(TARGETS_DIR)/fs.src
TARGET_FS = $(TARGETS_DIR)/$(PROFILE)/fs
PROFILE_DIR = $(TARGETS_DIR)/$(PROFILE)
PROFILE_PATH = $(TARGETS_DIR)/$(PROFILE)/$(PROFILE)
VENDOR_NAME = bcm
FS_KERNEL_IMAGE_NAME = $(VENDOR_NAME)$(PROFILE)_fs_kernel
CFE_FS_KERNEL_IMAGE_NAME = $(VENDOR_NAME)$(PROFILE)_cfe_fs_kernel
FLASH_IMAGE_NAME = $(VENDOR_NAME)$(PROFILE)_flash_image_$(BRCM_BOARD_ID)
INC_BRCMDRIVER_PUB_PATH=$(BRCMDRIVERS_DIR)/opensource/include
INC_BRCMDRIVER_PRIV_PATH=$(BRCMDRIVERS_DIR)/broadcom/include
INC_BRCMBOARDPARMS_PATH=$(TARGETS_DIR)/boardparms
INC_ENDPOINT_PATH=$(BRCMDRIVERS_DIR)/broadcom/char/endpoint/bcm9$(BRCM_CHIP)/inc
#INC_ADSLDRV_PATH=$(BRCMDRIVERS_DIR)/broadcom/char/adsl/bcm9$(BRCM_CHIP)
INC_ADSLDRV_PATH=$(BRCMDRIVERS_DIR)/broadcom/char/adsl/impl1
BROADCOM_CFM_DIR=$(BROADCOM_DIR)/cfm
INC_BRCMCFM_PATH=$(BROADCOM_CFM_DIR)/inc


ifeq ($(strip $(BRCM_APP_PHONE)),sip)
export VOXXXLOAD=1
export VOIPLOAD=1
export SIPLOAD=1
BRCM_RELEASETAG := $(BRCM_RELEASETAG).sip
endif

ifeq ($(strip $(BRCM_APP_PHONE)),mgcp)
export VOXXXLOAD=1
export VOIPLOAD=1
export MGCPLOAD=1
BRCM_RELEASETAG := $(BRCM_RELEASETAG).mgcp
endif

ifneq ($(strip $(BUILD_VODSL)),)
export VOXXXLOAD=1
endif

BRCM_DSP_HAL := gw
BRCM_DSP_HAL_EXTENSION :=
XCHANGE_DSP_APP_EXTENSION :=
export XCHANGE_DSP_APP=$(BRCM_DSP_CODEC)

ifeq ($(strip $(BRCM_DSP_PCM)),y)
XCHANGE_DSP_APP := dspApp3341_tdm
BRCM_DSP_HAL_EXTENSION := _pcm
endif

ifeq ($(strip $(BRCM_DSP_HYBRID)),y)
XCHANGE_DSP_APP := dspApp3341_hybrid
BRCM_DSP_HAL_EXTENSION := _hybrid
endif

ifeq ($(strip $(BRCM_DSP_HYBRID_EXT)),y)
BRCM_DSP_HAL_EXTENSION := _hybrid
XCHANGE_DSP_APP := dspApp3341_hybrid
XCHANGE_DSP_APP_EXTENSION := _ext
endif

# APM application with FXO uses the hybrid HAL, as the FXO is provided by TDM port
ifeq ($(strip $(BRCM_DSP_APM_FXO)),y)
XCHANGE_DSP_APP := dspApp3341
BRCM_DSP_HAL_EXTENSION := _hybrid
XCHANGE_DSP_APP_EXTENSION := _fxo
endif

ifeq ($(strip $(BRCM_DSP_APM_FXO_EXT)),y)
XCHANGE_DSP_APP := dspApp3341
BRCM_DSP_HAL_EXTENSION := _hybrid
XCHANGE_DSP_APP_EXTENSION := _fxo_ext
endif

ifeq ($(strip $(BRCM_DSP_HYBRID_FXO)),y)
XCHANGE_DSP_APP := dspApp3341_hybrid
BRCM_DSP_HAL_EXTENSION := _hybrid
XCHANGE_DSP_APP_EXTENSION := _fxo
endif

ifeq ($(strip $(BRCM_DSP_HYBRID_FXO_EXT)),y)
XCHANGE_DSP_APP := dspApp3341_hybrid
BRCM_DSP_HAL_EXTENSION := _fxo
XCHANGE_DSP_APP_EXTENSION := _fxo_ext
endif

export BRCM_DSP_FXO
export XCHANGE_BUILD_APP=Bcm$(BRCM_CHIP)$(BRCM_DSP_HAL)$(BRCM_DSP_HAL_EXTENSION)
export XCHANGE_DSP_APP_EXTENSION
export BRCM_DSP_HAL_EXTENSION
BRCM_RELEASETAG := $(BRCM_RELEASETAG).$(XCHANGE_DSP_APP)

# If no codec is selected, build G.711 load.
# Any XCHANGE_BUILD_APP directory would be OK
# because G.711 is included with all the voice DSP images.
ifneq ($(strip $(BUILD_VODSL)),)
ifeq ($(strip $(XCHANGE_DSP_APP)),)
export XCHANGE_BUILD_APP=Bcm$(BRCM_CHIP)gw
export XCHANGE_DSP_APP=g711
BRCM_RELEASETAG := $(BRCM_RELEASETAG).g711
endif
endif
                                                                                
ifeq ($(strip $(XCHG_LE9502_SLIC)),y)
ifeq ($(strip $(BRCM_DSP_FXO)),y)
export XCHANGE_BUILD_APP=Bcm$(BRCM_CHIP)_Le9502FXO
BRCM_RELEASETAG := $(BRCM_RELEASETAG).LE9502
BRCM_DSP_HAL := LE9502_FXO
else
export XCHANGE_BUILD_APP=Bcm$(BRCM_CHIP)_Le9502
BRCM_RELEASETAG := $(BRCM_RELEASETAG).LE9502
BRCM_DSP_HAL := LE9502
endif
export XCHG_LE9502_SLIC
endif
                                                                                

ifeq ($(strip $(XCHG_LE9500_SLIC)),y)
ifeq ($(strip $(BRCM_DSP_FXO)),y)
export XCHANGE_BUILD_APP=Bcm$(BRCM_CHIP)_Le9500FXO
BRCM_RELEASETAG := $(BRCM_RELEASETAG).LE9500
BRCM_DSP_HAL := LE9500_FXO
endif
export XCHG_LE9500_SLIC
endif

                                                                                
#Set up ADSL standard
export ADSL=$(BRCM_ADSL_STANDARD)

#Set up ADSL_PHY_MODE  {file | obj}
export ADSL_PHY_MODE=file

#Set up ADSL_SELF_TEST
export ADSL_SELF_TEST=$(BRCM_ADSL_SELF_TEST)

###########################################
#
# Complete list of applications
#
###########################################
export OPENSOURCE_DIR=$(USERAPPS_DIR)/opensource
SUBDIRS_OPENSOURCE = $(OPENSOURCE_DIR)/atm2684/pvc2684ctl \
        $(OPENSOURCE_DIR)/bridge-utils \
        $(OPENSOURCE_DIR)/ppp/pppoe \
        $(OPENSOURCE_DIR)/udhcp \
        $(OPENSOURCE_DIR)/iptables \
        $(OPENSOURCE_DIR)/ebtables \
        $(OPENSOURCE_DIR)/reaim  \
        $(OPENSOURCE_DIR)/gdbserver  \
        $(OPENSOURCE_DIR)/siproxd \
        $(OPENSOURCE_DIR)/zebra  \
        $(OPENSOURCE_DIR)/net-snmp  \
        $(OPENSOURCE_DIR)/ftpd \
        $(OPENSOURCE_DIR)/libcreduction \
        $(OPENSOURCE_DIR)/busybox \
	$(OPENSOURCE_DIR)/openssl

#In future, we need to add soap when it
#is decoupled from cli

export BROADCOM_DIR=$(USERAPPS_DIR)/broadcom
SUBDIRS_BROADCOM = $(BROADCOM_DIR)/cfm \
        $(BROADCOM_DIR)/upnp/router/upnp \
        $(BROADCOM_DIR)/nas \
        $(BROADCOM_DIR)/wlctl \
        $(BROADCOM_DIR)/vodsl \
        $(BROADCOM_DIR)/atmctl \
        $(BROADCOM_DIR)/adslctl \
        $(BROADCOM_DIR)/netctl \
        $(BROADCOM_DIR)/dnsprobe \
        $(BROADCOM_DIR)/igmp \
        $(BROADCOM_DIR)/dhcpr \
	$(BROADCOM_DIR)/sntp \
	$(BROADCOM_DIR)/ippd \
	$(BROADCOM_DIR)/ddnsd \
	$(BROADCOM_DIR)/ethctl \
        $(BROADCOM_DIR)/hotplug \
        $(BROADCOM_DIR)/epittcp \
        $(BROADCOM_DIR)/urlfilter \
        $(BROADCOM_DIR)/fwscheduler \
        $(BROADCOM_DIR)/traffic_ctl \
 	$(BROADCOM_DIR)/pcscan \
	$(BROADCOM_DIR)/ntp \
        $(BROADCOM_DIR)/smdog \
        $(BROADCOM_DIR)/ledtest
                                                                                                               
SUBDIRS_APP = $(SUBDIRS_BROADCOM) $(SUBDIRS_OPENSOURCE)
SUBDIRS = $(foreach dir, $(SUBDIRS_APP), $(shell if [ -d "$(dir)" ]; then echo $(dir); fi))

OPENSOURCE_APPS = pvc2684ctl pvc2684d brctl pppd udhcp iptables ebtables \
                  reaim siproxd snmp zebra bftpd busybox gdbserver openssl

BROADCOM_APPS = cfm upnp nas wlctl vodsl atmctl adslctl netctl dnsprobe \
                igmp dhcpr diagapp sntp ddnsd ilmi ippd hotplug ethctl epittcp\
                fwscheduler urlfilter traffic_ctl pcscan ntp smdog ledtest

LIBC_OPTIMIZATION = libcreduction

BUSYBOX_DIR = $(OPENSOURCE_DIR)/busybox

BRCMAPPS = $(BROADCOM_APPS) $(OPENSOURCE_APPS) $(LIBC_OPTIMIZATION)

all: sanity_check profile_check kernelbuild modbuild app hosttools buildimage

menuconfig:
	@cd $(INC_KERNEL_BASE); \
	if [ ! -e linux/CREDITS ]; then \
	  echo Untarring original Linux kernel source...; \
	  (tar xkfj $(ORIGINAL_KERNEL) 2> /dev/null || true); \
	fi
	$(MAKE) -C $(KERNEL_DIR)/scripts/lxdialog HOSTCC=gcc
	$(CONFIG_SHELL) $(HOSTTOOLS_DIR)/scripts/Menuconfig $(TARGETS_DIR)/config.in

sanity_check:
	@if [ "$(PROFILE)" = "" ]; then \
          echo You need to specify build profile name from $(TARGETS_DIR) using 'make PROFILE=<profile name>...'; exit 1; \
	fi

profile_check:
	@if [ "$(LAST_PROFILE)" != "" ] && [ "$(LAST_PROFILE)" != "$(PROFILE)" ]; then \
		echo "The specified profile, $(PROFILE), differs from the last one built, $(LAST_PROFILE)."; \
		echo "The entire image must be rebuilt."; \
		read -p "Press ENTER to rebuild the entire image or CTRL-C to abort. " ; \
		$(MAKE) PROFILE=$(LAST_PROFILE) clean; \
		$(MAKE) PROFILE=$(PROFILE); \
		echo "Ignore the make exit error, Error 1"; \
		exit 1; \
	fi

$(KERNEL_DIR)/vmlinux:
	$(GENDEFCONFIG_CMD) $(PROFILE_PATH)
	cd $(KERNEL_DIR); \
	cp -f $(KERNEL_DIR)/arch/mips/defconfig $(KERNEL_DIR)/.config; \
	$(MAKE) oldconfig; $(MAKE); $(MAKE) modules_install

kernelbuild:
ifeq ($(wildcard $(KERNEL_DIR)/vmlinux),)
	@cd $(INC_KERNEL_BASE); \
	if [ ! -e linux/CREDITS ]; then \
	  echo Untarring original Linux kernel source...; \
	  (tar xkfj $(ORIGINAL_KERNEL) 2> /dev/null || true); \
	fi
	$(GENDEFCONFIG_CMD) $(PROFILE_PATH)
	cd $(KERNEL_DIR); \
	cp -f $(KERNEL_DIR)/arch/mips/defconfig $(KERNEL_DIR)/.config; \
	$(MAKE) oldconfig; $(MAKE)
else
	cd $(KERNEL_DIR); $(MAKE)
endif

kernel: profile_check kernelbuild hosttools buildimage

ifeq ($(strip $(VOXXXLOAD)),1)
modbuild: touch_voice_files
	cd $(KERNEL_DIR); $(MAKE) modules && $(MAKE) modules_install
else
modbuild:
	cd $(KERNEL_DIR); $(MAKE) modules && $(MAKE) modules_install
endif

modules: profile_check modbuild hosttools buildimage

app: profile_check prebuild $(BRCMAPPS) hosttools buildimage

prebuild:
	mkdir -p $(INSTALL_DIR)/bin $(INSTALL_DIR)/lib

# touch_voice_files doesn't clean up voice, just enables incremental build of voice code
touch_voice_files:
	find bcmdrivers/broadcom/char/endpoint/ \( -name '*.o' -o -name '*.a' -o -name '*.lib' -o -name '*.ko' -o -name '*.cmd' -o -name '.*.cmd' -o -name '*.c' -o -name '*.mod' \) -print -exec rm -f "{}" ";"
	rm -rf kernel/linux/.tmp_versions/endpointdd.mod
	rm -rf kernel/linux/arch/mips/defconfig
	rm -rf kernel/linux/include/config/bcm/endpoint/
	rm -rf kernel/linux/include/asm-mips/offset.h
	rm -rf kernel/linux/include/asm-mips/reg.h
	find kernel/linux/lib/ -name '*.o' -print -exec rm -f "{}" ";"
	find kernel/linux/lib/ -name '*.lib' -print -exec rm -f "{}" ";"

# Build user applications depending on if they are
# specified in the profile
ifneq ($(strip $(BUILD_PVC2684CTL)),)
export BUILD_PVC2684D=$(BUILD_PVC2684CTL)
pvc2684d:
pvc2684ctl:
	$(MAKE) -C $(OPENSOURCE_DIR)/atm2684/pvc2684ctl $(BUILD_PVC2684CTL)
else
pvc2684ctl:
endif

ifneq ($(strip $(BUILD_BRCTL)),)
brctl:
	cd $(OPENSOURCE_DIR);   (tar xkfj bridge-utils.tar.bz2 2> /dev/null || true)
	$(MAKE) -C $(OPENSOURCE_DIR)/bridge-utils $(BUILD_BRCTL)
else
brctl:
endif

ifneq ($(strip $(BUILD_VCONFIG)),)
export BUILD_VCONFIG=y
endif

ifneq ($(strip $(BUILD_CFM)),)

ifneq ($(strip $(BUILD_CFM_MENU)),)
export BUILD_CFM_MENU=y
endif

cfm:
	$(MAKE) -C $(BROADCOM_DIR)/cfm $(BUILD_CFM)
else
cfm:
endif

# iptables is dependent on kernel netfilter modules
ifneq ($(strip $(BRCM_KERNEL_NETFILTER)),)
ifneq ($(strip $(BUILD_IPTABLES)),)
iptables:
	cd $(OPENSOURCE_DIR);   (tar xkfj iptables.tar.bz2 2> /dev/null || true)
	$(MAKE) -C $(OPENSOURCE_DIR)/iptables $(BUILD_IPTABLES)
iptables-build:
	cd $(OPENSOURCE_DIR);   (tar xkfj iptables.tar.bz2 2> /dev/null || true)
	$(MAKE) -C $(OPENSOURCE_DIR)/iptables static
else
iptables:
endif
else
iptables:
	@echo Warning: You need to enable netfilter in the kernel !!!!!
endif

ifneq ($(strip $(BUILD_EBTABLES)),)
ebtables:
	cd $(OPENSOURCE_DIR);   (tar xkfj ebtables.tar.bz2 2> /dev/null || true)
	$(MAKE) -C $(OPENSOURCE_DIR)/ebtables $(BUILD_EBTABLES)
else
ebtables:
endif

ifneq ($(strip $(BUILD_PPPD)),)
pppd:
	$(MAKE) -C $(OPENSOURCE_DIR)/ppp/pppoe $(BUILD_PPPD)
else
pppd:
endif

ifneq ($(strip $(BUILD_REAIM)),)
reaim:
	cd $(OPENSOURCE_DIR);   (tar xkfj reaim.tar.bz2 2> /dev/null || true)
	$(MAKE) -C $(OPENSOURCE_DIR)/reaim $(BUILD_REAIM)
else
reaim:
endif

######## for smdog #####################################
ifneq ($(strip $(BUILD_SMDOG)),)
export SMDOG=1
smdog:
	$(MAKE) -C $(BROADCOM_DIR)/smdog $(BUILD_SMDOG)
else
export SMDOG=0
smdog:
endif
                                                                                                               
ledtest:
	$(MAKE) -C $(BROADCOM_DIR)/ledtest dynamic                                                                                                              

ifneq ($(strip $(BUILD_GDBSERVER)),)
gdbserver:
	$(MAKE) -C $(OPENSOURCE_DIR)/gdbserver dynamic
else
gdbserver:
endif

ifneq ($(strip $(BUILD_OPENSSL)),)
openssl:
	#$(MAKE) -C $(OPENSOURCE_DIR)/openssl
else
openssl:
endif

ifneq ($(strip $(BUILD_ETHWAN)),)
export BUILD_ETHWAN=y
endif

ifneq ($(strip $(BUILD_UDHCP)),)
udhcp:
	$(MAKE) -C $(OPENSOURCE_DIR)/udhcp $(BUILD_UDHCP)
else
udhcp:
endif

# UPNP is dependent on iptables
ifneq ($(strip $(BUILD_IPTABLES)),)
ifneq ($(strip $(BUILD_UPNP)),)
upnp: iptables-build
	$(MAKE) -C $(BROADCOM_DIR)/upnp/router/upnp  $(BUILD_UPNP)
else
upnp:
endif
else
upnp:
	@echo Warning: You need to build iptables first !!!!!
endif


ifneq ($(strip $(BUILD_SIPROXD)),)
siproxd:
	cd $(OPENSOURCE_DIR);   (tar xkfj libosip2.tar.bz2 2> /dev/null || true)
	cd $(OPENSOURCE_DIR);   (tar xkfj siproxd.tar.bz2 2> /dev/null || true)
	$(MAKE) -C $(OPENSOURCE_DIR)/siproxd $(BUILD_SIPROXD)
else
siproxd:
endif

ifneq ($(strip $(BUILD_SNMP)),)

ifneq ($(strip $(BUILD_SNMP_SET)),)
export BUILD_SNMP_SET=1
else
export BUILD_SNMP_SET=0
endif

ifneq ($(strip $(BUILD_SNMP_ADSL_MIB)),)
export BUILD_SNMP_ADSL_MIB=1
else
export BUILD_SNMP_ADSL_MIB=0
endif

ifneq ($(strip $(BUILD_SNMP_ATM_MIB)),)
export BUILD_SNMP_ATM_MIB=1
else
export BUILD_SNMP_ATM_MIB=0
endif

ifneq ($(strip $(BUILD_SNMP_AT_MIB)),)
export BUILD_SNMP_AT_MIB=1
else
export BUILD_SNMP_AT_MIB=0
endif

ifneq ($(strip $(BUILD_SNMP_SYSOR_MIB)),)
export BUILD_SNMP_SYSOR_MIB=1
else
export BUILD_SNMP_SYSOR_MIB=0
endif

ifneq ($(strip $(BUILD_SNMP_TCP_MIB)),)
export BUILD_SNMP_TCP_MIB=1
else
export BUILD_SNMP_TCP_MIB=0
endif

ifneq ($(strip $(BUILD_SNMP_UDP_MIB)),)
export BUILD_SNMP_UDP_MIB=1
else
export BUILD_SNMP_UDP_MIB=0
endif

ifneq ($(strip $(BUILD_SNMP_IP_MIB)),)
export BUILD_SNMP_IP_MIB=1
else
export BUILD_SNMP_IP_MIB=0
endif

ifneq ($(strip $(BUILD_SNMP_ICMP_MIB)),)
export BUILD_SNMP_ICMP_MIB=1
else
export BUILD_SNMP_ICMP_MIB=0
endif

ifneq ($(strip $(BUILD_SNMP_SNMP_MIB)),)
export BUILD_SNMP_SNMP_MIB=1
else
export BUILD_SNMP_SNMP_MIB=0
endif

ifneq ($(strip $(BUILD_SNMP_ATMFORUM_MIB)),)
export BUILD_SNMP_ATMFORUM_MIB=1
else
export BUILD_SNMP_ATMFORUM_MIB=0
endif

snmp:
	cd $(OPENSOURCE_DIR);   (tar xkfj net-snmp.tar.bz2 2> /dev/null || true)
	$(MAKE) -C $(OPENSOURCE_DIR)/net-snmp $(BUILD_SNMP)
else
snmp:
endif

ifneq ($(strip $(BUILD_ILMI)),)
ilmi:
	cd $(OPENSOURCE_DIR);   (tar xkfj net-snmp.tar.bz2 2> /dev/null || true)
	$(MAKE) -C $(BROADCOM_DIR)/ilmi $(BUILD_ILMI)
else
ilmi:
endif

ifneq ($(strip $(BUILD_VODSL)),)
vodsl:
	$(MAKE) -C $(BROADCOM_DIR)/vodsl $(BUILD_VODSL)
else
vodsl:
endif

# Leave it for the future when soap server is decoupled from cfm
ifneq ($(strip $(BUILD_SOAP)),)
ifeq ($(strip $(BUILD_SOAP_VER)),2)
soapserver:
	$(MAKE) -C $(BROADCOM_DIR)/SoapToolkit/SoapServer $(BUILD_SOAP)
else
soap:
	$(MAKE) -C $(BROADCOM_DIR)/soap $(BUILD_SOAP)
endif
else
soap:
endif

ifneq ($(strip $(BUILD_NAS)),)
export WIRELESS=1
nas:
	$(MAKE) -C $(BROADCOM_DIR)/nas $(BUILD_NAS)

#add hotplug here, for nas use only
hotplug:
	$(MAKE) -C $(BROADCOM_DIR)/hotplug $(BUILD_NAS)
	
else
export WIRELESS=0
nas:
#add hotplug here, for nas use only
hotplug:
endif

ifneq ($(strip $(BUILD_WLCTL)),)
export WIRELESS=1
wlctl:
	$(MAKE) -C $(BROADCOM_DIR)/wlctl $(BUILD_WLCTL)
else
export WIRELESS=0
wlctl:
endif

######### for fwscheduler ##############################
ifneq ($(strip $(BUILD_FWSCHEDULER)),)
export FWSCHEDULER=1
fwscheduler:
	$(MAKE) -C $(BROADCOM_DIR)/fwscheduler $(BUILD_FWSCHEDULER)
else
export FWSCHEDULER=0
fwscheduler:
endif

######### for urlfilter ################################
ifneq ($(strip $(BUILD_URLFILTER)),)
export URLFILTER=1
urlfilter:
	$(MAKE) -C $(BROADCOM_DIR)/urlfilter $(BUILD_URLFILTER)
else
export URLFILTER=0
urlfilter:
endif

################for traffic_ctl########################
ifneq ($(strip $(BUILD_BUDGET)),)	
traffic_ctl:
	$(MAKE) -C $(BROADCOM_DIR)/traffic_ctl $(BUILD_BUDGET)
else
traffic_ctl:
endif
ifneq ($(strip $(BUILD_PCSCAN)),)
pcscan:
	$(MAKE) -C $(BROADCOM_DIR)/pcscan $(BUILD_PCSCAN);
else
pcscan:
endif	

ifneq ($(strip $(BUILD_NTP)),)
ntp:
	$(MAKE) -C $(BROADCOM_DIR)/ntp $(BUILD_NTP);
else
ntp:
endif	


#Always compile Ethernet control utility
ethctl:
	$(MAKE) -C $(BROADCOM_DIR)/ethctl dynamic

ifneq ($(strip $(BUILD_DNSPROBE)),)
dnsprobe:
	$(MAKE) -C $(BROADCOM_DIR)/dnsprobe $(BUILD_DNSPROBE)
else
dnsprobe:
endif

ifneq ($(strip $(BUILD_IGMP)),)
igmp:
	$(MAKE) -C $(BROADCOM_DIR)/igmp $(BUILD_IGMP)
else
igmp:
endif

ifneq ($(strip $(BUILD_DHCPR)),)
dhcpr:
	$(MAKE) -C $(BROADCOM_DIR)/dhcpr $(BUILD_DHCPR)
else
dhcpr:
endif

ifneq ($(strip $(BUILD_ZEBRA)),)
zebra:
	cd $(OPENSOURCE_DIR);   (tar xkfj zebra.tar.bz2 2> /dev/null || true)
	$(MAKE) -C $(OPENSOURCE_DIR)/zebra $(BUILD_ZEBRA)
else
zebra:
endif

ifneq ($(strip $(BUILD_ATMCTL)),)
atmctl:
	$(MAKE) -C $(BROADCOM_DIR)/atmctl $(BUILD_ATMCTL)
else
atmctl:
endif

ifneq ($(strip $(BUILD_ADSLCTL)),)
adslctl:
	$(MAKE) -C $(BROADCOM_DIR)/adslctl $(BUILD_ADSLCTL)
else
adslctl:
endif

ifeq ($(strip $(BUILD_CFM_CLI)),y)
ifneq ($(strip $(BUILD_NETCTL)),)
netctl:
	$(MAKE) -C $(BROADCOM_DIR)/netctl $(BUILD_NETCTL)
else
netctl:
endif
else
netctl:
endif

ifneq ($(strip $(BUILD_BUSYBOX)),)
busybox:
	cd $(OPENSOURCE_DIR); (tar xkfj busybox.tar.bz2 2> /dev/null || true)
#	$(MAKE) -C $(OPENSOURCE_DIR)/busybox $(BUILD_BUSYBOX)
	cd $(OPENSOURCE_DIR)/busybox; cp -f brcm.config .config
	$(MAKE) -C $(OPENSOURCE_DIR)/busybox install
else
busybox:
endif

ifneq ($(strip $(BUILD_LIBCREDUCTION)),)
libcreduction:
	$(MAKE) -C $(OPENSOURCE_DIR)/libcreduction install
else
libcreduction:
endif

ifneq ($(strip $(BUILD_DIAGAPP)),)
diagapp:
	$(MAKE) -C $(BROADCOM_DIR)/diagapp $(BUILD_DIAGAPP)
else
diagapp:
endif

ifneq ($(strip $(BUILD_FTPD)),)
bftpd:
	cd $(OPENSOURCE_DIR);   (tar xkfj ftpd.tar.bz2 2> /dev/null || true)
	$(MAKE) -C $(OPENSOURCE_DIR)/ftpd $(BUILD_FTPD)
else
bftpd:
endif

ifneq ($(strip $(BUILD_DDNSD)),)
ddnsd:
	$(MAKE) -C $(BROADCOM_DIR)/ddnsd $(BUILD_DDNSD)
else
ddnsd:
endif

ifneq ($(strip $(BUILD_SNTP)),)
sntp:
	$(MAKE) -C $(BROADCOM_DIR)/sntp $(BUILD_SNTP)
else
sntp:
endif

ifneq ($(strip $(BUILD_EPITTCP)),)
epittcp:
	$(MAKE) -C $(BROADCOM_DIR)/epittcp $(BUILD_EPITTCP)
else
epittcp:
endif

ifneq ($(strip $(BUILD_IPPD)),)
ippd:
	$(MAKE) -C $(BROADCOM_DIR)/ippd $(BUILD_IPPD)
else
ippd:
endif

hosttools:
	$(MAKE) -C $(HOSTTOOLS_DIR)


buildimage: $(KERNEL_DIR)/vmlinux
	su --command="cd $(TARGETS_DIR); ./buildFS"
ifeq ($(strip $(BRCM_KERNEL_ROOTFS)),squashfs)
	#$(HOSTTOOLS_DIR)/mksquashfs $(TARGET_FS) $(PROFILE_DIR)/rootfs.img -noappend -be -always-use-fragments -gzip
	$(HOSTTOOLS_DIR)/mksquashfs $(TARGET_FS) $(PROFILE_DIR)/rootfs.img -noappend -be -lzma -no-fragments -noI
else
 ifeq ($(strip $(BRCM_KERNEL_ROOTFS)),cramfs)
#	$(HOSTTOOLS_DIR)/mkcramfs -r -g $(TARGET_FS) $(PROFILE_DIR)/rootfs.img
	$(HOSTTOOLS_DIR)/mkcramfs -r $(TARGET_FS) $(PROFILE_DIR)/rootfs.img
 else
  ifeq ($(strip $(BRCM_KERNEL_ROOTFS)),jffs2)
	$(HOSTTOOLS_DIR)/mkfs.jffs2 -b -p -e $(BRCM_FLASHBLK_SIZE) -r $(TARGET_FS) -o $(PROFILE_DIR)/rootfs.img
  endif
 endif
endif

ifneq ($(strip $(BRCM_KERNEL_ROOTFS)),nfs)
	cd $(PROFILE_DIR); \
	cp $(KERNEL_DIR)/vmlinux . ; \
	$(STRIP) --remove-section=.note --remove-section=.comment vmlinux; \
	$(OBJCOPY) -O binary vmlinux vmlinux.bin; \
	$(HOSTTOOLS_DIR)/cmplzma -k -2 vmlinux vmlinux.bin vmlinux.lz;\
	$(HOSTTOOLS_DIR)/bcmImageBuilder --output $(FS_KERNEL_IMAGE_NAME) --chip $(BRCM_CHIP) --board $(BRCM_BOARD_ID) --blocksize $(BRCM_FLASHBLK_SIZE) --cfefile $(CFE_FILE) --rootfsfile rootfs.img --kernelfile vmlinux.lz; \
	$(HOSTTOOLS_DIR)/bcmImageBuilder --output $(CFE_FS_KERNEL_IMAGE_NAME) --chip $(BRCM_CHIP) --board $(BRCM_BOARD_ID) --blocksize $(BRCM_FLASHBLK_SIZE) --cfefile $(CFE_FILE) --rootfsfile rootfs.img --kernelfile vmlinux.lz --include-cfe; \
	$(HOSTTOOLS_DIR)/createimg -b $(BRCM_BOARD_ID) -n $(BRCM_NUM_MAC_ADDRESSES) -m $(BRCM_BASE_MAC_ADDRESS) -i $(CFE_FS_KERNEL_IMAGE_NAME) -o $(FLASH_IMAGE_NAME); \
	$(HOSTTOOLS_DIR)/addvtoken $(FLASH_IMAGE_NAME) $(FLASH_IMAGE_NAME).w
	@mkdir -p $(IMAGES_DIR)
	@cp $(PROFILE_DIR)/$(FS_KERNEL_IMAGE_NAME) $(IMAGES_DIR)/$(FS_KERNEL_IMAGE_NAME)_$(BRCM_RELEASETAG)-$(shell date '+%y%m%d_%H%M')
	@echo
	@echo -e "Done! Image $(PROFILE) has been built in $(IMAGES_DIR)."
else
	cd $(PROFILE_DIR); \
	cp $(KERNEL_DIR)/vmlinux . ; \
	$(STRIP) --remove-section=.note --remove-section=.comment vmlinux
	@echo
	@echo -e "\t=== Following the below steps to start your NFS root file system on host ==="
	@echo -e "Step 1: Copy $(PROFILE_DIR)/vmlinux to your TFTP server boot directory, such as /tftpboot"
	@echo -e "Step 2: Add \"$(PROFILE_DIR)/fs *(rw,no_root_squash)\" to /etc/exports"
	@echo -e "Step 3: Become root and restart your nfs server, such as \"service nfs restart\""
	@echo -e "Step 4: Reboot your board and break into CFE bootloader, choose h on \"Run from flash/host\" and vmlinux on \"Default host run file name\""
endif


###########################################
#
# System code clean-up
#
###########################################	
	
subdirs: $(patsubst %, _dir_%, $(SUBDIRS))

$(patsubst %, _dir_%, $(SUBDIRS)) :
	$(MAKE) -C $(patsubst _dir_%, %, $@) $(TGT)

clean: target_clean app_clean kernel_clean hosttools_clean
	rm -f .tmpconfig*

fssrc_clean:
	rm -fr $(INSTALL_DIR)/bin
	rm -fr $(INSTALL_DIR)/sbin
	rm -fr $(INSTALL_DIR)/lib
	rm -fr $(INSTALL_DIR)/upnp
	rm -fr $(INSTALL_DIR)/docs
	rm -fr $(INSTALL_DIR)/webs
	rm -fr $(INSTALL_DIR)/usr
	rm -fr $(INSTALL_DIR)/linuxrc

kernel_clean: sanity_check
	$(MAKE) -C $(KERNEL_DIR) mrproper
	rm -f $(KERNEL_DIR)/arch/mips/defconfig
	rm -f $(HOSTTOOLS_DIR)/lzma/decompress/*.o
	rm -rf $(XCHANGE_DIR)/dslx/lib/LinuxKernel
	rm -rf $(XCHANGE_DIR)/dslx/obj/LinuxKernel

app_clean: sanity_check fssrc_clean
	$(MAKE) subdirs TGT=clean
	rm -rf $(XCHANGE_DIR)/dslx/lib/LinuxUser
	rm -rf $(XCHANGE_DIR)/dslx/obj/LinuxUser

target_clean: sanity_check
	rm -f $(PROFILE_DIR)/rootfs.img
	rm -f $(PROFILE_DIR)/vmlinux
	rm -f $(PROFILE_DIR)/vmlinux.bin
	rm -f $(PROFILE_DIR)/vmlinux.lz
	rm -f $(PROFILE_DIR)/$(FS_KERNEL_IMAGE_NAME)
	rm -f $(PROFILE_DIR)/$(CFE_FS_KERNEL_IMAGE_NAME)
	rm -f $(PROFILE_DIR)/$(FLASH_IMAGE_NAME)
	rm -f $(PROFILE_DIR)/$(FLASH_IMAGE_NAME).w
	rm -fr $(PROFILE_DIR)/modules
	find targets -name vmlinux -print -exec rm -f "{}" ";"
	su --command="rm -fr $(TARGET_FS)"

hosttools_clean:
	$(MAKE) -C $(HOSTTOOLS_DIR) clean
	
###########################################
#
# System-wide exported variables
#
###########################################	

export  BRCM_VERSION BRCM_RELEASE BRCM_EXTRAVERSION BRCM_RELEASETAG BRCM_BOARD RUN_NOISE \
	INC_KERNEL_BASE KERNEL_DIR BRCMDRIVERS_DIR USERAPPS_DIR HOSTTOOLS_DIR TARGETS_DIR DEFAULTCFG_DIR XCHANGE_DIR FSSRC_DIR BUSYBOX_DIR \
	PROFILE_DIR INSTALL_DIR LINUXDIR INC_BRCMDRIVER_PUB_PATH INC_BRCMDRIVER_PRIV_PATH INC_BRCMBOARDPARMS_PATH INC_ENDPOINT_PATH INC_ADSLDRV_PATH BROADCOM_CFM_DIR INC_BRCMCFM_PATH BRCM_KERNEL_ROOTFS BRCMAPPS \
	BRCM_UCLIBC CROSS_COMPILE TOOLCHAIN AS LD CC CXX AR NM STRIP SSTRIP OBJCOPY OBJDUMP RANLIB LIB_PATH LIBCDIR LIBDIR  \
	BUILD_BR2684CTL BUILD_PVC2684CTL BUILD_RT2684D BUILD_BRCTL BUILD_CFM BUILD_CFM_CLI BUILD_IPTABLES BUILD_EBTABLES BUILD_VODSL BUILD_SIPROXD \
	BRCM_APP_PHONE BUILD_SOAP BUILD_SOAP_VER BRCM_DSP_CODEC_G711 BRCM_DSP_CODEC_G723 BRCM_DSP_CODEC_G726 BRCM_DSP_CODEC_G729 \
   BRCM_DSP_CODEC_G7xx BRCM_DSP_PCM BRCM_DSP_HYBRID BRCM_DSP_HYBRID_EXT BRCM_DSP_APM_FXO BRCM_DSP_APM_FXO_EXT BRCM_DSP_HYBRID_FXO \
   BRCM_DSP_HYBRID_FXO_EXT BRCM_DSP_CODEC_T38_EXT BRCM_DSP_CODEC_T38_INT BRCM_DSP_HAL BRCM_DSP_HAL_EXTENSION  XCHANGE_DSP_APP_EXTENSION BRCM_VOICE_COUNTRY_JAPAN BRCM_VOICE_GLOBAL_CFLAGS \
	BUILD_PPPD BUILD_REAIM BUILD_GDBSERVER BUILD_UDHCP BUILD_DHCPR BUILD_UPNP BUILD_SNMP BUILD_NAS BUILD_WLCTL BUILD_BUSYBOX BUILD_DNSPROBE BUILD_SLACTEST BUILD_VCONFIG BUILD_ETHWAN  BUILD_NTP BUILD_OPENSSL \
	BUILD_ZEBRA BUILD_ATMCTL BUILD_ADSLCTL BUILD_NETCTL BUILD_IGMP BRCM_PTHREADS BUILD_DIAGAPP \
	BUILD_CFM_TELNETD BUILD_CFM_SSHD BUILD_SSHD_MIPS_GENKEY BUILD_FTPD BRCM_DRIVER_PCI \
	BRCM_PSI_VERSION WEB_POPUP BUILD_DIR BUILD_DDNSD BUILD_SNTP BUILD_TOD BUILD_IPPD BUILD_VCONFIG JTAG_KERNEL_DEBUG \
	BUILD_EPITTCP
