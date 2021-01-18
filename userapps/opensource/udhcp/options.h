/* options.h */
#ifndef _OPTIONS_H
#define _OPTIONS_H

#include "packet.h"

#define TYPE_MASK	0x0F

enum {
	OPTION_IP=1,
	OPTION_IP_PAIR,
	OPTION_STRING,
	OPTION_BOOLEAN,
	OPTION_U8,
	OPTION_U16,
	OPTION_S16,
	OPTION_U32,
	OPTION_S32
};

#define OPTION_LIST	0x80

struct dhcp_option {
	char name[10];
	char flags;
	char code;
};

extern struct dhcp_option options[];
extern int option_lengths[];

unsigned char *get_option(struct dhcpMessage *packet, int code);
int end_option(unsigned char *optionptr);
int add_option_string(unsigned char *optionptr, unsigned char *string);
int add_simple_option(unsigned char *optionptr, unsigned char code, u_int32_t data);
struct option_set *find_option(struct option_set *opt_list, char code);
void attach_option(struct option_set **opt_list, struct dhcp_option *option, char *buffer, int length);

// brcm
extern char session_path[];

// brcm
#define _PATH_RESOLV	 "/var/fyi/sys/dns"
#define _PATH_GW	 "/var/fyi/sys/gateway"
#define _PATH_SYS_DIR	 "/var/fyi/sys"

#define _PATH_WAN_DIR	"/proc/var/fyi/wan"
#define _PATH_MSG	"daemonstatus"
#define _PATH_IP	"ipaddress"
#define _PATH_MASK	"subnetmask"
#define _PATH_PID	"pid"

#endif
