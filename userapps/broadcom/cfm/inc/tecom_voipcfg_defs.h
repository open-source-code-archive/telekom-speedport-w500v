//*****************************************************************************
//
//  Copyright (c) 2003-2005  TECOM Corporation
//  All Rights Reserved
//  No portions of this material may be reproduced in any form without the
//  written permission of:
//          Tecom Wuhan Corporation
//          16215 Eric liu
//          Tecom Wuhan 619
//  All information contained in this document is Tecom Wuhan Corporation
//  company private, proprietary, and trade secret.
//
//******************************************************************************
//
//  Filename:       tecom_fwschedule_defs.h
//  Author:         Eric liu
//  Creation Date:  04/19/05
//
//******************************************************************************
//  Description:
//      Define the Voip Releated data Structure.
//
//*****************************************************************************/

#ifndef __TECOM_VOIP_CFG_DEFS_H__
#define __TECOM_VOIP_CFG_DEFS_H__

/********************** Include Files ***************************************/

#include "psiapi.h"
#include "vodslapi.h"

#include <sys/types.h>
#include <signal.h>

/**********************  define conf files **********************************/
#define	PORT_SETTING_FILE "/var/tcm_port.conf"
#define	EMG_CONF_FILE 		"/var/tcm_emg.conf"
#define	OUTBLOCK_CONF_FILE "/var/tcm_outgoing.conf"
#define	INBLOCK_CONF_FILE	"/var/tcm_incoming.conf"
#define	PARTIAL_CONF_FILE "/var/tcm_partial.conf"
#define	SHORTDIAL_CONF_FILE "/var/tcm_short.conf"
#define	BCM_CMTASK_PID_FILE "/var/Bcm_cmtask.pid"
#define	UPDATE_OPTION_FILE	"/var/tcm_updateoption"
#define	OUTGOING_CALL_LOG_FILE_EP0 "/var/tcm_outgoingep0.log"
#define	OUTGOING_CALL_LOG_FILE_EP1 "/var/tcm_outgoingep1.log"
#define	INCOMING_CALL_LOG_FILE_EP0 "/var/tcm_incomingep0.log"
#define	INCOMING_CALL_LOG_FILE_EP1 "/var/tcm_incomingep1.log"

#define PPP_UP 1
#define PPP_DOWN 0

/********************** Global Types ****************************************/
typedef enum {
   VOIP_STS_OK = 0,
   VOIP_STS_ERR_GENERAL,
   VOIP_STS_ERR_MEMORY,
   VOIP_STS_ERR_OBJECT_NOT_FOUND
} VOIP_STATUS;

typedef enum _TECOM_UPDATE_STATE_
{
	TCM_UPDATE_DIALTBLS_ERROR,		// update dialplan tables error
	TCM_UPDATE_DIALTBLS_SUCCESS,	// update dialplan tables success
	TCM_UPDATE_PORTSETTING = 1,
	TCM_UPDATE_EMG_TBL = 2,
	TCM_UPDATE_OUTGOING_TBL = 4,
	TCM_UPDATE_INCOMING_TBL = 8,
	TCM_UPDATE_PARTIAL_TBL = 16,
	TCM_UPDATE_SHORT_TBL = 32,
	TCM_UPDATE_ALL_DIALTBLS = 64,	// update all dial plan tables
	TCM_UPDATE_PORTSETTING_ERROR,
	TCM_UPDATE_EMG_TBL_ERROR,
	TCM_UPDATE_OUTGOING_TBL_ERROR,
	TCM_UPDATE_INCOMING_TBL_ERROR,
	TCM_UPDATE_SHORT_TBL_ERROR,
	TCM_UPDATE_PARTIAL_TBL_ERROR,
	TCM_UPDATE_SIP_UNREGISTER, // Samuel 05/05/2006, do SIP unresigter before call TecomVoice_reset.
} TECOM_UPDATE_STATE;

/*Vinson add 2006-02-22 begin*/
typedef enum _TECOM_FIFO_TYPE_
{
	TCM_UPDATE_DIALPLAN = 1,
	TCM_DELETE_OUTGOING_CALL_LOG,
	TCM_DELETE_INCOMING_CALL_LOG,
	TCM_PPP_UP,
	TCM_PPP_DOWN,
	TCM_SIP_UNREGISTER, // Samuel 05/05/2006, do SIP unresigter before call TecomVoice_reset.
	UNKONWN_TCM_FIFO_TYPE
}TECOM_FIFO_TYPE;

