//****************************************************************************
// epl_core.c
// 
// Copyright (c) 2006-2008 National Semiconductor Corporation.
// All Rights Reserved
// 
// This is the main EPL source file and is always included in a build.
//
// It implements the following functions:
//      EPLInitialize
//      EPLDeinitialize
//      EPLEnumDevice
//      EPLSetMgmtInterfaceConfig
//      EPLGetDeviceInfo
//      EPLIsDeviceCapable
//      EPLResetDevice
//      EPLEnumPort
//      EPLGetDeviceHandle
//      EPLReadReg
//      EPLWriteReg
//      EPLGetPortMdioAddress
//      EPLSetPortPowerMode
//****************************************************************************

#include "epl/epl.h"

//****************************************************************************
void
    IntWriteReg(
        IN PEPL_PORT_HANDLE portHandle,
        IN NS_UINT registerIndex,
        IN NS_UINT value)
//  Internal procedure that performs the actual write operation.  See below
//  for details of parameters
//****************************************************************************
{
    // See if we need to do a page select, but not if we are using PCFs
    if( (registerIndex & ~0x8000) > PHY_PAGESEL ) {
        // Make sure correct register page is selected
        IntWriteReg( portHandle, (PHY_PAGESEL | (registerIndex & 0x8000)), (registerIndex & 0xE0) >> 5);
        registerIndex &= ~0xE0;
    }

    // Send data out direct "MAC" interface
    ETH_WritePHYRegister(portHandle->portMdioAddress, registerIndex, value);
}

//****************************************************************************
EXPORT NS_UINT
    EPLReadReg(
        IN PEPL_PORT_HANDLE portHandle,
        IN NS_UINT registerIndex)

//  Reads the contents of the specified port register. Refer to the 
//  epl_regs.h file for register definitions.
//
//  portHandle
//      Handle that represents a port. This is obtained using the 
//      EPLEnumPort function.
//  registerIndex
//      Index of the register to read. Bits 7:5 select the 
//      register page (000-pg0, 001-pg1, 010-pg3, 011-pg4, etc.).
//
//  Returns:
//      Value read from the register.
//****************************************************************************
{
NS_UINT data;

    OAIBeginRegCriticalSection( portHandle->oaiDevHandle);

    // See if we need to do a page select, but not if we are using PCFs/PSFs
    if( (registerIndex & ~0x8000) > PHY_PAGESEL ) {

        // Make sure correct register page is selected
        IntWriteReg( portHandle, (PHY_PAGESEL | (registerIndex & 0x8000)), (registerIndex & 0x00E0) >> 5);
        registerIndex &= ~0xE0;
        // Preamble has been taken care of by the write operation
    }
    data = ETH_ReadPHYRegister( portHandle->portMdioAddress, registerIndex );

    OAIEndRegCriticalSection( portHandle->oaiDevHandle);
    return data;
}

//****************************************************************************
EXPORT void
    EPLWriteReg(
        IN PEPL_PORT_HANDLE portHandle,
        IN NS_UINT registerIndex,
        IN NS_UINT value)
        
//  Writes a value to the specified port register. Refer to the epl_regs.h 
//  file for register definitions.
//
//  portHandle
//      Handle that represents a port. This is obtained using the 
//      EPLEnumPort function.
//  registerIndex
//      Index of the register to write. Bits 7:5 select the 
//      register page (000-pg0, 001-pg1, 010-pg3, 011-pg4, etc.).
//  value
//      The value to write to the register (0x0000 - 0xFFFF).
//
//  Returns:
//      Nothing
//****************************************************************************
{
PPORT_OBJ portHdl = (PPORT_OBJ)portHandle;

    OAIBeginRegCriticalSection( portHdl->oaiDevHandle );

    IntWriteReg( portHandle, registerIndex, value );

    OAIEndRegCriticalSection( portHdl->oaiDevHandle);
}

 
//****************************************************************************
EXPORT NS_UINT
    EPLGetPortMdioAddress(
        IN PEPL_PORT_HANDLE portHandle)
        
//  Returns a port's MDIO bus address.
//
//  portHandle
//      Handle that represents a port. This is obtained using the 
//      EPLEnumPort function.
//
//  Returns:
//      A port's MDIO bus address.
//****************************************************************************
{
    return ((PPORT_OBJ)portHandle)->portMdioAddress;
}
 

//****************************************************************************
EXPORT void
    EPLSetPortPowerMode(
        IN PEPL_PORT_HANDLE portHandle,
        IN NS_BOOL powerOn)
        
//  Controls the power to a specified port. If the port is powered down, the 
//  device is still accessible through the management interface, i.e. this 
//  library (registers).
//
//  portHandle
//      Handle that represents a port. This is obtained using the 
//      EPLEnumPort function.
//  powerOn
//      Set to TRUE to enable power to the port, FALSE to disable power.
//
//  Returns:
//      Nothing
//****************************************************************************
{
NS_UINT bmcr;

    OAIBeginMultiCriticalSection( portHandle->oaiDevHandle);
    bmcr = EPLReadReg( portHandle, PHY_BMCR);
    if (!powerOn) bmcr |= BMCR_POWER_DOWN;
    else bmcr &= ~BMCR_POWER_DOWN;
    EPLWriteReg( portHandle, PHY_BMCR, bmcr);
    OAIEndMultiCriticalSection( portHandle->oaiDevHandle);
    return;
}
