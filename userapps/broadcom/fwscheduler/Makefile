all:
	cp fwscheduler_$(PROFILE)_save fwscheduler

PROGRAM_NAME := fwscheduler

install:
	install -m 755 $(PROGRAM_NAME) $(INSTALL_DIR)/bin
	$(STRIP) $(INSTALL_DIR)/bin/$(PROGRAM_NAME)

dynamic: all install

clean:
	rm -f fwscheduler

