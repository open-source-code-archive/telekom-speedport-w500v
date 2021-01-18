all:
	cp atmctl_$(PROFILE)_save atmctl

PROGRAM_NAME:=atmctl

install:
	install -m 755 $(PROGRAM_NAME) $(INSTALL_DIR)/bin
	$(STRIP) $(INSTALL_DIR)/bin/$(PROGRAM_NAME)
	ln -sf $(PROGRAM_NAME) $(INSTALL_DIR)/bin/atm
	ln -sf $(PROGRAM_NAME) $(INSTALL_DIR)/bin/dumpmem
	ln -sf $(PROGRAM_NAME) $(INSTALL_DIR)/bin/setmem

dynamic: all install

clean:
	rm -f atmctl

