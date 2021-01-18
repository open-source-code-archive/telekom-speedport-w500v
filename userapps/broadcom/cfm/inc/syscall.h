/*****************************************************************************
//
//  Copyright (c) 2000-2001  Broadcom Corporation
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
//  Filename:       syscall.h
//  Author:         Peter T. Tran
//  Creation Date:  12/26/01
//
******************************************************************************
//  Description:
//      Define the global constants, and functions for sysCall utility.
//
*****************************************************************************/

#ifndef __SYS_CALL_H__
#define __SYS_CALL_H__
#include <netinet/in.h>

/********************** Global Functions ************************************/

#define FILE_OPEN_OK			0
#define FILE_OPEN_ERR			-1

#define MNTR_STS_OK			0
#define MNTR_STS_ADSL_DOWN		1
#define MNTR_STS_PPP_AUTH_ERR		2
#define MNTR_STS_PPP_DOWN		3
#define MNTR_STS_OPEN_ERR		4
#define MNTR_STS_DHCPC_PROGRESS  	5
#define MNTR_STS_DHCPC_FAIL   		6
#define MNTR_STS_ADSL_TRAINING		7

#define DHCPC_STS_FAIL           	0
#define DHCPC_STS_SUCCESS        	1
#define DHCPC_FAIL_MAX           	15

// Values for network protocol
#define PROTO_PPPOE			0
#define PROTO_PPPOA			1
#define PROTO_MER			2
#define PROTO_BRIDGE			3
#define PROTO_PPPOE_RELAY	        4
#define PROTO_IPOA			5
#if SUPPORT_ETHWAN
#define PROTO_IPOWAN                    6
#endif
#define PROTO_NONE 			10

#define SYSTEM_APPID       "SystemInfo"
#define SYS_USER_NAME_ID   1
#define SYS_PASSWORD_ID    2
#define SPT_USER_NAME_ID   3
#define SPT_PASSWORD_ID    4
#define USR_USER_NAME_ID   5
#define USR_PASSWORD_ID    6
#define SYS_DFT_GTWY_ID    7
#define SYS_DNS_ID         8
#define SYS_LOG_ID         9
#define SYS_AUTH_TIME_ID   10
#define SYS_SNMP_ID        11
#define SYS_FLAG_ID        12
#define SYS_ACTIVE_SERVICE_ID 13

// Values that are used in syscall.c
#define SYS_CMD_LEN        256

#define IP_TBL_COL_NUM     0
#define IP_TBL_COL_PKTS    1
#define IP_TBL_COL_BYTES   2
#define IP_TBL_COL_TARGET  3
#define IP_TBL_COL_PROT    4
#define IP_TBL_COL_OPT     5
#define IP_TBL_COL_IN      6
#define IP_TBL_COL_OUT     7
#define IP_TBL_COL_SRC     8
#define IP_TBL_COL_DST     9
#define IP_TBL_COL_MAX     10

#define UPNP_IP_ADDRESS    "239.255.255.250"


