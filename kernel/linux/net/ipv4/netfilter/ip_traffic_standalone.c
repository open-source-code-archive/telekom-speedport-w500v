/* This file contains all the functions required for the standalone
   ip_traffic module.

   These are not required by the compatibility layer.
*/

/* (c) 2005 Echo Licenced under the GNU General
   Public Licence. */

#include <linux/config.h>
#include <linux/types.h>
#include <linux/ip.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/module.h>
#include <linux/skbuff.h>
#include <linux/proc_fs.h>
#ifdef CONFIG_SYSCTL
#include <linux/sysctl.h>
#endif
#include <net/checksum.h>
#include <net/ip.h>


#include <linux/netfilter_ipv4/traffic_defs.h>
#include <linux/netfilter_ipv4/ip_conntrack.h>

#if 0
#define DEBUGP printk
#else
#define DEBUGP(format, args...)
#endif

#define ECHO_DEBUG 0

struct module *ip_traffic_module = THIS_MODULE;
MODULE_LICENSE ("GPL");

#define MEGA_BYTE	0xFFF00000	//Mega byte
#define MEGA_BYTE_MASK	0x000FFFFF

unsigned int traffic_bytes = 0;	// means 0MB
unsigned int traffic_tmp = 0;	//use to temporaly store the bytes less than 1 M

extern struct list_head traffic_config_list_head;

static int
list_traffics (char *buffer, char **start, off_t offset, int length)
{
  int len = 0;
  int i = 0;
  const struct list_head *__t = &traffic_config_list_head;

#define BUFFSIZE 1024
  char *tmp = kmalloc (BUFFSIZE, GFP_KERNEL);
  if (tmp == NULL)
    {
      printk ("kernel malloc memory failed.\n");
      return 0;
    }
  tmp[0] = 0;

  //Note:
  /*
   * This simple implementation can only work in condition that data needed to show and
   * configure is less than 4K.
   * If the assumption is not true, then you should deal with the parameters start&offset
   * You can find some helps in linux/fs/proc/generic.c about line 65. 
   */

  sprintf (tmp, "%sthrough_bytes(MB)=%d\n", tmp, traffic_bytes);
  do
    {
      __t = __t->next;
      if (__t == (&traffic_config_list_head))
	{
	  __t = NULL;
	  break;
	}
      i++;
      snprintf (tmp, BUFFSIZE, "%sip=%d\tlimit=%d\tblock=%d\n", tmp,
		((const ptraffic_config_t) __t)->ip_address,
		((const ptraffic_config_t) __t)->ip_traffic_MAX,
		((const ptraffic_config_t) __t)->autoBlock);
    }
  while (1);
  strncpy (buffer, tmp, BUFFSIZE);
  kfree (tmp);
  len = strlen (buffer);
  return len;
}


/*
* The function is used to count the packet through the wan interface. 
* Packet is counted and indentified by IP address.
*
* When the sum of packet for certain IP address reaches the budget, than the 
* 1. No more packet can be sent to Internet through the router here.
* 2. No more new connection is allowed to established, but the current 
*    connection is not affected at all.
*/

