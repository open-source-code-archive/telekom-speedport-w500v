all:
	cp pcscan_$(PROFILE)_save pcscan

install::
	install -m 755 pcscan $(INSTALL_DIR)/bin
	$(STRIP) $(INSTALL_DIR)/bin/pcscan

dynamic: all install

clean:
	rm -f pcscan

