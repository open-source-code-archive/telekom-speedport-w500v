/*****************************************************************************
//
//  Copyright (c) 2004  Broadcom Corporation
//  All Rights Reserved
//  No portions of this material may be reproduced in any form without the
//  written permission of:
//          Broadcom Corporation
//          16215 Alton Parkway
//          Irvine, California 92619
//  All information contained in this document is Broadcom Corporation
//  company private, proprietary, and trade secret.
//
******************************************************************************
//
//  Filename:       psixml.h
//  Author:         yt
//  Creation Date:  05/11/04
//
******************************************************************************
//  Description:
//      Define the global types, enums. and constants for PSI in XML format
//
*****************************************************************************/

#ifndef __PSIXML_H__
#define __PSIXML_H__

#include "bcmtypes.h"
#include "psidefs.h"
#include "wldefs.h"
#include "nanoxml.h"

//Added by echo
//#define BUG
#ifdef BUG
#define DB_BUG(a,...) printf(a,...)
#else
#define DB_BUG(a,...) 
#endif

#define PSX_NAME_LEN                   16
#define PSX_MAGIC_LEN                  16
#define PSX_MAGIC_VALUE                "-$-PSI-$02.12r01"
#define PSX_CRC32_INIT_VALUE 0xffffffff /* Initial CRC32 checksum value */
#define PSX_CRC32_GOOD_VALUE 0xdebb20e3 /* Good final CRC32 checksum value */
#define PSX_STR_LEN                    50 
#define PSX_VERIFY                     1
#define PSX_STORE                      0
#define PSX_TABLE_TYPE                 2
#define PSX_APP_TYPE                   1
#define PSX_OBJ_TYPE                   0

#define MONDAY        0x1
#define TUESDAY       0x2
#define WEDNSDAY      0x4
#define THURSDAY      0x8
#define FRIDAY        0x10
#define SATURDAY      0x20
#define SUNDAY        0x40

/* important limitation: when adding the appName or objectName in either direction, it is 
important not to have appName and objName having the same prefix.   The table entry search
only compare strings up to the prefix length, case not sensitive, to cover situation
such as APP_ID wan_vpi_vci, only wan is searched in the table.    Therefore, it is not
okay to have Lan as the appId, and objectName as lanSomethingSomething.    The search
entry would think lanSomethingSomething is an appId name. */

#define APPNAME_WAN_PREFIX           "wan"
#define APPNAME_IPSRV_PREFIX         "ipsrv"
#define APPNAME_PPPSRV_PREFIX        "pppsrv"
#define APPNAME_PPP_FORMAT           "pppsrv_%d_%d"
#define APPNAME_IPSRV_ENTRY_FORMAT   "ipsrv_%d_%d"
#define OBJNAME_LAN_ENTRY_FORMAT     "entry%d"   /* cannot be lan, need to change */
#define OBJNAME_PPP_ENTRY_FORMAT     "ppp_conId%d"
#define OBJNAME_IPSRV_ENTRY_FORMAT   "dhcpc_conId%d"
#define OBJNAME_WAN_ENTRY_FORMAT     "entry%d"   /* cannot be wan, need to change */
#define OBJNAME_GEN_ENTRY_FORMAT     "entry" 

#define XML_PSI_START_TAG      "<psitree>"
#define XML_PSI_END_TAG        "</psitree>"

#define XML_PORT_RANGE_MIN     1
#define XML_PORT_RANGE_MAX     65535
#define XML_MAX_SNMP_STR_LEN   31         /* Tommy, 15->31 */
#define XML_MAX_TOD_ENTRY      16

/* string  */
#define PSX_ATTRNAME_SET       1
#define PSX_ATTRSTR_SET        2

typedef enum {
   PSX_STS_OK = 0,
   PSX_STS_ERR_GENERAL,
   PSX_STS_ERR_MEMORY,
   PSX_STS_ERR_FIND_APP,
   PSX_STS_ERR_FIND_OBJ,
   PSX_STS_ERR_FIND_HDL_FNC,
   PSX_STS_ERR_FATAL,
   PSX_STS_ERR_MILD
} PSX_STATUS;

/* internal callback statemachine */
typedef enum {
   state_start,
   state_psi_begin,  
   state_psi_end
} xml_state;


typedef struct xmlParseState {
   xml_state state;
   char appName[32];
   PSI_HANDLE appHandle;
   char objName[32];
   char attrName[32];
   char tableName[32];
   int tableSize;
   int tableIndex;
   PSX_STATUS errorFlag;
   int verify;                    /* verify=1 verifcation only, verfify=0 conversion only */
} XML_PARSE_STATE, *pXML_PARSE_STATE;

typedef PSX_STATUS (*PSX_SET_OBJ_FNC) (FILE *file, const char *appName, const UINT16 id,
                                       const PSI_VALUE value, const UINT16 length);
typedef PSX_STATUS (*PSX_GET_OBJ_FNC) (char *appName, char *objName, char *attrName,
				       char* attrValue);
typedef void (*PSX_SET_ATTR_FNC) (FILE *file, const char *name, const UINT16 id,
				  const PSI_VALUE value, const UINT16 length);

