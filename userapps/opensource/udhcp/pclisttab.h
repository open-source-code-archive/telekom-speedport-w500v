/**********************************************************************************************
*File Description :
*		This file read a table from a file,the data struct stored in this file's format 
*               like this:
*                       |__16-IP-Bytes__|__16-MAC-Bytes__|
*				
*File Name:
*          PcListTab.h				-header file define
*Paul 2005/04/28
***********************************************************************************************/
#ifndef _PCLISTTAB_H
#define _PCLISTTAB_H
//define PcListEntry 
struct  PcListEntry
{
 char IpAddr[16];
 char MacAddr[16];
};
//define PcListTab
struct PcList
{
  struct PcListEntry entry;
  struct PcList *next;
};
//global param
extern struct PcList *g_pclist;
void PcListInit(void);
char * find_ip_by_mac(char *mac);
int Ip_in_pclist(char *ipaddr);
void PcListRelease(void);
void PcListReInit(void);
#endif
