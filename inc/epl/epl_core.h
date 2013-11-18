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

EXPORT NS_STATUS EPLInitialize( void);

EXPORT void EPLDeinitialize( void);

EXPORT PEPL_DEV_HANDLE	
    EPLEnumDevice(
        IN OAI_DEV_HANDLE oaiDevHandle,
        IN NS_UINT deviceMdioAddress,
        IN EPL_ENUM_TYPE enumType);

EXPORT void
    EPLSetMgmtInterfaceConfig(
        IN PEPL_PORT_HANDLE portHandle,
        IN NS_BOOL  usePhyControlFrames,
        IN NS_BOOL  pcfDA_SEL,
        IN NS_UINT8 pcfBufSize);

EXPORT PEPL_DEV_INFO 
    EPLGetDeviceInfo(
        IN PEPL_DEV_HANDLE deviceHandle);

EXPORT NS_BOOL
    EPLIsDeviceCapable(
        IN PEPL_DEV_HANDLE deviceHandle,
        IN EPL_DEVICE_CAPA_ENUM capability);

EXPORT void
    EPLResetDevice(
        IN PEPL_DEV_HANDLE deviceHandle);

EXPORT PEPL_PORT_HANDLE
    EPLEnumPort(
        IN PEPL_DEV_HANDLE deviceHandle,
        IN NS_UINT portIndex);

EXPORT PEPL_DEV_HANDLE
    EPLGetDeviceHandle(
        IN PEPL_PORT_HANDLE portHandle);

EXPORT NS_UINT
    EPLReadReg(
        IN PEPL_PORT_HANDLE portHandle,
        IN NS_UINT registerIndex);

EXPORT void
    EPLWriteReg(
        IN PEPL_PORT_HANDLE portHandle,
        IN NS_UINT registerIndex,
        IN NS_UINT value);

EXPORT NS_UINT
    EPLGetPortMdioAddress(
        IN PEPL_PORT_HANDLE portHandle);

EXPORT void
    EPLSetPortPowerMode(
        IN PEPL_PORT_HANDLE portHandle,
        IN NS_BOOL powerOn);

#ifdef __cplusplus
}
#endif

#endif // _EPL_CORE_INCLUDE
