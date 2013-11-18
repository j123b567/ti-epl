//****************************************************************************
// oai.h
// 
// Copyright (c) 2006-2008 National Semiconductor Corporation.
// All Rights Reserved
// 
// OS Abstraction Interface (OAI) include file.
//
// This can be customized as needed for a target O/S
//****************************************************************************

#ifndef _OAI_INCLUDE
#define _OAI_INCLUDE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "epl.h"

//#define WritePort( port, data) _outp( (NS_UINT16)(port), (NS_UINT16)(data))
//#define ReadPort( port) _inp( (NS_UINT16)(port))

void 
    OAIInitialize( 
        IN OAI_DEV_HANDLE oaiDevHandle);

void 
    OAIBeginRegCriticalSection(
        IN OAI_DEV_HANDLE oaiDevHandle);

void 
    OAIEndRegCriticalSection(
        IN OAI_DEV_HANDLE oaiDevHandle);

void 
    OAIBeginMultiCriticalSection(
        IN OAI_DEV_HANDLE oaiDevHandle);
void 
    OAIEndMultiCriticalSection(
        IN OAI_DEV_HANDLE oaiDevHandle);


// Define EXPORTED if we're building for Windows
#define EXPORT

#endif // _OAI_INCLUDE
