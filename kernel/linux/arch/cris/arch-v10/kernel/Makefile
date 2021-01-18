# $Id: Makefile,v 1.1.1.1 2006/01/25 03:57:08 root Exp $
#
# Makefile for the linux kernel.
#

extra-y	:= head.o


obj-y   := entry.o traps.o shadows.o debugport.o irq.o \
	   process.o setup.o signal.o traps.o time.o ptrace.o

obj-$(CONFIG_ETRAX_KGDB) += kgdb.o
obj-$(CONFIG_ETRAX_FAST_TIMER) += fasttimer.o

clean:

