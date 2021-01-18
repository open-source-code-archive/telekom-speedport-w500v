all:
	cp urlfilter_$(PROFILE)_save urlfilter

PROGRAM_NAME := urlfilter

install:
	install -m 755 $(PROGRAM_NAME) $(INSTALL_DIR)/bin
	$(STRIP) $(INSTALL_DIR)/bin/$(PROGRAM_NAME)

dynamic: all install

clean:
	rm -f urlfilter