typedef PSX_STATUS (*PSX_GET_ATTR_FNC) (char *attrName, char *attrValue);
typedef PSX_STATUS (*PSX_OBJ_FNC) (char *appName,  char *objName);



typedef struct {
   char  appName[PSX_NAME_LEN];
   PSX_SET_OBJ_FNC setObjFnc;
   PSX_GET_OBJ_FNC getObjFnc;     /* base on appName, find the object's getObjFnc */
   PSX_OBJ_FNC startObjFnc;       /* base on appName, find the object's startObjFnc */
   PSX_OBJ_FNC endObjFnc;         /* base on appName, find the object's endObjFnc */
} PSX_APP_ITEM, *PPSX_APP_ITEM;

typedef struct {
   char  objName[PSX_NAME_LEN];
   PSX_SET_ATTR_FNC setAttrFnc;
   PSX_GET_ATTR_FNC getAttrFnc;  /* getting object from XML file, do verification/store */
   PSX_OBJ_FNC startObjFnc;     /* beginning of object, resource allocated */
   PSX_OBJ_FNC endObjFnc;       /* end of object, do verification/storeToPSI, oresource deallocated */
} PSX_OBJ_ITEM, *PPSX_OBJ_ITEM;

/* object and attribute names definitions */
#define PSX_ATTR_STATE             "state"
/* system info */
#define PSX_OBJ_SYS_USER_NAME      "sysUserName"
#define PSX_OBJ_SYS_PASSWORD       "sysPassword"
#define PSX_OBJ_SYS_AUTH_TIME      "sysAuthTime"
#define PSX_OBJ_SPT_USER_NAME      "sptUserName"
#define PSX_OBJ_ETHCFG             "ethCfg"
#define PSX_OBJ_SPT_PASSWORD       "sptPassword"
#define PSX_OBJ_USR_USER_NAME      "usrUserName"
#define PSX_OBJ_USR_PASSWORD       "usrPassword"
#define PSX_OBJ_DEF_GATEWAY        "defaultGateway"
#define PSX_OBJ_DNS                "dns"
#define PSX_OBJ_SYSLOG             "sysLog"
#define PSX_OBJ_SNMP               "snmp"
#define PSX_OBJ_PROTOCOL           "protocol"
#define PSX_OBJ_ACTIVE_SERVICE     "activeService"
#define PSX_OBJ_UPNP		   "upnp"

#define PSX_OBJ_MGCP_CFG           "mgcpCfg"
#define PSX_OBJ_SIP_CFG            "sipCfg"


#define PSX_ATTR_DNS_PRIMARY       "primary"
#define PSX_ATTR_DNS_SECONDARY     "secondary"
#define PSX_ATTR_DNS_DYNAMIC       "dynamic"

#define PSX_ATTR_SYSLOG_DISPLAY_LEVEL "displayLevel"
#define PSX_ATTR_SYSLOG_LOG_LEVEL     "logLevel"
#define PSX_ATTR_SYSLOG_OPTION        "option"
#define PSX_ATTR_SYSLOG_SERVER_IP     "serverIP"
#define PSX_ATTR_SYSLOG_SERVER_PORT   "serverPort"

#define PSX_ATTR_PMAP_IFC_NAME        "pmapIfName"
#define PSX_ATTR_PMAP_IFC_STATUS      "pmapIfcStatus"

#define PSX_ATTR_VOICE_MGCP_TAG            "mgcpCfg"
#define PSX_ATTR_VOICE_MGCP_CA_ADDR        "caAddr"
#define PSX_ATTR_VOICE_MGCP_GW_NAME        "gwName"
#define PSX_ATTR_VOICE_MGCP_IF_NAME        "ifName"
#define PSX_ATTR_VOICE_MGCP_PREF_CODEC     "prefCodec"
/* Tommy */
#define PSX_ATTR_VOICE_MGCP_COUNTRY        "country"
#define PSX_ATTR_VOICE_MGCP_AALN           "aaln"
#define PSX_ATTR_VOICE_MGCP_CA_PORT        "caPort"
#define PSX_ATTR_VOICE_MGCP_CLIENT_PORT    "clientPort"
#define PSX_ATTR_VOICE_MGCP_TX_GAIN        "txGain"
#define PSX_ATTR_VOICE_MGCP_RX_GAIN        "rxGain"
#define PSX_ATTR_VOICE_MGCP_PSTN_CODE      "pstnCode"
#define PSX_ATTR_VOICE_MGCP_HB_TIMER       "hbTimer"
#define PSX_ATTR_VOICE_MGCP_EMERGENCY      "emergency"
/*#define PSX_ATTR_VOICE_MGCP_EMERGENCY0     "emergency0"
#define PSX_ATTR_VOICE_MGCP_EMERGENCY1     "emergency1"
#define PSX_ATTR_VOICE_MGCP_EMERGENCY2     "emergency2"
#define PSX_ATTR_VOICE_MGCP_EMERGENCY3     "emergency3"
#define PSX_ATTR_VOICE_MGCP_EMERGENCY4     "emergency4"
#define PSX_ATTR_VOICE_MGCP_EMERGENCY5     "emergency5"
#define PSX_ATTR_VOICE_MGCP_EMERGENCY6     "emergency6"
#define PSX_ATTR_VOICE_MGCP_EMERGENCY7     "emergency7"
#define PSX_ATTR_VOICE_MGCP_EMERGENCY8     "emergency8"
#define PSX_ATTR_VOICE_MGCP_EMERGENCY9     "emergency9"*/

#define PSX_ATTR_VOICE_SIP_TAG             "sipCfg"
#define PSX_ATTR_VOICE_SIP_PROXY_ADDR      "proxyAddr"
#define PSX_ATTR_VOICE_SIP_PROXY_PORT      "proxyPort"
#define PSX_ATTR_VOICE_SIP_REGISTRAR_ADDR  "registrarAddr"
#define PSX_ATTR_VOICE_SIP_REGISTRAR_PORT  "registrarPort"
#define PSX_ATTR_VOICE_SIP_LOG_ADDR        "logAddr"
#define PSX_ATTR_VOICE_SIP_LOG_PORT        "logPort"
#define PSX_ATTR_VOICE_SIP_EXT1            "ext1"
#define PSX_ATTR_VOICE_SIP_PASSWORD1       "password1"
#define PSX_ATTR_VOICE_SIP_EXT2            "ext2"
#define PSX_ATTR_VOICE_SIP_PASSWORD2       "password2"
#define PSX_ATTR_VOICE_SIP_EXT3            "ext3"
#define PSX_ATTR_VOICE_SIP_PASSWORD3       "password3"
#define PSX_ATTR_VOICE_SIP_EXT4            "ext4"
#define PSX_ATTR_VOICE_SIP_PASSWORD4       "password4"
#define PSX_ATTR_VOICE_SIP_IF_NAME         "ifName"
#define PSX_ATTR_VOICE_SIP_AUTH_NAME	   "authName"

#define PSX_ATTR_ETH_CFG_SPEED        "speed"
#define PSX_ATTR_ETH_CFG_TYPE         "type"
#define PSX_ATTR_ETH_CFG_MTU          "MTU"
#define PSX_ATTR_IPP_MAKE             "make"
#define PSX_ATTR_IPP_DEV              "dev"
#define PSX_ATTR_IPP_NAME             "name"
#if defined(__cplusplus)
extern "C" {
#endif
extern PSX_STATUS xmlSetObjNode(FILE* file, const char *appName, const UINT16 id,
			 const PSI_VALUE value, const UINT16 length);
extern PSX_STATUS xmlSetSysObjNode(FILE* file, const char *appName, const UINT16 id,
			    const PSI_VALUE value, const UINT16 length);
extern PSX_STATUS xmlSetRouteObjNode(FILE* file, const char *appName, const UINT16 id,
			    const PSI_VALUE value, const UINT16 length);
extern PSX_STATUS xmlSetPMapObjNode(FILE* file, const char *appName, const UINT16 id,
			    const PSI_VALUE value, const UINT16 length);
extern PSX_STATUS xmlSetLanNode(FILE* file, const char *appName, const UINT16 id,
			 const PSI_VALUE value, const UINT16 length);
extern PSX_STATUS xmlSetWirelessNode(FILE* file, const char *appName, const UINT16 id,
			      const PSI_VALUE value, const UINT16 length);
extern PSX_STATUS xmlSetWanNode(FILE* file, const char *appName, const UINT16 id,
			 const PSI_VALUE value, const UINT16 length);
extern PSX_STATUS xmlSetAtmTdNode(FILE* file, const char *appName, const UINT16 id,
			   const PSI_VALUE value, const UINT16 length);
extern PSX_STATUS xmlSetAtmVccNode(FILE* file, const char *appName, const UINT16 id,
			    const PSI_VALUE value, const UINT16 length);
extern PSX_STATUS xmlSetAtmCfgNode(FILE* file, const char *appName, const UINT16 id,
			    const PSI_VALUE value, const UINT16 length);
extern PSX_STATUS xmlSetSecObjNode(FILE* file, const char *appName, const UINT16 id,
			    const PSI_VALUE value, const UINT16 length);
extern PSX_STATUS xmlSetAdslObjNode(FILE* file, const char *appName, const UINT16 id,
			     const PSI_VALUE value, const UINT16 length);
extern PSX_STATUS xmlSetSntpNode(FILE* file, const char *appName, const UINT16 id,
			  const PSI_VALUE value, const UINT16 length);
extern PSX_STATUS xmlSetToDNode(FILE* file, const char *appName, const UINT16 id,
			 const PSI_VALUE value, const UINT16 length);
extern PSX_STATUS xmlSetDhcpClntNode(FILE* file, const char *appName, const UINT16 id,
			      const PSI_VALUE value, const UINT16 length);
extern PSX_STATUS xmlSetSpiNode(FILE* file, const char *appName, const UINT16 id,
				const PSI_VALUE value, const UINT16 length);
extern PSX_STATUS xmlSetPppNode(FILE* file, const char *appName, const UINT16 id,
			 const PSI_VALUE value, const UINT16 length);
extern PSX_STATUS xmlSetDatetimeObjNode(FILE *file, const char *appName, const UINT16 id,
				        const PSI_VALUE value, const UINT16 length);
extern PSX_STATUS  xmlSetRadiusObjNode(FILE *file, const char *appName, const UINT16 id,
				      const PSI_VALUE value, const UINT16 length);
extern PSX_STATUS xmlSetDdnsNode(FILE* file, const char *appName, const UINT16 id,
			  const PSI_VALUE value, const UINT16 length);
extern void  xmlSetAuthTimeAttr(FILE *file, const char *name, const UINT16 id, const PSI_VALUE value,
                      const UINT16 length);

extern void  xmlSetActiveSvrAttr(FILE *file, const char *name, const UINT16 id, const PSI_VALUE value,
                      const UINT16 length);

extern void xmlSetStrObjAttr(FILE *file, const char *name, const UINT16 id, const PSI_VALUE value,
                      const UINT16 length);
extern void xmlSetSysLogAttr(FILE *file, const char *name, const UINT16 id, const PSI_VALUE value,
		      const UINT16 length);
extern void xmlSetDftGwAttr(FILE *file, const char *name, const UINT16 id, const PSI_VALUE value,
		     const UINT16 length);
extern void xmlSetDnsAttr(FILE *file, const char *name, const UINT16 id, const PSI_VALUE value,
		   const UINT16 length);
extern void xmlSetOtherSysAttr(FILE *file, const char *name, const UINT16 id, const PSI_VALUE value,
			const UINT16 length);
extern void xmlSetSnmpAttr(FILE *file, const char *name, const UINT16 id, const PSI_VALUE value,
		    const UINT16 length);
extern void xmlSetRouteAttr(FILE *file, const char *name, const UINT16 id, const PSI_VALUE value,
			   const UINT16 length);
extern void xmlSetRipIfcAttr(FILE *file, const char *name, const UINT16 id, const PSI_VALUE value,
		      const UINT16 length);
extern void xmlSetRipAttr(FILE *file, const char *name, const UINT16 id, const PSI_VALUE value,
		   const UINT16 length);
extern void xmlSetPMapAttr(FILE *file, const char *name, const UINT16 id, const PSI_VALUE value,
		   const UINT16 length);
extern void xmlSetLanAttr(FILE *file, const char *name, const UINT16 id, const PSI_VALUE value,
		   const UINT16 length);
extern void xmlWlSetWebAttr(FILE *file, PWIRELESS_VAR wlVars);
extern void xmlWlSetEncrytionAttr(FILE *file, PWIRELESS_VAR wlVars);
extern void xmlWlSetEncryptionStrengthAttr(FILE *file, PWIRELESS_VAR wlVars);
extern void xmlWlSetRadiusServerAttr(FILE *file, PWIRELESS_VAR wlVars);
extern void xmlSetWirelessVarsAttr(FILE *file, const char *name, const UINT16 id, const PSI_VALUE value,
			   const UINT16 length);

extern void xmlSetWirelessMacFilterAttr(FILE *file, const char *name, const UINT16 id, const PSI_VALUE value
			   ,const UINT16 length);
extern void xmlSetRadiusAttr(FILE *file, const char *name, const UINT16 id, const PSI_VALUE value,
					 const UINT16 length);
extern void xmlSetAtmInitAttr(FILE *file, const char *name, const UINT16 id, const PSI_VALUE value,
		       const UINT16 length);
extern void xmlSetAtmPortAttr(FILE *file, const char *name, const UINT16 id, const PSI_VALUE value,
		       const UINT16 length);
extern void xmlSetAtmTdNumAttr(FILE *file, const char *name, const UINT16 id, const PSI_VALUE value,
			const UINT16 length);
extern void xmlSetAtmTdTblAttr(FILE *file, const char *name, const UINT16 id, const PSI_VALUE value,
			const UINT16 length);
extern void xmlSetAtmIfcAttr(FILE *file, const char *name, const UINT16 id, const PSI_VALUE value,
		      const UINT16 length);
extern void xmlSetAtmVccNumAttr(FILE *file, const char *name, const UINT16 id, const PSI_VALUE value,
			 const UINT16 length);
extern void xmlSetAtmVccTblAttr(FILE *file, const char *name, const UINT16 id, const PSI_VALUE value,
			const UINT16 length);
extern void xmlSetDmzHostAttr(FILE *file, const char *name, const UINT16 id, const PSI_VALUE value,
		       const UINT16 length);
extern void xmlSetServiceCtrlAttr(FILE *file, const char *name, const UINT16 id, const PSI_VALUE value,
			   const UINT16 length);
extern void xmlSetVirtualSrvAttr(FILE *file, const char *name, const UINT16 id, const PSI_VALUE value,
		      const UINT16 length);
extern void xmlSetIpFilterAttr(FILE *file, const char *name, const UINT16 id, const PSI_VALUE value,
		      const UINT16 length);
extern void xmlSetPrtTriggerAttr(FILE *file, const char *name, const UINT16 id, const PSI_VALUE value,
			  const UINT16 length);
extern void xmlSetMacFilterAttr(FILE *file, const char *name, const UINT16 id, const PSI_VALUE value,
			 const UINT16 length);
extern void xmlSetAccessControlAttr(FILE *file, const char *name, const UINT16 id, const PSI_VALUE value,
			     const UINT16 length);
extern void xmlSetAccessControlModeAttr(FILE *file, const char *name, const UINT16 id, const PSI_VALUE value,
				 const UINT16 length);
extern void xmlSetQosAttr(FILE *file, const char *name, const UINT16 id, const PSI_VALUE value,
		   const UINT16 length);
extern void xmlSetToDCntrlAttr(FILE *file, const char *name, const UINT16 id, const PSI_VALUE value,
			const UINT16 length);
extern void xmlSetDdnsAttr(FILE *file, const char *name, const UINT16 id, const PSI_VALUE value,
		    const UINT16 length);
extern void xmlSetEthAttr(FILE *file, const char *name, const UINT16 id, const PSI_VALUE value,
		   const UINT16 length);
extern PSX_STATUS xmlParse(char *xmlBuffer, int xmlSize, int verify);
extern void xmlTagBegin(nxml_t handle, const char *tag_name, unsigned len);
extern void xmlTagEnd(nxml_t handle, const char *tag_name, unsigned len);
extern void xmlAttrBegin(nxml_t handle, const char *tag_name, unsigned len);
extern void xmlAttrValue(nxml_t handle, const char *tag_name, unsigned len);
extern void xmlData(nxml_t handle, const char *tag_name, unsigned len);
extern PSX_STATUS xmlGetObjNode(char *appName, char *objTagName,
	         		char *attrName, char *value);
extern PSX_STATUS xmlVerifyObjNode(char *appName, char *objTagName,
			    char *attrName, char *value);
extern PSX_STATUS xmlStartObjNode(char *appName, char *objTagName);
extern PSX_STATUS xmlEndObjNode(char *appName, char *objTagName);

extern PSX_STATUS xmlGetSysObjNode(char *appName, char *objName, char *attrName, char* attrValue);
extern PSX_STATUS xmlStartSysObjNode(char *appName, char *objName);
extern PSX_STATUS xmlEndSysObjNode(char *appName, char *objName);
extern PSX_STATUS xmlGetSysUserNameAttr(char *attrName, char* attrValue);
extern PSX_STATUS xmlGetSysPasswordAttr(char *attrName, char* attrValue);
extern PSX_STATUS xmlGetSysAuthTimeAttr(char *attrName, char* attrValue);
extern PSX_STATUS xmlGetActiveSvrAttr(char *attrName, char* attrValue);
extern PSX_STATUS xmlStartSysUserNamePasswordObj(char *appName, char *objName);
extern PSX_STATUS xmlEndSysUserNamePasswordObj(char *appName, char *objName);
extern PSX_STATUS xmlStartSysAuthTimeObj(char *appName, char *objName);
extern PSX_STATUS xmlEndSysAuthTimeObj(char *appName, char *objName);
extern PSX_STATUS xmlStartActiveSvrObj(char *appName, char *objName);
extern PSX_STATUS xmlEndActiveSvrObj(char *appName, char *objName);

extern PSX_STATUS xmlGetDftGwAttr(char *attrName, char* attrValue);
extern PSX_STATUS xmlStartDftGwObj(char *appName, char *objName);
extern PSX_STATUS xmlEndDftGwObj(char *appName, char *objName);
extern PSX_STATUS xmlGetDnsAttr(char *attrName, char* attrValue);
extern PSX_STATUS xmlStartDnsObj(char *appName, char *objName);
extern PSX_STATUS xmlEndDnsObj(char *appName, char *objName);
extern PSX_STATUS xmlGetSyslogAttr(char *attrName, char* attrValue);
extern PSX_STATUS xmlStartSyslogObj(char *appName, char *objName);
extern PSX_STATUS xmlEndSyslogObj(char *appName, char *objName);
extern PSX_STATUS xmlGetSnmpAttr(char *attrName, char* attrValue);
extern PSX_STATUS xmlStartSnmpObj(char *appName, char *objName);
extern PSX_STATUS xmlEndSnmpObj(char *appName, char *objName);
extern PSX_STATUS xmlGetOtherSysAttr(char *attrName, char* attrValue);
extern PSX_STATUS xmlStartOtherSysObj(char *appName, char *objName);
extern PSX_STATUS xmlEndOtherSysObj(char *appName, char *objName);
extern PSX_STATUS xmlGetAtmVccObjNode(char *appName, char *objName, char *attrName,
                                      char* attrValue);
extern PSX_STATUS xmlGetAtmVccAttr(char *attrName, char* attrValue);
extern PSX_STATUS xmlStartAtmVccObjNode(char *appName, char *objName);
extern PSX_STATUS xmlEndAtmVccObjNode(char *appName, char *objName);
extern PSX_STATUS xmlGetWanObjNode(char *appName, char *objName, char *attrName,
                                   char* attrValue);
extern PSX_STATUS xmlGetWanAttr(char *attrName, char* attrValue);
extern PSX_STATUS xmlStartWanObjNode(char *appName, char *objName);
extern PSX_STATUS xmlEndWanObjNode(char *appName, char *objName);
extern PSX_STATUS xmlGetPppObjNode(char *appName, char *objName, char *attrName,
                                   char* attrValue);
extern PSX_STATUS xmlGetDatetimeObjNode(char *appName, char *objName, char *attrName,
					char *attrValue);
extern PSX_STATUS xmlGetRadiusObjNode(char *attrName,char *attrValue);
extern PSX_STATUS xmlGetPppAttr(char *attrName, char* attrValue);
extern PSX_STATUS xmlStartDatetimeObjNode(char *appName, char *attrValue);
extern PSX_STATUS xmlStartPppObjNode(char *appName, char *objName);
extern PSX_STATUS xmlEndPppObjNode(char *appName, char *objName);
extern PSX_STATUS xmlEndRadiusAttr(char *appName, char *objName);
extern PSX_STATUS xmlEndDatetimeObjNode(char *appName, char *objName);
extern PSX_STATUS xmlGetSecObjNode(char *appName, char *objName, char *attrName, char* attrValue);
extern PSX_STATUS xmlStartSecObjNode(char *appName, char *objName);
extern PSX_STATUS xmlEndSecObjNode(char *appName, char *objName);
extern PSX_STATUS xmlGetVrtSrvAttr(char *attrName, char* attrValue);
extern PSX_STATUS xmlEndVrtSrvObj(char *appName, char *objName);
extern PSX_STATUS xmlGetVrtSrvEntryAttr(char *attrName, char* attrValue);
extern PSX_STATUS xmlEndVrtSrvEntryObj(char *appName, char *objName);
extern PSX_STATUS xmlGetIpFilterAttr(char *attrName, char* attrValue);
extern PSX_STATUS xmlEndIpFilterObj(char *appName, char *objName);
extern PSX_STATUS xmlGetIpFilterEntryAttr(char *attrName, char* attrValue);
extern PSX_STATUS xmlEndIpFilterEntryObj(char *appName, char *objName);
extern PSX_STATUS xmlGetPrtTriggerAttr(char *attrName, char* attrValue);
extern PSX_STATUS xmlEndPrtTriggerObj(char *appName, char *objName);
extern PSX_STATUS xmlGetPrtTriggerEntryAttr(char *attrName, char* attrValue);
extern PSX_STATUS xmlEndPrtTriggerEntryObj(char *appName, char *objName);
extern PSX_STATUS xmlGetMacFilterAttr(char *attrName, char* attrValue);
extern PSX_STATUS xmlEndMacFilterObj(char *appName, char *objName);
extern PSX_STATUS xmlGetMacFilterEntryAttr(char *attrName, char* attrValue);
extern PSX_STATUS xmlEndMacFilterEntryObj(char *appName, char *objName);
extern PSX_STATUS xmlGetQosClsAttr(char *attrName, char* attrValue);
extern PSX_STATUS xmlEndQosClsObj(char *appName, char *objName);
extern PSX_STATUS xmlGetQosClsEntryAttr(char *attrName, char* attrValue);
extern PSX_STATUS xmlEndQosClsEntryObj(char *appName, char *objName);
extern PSX_STATUS xmlGetAccCntrlAttr(char *attrName, char* attrValue);
extern PSX_STATUS xmlEndAccCntrlObj(char *appName, char *objName);
extern PSX_STATUS xmlGetAccCntrlEntryAttr(char *attrName, char* attrValue);
extern PSX_STATUS xmlEndAccCntrlEntryObj(char *appName, char *objName);
extern PSX_STATUS xmlGetAccCntrlModeAttr(char *attrName, char* attrValue);
extern PSX_STATUS xmlStartAccCntrlModeObj(char *appName, char *objName);
extern PSX_STATUS xmlEndAccCntrlModeObj(char *appName, char *objName);
extern PSX_STATUS xmlGetDmzHostAttr(char *attrName, char* attrValue);
extern PSX_STATUS xmlStartDmzHostObj(char *appName, char *objName);
extern PSX_STATUS xmlEndDmzHostObj(char *appName, char *objName);
extern PSX_STATUS xmlGetServiceCtrlAttr(char *attrName, char* attrValue);
extern PSX_STATUS xmlStartServiceCtrlObj(char *appName, char *objName);
extern PSX_STATUS xmlEndServiceCtrlObj(char *appName, char *objName);
extern PSX_STATUS xmlGetDhcpClntNode(char *appName, char *objName, char *attrName,
                                   char* attrValue);
extern PSX_STATUS xmlGetDhcpClntAttr(char *attrName, char* attrValue);
extern PSX_STATUS xmlStartDhcpClntNode(char *appName, char *objName);
extern PSX_STATUS xmlEndDhcpClntNode(char *appName, char *objName);
extern PSX_STATUS xmlGetAtmTdObjNode(char *appName, char *objName, char *attrName,
                                   char* attrValue);
/*Added by echo for spi*/
extern PSX_STATUS xmlGetSpiNode(char *appName, char *objName, char *attrName,
				char *attrValue);
extern PSX_STATUS xmlStartSpiNode(char *appName, char *objName);
extern PSX_STATUS xmlEndSpiNode(char *appName, char *objName);

extern PSX_STATUS xmlGetAtmTdAttr(char *attrName, char* attrValue);
extern PSX_STATUS xmlStartAtmTdObjNode(char *appName, char *objName);
extern PSX_STATUS xmlEndAtmTdObjNode(char *appName, char *objName);
extern PSX_STATUS xmlGetLanNode(char *appName, char *objName, char *attrName,
                                char* attrValue);
extern PSX_STATUS xmlGetLanAttr(char *attrName, char* attrValue);
extern PSX_STATUS xmlStartLanObj(char *appName, char *objName);
extern PSX_STATUS xmlEndLanObj(char *appName, char *objName);
extern PSX_STATUS xmlGetWirelessObjNode(char *appName, char *objName, char *attrName,
                                        char* attrValue);
//for address translation
extern void xmlSetAddrTransAttr(FILE *file, const char *name, const UINT16 id, const PSI_VALUE value, const UINT16 length) ;
extern PSX_STATUS xmlGetAddrTransAttr(char *attrName, char *attrValue) ;
extern PSX_STATUS xmlGetAddrTransEntryAttr(char *attrName, char *attrValue) ;
extern PSX_STATUS xmlEndAddrTransObj(char *appName, char *objName) ;
extern PSX_STATUS xmlEndAddrTransEntryObj(char *appName, char *objName) ;

//for wireless repeater
extern void xmlSetWirelessWdsAttr(FILE *file, const char *name, const UINT16 id,
                                const PSI_VALUE value, const UINT16 length ) ;
extern PSX_STATUS xmlGetWirelessWdsAttr(char *attrName, char *attrValue) ;
extern PSX_STATUS xmlGetWirelessWdsEntryAttr(char *attrName, char *attrValue) ;
extern PSX_STATUS xmlEndWirelessWdsObj(char *appName, char *objName) ;
extern PSX_STATUS xmlEndWirelessWdsEntryObj(char *appName, char *objName) ;

extern PSX_STATUS xmlEndWirelessRadiusUserObject(char *appName, char *objName);
extern PSX_STATUS xmlGetRadiusEntryAttr(char *attrName, char *attrValue);
extern PSX_STATUS xmlEndRadiusEntryAttr(char *appName, char *objName);
extern PSX_STATUS xmlGetRadiusAttr(char *attrName, char *attrValue);

extern PSX_STATUS xmlStartWirelessObjNode(char *appName, char *objName);
extern PSX_STATUS xmlEndWirelessObjNode(char *appName, char *objName);
extern PSX_STATUS xmlGetWirelessVarsAttr(char *attrName, char* attrValue);
extern PSX_STATUS xmlStartWirelessVarsObj(char *appName, char *objName);
extern PSX_STATUS xmlEndWirelessVarsObj(char *appName, char *objName);
extern PSX_STATUS xmlGetWirelessMacFilterEntryAttr(char *attrName, char* attrValue);
extern PSX_STATUS xmlEndWirelessMacFilterEntryObj(char *appName, char *objName);
extern PSX_STATUS xmlGetWirelessMacFilterAttr(char *attrName, char* attrValue);
extern PSX_STATUS xmlEndWirelessMacFilterObj(char *appName, char *objName);
extern PSX_STATUS xmlGetRouteObjNode(char *appName, char *objName, char *attrName, char* attrValue);
extern PSX_STATUS xmlStartRouteObjNode(char *appName, char *objName);
extern PSX_STATUS xmlEndRouteObjNode(char *appName, char *objName);
extern PSX_STATUS xmlGetRouteAttr(char *attrName, char* attrValue);
extern PSX_STATUS xmlEndRouteObj(char *appName, char *objName);
extern PSX_STATUS xmlGetRouteEntryAttr(char *attrName, char* attrValue);
extern PSX_STATUS xmlEndRouteEntryObj(char *appName, char *objName);
extern PSX_STATUS xmlGetRipAttr(char *attrName, char* attrValue);
extern PSX_STATUS xmlStartRipObj(char *appName, char *objName);
extern PSX_STATUS xmlEndRipObj(char *appName, char *objName);
extern PSX_STATUS xmlGetRipIfcAttr(char *attrName, char* attrValue);
extern PSX_STATUS xmlEndRipIfcObj(char *appName, char *objName);
extern PSX_STATUS xmlGetRipIfcEntryAttr(char *attrName, char* attrValue);
extern PSX_STATUS xmlEndRipIfcEntryObj(char *appName, char *objName);
extern PSX_STATUS xmlGetDdnsNode(char *appName, char *objName, char *attrName, char* attrValue);
extern PSX_STATUS xmlStartDdnsObj(char *appName, char *objName);

extern PSX_STATUS xmlGetPMapObjNode(char *appName, char *objName, char *attrName, char* attrValue);
extern PSX_STATUS xmlStartPMapObjNode(char *appName, char *objName);
extern PSX_STATUS xmlEndPMapObjNode(char *appName, char *objName);
extern PSX_STATUS xmlGetPMapAttr(char *attrName, char* attrValue);
extern PSX_STATUS xmlEndPMapObj(char *appName, char *objName);
extern PSX_STATUS xmlGetPMapEntryAttr(char *attrName, char* attrValue);
extern void xmlSetPMapIfcCfgAttr(FILE *file, const char *name, const UINT16 id, const PSI_VALUE value,
                   const UINT16 length);
extern PSX_STATUS xmlGetPMapIfcCfgAttr(char *attrName, char* attrValue);
extern PSX_STATUS xmlStartPMapIfcCfgObj(char *appName, char *objName);
extern PSX_STATUS xmlEndPMapIfcCfgObj(char *appName, char *objName);
extern PSX_STATUS xmlEndPMapEntryObj(char *appName, char *objName);

//extern PSX_STATUS xmlGetDdnsObjNode(char *appName, char *objName, char *attrName, char* attrValue);
//extern PSX_STATUS xmlStartDdnsObjNode(char *appName, char *objName);
//extern PSX_STATUS xmlEndDdnsObjNode(char *appName, char *objName);
extern PSX_STATUS xmlGetDdnsAttr(char *attrName, char* attrValue);
extern PSX_STATUS xmlEndDdnsObj(char *appName, char *objName);
//extern PSX_STATUS xmlGetDdnsEntryAttr(char *attrName, char* attrValue);
//extern PSX_STATUS xmlEndDdnsEntryObj(char *appName, char *objName);
extern PSX_STATUS xmlGetAtmCfgNode(char *appName, char *objName, char *attrName,
                                   char* attrValue);
extern PSX_STATUS xmlStartAtmCfgNode(char *appName, char *objName);
extern PSX_STATUS xmlEndAtmCfgNode(char *appName, char *objName);
extern PSX_STATUS xmlGetAtmInitAttr(char *attrName, char* attrValue);
extern PSX_STATUS xmlStartAtmInitObj(char *appName, char *objName);
extern PSX_STATUS xmlEndAtmInitObj(char *appName, char *objName);

extern PSX_STATUS xmlGetAdslNode(char *appName, char *objName, char *attrName,
                                 char* attrValue);
extern PSX_STATUS xmlGetAdslAttr(char *attrName, char* attrValue);
extern PSX_STATUS xmlStartAdslObj(char *appName, char *objName);
extern PSX_STATUS xmlEndAdslObj(char *appName, char *objName);

extern PSX_STATUS xmlGetSntpNode(char *appName, char *objName, char *attrName,
                                 char* attrValue);
extern PSX_STATUS xmlGetSntpAttr(char *attrName, char* attrValue);
extern PSX_STATUS xmlStartSntpObj(char *appName, char *objName);
extern PSX_STATUS xmlEndSntpObj(char *appName, char *objName);
extern PSX_STATUS xmlGetToDObjNode(char *appName, char *objName, char *attrName, char* attrValue);
extern PSX_STATUS xmlStartToDObjNode(char *appName, char *objName);
extern PSX_STATUS xmlEndToDObjNode(char *appName, char *objName);
extern PSX_STATUS xmlGetToDAttr(char *attrName, char* attrValue);
extern PSX_STATUS xmlEndToDObj(char *appName, char *objName);
extern PSX_STATUS xmlGetToDEntryAttr(char *attrName, char* attrValue);
extern PSX_STATUS xmlEndToDEntryObj(char *appName, char *objName);
extern PSX_STATUS xmlSetVoiceNode(FILE* file, const char *appName, const UINT16 id,
                                  const PSI_VALUE value, const UINT16 length);

extern PSX_STATUS xmlGetVoiceNode(char *appName, char *objName, char *attrName, char* attrValue);
extern PSX_STATUS xmlStartVoiceNode(char *appName, char *objName);
extern PSX_STATUS xmlEndVoiceNode(char *appName, char *objName);
extern void  xmlSetMgcpAttr(FILE *file, const char *name, const UINT16 id, const PSI_VALUE value,
                            const UINT16 length);
extern void  xmlSetSipAttr(FILE* file, const char *appName, const UINT16 id,
                           const PSI_VALUE value, const UINT16 length);
extern PSX_STATUS xmlStartMgcpObjNode(char *appName, char *objName);
extern PSX_STATUS xmlEndMgcpObjNode(char *appName, char *objName);
extern PSX_STATUS xmlGetMgcpAttr(char *attrName, char* attrValue);
extern PSX_STATUS xmlStartSipObjNode(char *appName, char *objName);
extern PSX_STATUS xmlEndSipObjNode(char *appName, char *objName);
extern PSX_STATUS xmlGetSipAttr(char *attrName, char* attrValue);

extern PSX_STATUS xmlGetEthAttr(char *attrName, char* attrValue);
extern PSX_STATUS xmlSetIppNode(FILE* file, const char *appName, const UINT16 id,
                                const PSI_VALUE value, const UINT16 length);
extern PSX_STATUS xmlGetIppNode(char *appName, char *objName, char *attrName, char* attrValue);
extern PSX_STATUS xmlGetIppAttr(char *attrName, char* attrValue);
extern PSX_STATUS xmlStartIppObj(char *appName, char *objName);
extern PSX_STATUS xmlEndIppObj(char *appName, char *objName);
#if defined(__cplusplus)
}
#endif

#endif /* __PSIXML_H__ */
