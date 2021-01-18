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
//  Filename:       voiceapi.h
//
******************************************************************************
//  Description:
//      Define the Voice Configuration Api functions.
//
*****************************************************************************/

#ifndef VOICE_API_H
#define VOICE_API_H

#define VOICE_APPID           "Voice"
#define VOICE_MGCPINFO_ID     1
#define VOICE_SIPINFO_ID      2
#define VOICE_LESINFO_ID      3

#define CFG_MAX_HOST_STR_LEN           80
#define CFG_MAX_IPADDR_STR_LEN         20
#define CFG_MAX_FQDN_STR_LEN           80
#define CFG_MAX_PORT_STR_LEN           8
#define CFG_MAX_GWNAME_STR_LEN         40
#define CFG_MAX_IFNAME_STR_LEN         12
#define CFG_MAX_CODEC_STR_LEN          8
#define CFG_MAX_EXTENSION_STR_LEN      32		// eric modified to 32
#define CFG_MAX_PASSWORD_STR_LEN       20
/* Tommy */
#define CFG_MAX_COUNTRY_STR_LEN        20
#define CFG_MAX_AALN_STR_LEN           5
#define CFG_MAX_GAIN_STR_LEN           5
#define CFG_MAX_PSTNCODE_STR_LEN       5
#define CFG_MAX_HBTIMER_STR_LEN        5
#define CFG_MAX_EMERGENCY_STR_LEN      127

#define  VOICE_STATUS_DIR              "/var/voice"
#define  VOICE_STATUS_FILENAME         "status"

#define  VOICE_TIME_NEEDED_FOR_INIT    5
#define  VOICE_TIME_NEEDED_FOR_DEINIT  6


/********************** Include Files ***************************************/

#include <bcmtypes.h>

typedef enum VOICE_APP_STATUS
{
   VOICE_APP_DEINITIALIZED = 0,
   VOICE_APP_INITIALIZED,
   VOICE_APP_INIT_IN_PROGRESS,
   VOICE_APP_DEINIT_IN_PROGRESS,
   VOICE_APP_STATUS_UNKNOWN,

} VOICE_APP_STATUS;

/********************** Global APIs Definitions *****************************/

#if defined(__cplusplus)
extern "C" {
#endif
extern void BcmVoice_Init(void);
extern void BcmVoice_Uninit(void);
extern void BcmVoice_Store(void);
extern void BcmVoice_Retrieve(int isDefault);
extern void BcmVoice_GetVar(char *varName, char *varValue);
extern void BcmVoice_SetVar(char *varName, char *varValue);
extern void BcmVoice_ShowVars(void);
extern void BcmVoice_ShowCmdSyntax(void);
extern void BcmVoice_ProcessSetCmd(char* cmdLine);
extern void BcmVoice_Start(void);
extern void BcmVoice_Stop(void);
extern void BcmVoice_EndptConsoleCmd(int lineId, int cnxId, int cmdId);
extern VOICE_APP_STATUS  BcmVoice_GetAppStatus(void);
#if defined(__cplusplus)
}
#endif

#endif
