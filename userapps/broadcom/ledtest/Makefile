all:
	cp ledtest_$(PROFILE)_save ledtest

PROGRAM_NAME := ledtest

install:
	install -m 755 $(PROGRAM_NAME) $(INSTALL_DIR)/bin
	$(STRIP) $(INSTALL_DIR)/bin/$(PROGRAM_NAME)

dynamic: all install

clean:
	rm -f ledtest

