//****************************************************************************
// oai.c (Windows Version)
// 
// Copyright (c) 2006-2008 National Semiconductor Corporation.
// All Rights Reserved
// 
// OS Abstraction Interface (OAI) implementation for Windows.
//****************************************************************************

// Prevent inclusion of winsock.h in windows.h will be added as part 
// epl.h by way of ptp stack includes.
#include <stdlib.h>
#include "FreeRTOS.h"
#include "semphr.h"


#include "epl/epl.h"

//****************************************************************************
void 
	OAIInitialize( 
		IN OAI_DEV_HANDLE oaiDevHandle)

//  Called by EPL to initialize the OAI layer.
//
//  oaiDevHandle
//      Handle that represents the device. The definition of this is 
//      completely up to higher layer software.
//
//  Returns:
//      Nothing
//****************************************************************************
{
    if (!oaiDevHandle->multiOpMutex) {
        oaiDevHandle->multiOpMutex = xSemaphoreCreateMutex();
    }
    if (!oaiDevHandle->regularMutex) {
        oaiDevHandle->regularMutex = xSemaphoreCreateMutex();
    }
    
}

//****************************************************************************
void
	OAIBeginCriticalSection( 
		xSemaphoreHandle hMutex )

//  Begins a critical section given an arbitrary mutex handle.
//  This provides a more flexible method of managing
//
//  Returns:
//      Nothing
//****************************************************************************
{
    if(!xSemaphoreTake(hMutex, 1000)) {
        PLATFORM_ASSERT("EPL_OAI", "xSemaphoreTake timeout");
    }
    return;
}

//****************************************************************************
void
	OAIEndCriticalSection( 
		xSemaphoreHandle hMutex )

//  Ends a critical section given an arbitrary mutex handle.
//  This provides a more flexible method of managing
//
//  Returns:
//      Nothing
//****************************************************************************
{
    xSemaphoreGive(hMutex);
    return;
}

//****************************************************************************
void 
    OAIBeginRegCriticalSection(
        IN OAI_DEV_HANDLE oaiDevHandle)
//****************************************************************************
{
    OAIBeginCriticalSection( oaiDevHandle->regularMutex);
    return;
}


//****************************************************************************
void 
    OAIEndRegCriticalSection(
        IN OAI_DEV_HANDLE oaiDevHandle)
//****************************************************************************
{
    OAIEndCriticalSection( oaiDevHandle->regularMutex);
    return;
}


//****************************************************************************
void 
    OAIBeginMultiCriticalSection(
        IN OAI_DEV_HANDLE oaiDevHandle)
//****************************************************************************
{
    OAIBeginCriticalSection( oaiDevHandle->multiOpMutex);
    return;
}


//****************************************************************************
void 
    OAIEndMultiCriticalSection(
        IN OAI_DEV_HANDLE oaiDevHandle)
//****************************************************************************
{
    OAIEndCriticalSection( oaiDevHandle->multiOpMutex );
    return;
}
