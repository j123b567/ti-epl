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

typedef struct ALP_ENDPOINTS_STRUCT {
    NS_UINT REG_CNTRL_WR;
    NS_UINT REG_TX_FRAME_SIZE;
    NS_UINT REG_MDIO_ADDR;
    NS_UINT REG_MDIO_DATA;
    NS_UINT DATA_FIFO_LOAD;
    NS_UINT TX_BURST_COUNT;
    NS_UINT REG_CNTRL_OUT_RD;
    NS_UINT REG_MDIO_ADDR_RD;
    NS_UINT REG_MDIO_DATA_RD;
    NS_UINT RX_DATA_ADDR;
    NS_UINT RX_BYTE_COUNT;
    NS_UINT RX_CRC_ERROR_CNT;
    NS_UINT RX_RUNT_CNT;
    NS_UINT RX_ERROR_CNT;
    NS_UINT RX_MISSED_PKT_CNT;
    NS_UINT MDIO_TRIGGER_IN;
    NS_UINT MAC_CTRL;
    NS_UINT START_TX;
    NS_UINT PKT_RD_DONE;
    NS_UINT TX_DONE;
    NS_UINT MDIO_DONE;
    NS_UINT RX_PKT_READY;
    NS_UINT TX_FIFO_WR_DATA;
    NS_UINT RX_FIFO_WR_DATA;
    NS_UINT TXFIFO_RD_DATA;
    NS_UINT RXFIFO_RD_DATA;
} ALP_ENDPOINTS_STRUCT;

#include "okFrontPanelDLL.h"
#ifdef SWIG
// Fix up SWIG/Python misunderstanding about the HANDLE type
typedef NS_UINT32 IF_HANDLE;
#else
typedef HANDLE IF_HANDLE;
#endif

#ifdef _DEBUG
    #undef _DEBUG
    #include <python.h>
    #define _DEBUG
#else
    #include <python.h>
#endif

// Default platform to always use PCF/PSF for reg read/writes
// This is only possible if PCF_EN is strapped enabled on the
// part.  This forces the library to initialize to only use
// PCFs to interact with the part.
#define PLATFORM_PCF_DEFAULT    TRUE

typedef struct OAI_DEV_HANDLE_STRUCT {
    // Generic pointer for use by the library to store interface information
    IF_HANDLE ifHandle;     

    // Determines if PCF/PSF (as opposed to MDIO) will be used to configure
    // the PHY.
    NS_BOOL pcfDefault;

    // Used by interface to describe which "board" to use if there are multiple
    // possibilities
    NS_UINT board;

    // Used by interface to describe which "connector" to use
    NS_UINT connector;

    // Used by interface to describe which "address" to use
    NS_UINT address;

    // Used by the interface code to determine if it needs to add a checksum
    // to the UDP portion of the packets
    NS_BOOL udpChksumEnable;

    // Used by the protocol stack to kill the upper layer thread if it exists
    NS_BOOL killThread;

    // Mutex objects used by the library
    HANDLE regularMutex;    
    HANDLE multiOpMutex;

    NS_BOOL Python;
    void *guiObj;
    void *stdioCallback;
    void *statusUpdateCallback;
    PyThreadState *pythonThrdSave;
  
    NS_UINT8 sprintfBuffer[1024];

    // OAI extension used by the ALP/OK interface code.
    ALP_ENDPOINTS_STRUCT alpEP;

} OAI_DEV_HANDLE_STRUCT;

typedef OAI_DEV_HANDLE_STRUCT *OAI_DEV_HANDLE;

#endif // _PLATFORM_INCLUDE
