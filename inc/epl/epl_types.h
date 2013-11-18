//****************************************************************************
// epl_types.h
// 
// Copyright (c) 2007-2008 National Semiconductor Corporation.
// All Rights Reserved
// 
// This is the EPL base type definitions header file.
//****************************************************************************

#ifndef _EPL_TYPES_INCLUDE
#define _EPL_TYPES_INCLUDE

#include "epl.h"

// Note: On platforms where the natural integer size is less then 32-bits
// in size (eg 16-bit platforms), NS_UINT and NS_SINT must be defined as a 
// data type no less than 32-bits in size.
typedef void                NS_VOID;
typedef unsigned int        NS_UINT;    // unsigned variable sized 
typedef int                 NS_SINT;    // signed variable sized 
typedef unsigned char       NS_UINT8;   // unsigned 8-bit fixed 
typedef char                NS_SINT8;   // signed 8-bit fixed 
typedef unsigned short int  NS_UINT16;  // unsigned 16-bit fixed 
typedef short int           NS_SINT16;  // signed 16-bit fixed 
typedef unsigned long int   NS_UINT32;  // unsigned 32-bit fixed
typedef long int            NS_SINT32;  // signed 32-bit fixed
typedef unsigned char       NS_CHAR;
typedef unsigned char       NS_BOOL;    // TRUE or FALSE

#ifndef TRUE
#define TRUE    1
#endif
#ifndef FALSE
#define FALSE   0
#endif
#ifndef IN
#define IN
#endif
#ifndef OUT
#define OUT
#endif
#ifndef NULL
#define NULL ((void*)0)
#endif

// EPL return codes
typedef enum NS_STATUS {
    NS_STATUS_SUCCESS,          // The request operation completed successfully
    NS_STATUS_FAILURE,          // The operation failed 
    NS_STATUS_INVALID_PARM,     // An invalid parameter was detected
    NS_STATUS_RESOURCES,        // Failed to allocate resources required
    NS_STATUS_NOT_SUPPORTED,    // Operation not supported
    NS_STATUS_ABORTED,          // Operation was interrupted before completion
    NS_STATUS_HARDWARE_FAILURE  // Unexpected hardware error encountered
} NS_STATUS;	// epl.h epl_core.c epl_quality.c epl_tdr.c

// EPL Data Structures and Defines
typedef enum EPL_ENUM_TYPE {
    EPL_ENUM_MDIO_BIT_BANG,			// bit bang on LPT port
    EPL_ENUM_DIRECT,				// Use OK MAC interface
	EPL_ENUM_CYUSB_MDIO				// Use Cypress USB MDIO interface
}EPL_ENUM_TYPE;

typedef enum EPL_DEVICE_CAPA_ENUM {
    EPL_CAPA_NONE = 0x00000000,
    EPL_CAPA_TDR = 0x00000001,
    EPL_CAPA_LINK_QUALITY = 0x00000002,
    EPL_CAPA_MII_PORT_CFG = 0x00000004,
    EPL_CAPA_MII_REG_ACCESS = 0x00000008
}EPL_DEVICE_CAPA_ENUM;

typedef enum EPL_DEVICE_TYPE_ENUM {
    DEV_UNKNOWN,
    DEV_DP83848,
    DEV_DP83849,
    DEV_DP83640
}EPL_DEVICE_TYPE_ENUM;

/*
typedef struct EPL_DEV_INFO {
    EPL_DEVICE_TYPE_ENUM deviceType;
    NS_UINT numOfPorts;
    NS_UINT deviceModelNum;
    NS_UINT deviceRevision;
    NS_UINT numExtRegisterPages;
}EPL_DEV_INFO,*PEPL_DEV_INFO;
*/

#include "epl_platform.h"   // needed for OAI_DEV_HANDLE

/*
typedef struct DEVICE_OBJ {
    struct DEVICE_OBJ *link;
    struct PORT_OBJ *portObjs;
    OAI_DEV_HANDLE oaiDevHandle;
    NS_UINT baseMdioAddress;
    EPL_DEV_INFO devInfo;
    EPL_DEVICE_CAPA_ENUM capa;
}DEVICE_OBJ,*PDEVICE_OBJ;
*/
 
typedef struct PORT_OBJ {
//    struct PORT_OBJ *link;              // Must be first field in struct
    OAI_DEV_HANDLE oaiDevHandle;
//    PDEVICE_OBJ deviceObj;
    NS_UINT portMdioAddress;
//    NS_BOOL pcfDA_SEL;
    NS_UINT rxConfigOptions;
    NS_UINT tsSecondsLen;
    NS_UINT rxTsNanoSecOffset;
    NS_UINT rxTsSecondsOffset;
    NS_UINT psfConfigOptions;
//    void *psfList;
    NS_UINT8 psfSrcMacAddr[6];
//    void *pktList;
}PORT_OBJ,*PPORT_OBJ;

#define PEPL_DEV_HANDLE     PDEVICE_OBJ
#define PEPL_PORT_HANDLE    PPORT_OBJ


#endif	// _EPL_TYPES_INCLUDE