all:
	cp wlctl_$(PROFILE)_save wlctl

PROGRAM_NAME:= wlctl

install::
	install -m 755 $(PROGRAM_NAME) $(INSTALL_DIR)/bin
	$(STRIP) $(INSTALL_DIR)/bin/$(PROGRAM_NAME)
	mkdir -p $(INSTALL_DIR)/sbin

dynamic: all install

clean:
	rm -f wlctl

