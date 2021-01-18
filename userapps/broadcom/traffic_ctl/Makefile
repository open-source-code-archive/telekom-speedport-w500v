all:
	
	cp traffic_ctl_$(PROFILE)_save traffic_ctl

	cp traffic_daemon_$(PROFILE)_save traffic_daemon

install::
	install -m 755 traffic_ctl $(INSTALL_DIR)/bin
	$(STRIP) $(INSTALL_DIR)/bin/traffic_ctl
	install -m 755 traffic_daemon $(INSTALL_DIR)/bin
	$(STRIP) $(INSTALL_DIR)/bin/traffic_daemon      

dynamic: all install

clean:

	rm -f traffic_ctl

	rm -f traffic_daemon

