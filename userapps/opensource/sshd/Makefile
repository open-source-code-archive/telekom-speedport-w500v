O_TARGET := sshd.o 

###-DDEBUG_TRACE -DDEBUG_RSA -DDEBUG_DSS
CFLAGS= -s -Os -fomit-frame-pointer -W -I. -Ilibtomcrypt \
	-I$(INC_APP_PATH) -I$(INC_BRCMDRIVER_PUB_PATH)/bcm963xx

subdir-y :=	libtomcrypt libtommath  

obj-y :=main.o chansession.o \
		util.o session.o packet.o algo.o buffer.o kex.o dss.o bignum.o \
		signkey.o rsa.o random.o service.o auth.o authpasswd.o channel.o \
		queue.o sshpty.o termcodes.o authpubkey.o runopts.o \
		loginrec.o atomicio.o x11fwd.o agentfwd.o localtcpfwd.o \
		$(join $(subdir-y), $(patsubst %,/%.o,$(notdir $(subdir-y))))
		
include $(TOPDIR)/Rules.make