static unsigned int
ip_traffic_control (unsigned int hooknum, struct sk_buff **pskb,
		    const struct net_device *in,
		    const struct net_device *out,
		    int (*okfn) (struct sk_buff *))
{
  long int addr;
  char *p = (char *) &addr;
  struct list_head *__t = &traffic_config_list_head;
//for check the conntrack status of the packet.
  struct ip_conntrack *ct;
  enum ip_conntrack_info ctinfo;
  unsigned int verdict = NF_ACCEPT;

  int found = 0;		//the packet is in the list 
  struct list_head *other = NULL;	//refer to configuration for other pc.


  *p = 192;
  p[1] = 168;
  p[2] = 10;
  p[3] = 41;

#if ECHO_DEBUG
  printk (KERN_INFO "a packet with daddr=%ld sapass throuth post_routing.\n",
	  (*pskb)->nh.iph->daddr);
  printk (KERN_INFO "htonl(addr) = %ld", htonl (addr));
#endif


//      the packet coming from/to wan interface  

  if ((out->name != NULL && strcmp (out->name, "br0") != 0)
      || (*pskb)->sk == NULL)
    {

      if (out->name != NULL && strcmp (out->name, "br0") != 0)
	{
	  traffic_tmp += (*pskb)->nh.iph->tot_len;
	  if (traffic_tmp > MEGA_BYTE_MASK)
	    {
	      traffic_bytes += (traffic_tmp & MEGA_BYTE) >> 20;
	      traffic_tmp = traffic_tmp & MEGA_BYTE_MASK;
	    }
	}

      found = 0;
      other = NULL;
      if ((*pskb)->sk == NULL)
	{
	  do
	    {
	      __t = __t->next;
	      if (__t == (&traffic_config_list_head))
		{
		  __t = NULL;
		  break;
		}
/*      if ((*pskb)->mac.raw >= (*pskb)->head
	  && ((*pskb)->mac.raw + ETH_HLEN) <= (*pskb)->data
	  && memcmp ((*pskb)->mac.ethernet->h_source,
		     ((ptraffic_config_t) __t)->h_dest, ETH_ALEN) == 0)
*/
	      if (((ptraffic_config_t) __t)->ip_address == 0)
		other = __t;
	      if ((*pskb)->nh.iph->daddr ==
		  htonl (((ptraffic_config_t) __t)->ip_address)
		  || (*pskb)->nh.iph->saddr ==
		  htonl (((ptraffic_config_t) __t)->ip_address))
		{
		  ((ptraffic_config_t) __t)->ip_traffic_local +=
		    (*pskb)->nh.iph->tot_len;
		  if (((ptraffic_config_t) __t)->ip_traffic_local >
		      MEGA_BYTE_MASK)
		    {
		      ((ptraffic_config_t) __t)->ip_traffic_MAX -=
			(((ptraffic_config_t) __t)->ip_traffic_local &
			MEGA_BYTE) >> 20;
		      ((ptraffic_config_t) __t)->ip_traffic_local =
			((ptraffic_config_t) __t)->ip_traffic_local &
			MEGA_BYTE_MASK;
		    }
		  if (((ptraffic_config_t) __t)->ip_traffic_MAX <= 0)
		    {
		      //the verdict is according the autoBlock value  
		      if (((ptraffic_config_t) __t)->autoBlock == 1)
			verdict = NF_DROP;
		      else
			{
			  ct = ip_conntrack_get (*pskb, &ctinfo);
			  if (ct
			      && (ctinfo == IP_CT_NEW
				  || ctinfo == IP_CT_RELATED))
			    {
			      verdict = NF_DROP;
			    }
			  else
			    {
			      verdict = NF_ACCEPT;
			    }

			}

		    }
		  found = 1;
		  break;
		}

	    }
	  while (1);
	}
    }

//do other accounting and block action
  if (found == 0 && other != NULL)
    {
      ((ptraffic_config_t) other)->ip_traffic_local +=
	(*pskb)->nh.iph->tot_len;
      if (((ptraffic_config_t) other)->ip_traffic_local > MEGA_BYTE_MASK)
	{
	  ((ptraffic_config_t) other)->ip_traffic_MAX -=
	    (((ptraffic_config_t) other)->ip_traffic_local & MEGA_BYTE) >> 20;
	  ((ptraffic_config_t) other)->ip_traffic_local =
	    ((ptraffic_config_t) other)->ip_traffic_local & MEGA_BYTE_MASK;
	}

      if (((ptraffic_config_t) other)->ip_traffic_MAX <= 0)
	{
	  //the verdict is according the autoBlock value
	  if (((ptraffic_config_t) other)->autoBlock == 1)
	    verdict = NF_DROP;
	  else
	    {
	      ct = ip_conntrack_get (*pskb, &ctinfo);
	      if (ct && (ctinfo == IP_CT_NEW || ctinfo == IP_CT_RELATED))
		{
		  verdict = NF_DROP;
		}
	      else
		{
		  verdict = NF_ACCEPT;
		}

	    }

	}

    }


  return verdict;

}

/*
* just count the packet received from wan
*/

static unsigned int
ip_general_traffic_control (unsigned int hooknum, struct sk_buff **pskb,
			    const struct net_device *in,
			    const struct net_device *out,
			    int (*okfn) (struct sk_buff *))
{
  if (in->name != NULL && strcmp (in->name, "br0") != 0)
    {
      traffic_tmp += (*pskb)->nh.iph->tot_len;
      if (traffic_tmp > MEGA_BYTE_MASK)
	{
	  traffic_bytes += (traffic_tmp & MEGA_BYTE) >> 20;
	  traffic_tmp = traffic_tmp & MEGA_BYTE_MASK;
	}
    }
  return NF_ACCEPT;
}


/*
 * When the data is prepared to leave the ip stack, traffic control is done.
 * So we made a hook call-back function at POST_ROUTING
 */
static struct nf_hook_ops ip_traffic_control_ops = {
  .hook = ip_traffic_control,
  .owner = THIS_MODULE,
  .pf = PF_INET,
  .hooknum = NF_IP_POST_ROUTING,
  .priority = NF_IP_PRI_CONNTRACK,
};

static struct nf_hook_ops ip_general_traffic_control_ops = {
  .hook = ip_general_traffic_control,
  .owner = THIS_MODULE,
  .pf = PF_INET,
  .hooknum = NF_IP_PRE_ROUTING,
  .priority = NF_IP_PRI_CONNTRACK,
};

static int
init_or_cleanup (int init)
{
  struct proc_dir_entry *proc;
  int ret = 0;

  if (!init)
    goto cleanup;

/*	ret = ip_traffic_init();
	if (ret < 0)
		goto cleanup_nothing;
*/
  proc = proc_net_create ("ip_traffic", 0440, list_traffics);
  if (!proc)
    goto cleanup_init;
  proc->owner = THIS_MODULE;

  ret = nf_register_hook (&ip_traffic_control_ops);
  if (ret < 0)
    {
      printk ("ip_traffic: can't register hook.\n");
      goto cleanup_proc;
    }
  ret = nf_register_hook (&ip_general_traffic_control_ops);
  if (ret < 0)
    {
      printk ("ip_traffic: can't register hook.\n");
      goto cleanup_outops;
    }
  return ret;

cleanup:
cleanup_inops:
  nf_unregister_hook (&ip_general_traffic_control_ops);
cleanup_outops:
  nf_unregister_hook (&ip_traffic_control_ops);
cleanup_proc:
  proc_net_remove ("ip_traffic");
cleanup_init:
/*
	ip_traffic_cleanup();
*/
cleanup_nothing:
  return ret;
}

static int __init
init (void)
{
  return init_or_cleanup (1);
}

static void __exit
fini (void)
{
  init_or_cleanup (0);
}

module_init (init);
module_exit (fini);
