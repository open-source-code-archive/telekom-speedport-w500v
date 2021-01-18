all:
	cp vodsl_$(PROFILE)_save vodsl

install:
		install -m 755 vodsl $(INSTALL_DIR)/bin
		$(STRIP) $(INSTALL_DIR)/bin/vodsl

dynamic: all install

clean:
	rm -f vodsl

