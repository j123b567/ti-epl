//****************************************************************************
// platform.h
// 
// Copyright (c) 2008 National Semiconductor Corporation.
// All Rights Reserved
// 
// Platform specific definitions
//
// Pulls together specific pieces of defintions for this specific platform
//****************************************************************************

#ifndef _PLATFORM_INCLUDE
#define _PLATFORM_INCLUDE

#include "stm32f2x7_eth.h"

#include "FreeRTOS.h"
#include "semphr.h"

#define VERSION_PTP     2


typedef struct OAI_DEV_HANDLE_STRUCT {
  
    // Mutex objects used by the library
    xSemaphoreHandle regularMutex;    
    xSemaphoreHandle multiOpMutex;
} OAI_DEV_HANDLE_STRUCT;


typedef OAI_DEV_HANDLE_STRUCT *OAI_DEV_HANDLE;

#endif // _PLATFORM_INCLUDE
