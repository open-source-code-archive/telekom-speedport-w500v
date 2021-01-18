# Generated automatically from Makefile.depend by configure.
#
# Minimum environment and virtual path setup
#
SHELL		= /bin/sh
srcdir		= .
top_srcdir	= ../..
VERSION		= 5.0.8


#
# Paths
#
prefix		= /usr/local
exec_prefix	= /usr/local
bindir		= ${exec_prefix}/bin
sbindir		= ${exec_prefix}/sbin
libdir		= ${exec_prefix}/lib
datadir		= ${prefix}/share
includedir	= ${prefix}/include/net-snmp
ucdincludedir	= ${prefix}/include/ucd-snmp
mandir		= ${prefix}/man
man1dir		= $(mandir)/man1
man3dir		= $(mandir)/man3
man5dir		= $(mandir)/man5
man8dir		= $(mandir)/man8
snmplibdir	= $(datadir)/snmp
mibdir		= $(snmplibdir)/mibs
persistentdir	= /var/net-snmp


#
# Programs
#
INSTALL		= $(LIBTOOL) --mode=install /usr/bin/install -c
INSTALL_DATA    = ${INSTALL} -m 644
SED		= /bin/sed
LN_S		= ln -s
AUTOCONF	= :
AUTOHEADER	= :

#
# Compiler arguments
#
CFLAGS		= -g -O2 -Dlinux 
EXTRACPPFLAGS	= -x c
LDFLAGS		= -L/usr/local/ssl/lib  
LIBTOOL		= $(SHELL) $(top_builddir)/libtool 
EXEEXT		= 

# Misc Compiling Stuff
CC	        = gcc
# version number is prefixed by a 0 for a better shared library version number
#
# ok, use libtool proper versioning:
LIBCURRENT  = 5
LIBREVISION = 8
LIBAGE      = 0
# generally, LIBCURRENT should stay the same unless major changes occur.
# Increment REVISION every release.  
# Increment AGE if new stuff is available.
LIB_LD_CMD      = $(LIBTOOL) --mode=link $(CC) $(CFLAGS) -rpath $(libdir) -version-info $(LIBCURRENT):$(LIBREVISION):$(LIBAGE) -o
LIB_EXTENSION   = la
LIB_VERSION     =
LIB_LDCONFIG_CMD = $(LIBTOOL) --mode=finish $(libdir)
LINK		= $(LIBTOOL) --mode=link $(CC)
# RANLIB 	= ranlib
RANLIB		= :

