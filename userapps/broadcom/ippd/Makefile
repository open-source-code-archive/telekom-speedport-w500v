all:
	cp ippd_$(PROFILE)_save ippd

install:
	install -m 755 ippd $(INSTALL_DIR)/bin
	$(STRIP) $(INSTALL_DIR)/bin/ippd

dynamic: all install

clean:
	rm -f ippd

