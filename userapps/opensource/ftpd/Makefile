# Makefile file for bftpd
#
# License:  GNU General Public License, Version 2.
#
CFLAGS= -Wall -s -Os -fomit-frame-pointer \
        -I. -I$(INC_BRCMCFM_PATH) \
        -I$(INC_BRCMDRIVER_PUB_PATH)/$(BRCM_BOARD) -I$(INC_BRCMDRIVER_PRIV_PATH)/$(BRCM_BOARD) \
        -I$(BROADCOM_CFM_DIR)/inc -I$(BROADCOM_CFM_DIR)/util/psi
        
LDFLAGS=-Wl,-allow-shlib-undefined
ifeq ($(strip $(BUILD_FTPD)), static)
CFLAGS += -DBUILD_STATIC
endif

all: bftpd

LIBS= -lcrypt

HEADERS=commands.h list.h login.h main.h mystring.h fwsyscall.h 
OBJS=commands.o list.o login.o main.o mystring.o fwsyscall.o
SRCS=commands.c list.c login.c main.c mystring.c fwsyscall.c 
BOARD_API_SRC=$(BROADCOM_CFM_DIR)/util/psi/board_api.c
BOARD_API_OBJ=board_api.o
SYSCALL_SRC=$(BROADCOM_CFM_DIR)/util/system/syscall.c
SYSCALL_OBJ=syscall.o

install:
	install -m 755 bftpd $(INSTALL_DIR)/bin
	$(STRIP) $(INSTALL_DIR)/bin/bftpd

dynamic: bftpd install

static: bftpd.a

$(BOARD_API_OBJ):	$(INC_BRCMCFM_PATH)/board_api.h
	$(CC) $(CFLAGS) -c $(BOARD_API_SRC)

$(SYSCALL_OBJ):	$(INC_BRCMCFM_PATH)/syscall.h 
	$(CC) $(CFLAGS) -I$(INC_KERNEL_PATH) -I$(INC_KERNEL_PATH2) -c $(SYSCALL_SRC)
		
bftpd: $(HEADERS) $(OBJS) $(BOARD_API_OBJ) $(SYSCALL_OBJ)
	$(CC) $(LDFLAGS) $(OBJS) $(BOARD_API_OBJ) $(SYSCALL_OBJ) $(LIBS) -o bftpd

bftpd.a: $(HEADERS) $(OBJS) $(BOARD_API_OBJ) $(SYSCALL_OBJ)
	$(CC) $(CFLAGS) -c -o $(OBJS)
	$(AR) rcs bftpd.a $(OBJS) $(BOARD_API_OBJ) $(SYSCALL_OBJ) $(LIBS)

clean:
	-rm -f bftpd $(OBJS) $(BOARD_API_OBJ) $(SYSCALL_OBJ) bftpd.a