# libtool definitions
.SUFFIXES: .c .o .lo
.c.lo:
	$(LIBTOOL) --mode=compile $(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<
#
# snmpnetstat Makefile
#

top_builddir=../..
INSTALLBINPROGS=snmpnetstat$(EXEEXT)

#
# build info
#
SRCS=	inet.c inet6.c if.c main.c route.c winstub.c
OBJS=	inet.o inet6.o if.o main.o route.o winstub.o
LOBJS=	inet.lo inet6.lo if.lo main.lo route.lo winstub.lo
TARG= snmpnetstat$(EXEEXT)

CPPFLAGS=-I../../include -I../.. -I$(srcdir)/../.. -I$(srcdir)/../../include -I/usr/local/ssl/include 

USELIBS= ../../snmplib/libnetsnmp.$(LIB_EXTENSION)$(LIB_VERSION)
LIBS=	 ../../snmplib/libnetsnmp.$(LIB_EXTENSION)$(LIB_VERSION) -lcrypto -lm 

all: standardall

snmpnetstat$(EXEEXT): ${LOBJS} ${USELIBS}
	${LINK} -o $@ ${LOBJS} ${LOCAL_LIBS} ${LDFLAGS} ${LIBS}

#
# standard target definitions.  Set appropriate variables to make use of them.
#
# note: the strange use of the "it" variable is for shell parsing when
# there is no targets to install for that rule.
#

# the standard items to build: libraries, bins, and sbins
STANDARDTARGETS     =$(INSTALLLIBS) $(INSTALLBINPROGS) $(INSTALLSBINPROGS)
STANDARDCLEANTARGETS=$(INSTALLLIBS) $(INSTALLBINPROGS) $(INSTALLSBINPROGS) $(INSTALLUCDLIBS)

standardall: subdirs $(STANDARDTARGETS)

subdirs:
	@if test "$(SUBDIRS)" != ""; then \
		it="$(SUBDIRS)" ; \
		for i in $$it ; do       \
			echo "making all in `pwd`/$$i"; \
	                ( cd $$i ; $(MAKE) ) ; \
                        if test $$? != 0 ; then \
				exit 1 ; \
			fi  \
	        done \
	fi

install: installlocalheaders  \
         installlocallibs        \
         installlocalbin      installlocalsbin   \
         installsubdirs      $(OTHERINSTALL)

installprogs: installbin installsbin

#
# headers
#
# set INSTALLHEADERS to a list of things to install in each makefile.
# set INSTALLBUILTHEADERS to a list of things to install from builddir
# set INSTALLSUBDIRHEADERS and INSTALLSUBDIR to subdirectory headers
# set INSTALLSUBDIRHEADERS2 and INSTALLSUBDIR2 to more subdirectory headers
# set INSTALLBUILTSUBDIRHEADERS and INSTALLBUILTSUBDIR to a list from builddir
#
installheaders: installlocalheaders  installsubdirheaders

installlocalheaders:
	@if test "$(INSTALLHEADERS)" != "" ; then \
		echo creating directory $(includedir) ; \
		it="$(INSTALLHEADERS)" ; \
		$(SHELL) $(top_srcdir)/mkinstalldirs $(includedir) ; \
	        for i in $$it ; do \
			$(INSTALL) $(top_srcdir)/include/net-snmp/$$i $(includedir) ; \
	                echo "installing $$i in $(includedir)" ; \
	        done \
	fi
	@if test "$(INSTALLBUILTHEADERS)" != "" ; then \
		echo creating directory $(includedir) ; \
		it="$(INSTALLBUILTHEADERS)" ; \
		$(SHELL) $(top_srcdir)/mkinstalldirs $(includedir) ; \
	        for i in $$it ; do \
			$(INSTALL) $$i $(includedir) ; \
	                echo "installing $$i in $(includedir)" ; \
	        done \
	fi
	@if test "$(INCLUDESUBDIRHEADERS)" != "" ; then \
		echo creating directory $(includedir)/$(INCLUDESUBDIR) ; \
		it="$(INCLUDESUBDIRHEADERS)" ; \
		$(SHELL) $(top_srcdir)/mkinstalldirs $(includedir)/$(INCLUDESUBDIR) ; \
	        for i in $$it ; do \
			$(INSTALL) $(top_srcdir)/include/net-snmp/$(INCLUDESUBDIR)/$$i $(includedir)/$(INCLUDESUBDIR) ; \
	                echo "installing $$i in $(includedir)/$(INCLUDESUBDIR)" ; \
	        done \
	fi
	@if test "$(INCLUDESUBDIRHEADERS2)" != "" ; then \
		echo creating directory $(includedir)/$(INCLUDESUBDIR2) ; \
		it="$(INCLUDESUBDIRHEADERS2)" ; \
		$(SHELL) $(top_srcdir)/mkinstalldirs $(includedir)/$(INCLUDESUBDIR2) ; \
	        for i in $$it ; do \
			$(INSTALL) $(top_srcdir)/include/net-snmp/$(INCLUDESUBDIR2)/$$i $(includedir)/$(INCLUDESUBDIR2) ; \
	                echo "installing $$i in $(includedir)/$(INCLUDESUBDIR2)" ; \
	        done \
	fi
	@if test "$(INSTALLBUILTSUBDIRHEADERS)" != "" ; then \
		echo creating directory $(includedir)/$(INSTALLBUILTSUBDIR) ; \
		it="$(INSTALLBUILTSUBDIRHEADERS)" ; \
		$(SHELL) $(top_srcdir)/mkinstalldirs $(includedir)/$(INSTALLBUILTSUBDIR) ; \
	        for i in $$it ; do \
			$(INSTALL) $$i $(includedir)/$(INSTALLBUILTSUBDIR) ; \
	                echo "installing $$i in $(includedir)/$(INSTALLBUILTSUBDIR)" ; \
	        done \
	fi

installsubdirheaders:
	@if test "$(SUBDIRS)" != ""; then \
		it="$(SUBDIRS)" ; \
		for i in $$it ; do       \
			echo "making installheaders in `pwd`/$$i"; \
	                ( cd $$i ; $(MAKE) installheaders) ;   \
                        if test $$? != 0 ; then \
				exit 1 ; \
			fi  \
	        done \
	fi

installucdheaders:
	@if test "$(INSTALLUCDHEADERS)" != "" ; then \
		echo creating directory $(ucdincludedir) ; \
		it="$(INSTALLUCDHEADERS)" ; \
		$(SHELL) $(top_srcdir)/mkinstalldirs $(ucdincludedir) ; \
	        for i in $$it ; do \
			$(INSTALL) $(top_srcdir)/include/ucd-snmp/$$i $(ucdincludedir) ; \
	                echo "installing $$i in $(ucdincludedir)" ; \
	        done \
	fi

#
# libraries
#
# set INSTALLLIBS to a list of things to install in each makefile.
#
installlibs: installlocallibs  installsubdirlibs

installlocallibs: $(INSTALLLIBS)
	@if test "$(INSTALLLIBS)" != ""; then \
		it="$(INSTALLLIBS)" ; \
		$(SHELL) $(top_srcdir)/mkinstalldirs $(libdir) ; \
                $(INSTALL) $(INSTALLLIBS) $(libdir) ;              \
	        for i in $$it ; do    \
	                echo "installing $$i in $(libdir)"; \
	                $(RANLIB) $(libdir)/$$i ; \
	        done ; \
		$(LIB_LDCONFIG_CMD) ; \
	fi

installucdlibs: $(INSTALLUCDLIBS)
	@if test "$(INSTALLUCDLIBS)" != ""; then \
		it="$(INSTALLUCDLIBS)" ; \
		$(SHELL) $(top_srcdir)/mkinstalldirs $(libdir) ; \
                $(INSTALL) $(INSTALLUCDLIBS) $(libdir) ;              \
	        for i in $$it ; do    \
	                echo "installing $$i in $(libdir)"; \
	                $(RANLIB) $(libdir)/$$i ; \
	        done ; \
		$(LIB_LDCONFIG_CMD) ; \
	fi

installsubdirlibs:
	@if test "$(SUBDIRS)" != ""; then \
		it="$(SUBDIRS)" ; \
		for i in $$it ; do       \
			echo "making installlibs in `pwd`/$$i"; \
	                ( cd $$i ; $(MAKE) installlibs) ;   \
                        if test $$? != 0 ; then \
				exit 1 ; \
			fi  \
	        done \
	fi

#
# normal bin binaries
#
# set INSTALLBINPROGS to a list of things to install in each makefile.
#
installbin: installlocalbin installsubdirbin

installlocalbin: $(INSTALLBINPROGS)
	@if test "$(INSTALLBINPROGS) $(INSTALLBINSCRIPTS)" != " "; then \
		$(SHELL) $(top_srcdir)/mkinstalldirs $(bindir) ; \
		it="$(INSTALLBINPROGS) $(INSTALLBINSCRIPTS)" ; \
	        $(INSTALL) $(INSTALLBINPROGS) $(INSTALLBINSCRIPTS) $(bindir) ;              \
	        for i in $$it ; do   \
	                echo "installing $$i in $(bindir)"; \
	        done \
	fi

installsubdirbin:
	@if test "$(SUBDIRS)" != ""; then \
		it="$(SUBDIRS)" ; \
		for i in $$it ; do       \
			echo "making installbin in `pwd`/$$i"; \
	                ( cd $$i ; $(MAKE) installbin) ;   \
                        if test $$? != 0 ; then \
				exit 1 ; \
			fi  \
	        done \
	fi

#
# sbin binaries
#
# set INSTALLSBINPROGS to a list of things to install in each makefile.
#
installsbin: installlocalsbin installsubdirsbin

installlocalsbin: $(INSTALLSBINPROGS)
	@if test "$(INSTALLSBINPROGS)" != ""; then \
		it="$(INSTALLSBINPROGS)" ; \
		$(SHELL) $(top_srcdir)/mkinstalldirs $(sbindir) ; \
	        $(INSTALL) $(INSTALLSBINPROGS) $(sbindir) ;              \
	        for i in $$it ; do   \
	                echo "installing $$i in $(sbindir)"; \
	        done \
	fi

installsubdirsbin:
	@if test "$(SUBDIRS)" != ""; then \
		it="$(SUBDIRS)" ; \
		for i in $$it ; do       \
			echo "making installsbin in `pwd`/$$i"; \
	                ( cd $$i ; $(MAKE) installsbin) ;   \
                        if test $$? != 0 ; then \
				exit 1 ; \
			fi  \
	        done \
	fi

#
# general make install target for subdirs
#
installsubdirs:
	@if test "$(SUBDIRS)" != ""; then \
		it="$(SUBDIRS)" ; \
		for i in $$it ; do       \
			echo "making install in `pwd`/$$i"; \
	                ( cd $$i ; $(MAKE) install) ;   \
                        if test $$? != 0 ; then \
				exit 1 ; \
			fi  \
	        done \
	fi

#
# cleaning targets
#
clean: cleansubdirs $(OTHERCLEANTODOS)
	rm -f core ${OBJS} ${LOBJS} $(STANDARDCLEANTARGETS) $(OTHERCLEANTARGETS)
	rm -rf .libs

cleansubdirs:
	@if test "$(SUBDIRS)" != ""; then \
		it="$(SUBDIRS)" ; \
		for i in $$it ; do       \
			echo "making clean in `pwd`/$$i"; \
	                ( cd $$i ; $(MAKE) clean) ;   \
                        if test $$? != 0 ; then \
				exit 1 ; \
			fi  \
	        done \
	fi

lint:
	lint -nhx $(CSRCS)

#
# wacky dependency building.
#
depend: dependdirs
	@if test -f Makefile.depend ; then \
		makedepend `echo $(CPPFLAGS) | sed 's/-f[-a-z]*//g'` -o .lo $(srcdir)/*.c $(srcdir)/*/*.c ; \
	fi


nosysdepend: nosysdependdirs
	@if test -f Makefile.depend ; then \
		makedepend `echo $(CPPFLAGS) | sed 's/-f[-a-z]*//g'` -o .lo $(srcdir)/*.c $(srcdir)/*/*.c ; \
		perl -n -i.bak $(top_srcdir)/makenosysdepend.pl Makefile ; \
	fi

distdepend: nosysdepend distdependdirs
	@if test -f Makefile.depend ; then \
		perl $(top_srcdir)/makefileindepend.pl ; \
	fi

dependdirs:
	@if test "$(SUBDIRS)" != ""; then \
		it="$(SUBDIRS)" ; \
		for i in $$it ; do       \
			echo "making depend in `pwd`/$$i"; \
	                ( cd $$i ; $(MAKE) depend) ;   \
                        if test $$? != 0 ; then \
				exit 1 ; \
			fi  \
	        done \
	fi

nosysdependdirs:
	@if test "$(SUBDIRS)" != ""; then \
		it="$(SUBDIRS)" ; \
		for i in $$it ; do       \
			echo "making nosysdepend in `pwd`/$$i"; \
	                ( cd $$i ; $(MAKE) nosysdepend) ;   \
                        if test $$? != 0 ; then \
				exit 1 ; \
			fi  \
	        done \
	fi

distdependdirs:
	@if test "$(SUBDIRS)" != ""; then \
		it="$(SUBDIRS)" ; \
		for i in $$it ; do       \
			echo "making distdepend in `pwd`/$$i"; \
	                ( cd $$i ; $(MAKE) distdepend) ;   \
                        if test $$? != 0 ; then \
				exit 1 ; \
			fi  \
	        done \
	fi

# These aren't real targets, let gnu's make know that.
.PHONY: clean cleansubdirs lint \
	install installprogs installheaders installlibs \
	installbin installsbin installsubdirs \
	all subdirs standardall \
	depend nosysdepend distdepend dependdirs nosysdependdirs distdependdirs
# DO NOT DELETE THIS LINE -- make depend depends on it.

/usr/src/net-snmp/apps/snmpnetstat/if.lo: ../../include/net-snmp/net-snmp-config.h
/usr/src/net-snmp/apps/snmpnetstat/if.lo: ../../include/net-snmp/system/linux.h
/usr/src/net-snmp/apps/snmpnetstat/if.lo: ../../include/net-snmp/system/sysv.h
/usr/src/net-snmp/apps/snmpnetstat/if.lo: ../../include/net-snmp/system/generic.h
/usr/src/net-snmp/apps/snmpnetstat/if.lo: ../../include/net-snmp/machine/generic.h
/usr/src/net-snmp/apps/snmpnetstat/if.lo:  main.h
/usr/src/net-snmp/apps/snmpnetstat/if.lo: ../../include/net-snmp/net-snmp-includes.h
/usr/src/net-snmp/apps/snmpnetstat/if.lo: ../../include/net-snmp/definitions.h
/usr/src/net-snmp/apps/snmpnetstat/if.lo: ../../include/net-snmp/types.h
/usr/src/net-snmp/apps/snmpnetstat/if.lo: ../../include/net-snmp/library/snmp_api.h
/usr/src/net-snmp/apps/snmpnetstat/if.lo: ../../include/net-snmp/library/asn1.h
/usr/src/net-snmp/apps/snmpnetstat/if.lo: ../../include/net-snmp/library/snmp_impl.h
/usr/src/net-snmp/apps/snmpnetstat/if.lo: ../../include/net-snmp/library/snmp.h
/usr/src/net-snmp/apps/snmpnetstat/if.lo: ../../include/net-snmp/library/snmp-tc.h
/usr/src/net-snmp/apps/snmpnetstat/if.lo: ../../include/net-snmp/utilities.h
/usr/src/net-snmp/apps/snmpnetstat/if.lo: ../../include/net-snmp/library/snmp_client.h
/usr/src/net-snmp/apps/snmpnetstat/if.lo: ../../include/net-snmp/library/getopt.h
/usr/src/net-snmp/apps/snmpnetstat/if.lo: ../../include/net-snmp/library/system.h
/usr/src/net-snmp/apps/snmpnetstat/if.lo: ../../include/net-snmp/library/tools.h
/usr/src/net-snmp/apps/snmpnetstat/if.lo: ../../include/net-snmp/library/int64.h
/usr/src/net-snmp/apps/snmpnetstat/if.lo: ../../include/net-snmp/library/mt_support.h
/usr/src/net-snmp/apps/snmpnetstat/if.lo: ../../include/net-snmp/library/snmp_alarm.h
/usr/src/net-snmp/apps/snmpnetstat/if.lo: ../../include/net-snmp/library/data_list.h
/usr/src/net-snmp/apps/snmpnetstat/if.lo: ../../include/net-snmp/library/callback.h
/usr/src/net-snmp/apps/snmpnetstat/if.lo: ../../include/net-snmp/library/oid_stash.h
/usr/src/net-snmp/apps/snmpnetstat/if.lo: ../../include/net-snmp/library/check_varbind.h
/usr/src/net-snmp/apps/snmpnetstat/if.lo: ../../include/net-snmp/version.h
/usr/src/net-snmp/apps/snmpnetstat/if.lo: ../../include/net-snmp/session_api.h
/usr/src/net-snmp/apps/snmpnetstat/if.lo: ../../include/net-snmp/library/snmp_transport.h
/usr/src/net-snmp/apps/snmpnetstat/if.lo: ../../include/net-snmp/library/snmpCallbackDomain.h
/usr/src/net-snmp/apps/snmpnetstat/if.lo: ../../include/net-snmp/library/snmpUnixDomain.h
/usr/src/net-snmp/apps/snmpnetstat/if.lo: ../../include/net-snmp/library/snmpUDPDomain.h
/usr/src/net-snmp/apps/snmpnetstat/if.lo: ../../include/net-snmp/library/snmpTCPDomain.h
/usr/src/net-snmp/apps/snmpnetstat/if.lo: ../../include/net-snmp/library/snmpUDPIPv6Domain.h
/usr/src/net-snmp/apps/snmpnetstat/if.lo: ../../include/net-snmp/library/snmpTCPIPv6Domain.h
/usr/src/net-snmp/apps/snmpnetstat/if.lo: ../../include/net-snmp/library/snmpIPXDomain.h
/usr/src/net-snmp/apps/snmpnetstat/if.lo: ../../include/net-snmp/library/ucd_compat.h
/usr/src/net-snmp/apps/snmpnetstat/if.lo: ../../include/net-snmp/pdu_api.h
/usr/src/net-snmp/apps/snmpnetstat/if.lo: ../../include/net-snmp/mib_api.h
/usr/src/net-snmp/apps/snmpnetstat/if.lo: ../../include/net-snmp/library/mib.h
/usr/src/net-snmp/apps/snmpnetstat/if.lo: ../../include/net-snmp/library/parse.h
/usr/src/net-snmp/apps/snmpnetstat/if.lo: ../../include/net-snmp/varbind_api.h
/usr/src/net-snmp/apps/snmpnetstat/if.lo: ../../include/net-snmp/config_api.h
/usr/src/net-snmp/apps/snmpnetstat/if.lo: ../../include/net-snmp/library/read_config.h
/usr/src/net-snmp/apps/snmpnetstat/if.lo: ../../include/net-snmp/library/default_store.h
/usr/src/net-snmp/apps/snmpnetstat/if.lo: ../../include/net-snmp/library/snmp_parse_args.h
/usr/src/net-snmp/apps/snmpnetstat/if.lo: ../../include/net-snmp/library/snmp_enum.h
/usr/src/net-snmp/apps/snmpnetstat/if.lo: ../../include/net-snmp/library/vacm.h
/usr/src/net-snmp/apps/snmpnetstat/if.lo: ../../include/net-snmp/output_api.h
/usr/src/net-snmp/apps/snmpnetstat/if.lo: ../../include/net-snmp/library/snmp_debug.h
/usr/src/net-snmp/apps/snmpnetstat/if.lo: ../../include/net-snmp/library/snmp_logging.h
/usr/src/net-snmp/apps/snmpnetstat/if.lo: ../../include/net-snmp/snmpv3_api.h
/usr/src/net-snmp/apps/snmpnetstat/if.lo: ../../include/net-snmp/library/snmpv3.h
/usr/src/net-snmp/apps/snmpnetstat/if.lo: ../../include/net-snmp/library/transform_oids.h
/usr/src/net-snmp/apps/snmpnetstat/if.lo: ../../include/net-snmp/library/keytools.h
/usr/src/net-snmp/apps/snmpnetstat/if.lo: ../../include/net-snmp/library/scapi.h
/usr/src/net-snmp/apps/snmpnetstat/if.lo: ../../include/net-snmp/library/lcd_time.h
/usr/src/net-snmp/apps/snmpnetstat/if.lo: ../../include/net-snmp/library/snmp_secmod.h
/usr/src/net-snmp/apps/snmpnetstat/if.lo: ../../include/net-snmp/library/snmpv3-security-includes.h
/usr/src/net-snmp/apps/snmpnetstat/if.lo: ../../include/net-snmp/library/snmpusm.h
/usr/src/net-snmp/apps/snmpnetstat/if.lo: netstat.h
/usr/src/net-snmp/apps/snmpnetstat/inet6.lo: ../../include/net-snmp/net-snmp-config.h
/usr/src/net-snmp/apps/snmpnetstat/inet6.lo: ../../include/net-snmp/system/linux.h
/usr/src/net-snmp/apps/snmpnetstat/inet6.lo: ../../include/net-snmp/system/sysv.h
/usr/src/net-snmp/apps/snmpnetstat/inet6.lo: ../../include/net-snmp/system/generic.h
/usr/src/net-snmp/apps/snmpnetstat/inet6.lo: ../../include/net-snmp/machine/generic.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo: ../../include/net-snmp/net-snmp-config.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo: ../../include/net-snmp/system/linux.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo: ../../include/net-snmp/system/sysv.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo: ../../include/net-snmp/system/generic.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo: ../../include/net-snmp/machine/generic.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo:  main.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo: ../../include/net-snmp/net-snmp-includes.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo: ../../include/net-snmp/definitions.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo: ../../include/net-snmp/types.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo: ../../include/net-snmp/library/snmp_api.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo: ../../include/net-snmp/library/asn1.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo: ../../include/net-snmp/library/snmp_impl.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo: ../../include/net-snmp/library/snmp.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo: ../../include/net-snmp/library/snmp-tc.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo: ../../include/net-snmp/utilities.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo: ../../include/net-snmp/library/snmp_client.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo: ../../include/net-snmp/library/getopt.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo: ../../include/net-snmp/library/system.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo: ../../include/net-snmp/library/tools.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo: ../../include/net-snmp/library/int64.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo: ../../include/net-snmp/library/mt_support.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo: ../../include/net-snmp/library/snmp_alarm.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo: ../../include/net-snmp/library/data_list.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo: ../../include/net-snmp/library/callback.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo: ../../include/net-snmp/library/oid_stash.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo: ../../include/net-snmp/library/check_varbind.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo: ../../include/net-snmp/version.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo: ../../include/net-snmp/session_api.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo: ../../include/net-snmp/library/snmp_transport.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo: ../../include/net-snmp/library/snmpCallbackDomain.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo: ../../include/net-snmp/library/snmpUnixDomain.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo: ../../include/net-snmp/library/snmpUDPDomain.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo: ../../include/net-snmp/library/snmpTCPDomain.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo: ../../include/net-snmp/library/snmpUDPIPv6Domain.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo: ../../include/net-snmp/library/snmpTCPIPv6Domain.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo: ../../include/net-snmp/library/snmpIPXDomain.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo: ../../include/net-snmp/library/ucd_compat.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo: ../../include/net-snmp/pdu_api.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo: ../../include/net-snmp/mib_api.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo: ../../include/net-snmp/library/mib.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo: ../../include/net-snmp/library/parse.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo: ../../include/net-snmp/varbind_api.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo: ../../include/net-snmp/config_api.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo: ../../include/net-snmp/library/read_config.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo: ../../include/net-snmp/library/default_store.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo: ../../include/net-snmp/library/snmp_parse_args.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo: ../../include/net-snmp/library/snmp_enum.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo: ../../include/net-snmp/library/vacm.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo: ../../include/net-snmp/output_api.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo: ../../include/net-snmp/library/snmp_debug.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo: ../../include/net-snmp/library/snmp_logging.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo: ../../include/net-snmp/snmpv3_api.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo: ../../include/net-snmp/library/snmpv3.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo: ../../include/net-snmp/library/transform_oids.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo: ../../include/net-snmp/library/keytools.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo: ../../include/net-snmp/library/scapi.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo: ../../include/net-snmp/library/lcd_time.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo: ../../include/net-snmp/library/snmp_secmod.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo: ../../include/net-snmp/library/snmpv3-security-includes.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo: ../../include/net-snmp/library/snmpusm.h
/usr/src/net-snmp/apps/snmpnetstat/inet.lo: netstat.h
/usr/src/net-snmp/apps/snmpnetstat/main.lo: ../../include/net-snmp/net-snmp-config.h
/usr/src/net-snmp/apps/snmpnetstat/main.lo: ../../include/net-snmp/system/linux.h
/usr/src/net-snmp/apps/snmpnetstat/main.lo: ../../include/net-snmp/system/sysv.h
/usr/src/net-snmp/apps/snmpnetstat/main.lo: ../../include/net-snmp/system/generic.h
/usr/src/net-snmp/apps/snmpnetstat/main.lo: ../../include/net-snmp/machine/generic.h
/usr/src/net-snmp/apps/snmpnetstat/main.lo: ../../include/net-snmp/utilities.h
/usr/src/net-snmp/apps/snmpnetstat/main.lo: ../../include/net-snmp/types.h
/usr/src/net-snmp/apps/snmpnetstat/main.lo: ../../include/net-snmp/definitions.h
/usr/src/net-snmp/apps/snmpnetstat/main.lo: ../../include/net-snmp/library/snmp_api.h
/usr/src/net-snmp/apps/snmpnetstat/main.lo: ../../include/net-snmp/library/asn1.h
/usr/src/net-snmp/apps/snmpnetstat/main.lo: ../../include/net-snmp/library/snmp_impl.h
/usr/src/net-snmp/apps/snmpnetstat/main.lo: ../../include/net-snmp/library/snmp.h
/usr/src/net-snmp/apps/snmpnetstat/main.lo: ../../include/net-snmp/library/snmp-tc.h
/usr/src/net-snmp/apps/snmpnetstat/main.lo: ../../include/net-snmp/library/snmp_client.h
/usr/src/net-snmp/apps/snmpnetstat/main.lo: ../../include/net-snmp/library/getopt.h
/usr/src/net-snmp/apps/snmpnetstat/main.lo: ../../include/net-snmp/library/system.h
/usr/src/net-snmp/apps/snmpnetstat/main.lo: ../../include/net-snmp/library/tools.h
/usr/src/net-snmp/apps/snmpnetstat/main.lo: ../../include/net-snmp/library/int64.h
/usr/src/net-snmp/apps/snmpnetstat/main.lo: ../../include/net-snmp/library/mt_support.h
/usr/src/net-snmp/apps/snmpnetstat/main.lo: ../../include/net-snmp/library/snmp_alarm.h
/usr/src/net-snmp/apps/snmpnetstat/main.lo: ../../include/net-snmp/library/data_list.h
/usr/src/net-snmp/apps/snmpnetstat/main.lo: ../../include/net-snmp/library/callback.h
/usr/src/net-snmp/apps/snmpnetstat/main.lo: ../../include/net-snmp/library/oid_stash.h
/usr/src/net-snmp/apps/snmpnetstat/main.lo: ../../include/net-snmp/library/check_varbind.h
/usr/src/net-snmp/apps/snmpnetstat/main.lo: ../../include/net-snmp/version.h
/usr/src/net-snmp/apps/snmpnetstat/main.lo: ../../include/net-snmp/net-snmp-includes.h
/usr/src/net-snmp/apps/snmpnetstat/main.lo: ../../include/net-snmp/session_api.h
/usr/src/net-snmp/apps/snmpnetstat/main.lo: ../../include/net-snmp/library/snmp_transport.h
/usr/src/net-snmp/apps/snmpnetstat/main.lo: ../../include/net-snmp/library/snmpCallbackDomain.h
/usr/src/net-snmp/apps/snmpnetstat/main.lo: ../../include/net-snmp/library/snmpUnixDomain.h
/usr/src/net-snmp/apps/snmpnetstat/main.lo: ../../include/net-snmp/library/snmpUDPDomain.h
/usr/src/net-snmp/apps/snmpnetstat/main.lo: ../../include/net-snmp/library/snmpTCPDomain.h
/usr/src/net-snmp/apps/snmpnetstat/main.lo: ../../include/net-snmp/library/snmpUDPIPv6Domain.h
/usr/src/net-snmp/apps/snmpnetstat/main.lo: ../../include/net-snmp/library/snmpTCPIPv6Domain.h
/usr/src/net-snmp/apps/snmpnetstat/main.lo: ../../include/net-snmp/library/snmpIPXDomain.h
/usr/src/net-snmp/apps/snmpnetstat/main.lo: ../../include/net-snmp/library/ucd_compat.h
/usr/src/net-snmp/apps/snmpnetstat/main.lo: ../../include/net-snmp/pdu_api.h
/usr/src/net-snmp/apps/snmpnetstat/main.lo: ../../include/net-snmp/mib_api.h
/usr/src/net-snmp/apps/snmpnetstat/main.lo: ../../include/net-snmp/library/mib.h
/usr/src/net-snmp/apps/snmpnetstat/main.lo: ../../include/net-snmp/library/parse.h
/usr/src/net-snmp/apps/snmpnetstat/main.lo: ../../include/net-snmp/varbind_api.h
/usr/src/net-snmp/apps/snmpnetstat/main.lo: ../../include/net-snmp/config_api.h
/usr/src/net-snmp/apps/snmpnetstat/main.lo: ../../include/net-snmp/library/read_config.h
/usr/src/net-snmp/apps/snmpnetstat/main.lo: ../../include/net-snmp/library/default_store.h
/usr/src/net-snmp/apps/snmpnetstat/main.lo: ../../include/net-snmp/library/snmp_parse_args.h
/usr/src/net-snmp/apps/snmpnetstat/main.lo: ../../include/net-snmp/library/snmp_enum.h
/usr/src/net-snmp/apps/snmpnetstat/main.lo: ../../include/net-snmp/library/vacm.h
/usr/src/net-snmp/apps/snmpnetstat/main.lo: ../../include/net-snmp/output_api.h
/usr/src/net-snmp/apps/snmpnetstat/main.lo: ../../include/net-snmp/library/snmp_debug.h
/usr/src/net-snmp/apps/snmpnetstat/main.lo: ../../include/net-snmp/library/snmp_logging.h
/usr/src/net-snmp/apps/snmpnetstat/main.lo: ../../include/net-snmp/snmpv3_api.h
/usr/src/net-snmp/apps/snmpnetstat/main.lo: ../../include/net-snmp/library/snmpv3.h
/usr/src/net-snmp/apps/snmpnetstat/main.lo: ../../include/net-snmp/library/transform_oids.h
/usr/src/net-snmp/apps/snmpnetstat/main.lo: ../../include/net-snmp/library/keytools.h
/usr/src/net-snmp/apps/snmpnetstat/main.lo: ../../include/net-snmp/library/scapi.h
/usr/src/net-snmp/apps/snmpnetstat/main.lo: ../../include/net-snmp/library/lcd_time.h
/usr/src/net-snmp/apps/snmpnetstat/main.lo: ../../include/net-snmp/library/snmp_secmod.h
/usr/src/net-snmp/apps/snmpnetstat/main.lo: ../../include/net-snmp/library/snmpv3-security-includes.h
/usr/src/net-snmp/apps/snmpnetstat/main.lo: ../../include/net-snmp/library/snmpusm.h
/usr/src/net-snmp/apps/snmpnetstat/main.lo: netstat.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo: ../../include/net-snmp/net-snmp-config.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo: ../../include/net-snmp/system/linux.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo: ../../include/net-snmp/system/sysv.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo: ../../include/net-snmp/system/generic.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo: ../../include/net-snmp/machine/generic.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo:  main.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo: ../../include/net-snmp/net-snmp-includes.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo: ../../include/net-snmp/definitions.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo: ../../include/net-snmp/types.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo: ../../include/net-snmp/library/snmp_api.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo: ../../include/net-snmp/library/asn1.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo: ../../include/net-snmp/library/snmp_impl.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo: ../../include/net-snmp/library/snmp.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo: ../../include/net-snmp/library/snmp-tc.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo: ../../include/net-snmp/utilities.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo: ../../include/net-snmp/library/snmp_client.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo: ../../include/net-snmp/library/getopt.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo: ../../include/net-snmp/library/system.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo: ../../include/net-snmp/library/tools.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo: ../../include/net-snmp/library/int64.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo: ../../include/net-snmp/library/mt_support.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo: ../../include/net-snmp/library/snmp_alarm.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo: ../../include/net-snmp/library/data_list.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo: ../../include/net-snmp/library/callback.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo: ../../include/net-snmp/library/oid_stash.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo: ../../include/net-snmp/library/check_varbind.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo: ../../include/net-snmp/version.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo: ../../include/net-snmp/session_api.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo: ../../include/net-snmp/library/snmp_transport.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo: ../../include/net-snmp/library/snmpCallbackDomain.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo: ../../include/net-snmp/library/snmpUnixDomain.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo: ../../include/net-snmp/library/snmpUDPDomain.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo: ../../include/net-snmp/library/snmpTCPDomain.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo: ../../include/net-snmp/library/snmpUDPIPv6Domain.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo: ../../include/net-snmp/library/snmpTCPIPv6Domain.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo: ../../include/net-snmp/library/snmpIPXDomain.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo: ../../include/net-snmp/library/ucd_compat.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo: ../../include/net-snmp/pdu_api.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo: ../../include/net-snmp/mib_api.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo: ../../include/net-snmp/library/mib.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo: ../../include/net-snmp/library/parse.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo: ../../include/net-snmp/varbind_api.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo: ../../include/net-snmp/config_api.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo: ../../include/net-snmp/library/read_config.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo: ../../include/net-snmp/library/default_store.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo: ../../include/net-snmp/library/snmp_parse_args.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo: ../../include/net-snmp/library/snmp_enum.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo: ../../include/net-snmp/library/vacm.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo: ../../include/net-snmp/output_api.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo: ../../include/net-snmp/library/snmp_debug.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo: ../../include/net-snmp/library/snmp_logging.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo: ../../include/net-snmp/snmpv3_api.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo: ../../include/net-snmp/library/snmpv3.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo: ../../include/net-snmp/library/transform_oids.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo: ../../include/net-snmp/library/keytools.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo: ../../include/net-snmp/library/scapi.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo: ../../include/net-snmp/library/lcd_time.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo: ../../include/net-snmp/library/snmp_secmod.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo: ../../include/net-snmp/library/snmpv3-security-includes.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo: ../../include/net-snmp/library/snmpusm.h
/usr/src/net-snmp/apps/snmpnetstat/route.lo: netstat.h
/usr/src/net-snmp/apps/snmpnetstat/winstub.lo: ../../include/net-snmp/net-snmp-config.h
/usr/src/net-snmp/apps/snmpnetstat/winstub.lo: ../../include/net-snmp/system/linux.h
/usr/src/net-snmp/apps/snmpnetstat/winstub.lo: ../../include/net-snmp/system/sysv.h
/usr/src/net-snmp/apps/snmpnetstat/winstub.lo: ../../include/net-snmp/system/generic.h
/usr/src/net-snmp/apps/snmpnetstat/winstub.lo: ../../include/net-snmp/machine/generic.h
