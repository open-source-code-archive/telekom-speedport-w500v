/*
 * ip_vs_proto.c: transport protocol load balancing support for IPVS
 *
 * Version:     $Id: ip_vs_proto.c,v 1.1.1.1 2006/01/25 03:57:12 root Exp $
 *
 * Authors:     Wensong Zhang <wensong@linuxvirtualserver.org>
 *              Julian Anastasov <ja@ssi.bg>
 *
 *              This program is free software; you can redistribute it and/or
 *              modify it under the terms of the GNU General Public License
 *              as published by the Free Software Foundation; either version
 *              2 of the License, or (at your option) any later version.
 *
 * Changes:
 *
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/skbuff.h>
#include <linux/in.h>
#include <linux/ip.h>
#include <net/protocol.h>
#include <net/tcp.h>
#include <net/udp.h>
#include <asm/system.h>
#include <linux/stat.h>
#include <linux/proc_fs.h>

#include <net/ip_vs.h>


/*
 * IPVS protocols can only be registered/unregistered when the ipvs
 * module is loaded/unloaded, so no lock is needed in accessing the
 * ipvs protocol table.
 */

#define IP_VS_PROTO_TAB_SIZE		32	/* must be power of 2 */
#define IP_VS_PROTO_HASH(proto)		((proto) & (IP_VS_PROTO_TAB_SIZE-1))

static struct ip_vs_protocol *ip_vs_proto_table[IP_VS_PROTO_TAB_SIZE];


/*
 *	register an ipvs protocol
 */
int register_ip_vs_protocol(struct ip_vs_protocol *pp)
{
	unsigned hash = IP_VS_PROTO_HASH(pp->protocol);

	pp->next = ip_vs_proto_table[hash];
	ip_vs_proto_table[hash] = pp;

	if (pp->init != NULL)
		pp->init(pp);

	return 0;
}


/*
 *	unregister an ipvs protocol
 */
int unregister_ip_vs_protocol(struct ip_vs_protocol *pp)
{
	struct ip_vs_protocol **pp_p;
	unsigned hash = IP_VS_PROTO_HASH(pp->protocol);

	pp_p = &ip_vs_proto_table[hash];
	for (; *pp_p; pp_p = &(*pp_p)->next) {
		if (*pp_p == pp) {
			*pp_p = pp->next;
			if (pp->exit != NULL)
				pp->exit(pp);
			return 0;
		}
	}

	return -ESRCH;
}


/*
 *	get ip_vs_protocol object by its proto.
 */
struct ip_vs_protocol * ip_vs_proto_get(unsigned short proto)
{
	struct ip_vs_protocol *pp;
	unsigned hash = IP_VS_PROTO_HASH(proto);

	for (pp = ip_vs_proto_table[hash]; pp; pp = pp->next) {
		if (pp->protocol == proto)
			return pp;
	}

	return NULL;
}


/*
 *	Propagate event for state change to all protocols
 */
void ip_vs_protocol_timeout_change(int flags)
{
	struct ip_vs_protocol *pp;
	int i;

	for (i = 0; i < IP_VS_PROTO_TAB_SIZE; i++) {
		for (pp = ip_vs_proto_table[i]; pp; pp = pp->next) {
			if (pp->timeout_change)
				pp->timeout_change(pp, flags);
		}
	}
}


int *
ip_vs_create_timeout_table(int *table, int size)
{
	int *t;

	t = kmalloc(size, GFP_ATOMIC);
	if (t == NULL)
		return NULL;
	memcpy(t, table, size);
	return t;
}


/*
 *	Set timeout value for state specified by name
 */
int
ip_vs_set_state_timeout(int *table, int num, char **names, char *name, int to)
{
	int i;

	if (!table || !name || !to)
		return -EINVAL;

	for (i = 0; i < num; i++) {
		if (strcmp(names[i], name))
			continue;
		table[i] = to * HZ;
		return 0;
	}
	return -ENOENT;
}


const char * ip_vs_state_name(__u16 proto, int state)
{
	struct ip_vs_protocol *pp = ip_vs_proto_get(proto);

	if (pp == NULL || pp->state_name == NULL)
		return "ERR!";
	return pp->state_name(state);
}


void
ip_vs_tcpudp_debug_packet(struct ip_vs_protocol *pp,
			  const struct sk_buff *skb,
			  int offset,
			  const char *msg)
{
	char buf[128];
	__u16 ports[2];
	struct iphdr iph;

	if (skb_copy_bits(skb, offset, &iph, sizeof(iph)) < 0)
		sprintf(buf, "%s TRUNCATED", pp->name);
	else if (iph.frag_off & __constant_htons(IP_OFFSET))
		sprintf(buf, "%s %u.%u.%u.%u->%u.%u.%u.%u frag",
			pp->name, NIPQUAD(iph.saddr),
			NIPQUAD(iph.daddr));
	else if (skb_copy_bits(skb, offset + iph.ihl*4, ports, sizeof(ports)) < 0)
		sprintf(buf, "%s TRUNCATED %u.%u.%u.%u->%u.%u.%u.%u",
			pp->name,
			NIPQUAD(iph.saddr),
			NIPQUAD(iph.daddr));
	else
		sprintf(buf, "%s %u.%u.%u.%u:%u->%u.%u.%u.%u:%u",
			pp->name,
			NIPQUAD(iph.saddr),
			ntohs(ports[0]),
			NIPQUAD(iph.daddr),
			ntohs(ports[1]));

	printk(KERN_DEBUG "IPVS: %s: %s\n", msg, buf);
}


int ip_vs_protocol_init(void)
{
	char protocols[64];
#define REGISTER_PROTOCOL(p)			\
	do {					\
		register_ip_vs_protocol(p);	\
		strcat(protocols, ", ");	\
		strcat(protocols, (p)->name);	\
	} while (0)

	protocols[0] = '\0';
	protocols[2] = '\0';
#ifdef CONFIG_IP_VS_PROTO_TCP
	REGISTER_PROTOCOL(&ip_vs_protocol_tcp);
#endif
#ifdef CONFIG_IP_VS_PROTO_UDP
	REGISTER_PROTOCOL(&ip_vs_protocol_udp);
#endif
#ifdef CONFIG_IP_VS_PROTO_ICMP
	REGISTER_PROTOCOL(&ip_vs_protocol_icmp);
#endif
#ifdef CONFIG_IP_VS_PROTO_AH
	REGISTER_PROTOCOL(&ip_vs_protocol_ah);
#endif
#ifdef CONFIG_IP_VS_PROTO_ESP
	REGISTER_PROTOCOL(&ip_vs_protocol_esp);
#endif
	IP_VS_INFO("Registered protocols (%s)\n", &protocols[2]);

	return 0;
}


void ip_vs_protocol_cleanup(void)
{
	struct ip_vs_protocol *pp;
	int i;

	/* unregister all the ipvs protocols */
	for (i = 0; i < IP_VS_PROTO_TAB_SIZE; i++) {
		while ((pp = ip_vs_proto_table[i]) != NULL)
			unregister_ip_vs_protocol(pp);
	}
}