typedef struct _TCM_UPDATE_DIALPLAN_MSG_T_ {
	long 	mType;
	int 	updateType;
} TCM_UPDATE_DIALPLAN_MSG_T;

/********************** Global Constants ************************************/

#if defined(__cplusplus)
extern "C" {
#endif

#define PARTIAL_MAX 50
#define EMERGENCY_MAX 10
#define OUTGOING_MAX 20
#define INCOMING_MAX 20
#define QUICKCALL_MAX 100
#define DESCRIPTION_MAXCHAR 20
#define TELENUMBER_MAXCHAR 64
#define AUTHNAME_MAXCHAR	65
#define PASSWORD_MAXCHAR 256
#define WEB_VALUE_LEN_VOIP 256
#define CALL_LOG_MAX	20
#define AREA_CODE_MAX 10


#define TECOM_VOIP_CFG_APP_ID "TecomVoipCfg"
#define TECOM_VOIP_PROVIDERNAME_OBJECT_ID 1
#define TECOM_VOIP_ACCOUNT_TONLINE_OBJECT_ID 2
#define TECOM_VOIP_ACCOUNT_ANOTHER_OBJECT_ID 3
#define TECOM_VOIP_PORTSETTING_OBJECT_ID 4
#define TECOM_VOIP_PARTIAL_MATCH_NUM_ID 5
#define TECOM_VOIP_PARTIAL_MATCH_TBL_ID 6
#define TECOM_VOIP_EMERGENCY_CALL_OBJECT_ID 7
#define TECOM_VOIP_OUTGOING_BLACK_OBJECT_ID 8
#define TECOM_VOIP_INCOMING_BLACK_OBJECT_ID 9
#define TECOM_VOIP_QUICK_CALL_OBJECT_ID 10
#define TECOM_VOIP_SIPCFG_OBJECT_ID 11		// not used yet
#define TECOM_VOIP_OUTGOING_CALL_LOG_OBJECT_ID 12
#define TECOM_VOIP_INCOMING_CALL_LOG_OBJECT_ID 13

/******************** Data structure definition*****************************/

typedef struct _VOIP_PROVIDERNAME_INFO {
	char provName[16];
} VOIP_PROVIDERNAME_INFO_T, *PVOIP_PROVIDERNAME_INFO_T;

typedef struct _VOIP_ACCOUNT_T_INFO_ {
	char	telenumber_TONLINE[TELENUMBER_MAXCHAR];		//telephone number T_ONLINE
	char	email_TONLINE[AUTHNAME_MAXCHAR];	//email address T_ONLINE, authname at t-online
	char	password_TONLINE[PASSWORD_MAXCHAR];			//password T_ONLINE
	char	registrar[CFG_MAX_HOST_STR_LEN];
	char	domainName[CFG_MAX_HOST_STR_LEN];
	int	enable_checkVAD_T;		//flags of Sprechpausen-Erkennung (VAD)
	int	enable_compres_T;		//flags of Bandbreitenoptimierte Sprachkompression
	/*Vinson add 20060308*/
	int	enable_areaCode_T;              // flags of areaCode
	char	areaCode_T[AREA_CODE_MAX];      // area code
	} VOIP_ACCOUNT_T_INFO, *PVOIP_ACCOUNT_T_INFO;

typedef struct _VOIP_ACCOUNT_A_INFO_ {
	char	telenumber_Another[TELENUMBER_MAXCHAR];		//telephone number Another
	char	username_Another[AUTHNAME_MAXCHAR];		// it is authname indeed
	char	password_Another[PASSWORD_MAXCHAR];
	char	registrar[CFG_MAX_HOST_STR_LEN];
	char	domainName[CFG_MAX_HOST_STR_LEN];
	int	regport_Another ;
	int	enable_userN_A ;
	int	dtmfstatus_Another ;
	int	enable_checkVAD_A;			//flags of Sprechpausen-Erkennung (VAD)
	int	enable_compres_A;		//flags of Bandbreitenoptimierte Sprachkompression
	/*Vinson add 20060308*/
	int	enable_areaCode_A;              // flags of areaCode 
	char	areaCode_A[AREA_CODE_MAX];      // area code
} VOIP_ACCOUNT_A_INFO, *PVOIP_ACCOUNT_A_INFO;

typedef struct _VOIP_SIPCFG_INFO_T_ {
	char proxyAddr[CFG_MAX_HOST_STR_LEN];		// proxy address
	char proxyPort[8];								// proxy port
	char registrarAddr[CFG_MAX_HOST_STR_LEN];	// registrar address
	char registrarPort[8];							// registrar port
	char logserverAddr[CFG_MAX_HOST_STR_LEN];	// logserver address
	char logserverPort[8];							// logserver port
	char domainName[CFG_MAX_HOST_STR_LEN];		// realm name
	char interfaceName[12];							// interface, "br0" or wanif if exists
	char authname[AUTHNAME_MAXCHAR];				// authentication name
	char phoneExt[TELENUMBER_MAXCHAR];			// phone number on registrar
	char password[PASSWORD_MAXCHAR];				// password used for authentication name
	int  dtmfState ;
	int  enable_checkVAD;						//flags of Sprechpausen-Erkennung (VAD)
	int  enable_compres;        				      //flags of Bandbreitenoptimierte Sprachkompression
	/*Vinson add 20060308*/
	int	enable_areaCode;                                    // flags of areaCode 
	char	areaCode[AREA_CODE_MAX];            // area code
}	VOIP_SIPCFG_INFo_T;

typedef struct _VOIP_PORTSETTING_INFO_ {
	int		pri_select;							//flags of primary phonenumber select
	int		sec_select;							//flags of secondry phonenumber select
	int		enbl_2line_dial;          //flag of whether allow user dial '2#xxx' out
	int		numberHide;						//flags of Rufnummer unterdrücken
	int		enable_CLIP;								//flags of Anzeige der Rufnummer (CLIP)
	int		enable_Anklopfen;						//flags of Anklopfen select
	int		enable_Analog;							//flags of analoger telefonanschluss
	int  		enable_Fallback;					//flags of enable fallback function
} VOIP_PORTSETTING_INFO, *PVOIP_PORTSETTING_INFO;

typedef struct _PARTIA_MATCH_ENTRY_ {
	char	partial_number[TELENUMBER_MAXCHAR];			//prefix for partial match
	int		net_select;								//select voip, pstn line or both
	} PARTIA_MATCH_ENTRY, *PPARTIA_MATCH_ENTRY;

typedef struct 	_EMERGENCY_CALL_INFO_ {
	char	emergency_number[EMERGENCY_MAX][TELENUMBER_MAXCHAR];
	char	emergency_description[EMERGENCY_MAX][DESCRIPTION_MAXCHAR];
	} EMERGENCY_CALL_INFO, *PEMERGENCY_CALL_INFO;				//note: first three emergency calls are fixed by DT

typedef struct _OUTGOING_BLACK_INFO_ {
	char	outgoing_black[OUTGOING_MAX][TELENUMBER_MAXCHAR];
	int		net_select[OUTGOING_MAX];
	} OUTGOING_BLACK_INFO, *POUTGOING_BLACK_INFO;

typedef struct _INCOMING_BLACK_INFO_ {
	char	incoming_black[INCOMING_MAX][TELENUMBER_MAXCHAR];
	} INCOMING_BLACK_INFO, *PINCOMING_BLACK_INFO;

typedef struct _QUICK_CALL_INFO_ {
	char	quick_description[QUICKCALL_MAX][DESCRIPTION_MAXCHAR];
	char	quick_number[QUICKCALL_MAX][TELENUMBER_MAXCHAR];
	int		net_select[QUICKCALL_MAX];
	} QUICK_CALL_INFO, *PQUICK_CALL_INFO;

typedef struct _CALL_LOG_ENTRY_T_
{
	char telenumber[TELENUMBER_MAXCHAR];
	time_t startTime;
	time_t endTime;
	time_t elapsedTime;
	int isAnswered ;
	int endpt;
	int issaved;   //Vinson add for delete call log 20060216
} CALL_LOG_ENTRY_T, *PCALL_LOG_ENTRY_T;

typedef struct _CALL_LOG_INDEX_
{
	int	outgoingIndex;
	int	incomingIndex;
} CALL_LOG_INDEX;

typedef enum _VOICE_TEST_RESULT {
	VOICE_TEST_NA,
	VOICE_TEST_OK,
	VOICE_TEST_NO_WAN,
	VOICE_TEST_DATA_ERROR
} VOICE_TEST_RESULT;

typedef struct _VOIP_TEST_INFO {
	VOICE_TEST_RESULT result;
	int need_test;
	int pppoe_restart;
} VOICE_TEST_INFO;

#if defined(__cplusplus)
}
#endif
#endif
