all:
	cp nas_$(PROFILE)_save nas

install:
	install -m 755 nas $(INSTALL_DIR)/bin
	$(STRIP) $(INSTALL_DIR)/bin/nas

dynamic: all install

clean:
	rm -f nas

