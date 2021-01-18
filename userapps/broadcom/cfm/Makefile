all:
	cp cfm_$(PROFILE)_save cfm

dynamic: all install webuihtml rmwl_html rmvoice_html

clean:
	rm -f cfm


install:
	install -m 755 cfm $(INSTALL_DIR)/bin
	$(STRIP) $(INSTALL_DIR)/bin/cfm

webuihtml:
	mkdir -p $(INSTALL_DIR)/webs
ifneq ($(strip $(PLATFORM)),)
	cp -f html_$(PLATFORM)/*.htm html_$(PLATFORM)/*.html html_$(PLATFORM)/*.jpg html_$(PLATFORM)/*.txt html_$(PLATFORM)/*.gif html_$(PLATFORM)/*.css $(INSTALL_DIR)/webs
else
	cp -f html_$(PLATFORM)/*.htm html_$(PLATFORM)/*.html html_$(PLATFORM)/*.jpg html_$(PLATFORM)/*.txt html_$(PLATFORM)/*.gif html_$(PLATFORM)/*.css $(INSTALL_DIR)/webs
endif
	
rmwl_html:
ifneq ($(strip $(WIRELESS)),1)
	rm -f $(INSTALL_DIR)/webs/wl*.html
else
rmwl_html:
endif

rmvoice_html:
ifneq ($(strip $(VOXXXLOAD)),1)
	rm -f $(INSTALL_DIR)/webs/voice*.html
else
rmvoice_html:
endif

install_ssl_cert_file:
	cp web/*.pem $(INSTALL_DIR)/etc
	rm -f $(INSTALL_DIR)/tmp
	ln -s /var $(INSTALL_DIR)/tmp

