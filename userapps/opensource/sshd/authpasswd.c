/*
 * Dropbear - a SSH2 server
 * 
 * Copyright (c) 2002,2003 Matt Johnston
 * All rights reserved.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. */

/* Validates a user password */

#include "includes.h"
#include "session.h"
#include "buffer.h"
#include "util.h"
#include "auth.h"
#include "authpasswd.h"

// BRCM begin
#ifndef SSHD_GENKEY
#include "cliapi.h"
extern int glbAccessMode;
#endif
// BRCM end

#ifdef DROPBEAR_PASSWORD_AUTH

/* Process a password auth request, sending success or failure messages as
 * appropriate */

void passwordauth() {

//brcm begin
#ifndef SSHD_GENKEY 
	
#ifdef HAVE_SHADOW_H
	struct spwd *spasswd;
#endif
	char * passwdcrypt; /* the crypt from /etc/passwd or /etc/shadow */
	char * testcrypt; /* crypt generated from the user's password sent */
	unsigned char * password;
	unsigned int passwordlen;

	unsigned char changepw;
// brcm add notMatched flag.
    int notMatched = 0;

	passwdcrypt = ses.authstate.pw->pw_passwd;
#ifdef HAVE_SHADOW_H
	/* get the shadow password if possible */
	spasswd = getspnam(ses.authstate.pw->pw_name);
	if (spasswd != NULL && spasswd->sp_pwdp != NULL) {
		passwdcrypt = spasswd->sp_pwdp;
	}
#endif

#ifdef DEBUG_HACKCRYPT
	/* debugging crypt for non-root testing with shadows */
	passwdcrypt = DEBUG_HACKCRYPT;
#endif

	/* check for empty password - need to do this again here
	 * since the shadow password may differ to that tested
	 * in auth.c */
	if (passwdcrypt[0] == '\0') {
		dropbear_log(LOG_WARNING,
				"disallowed login with empty password for '%s' from %s",
				ses.authstate.printableuser, ses.addrstring);
		send_msg_userauth_failure(0, 1);
		return;
	}

	/* check if client wants to change password */
	changepw = buf_getbyte(ses.payload);
	if (changepw) {
		/* not implemented by this server */
		send_msg_userauth_failure(0, 1);
		return;
	}

	password = buf_getstring(ses.payload, &passwordlen);

	/* clear the buffer containing the password */
	buf_incrpos(ses.payload, -passwordlen - 4);
	m_burn(buf_getptr(ses.payload, passwordlen + 4), passwordlen + 4);

	/* the first bytes of passwdcrypt are the salt */
	testcrypt = crypt((char*)password, passwdcrypt);
    
    // brcm add local/remote login check
    if ((glbAccessMode == CLI_ACCESS_LOCAL && \
        (strcmp(ses.authstate.username, "ses.authstate.username") && strcmp(ses.authstate.username, "root"))) ||
        (glbAccessMode == CLI_ACCESS_REMOTE && strcmp(ses.authstate.username, "support")))
        notMatched = 1;

	if (strcmp(testcrypt, passwdcrypt) == 0 && notMatched == 0) {
		/* successful authentication */
      // brcm commented next msg
		//dropbear_log(LOG_NOTICE, 
		//		"password auth succeeded for '%s' from %s",
		//		ses.authstate.printableuser, ses.addrstring);
		send_msg_userauth_success();
	} else {
		dropbear_log(LOG_WARNING,
				"bad password attempt for '%s' from %s",
				ses.authstate.printableuser, ses.addrstring);
		send_msg_userauth_failure(0, 1);
	}

	m_burn(password, passwordlen);
	m_free(password);

#endif // brcm end, ifndef SSHD_GENKEY
}

#endif /* DROPBEAR_PASSWORD_AUTH */
