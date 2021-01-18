# File: bcmdrivers/Makefile
#
# Makefile for the Linux kernel modules.
#
-include $(KERNEL_DIR)/.config

obj-y += opensource/

# If rootfs is nfs, we have to build Ethernet
# driver as built-n
ifeq ($(CONFIG_ROOTFS_NFS),y)
obj-y += broadcom/
endif

obj-m += broadcom/

