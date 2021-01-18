#ifndef __TECOM_VOIPCFG_API_H__
#define __TECOM_VOIPCFG_API_H__

#include "tecom_voipcfg_defs.h"

#if defined(__cplusplus)
extern "C" {
#endif

	void Tecom_voipcfgInit(void);
	void Tecom_voipcfgunInit(void);

	void Tecom_voipcfgPortSetVar(char *varName, char *varValue);
	void Tecom_voipcfgPortGetVar(char *varName, char *varValue);
	void Tecom_voipcfgPortStore(void);


	void Tecom_voipcfgTestGetVar(char *varName, char *varValue);
	void Tecom_voipcfgTestSetVar(char *varName, char *varValue);

	void Tecom_voipcfgAccountSetVar(char *varName, char *varValue);
	void Tecom_voipcfgAccountGetVar(char *varName, char *varValue);
	void Tecom_voipcfgTonlineStore(void);
	void Tecom_voipcfgAnotherStore(void);

	void Tecom_voipcfgprovNameStore(void);

	void Tecom_voipcfgEmgSetVar(char *varName, char *varValue);
	void Tecom_voipcfgEmgGetVar(char *varName, char *varValue);
	void Tecom_voipcfgEmgStore(void);
	void Tecom_voipcfgEmgSet(PEMERGENCY_CALL_INFO emgInfo);

	void Tecom_voipcfgOutgoingSetVar(char *varName, char *varValue);
	void Tecom_voipcfgOutgoingGetVar(char *varName, char *varValue);
	void Tecom_voipcfgOutgoingStore(void);

	void Tecom_voipcfgIncomingSetVar(char *varName, char *varValue);
	void Tecom_voipcfgIncomingGetVar(char *varName, char *varValue);
	void Tecom_voipcfgIncomingStore(void);

	void Tecom_voipcfgQuickSetVar(char *varName, char *varValue);
	void Tecom_voipcfgQuickStore(void);
	//void Tecom_voipcfgQuickInfoGet(PQUICK_CALL_INFO quickInfo);
	PQUICK_CALL_INFO Tecom_voipcfgQuickInfoGet(void);

	void Tecom_setWreg(PPARTIA_MATCH_ENTRY pEntry);
	void Tecom_voipcfgPartialStore(void);
	int Tecom_voipcfggetPartialnetSelectByNumber(char *name);
	int Tecom_voipcfggetPartialNrByNumber(char *name);
    int Tecom_voipIsAccountExist(void);

	int Tecom_voipcfggetPartialNum(void);
	void *Tecom_voipcfggetPartialEntry(void *pVoid, PPARTIA_MATCH_ENTRY pEntry);
	void Tecom_replaceWreg(char *old_number, PPARTIA_MATCH_ENTRY pEntry);
	void Tecom_delWreg(PPARTIA_MATCH_ENTRY pEntry);
	void TecomVoice_Start(void);
	void TecomVoice_Stop(void);
	void TecomVoice_setCurSipCfg(char *provName);
	void TecomVoice_reset(void);
	void TecomVoice_processSetCmd(char *cmdLine);
	void TecomVoice_showCmdSyntax(void);
	void TcomVoice_showSipCfg(void);
	VOICE_APP_STATUS TecomVoice_getAppStatus(void);
	void Tecom_voipSendMsg2CM(TECOM_UPDATE_STATE updateState);
	void Tecom_voipcfgStatusGetVar(char *varName, char *varValue);
	void Tecom_updatevoipApp4WanChanged(int status);
       int Tecom_voipcfgVarCheck(void);  /* TECOM--20050915--leander show correct Reg State after loading Config.bin */
	int Tecom_voipcfg_isProvNameExist(void);
	int Tecom_voipcfg_isTonlineAccExist(void);
	int Tecom_voipcfg_isAnotherAccExist(void);
	/*Added by Echo 2006-04-05 for update iptable rules when wan changed.*/
        void TecomVoice_updateIptables4WanChanged(void);
#if defined(__cplusplus)
}
#endif
#endif
