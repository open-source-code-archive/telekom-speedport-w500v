#
# Makefile for gdbserver 
#

PROGRAM_NAME:=gdbserver

SOURCE_FILES:= server.o target.o utils.o mem-break.o reg-mips.o linux-low.o linux-mips-low.o signals.o  \
	inferiors.o regcache.o remote-utils.o

CFLAGS= -s -Os -fomit-frame-pointer
LDFLAGS= -Wl,-allow-shlib-undefined

signals.o: signals.c
	$(CC) -c $(CFLAGS) -o $@ $< -DGDBSERVER

%.o: %.c 
	$(CC) -c $(CFLAGS) -o $@ $<

all: $(PROGRAM_NAME)

install:
	install -m 755 $(PROGRAM_NAME) $(INSTALL_DIR)/bin
	$(STRIP) $(INSTALL_DIR)/bin/$(PROGRAM_NAME)

dynamic: $(PROGRAM_NAME) install

static: $(PROGRAM_NAME).a 

$(PROGRAM_NAME): $(SOURCE_FILES)
	$(CC) $(LDFLAGS) -o  $@ $^

$(PROGRAM_NAME).a: $(SOURCE_FILES) 
	$(AR) rcs $(PROGRAM_NAME).a $^

clean:
	-rm -f $(PROGRAM_NAME) *.o *.a
