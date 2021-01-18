all:
	cp smdog_$(PROFILE)_save smdog

PROGRAM_NAME := smdog

install:
	install -m 755 $(PROGRAM_NAME) $(INSTALL_DIR)/bin
	$(STRIP) $(INSTALL_DIR)/bin/$(PROGRAM_NAME)

dynamic: all install

clean:
	rm -f smdog

