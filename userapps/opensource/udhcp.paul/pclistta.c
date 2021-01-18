/**********************************************************************************************
*File Description :
*		This file read a table from a file,the data struct stored in this file's format 
*               like this:
*                       |__16-IP-Bytes__|__16-MAC-Bytes__|
*				
*File Name:
*          PcListTab.c
*Paul 2005/04/28
***********************************************************************************************/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>
#include "PcListTab.h"

//#define  _DEBUG
#define  PATH_PCLIST  "/var/data"

//global param
struct PcList *g_pclist=NULL;

/*===================================================================================
*Function: PcListInit()
*			Inilizate the g_pclist from file 
*
*===================================================================================*/
void PcListInit(){
 	FILE *fd=NULL;
	struct PcListEntry listentry;
	struct PcList *pEntry=NULL,*phead=NULL;
#ifdef _DEBUG
    void PcListTest();
    PcListTest();  //Add by paul 2005/04/29 for test purpose
#endif
    fd = fopen (PATH_PCLIST,"r+");
	if(fd ==NULL){
		printf("can't open the PcListFile\n");
        return;
		}
	else{
		while( fread(&listentry,sizeof(listentry),1,fd)){
             pEntry=(struct PcList*)malloc(sizeof(struct PcList));
             if(pEntry==NULL)
			    return;
             if(g_pclist==NULL){
				 g_pclist=pEntry;
				 phead=pEntry;
                 memcpy(&(pEntry->entry),&listentry,sizeof(struct PcListEntry));
				 pEntry->next=NULL;
			 }
			 else{
                 g_pclist->next=pEntry;
				 g_pclist=pEntry;
				 memcpy(&(pEntry->entry),&listentry,sizeof(struct PcListEntry));
				 pEntry->next=NULL;
			 }
        }
		g_pclist=phead;
	}
}

/*===================================================================================
*Function: find_ip_by_mac()
*			find the ip address from the pclist table accroding to the given mac addr 
*
*===================================================================================*/
char * find_ip_by_mac(char *mac)
{
    struct PcList *plist;
	plist=g_pclist;
	
	if(mac==NULL)
		return NULL;
	while(plist){
     if(strcmp(plist->entry.MacAddr,mac)==0){
        return plist->entry.IpAddr; 
		break; 
	   }
    plist=plist->next;
    }	
	return NULL;
}


/*===================================================================================
*Function: Ip_in_pclist(char *ipaddr)
*			check  the specific ip address in  the pclist table,if in return true
*else return false
*===================================================================================*/
int Ip_in_pclist(char *ipaddr){
    int  ret=0;
    struct PcList *plist;
	plist=g_pclist;
	
	if(ipaddr==NULL)
		return 0;
	while(plist){
     if(strcmp(plist->entry.IpAddr,ipaddr)==0){
        ret=1; 
		break; 
	   }
    plist=plist->next;
    }
return ret;
};
/*===================================================================================
*Function: PcListRelease()
*			Release the g_pclist
*
*===================================================================================*/
void PcListRelease()
{
   struct  PcList *plist;
	while(g_pclist){
       plist=g_pclist->next;
	   if(g_pclist)
		   free(g_pclist);
       g_pclist=plist;
    }
	g_pclist=NULL;
}

/*===================================================================================
*Function: PcListReInit()
*			Re initlize the globale pclist table from the file  
*
*===================================================================================*/
void PcListReInit()
{
  signal(SIGUSR2,SIG_IGN);
  if(g_pclist)
	  PcListRelease();
  PcListInit();
  signal(SIGUSR2,PcListReInit);
}


//////////////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
void PcListTest(){
struct PcListEntry m_entry;
FILE *fd;
fd=fopen(PATH_PCLIST,"wb");
strcpy(m_entry.IpAddr,"192.168.10.38");
strcpy(m_entry.MacAddr,"AA40460272EB");
fwrite(&m_entry,sizeof(struct PcListEntry),1,fd);
strcpy(m_entry.IpAddr,"192.168.10.38");
strcpy(m_entry.MacAddr,"0040460272EB");
fwrite(&m_entry,sizeof(struct PcListEntry),1,fd);
fclose(fd);
}
#endif
///////////////////////////////////////////////////////////////////////////////////////