#if defined(__cplusplus)
extern "C" {
#endif
#define bcmSystem(cmd)		bcmSystemEx (cmd,1)
#define bcmSystemMute(cmd)	bcmSystemEx (cmd,0)
int tcmSystem(char *command);
int bcmSystemEx (char *command, int printFlag);
/*****Added by echo ****************************/
int tcmSystem (char *command);
int bcmSystemNoHang (char *command);
int bcmGetPid (char *command);
int bcmCreateDhcpCfg(char *ipAddr, char *mask, char *addrStart, char *addrEnd,
                     char *dns1, char *dns2, int leasedTime, int protocol,
                     int enblNat, int enblFirewall);
int bcmCreateIpExtDhcpCfg(char *lanAddr, char *mask, char *wanAddr);
int bcmCreateLocalDhcpCfg(char *addr, char *mask);
int bcmCreateResolvCfg(char *dns1, char *dns2);
int bcmCreateLoginCfg(char *cp_admin, char *cp_support, char *cp_user);
int bcmGetAdslStatus(void);
int bcmGetPppStatus(char *str, int len, char *devName);
int bcmGetDhcpcStatus(char *str, int len);
int bcmGetSystemStatus(char *str, int len);
int bcmSetSystemStatus(int status);
int bcmSetIpExtension(int ipExt);
int bcmGetIpExtension(char *str, int len);
void bcmDisplayLed(int status);
void bcmGetDns(char *dns);
void bcmGetDns2(char *dns);
void bcmGetDnsSettings(int *mode, char *primary, char *secondary);
void bcmRestartDnsProbe(void);
void bcmConfigDns(char *dns1, char *dns2, int dynamic);
void bcmRemoveDefaultGatewayByWanIf(char *wanIf);
void bcmGetDefaultGateway(char *gtwy, char *wanIf);
int  bcmIsDefaultGatewayExisted(char *gw, char *wanIf);
void bcmSetAutoDefaultGateway(char *errMsg);
void bcmSetStaticDefaultGateway(char *gw, char *wanIf, char *errMsg);
void bcmKillAllApps(void);
void disconnectPPP(void);
void setWanLinkStatus(int up);
int bcmCheckInterfaceUp(char *devname);
int bcmSetIpExtInfo(char *wan, char *gateway, char *dns);
void bcmGetIpExtInfo(char *buf, int type);
int bcmGetIfcIndexByName(char *ifcName);
char *bcmGetIfcNameByIndex(int ifcIdx, char *ifcName);
int bcmIsValidIfcName(char *ifcName);
char *bcmGetIfcNameById(int ifcId, char *ifcName);
void getPppoeServiceName(char *service, char *ifName);
void bcmGetDefaultRouteInterfaceName(char *ifcName);

void bcmSetConnTrackMax(void);
void bcmResetConnTrackTable(void);
void bcmHandleConnTrack(void);
void bcmInsertModules(char *path);
void bcmInsertModule(char *modName);
int bcmIsModuleInserted(char *modName);
int bcmRemoveIpTableRule(char *device, char *table, char *chain);
void bcmRemoveAllIpTableRules(char *device);
int bcmRemoveRipIpTableRule(void);
int bcmRemoveUpnpIpTableRule(void);
void bcmInsertAllUpnpIpTableRules(void);
int bcmGetIntfNameSocket(int socketfd, char *intfname);
int bcmCheckEnable(char *appName, struct in_addr clntAddr);

int bcmRemoveEbTableRule(char *device, char *table, char *chain);
void bcmRemoveAllEbTableRules(char *device);

void parseStrInfo(char *info, char *var, char *val, int len);
void bcmConvertStrToShellStr(char *str, char *buf);
void bcmProcessMarkStrChars(char *str);
int  bcmIsMarkStrChar(char c);
void bcmSetSwVer(char *swVer);
void bcmGetSwVer(char *swVer, int size);
void bcmSetAdslPhyVer(char *adslPhyVer) ; //add by Ali
void bcmSetImageDate(char *imageDate);	//add by Ali
void bcmGetImageDate(char *imageVer, int size)  ;	//add by Ali
void bcmGetAdslPhyVer(char *hwVer, int size) ;	//add by Ali
int isAccessFromLan(struct in_addr clntAddr);
int checkChipId(char *strTagChipId, char *sig2);
int TecomGetSystemStatus(char *str, int len, int activeServiceID) ;

void bcmRemoveModules(int lanIf);
int bcmWaitIntfExists(char *ifName);
int base64Encode(const void *inp, int insize, char **outptr);
void base64Decode(unsigned char *dest, char *src, int *rawLength);
// Keven Kuo
int SHA1Encription( char *input, char *output );
void Tcm_Remove_Passwords(char *input);
void Tcm_Add_Passwords(char *source_buffer);
void Tcm_Set_Passwords(char *input);

#define BCM_PPPOE_CLIENT_STATE_PADO          0   /* waiting for PADO */
#define BCM_PPPOE_CLIENT_STATE_PADS          1   /* got PADO, waiting for PADS */
#define BCM_PPPOE_CLIENT_STATE_CONFIRMED     2   /* got PADS, session ID confirmed */
#define BCM_PPPOE_CLIENT_STATE_DOWN          3   /* totally down */
#define BCM_PPPOE_CLIENT_STATE_UP            4   /* totally up */
#define BCM_PPPOE_SERVICE_AVAILABLE          5   /* ppp service is available on the remote */

#define BCM_PPPOE_AUTH_FAILED                7

#define BCM_PRIMARY_DNS                      1
#define BCM_SECONDARY_DNS                    0

#if defined(__cplusplus)
}
#endif

#endif
