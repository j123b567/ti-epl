//****************************************************************************
// epl_link.h
// 
// Copyright (c) 2006-2008 National Semiconductor Corporation.
// All Rights Reserved
// 
// This file contains all of the link related definitions and prototypes
//
//****************************************************************************

#ifndef _EPL_LINK_INCLUDE
#define _EPL_LINK_INCLUDE

#include "epl.h"

typedef enum {
    MDIX_AUTO,
    MDIX_FORCE_NORMAL,
    MDIX_FORCE_SWAP
} EPL_MDIX_ENUM;

typedef struct EPL_LINK_STS {
    NS_BOOL linkup;
    NS_BOOL autoNegEnabled;
    NS_BOOL autoNegCompleted;
    NS_UINT speed;
    NS_BOOL duplex;
    NS_BOOL mdixStatus;
    NS_BOOL autoMdixEnabled;
    NS_BOOL polarity;
    NS_BOOL energyDetectPower;
}EPL_LINK_STS,*PEPL_LINK_STS;

typedef struct EPL_LINK_CFG {
    NS_BOOL autoNegEnable;
    NS_UINT speed;
    NS_BOOL duplex;
    NS_BOOL pause;
    EPL_MDIX_ENUM autoMdix;
    NS_BOOL energyDetect;
    NS_UINT energyDetectErrCountThresh;
    NS_UINT energyDetectDataCountThresh;
}EPL_LINK_CFG,*PEPL_LINK_CFG;

// EPL Function Prototypes
#ifdef __cplusplus
extern "C" {
#endif

EXPORT NS_BOOL
    EPLIsLinkUp (
        IN PEPL_PORT_HANDLE portHandle);

EXPORT void
    EPLSetLinkConfig (
        IN PEPL_PORT_HANDLE portHandle,
        IN PEPL_LINK_CFG linkConfigStruct);

EXPORT void
    EPLGetLinkStatus (
        IN PEPL_PORT_HANDLE portHandle,
        IN OUT PEPL_LINK_STS linkStatusStruct);

EXPORT void
    EPLSetLoopbackMode (
        IN PEPL_PORT_HANDLE portHandle,
        IN NS_BOOL enableLoopback);

EXPORT void
    EPLRestartAutoNeg (
        IN PEPL_PORT_HANDLE portHandle);

#ifdef __cplusplus
}
#endif

#endif // _EPL_LINK_INCLUDE
