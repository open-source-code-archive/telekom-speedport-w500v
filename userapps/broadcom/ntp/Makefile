all:
	cp ntpclient_$(PROFILE)_save ntpclient

PROGRAM_NAME := ntpclient

install:
	install -m 755 $(PROGRAM_NAME) $(INSTALL_DIR)/bin
	$(STRIP) $(INSTALL_DIR)/bin/$(PROGRAM_NAME)

dynamic: all install

clean:
	rm -f ntpclient

