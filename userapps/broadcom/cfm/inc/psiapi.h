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
//  Filename:       psiapi.h
//  Author:         Peter T. Tran
//  Creation Date:  12/26/01
//
******************************************************************************
//  Description:
//      Define the PsiApi functions.
//
*****************************************************************************/

#ifndef __PSIAPI_H__
#define __PSIAPI_H__

/********************** Include Files ***************************************/

#include "psidefs.h"

/********************** Global APIs Definitions *****************************/

#if defined(__cplusplus)
extern "C" {
#endif
extern PSI_HANDLE BcmPsi_appOpen(char* appId);
extern PSI_STATUS BcmPsi_appClose(PSI_HANDLE appId);
extern PSI_STATUS BcmPsi_appRemove(PSI_HANDLE appId);
extern PSI_STATUS BcmPsi_objRemove(PSI_HANDLE appId, UINT16 objectId);
extern PSI_STATUS BcmPsi_objStore(PSI_HANDLE appId, UINT16 objectId,
                                  PSI_VALUE value, UINT16 length);
extern PSI_STATUS BcmPsi_objRetrieve(PSI_HANDLE appId, UINT16 objectId,
                                     PSI_VALUE value, UINT16 len,
                                     UINT16* retLen);
extern PSI_STATUS BcmPsi_flush(void);
extern PSI_STATUS BcmPsi_writeFileToFlash(char *filename);
extern PSI_STATUS BcmPsi_writeStreamToFlash(char *filestream, UINT32 len);
extern PSI_STATUS BcmPsi_writeFlashToFile(void);
extern PSI_STATUS BcmPsi_profileStore(void);
extern PSI_STATUS BcmPsi_profileErase(void);
extern PSI_STATUS BcmPsi_profileRetrieve(void);
extern void BcmPsi_delSysPasswdFromFile(void) ;
extern void BcmPsi_setWlVarFromFile(void) ;
extern void BcmPsi_init(void);
extern void BcmPsi_unInit(void);
#if defined(__cplusplus)
}
#endif

#endif
