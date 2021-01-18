
export TOPDIR = $(OPENSOURCE_DIR)/siproxd

SUBDIRS = libosip2 siproxd_main

OBJS = siproxd.o

all: siproxd

install:
		install -m 755 siproxd $(INSTALL_DIR)/bin
		$(STRIP) $(INSTALL_DIR)/bin/siproxd

dynamic: siproxd install

siproxd: subdirs $(OBJS)
		$(CC) $(CFLAGS) -o siproxd -lpthread $(OBJS)
		mkdir -p $(TARGETS_DIR)/fs.src/etc/siproxd
		cp -f $(TOPDIR)/siproxd.conf $(TARGETS_DIR)/fs.src/etc/siproxd

subdirs: $(patsubst %, _dir_%, $(SUBDIRS))

$(patsubst %, _dir_%, $(SUBDIRS)) :
	$(MAKE) -C $(patsubst _dir_%, %, $@) $(TGT)

clean:
	$(MAKE) -i TGT=clean subdirs
	-rm -f siproxd siproxd.o
	-rm -rf $(TARGETS_DIR)/fs.src/etc/siproxd
