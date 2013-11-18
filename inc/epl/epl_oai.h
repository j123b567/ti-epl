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

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "epl.h"

#define WritePort( port, data) _outp( (NS_UINT16)(port), (NS_UINT16)(data))
#define ReadPort( port) _inp( (NS_UINT16)(port))

void 
	OAIInitialize( 
		IN OAI_DEV_HANDLE oaiDevHandle);

void
	*OAIAlloc( 
		IN NS_UINT sizeInBytes);

void 
	OAIFree( 
		IN void *memPtr);

HANDLE 
	OAICreateMutex( 
		void );

void 
	OAIReleaseMutex( 
		IN HANDLE hMutex );

void 
	OAIBeginCriticalSection( 
		IN HANDLE hMutex );

void 
	OAIEndCriticalSection( 
		IN HANDLE hMutex );

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

void
	OAIManagementError(
        IN void *oaiDevHandle);

// Define EXPORTED if we're building for Windows
#ifdef EXPORTED
    #define EXPORT __declspec(dllexport)
#else
    #define EXPORT
#endif

#endif // _OAI_INCLUDE
