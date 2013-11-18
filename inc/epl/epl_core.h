//****************************************************************************
// epl_core.h
// 
// Copyright (c) 2006-2008 National Semiconductor Corporation.
// All Rights Reserved
// 
// This file contains all of the EPL core definitions and prototypes
//
//****************************************************************************

#ifndef _EPL_CORE_INCLUDE
#define _EPL_CORE_INCLUDE

#include "epl.h"

// EPL Function Prototypes
#ifdef __cplusplus
extern "C" {
#endif

EXPORT NS_UINT
    EPLReadReg(
        IN PEPL_PORT_HANDLE portHandle,
        IN NS_UINT registerIndex);

EXPORT void
    EPLWriteReg(
        IN PEPL_PORT_HANDLE portHandle,
        IN NS_UINT registerIndex,
        IN NS_UINT value);

#ifdef __cplusplus
}
#endif

#endif // _EPL_CORE_INCLUDE
