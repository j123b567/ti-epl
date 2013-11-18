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
#define _WINSOCKAPI_   
#include <windows.h>
#undef  _WINSOCKAPI_    // undo hack above.

#include <stdlib.h>
#include <conio.h>

#include "epl.h"

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
    return;
}

//****************************************************************************
void 
	*OAIAlloc( 
		IN NS_UINT sizeInBytes)

//  Provides basic memory allocation.
//
//  sizeInBytes
//      Size of the memory block to allocate in bytes.
//
//  Returns:
//      Returns a pointer to the allocated memory block. If a failure 
//      occurred allocating the memory, NULL is returned.
//****************************************************************************
{
    return malloc( sizeInBytes);
}


//****************************************************************************
void 
	OAIFree( 
		IN void *memPtr)

//  Frees a memory block allocated using the OAIAlloc function.
//
//  memPtr
//      Pointer to the memory block to free.
//  
//  Returns:
//      Nothing
//****************************************************************************
{
    free( memPtr);
}

//****************************************************************************
HANDLE 
	OAICreateMutex( 
		void )

//  Uses O/S specific function to create a mutex
//
//  Returns:
//      HANDLE to the created mutex
//****************************************************************************
{
    return CreateMutex( NULL, FALSE, NULL );
}

//****************************************************************************
void
	OAIReleaseMutex( 
		HANDLE hMutex )

//  Releases a previously created mutex
//
//  Returns:
//      Nothing
//****************************************************************************
{
	if( hMutex ) 
		ReleaseMutex( hMutex );

	return;
}

//****************************************************************************
void
	OAIBeginCriticalSection( 
		HANDLE hMutex )

//  Begins a critical section given an arbitrary mutex handle.
//  This provides a more flexible method of managing
//
//  Returns:
//      Nothing
//****************************************************************************
{
    WaitForSingleObject( hMutex, INFINITE);
    return;
}

//****************************************************************************
void
	OAIEndCriticalSection( 
		HANDLE hMutex )

//  Ends a critical section given an arbitrary mutex handle.
//  This provides a more flexible method of managing
//
//  Returns:
//      Nothing
//****************************************************************************
{
	OAIReleaseMutex( hMutex);
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
    OAIReleaseMutex( oaiDevHandle->regularMutex);
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
    OAIReleaseMutex( oaiDevHandle->multiOpMutex );
    return;
}
 
//****************************************************************************
void
    OAIManagementError(
        IN OAI_DEV_HANDLE oaiDevHandle)
        
//  EPL calls this function if a data integrity error is detected over the 
//  management information interface. If a checksum mismatch between host 
//  software's checksum tally and the hardware's checksum tally for register 
//  reads and writes, this function is called. It indicates that one or more 
//  bits read from or written to the Phy were corrupted. This would normally 
//  indicate a serious system error and should be dealt with by the host 
//  environment as necessary. 
//
//  oaiDevHandle
//      Handle that represents the device that the error occurred on.
//      The definition of this is completely up to higher layer software.
//
//  Returns:
//      Nothing
//****************************************************************************
{
	return;
}