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

#include "epl.h"

// Global list of device objects that have been enumerated.
PDEVICE_OBJ deviceObjList = NULL;

//****************************************************************************
EXPORT NS_STATUS EPLInitialize( void)

//  Called to initialize the EPL library. This function must be called prior 
//  to calling any other EPL functions. It initializes EPL's internal state. 
//  EPLDeinitialize should be called after all interaction with EPL has 
//  finished.
//
//  Returns:
//      NS_STATUS_SUCCESS
//          EPL initialization was successful.
//      NS_STATUS_FAILURE
//          EPL initialization failed, usually due to a memory allocation 
//          failure.
//****************************************************************************
{
NS_STATUS nsResult = NS_STATUS_SUCCESS;

    return( nsResult);
}


//****************************************************************************
EXPORT void EPLDeinitialize( void)

//  Called to de-initialize the EPL library. This function must be called 
//  after all interaction with EPL has finished.
//
//  Returns:
//      Nothing
//****************************************************************************
{
PDEVICE_OBJ devObj, nextDevObj;
PPORT_OBJ portObj, nextPortObj;
PHYMSG_LIST *psfList;
PKT_LIST    *pktList;

    // Free up all our memory allocations.
    for ( devObj = deviceObjList; devObj; )
    {
        for ( portObj = devObj->portObjs; portObj; )
        {
            switch( portObj->ifType ){
            case EPL_ENUM_DIRECT:
				MACDeInitialize( portObj->oaiDevHandle );
                break;
            case EPL_ENUM_CYUSB_MDIO:
				ifCyUSB_DeInit( portObj->oaiDevHandle );
			    break;
	        default:
		        // Don't know what type it is, do nothing
		        break;
            } // switch( portObj->ifType )

            // Free up any PSF list items
            while( portObj->psfList ) {
                psfList = portObj->psfList;
                portObj->psfList = psfList->nxtMsg;
                OAIFree( psfList );
            }

            // Free up any packet list items
            while( portObj->pktList ) {
                pktList = portObj->pktList;
                OAIFree( pktList->pPacket );
                portObj->pktList = pktList->nxtPkt;
                OAIFree( pktList );
            }

            nextPortObj = portObj->link;
            OAIFree( portObj);
            portObj = nextPortObj;
        }
        nextDevObj = devObj->link;
        OAIFree( portObj);
        devObj = nextDevObj;
    }

    deviceObjList = NULL;
    return;
}


//****************************************************************************
EXPORT PEPL_DEV_HANDLE	
    EPLEnumDevice(
        IN OAI_DEV_HANDLE oaiDevHandle,
        IN NS_UINT deviceMdioAddress,
        IN EPL_ENUM_TYPE enumType)

//  Enumerate a PHYTER device on the specified MDIO bus and returns a 
//  deviceHandle object. This function will only match devices that contain 
//  National's OUI value. The device can contain any device ID. A device 
//  can contain one or more ports. To interact with a port you must use the 
//  EPLEnumPort function to obtain the necessary port objects.
//
//  oaiDevHandle
//      Handle that represents the device that the enumeration should 
//      occur on. The definition of this is completely up to higher 
//      layer software. It is passed into the low-level register read/write 
//      OAI functions. 
//  deviceMdioAddress
//      Specifies the device address on the MDIO bus to try and 
//      enumerate. To enumerate all devices, start by calling this 
//      function with an address of 0, and continue to increment the 
//      value up to the maximum MDIO address (typically 31). The increment
//      amount should be the number of ports the device contains.
//  enumType
//      Indicates the type of OAI MDIO functions will be used during the
//      enumeration for register accesses. If EPL_ENUM_MDIO_BIT_BANG
//      is specified, the ifLPTMdioReadBit function will be used, if
//      EPL_ENUM_DIRECT is specified, the MACReadReg function will
//      be used.
//
//  Returns:
//      Returns NULL if no device was found at the specified MDIO device 
//      address, otherwise an opaque handle is returned representing the 
//      device (deviceHandle). This handle can then be used in other EPL 
//      functions to query and interact with the device.
//****************************************************************************
{
NS_UINT reg, model, revision, numPorts, x, numExtRegs;
PDEVICE_OBJ devObj;
PORT_OBJ tmpPrtObj;
PPORT_OBJ portObj, prevPortObj;
EPL_DEVICE_TYPE_ENUM devType;
EPL_DEVICE_CAPA_ENUM capa;

    // Make sure the interface in initialized once and only once
    if( deviceMdioAddress==0 || !oaiDevHandle->ifHandle ){
	    switch( enumType ) {
	    case EPL_ENUM_DIRECT:
            if( MACInitialize( oaiDevHandle ) != NS_STATUS_SUCCESS ) {
                return NULL;
            }
		    break;
	    case EPL_ENUM_CYUSB_MDIO:
            if( ifCyUSB_Init( oaiDevHandle ) != NS_STATUS_SUCCESS ) {
                return NULL;
            }
		    break;
	    default:
		    // Don't know what type it is
		    break;
	    }  // switch( enumType )
    } // if( deviceMdioAddress==0 )
    // Build a temporary port obj so we can read the port registers.
    tmpPrtObj.deviceObj = NULL;
    tmpPrtObj.oaiDevHandle = oaiDevHandle;
    tmpPrtObj.portMdioAddress = deviceMdioAddress;
    tmpPrtObj.ifType = enumType;            // Set interface type
    tmpPrtObj.psfList = NULL;
    tmpPrtObj.pktList = NULL;

    if( oaiDevHandle->pcfDefault ) {
        // We only have PCF abilities.  Whack registers to get us 
        // going until the upper level can provide a better configuration.
	    tmpPrtObj.usePhyControlFrames = TRUE;  // Default PCF state is on
        tmpPrtObj.psfConfigOptions = 0;
        tmpPrtObj.pcfDA_SEL = 0;
        PTPSetPhyStatusFrameConfig( &tmpPrtObj, 
                                    (STSOPT_PCFR_EN | STSOPT_IPV4), 
                                    STS_SRC_ADDR_2, 
                                    7, 0x00, VERSION_PTP, 0x0F, 0x0F, 
                                    0x44332211 );
        // Force read to MDIO for debug
        //tmpPrtObj.psfConfigOptions &= ~STSOPT_PCFR_EN;
        EPLSetMgmtInterfaceConfig( &tmpPrtObj, TRUE, FALSE, 15 );
    }
    else {
        // We have other options, force off until it is configured
	    tmpPrtObj.usePhyControlFrames = FALSE;  // Default PCF state is off
        tmpPrtObj.psfConfigOptions = 0;
    }

    // See if there's a device on this bus at the specified address.
    reg = EPLReadReg( (PEPL_PORT_HANDLE)&tmpPrtObj, PHY_IDR1);
    if ( reg != IDR1_NATIONAL_OUI_VAL)
        return NULL;

    reg = EPLReadReg( (PEPL_PORT_HANDLE)&tmpPrtObj, PHY_IDR2);
    model = (reg & IDR2_MODEL_NUMBER_MASK);
    revision = reg & IDR2_REVISION_MASK;
    capa = EPL_CAPA_NONE;
    numPorts = 1;
    numExtRegs = 1;
    
    switch( model ) {
        case IDR2_MODEL_DP83848_VAL:
        case IDR2_MODEL_DP48_MINI_VAL:
            devType = DEV_DP83848;
            numExtRegs = 1;
            break;

        case IDR2_MODEL_DP83849_VAL:
            devType = DEV_DP83849;
            capa = EPL_CAPA_TDR | EPL_CAPA_LINK_QUALITY | EPL_CAPA_MII_PORT_CFG;
            numPorts = 2;
            numExtRegs = 3;
            break;

        case IDR2_MODEL_DP83640_VAL:
            devType = DEV_DP83640;
            capa = EPL_CAPA_TDR | EPL_CAPA_LINK_QUALITY | EPL_CAPA_MII_REG_ACCESS;
            numPorts = 1;
            numExtRegs = 7;
            break;

        default:
            devType = DEV_UNKNOWN;
            break;
    }  // switch( model )
    
    // Do we already have a device obj for this device?
    for ( devObj = deviceObjList; devObj; devObj = devObj->link)
    {
        if ( devObj->oaiDevHandle == oaiDevHandle && 
             devObj->baseMdioAddress == deviceMdioAddress)
        {
            return (PEPL_DEV_HANDLE)devObj;
        }
    }
    
    // New device
    devObj = (PDEVICE_OBJ)OAIAlloc( sizeof( DEVICE_OBJ));
    if ( devObj == NULL) return (PEPL_DEV_HANDLE)NULL;
    
    devObj->oaiDevHandle = oaiDevHandle;
    devObj->baseMdioAddress = deviceMdioAddress;
    devObj->capa = capa;
    devObj->devInfo.deviceType = devType;
    devObj->devInfo.numOfPorts = numPorts;
    devObj->devInfo.deviceModelNum = model >> IDR2_MODEL_SHIFT;
    devObj->devInfo.deviceRevision = revision;
    devObj->devInfo.numExtRegisterPages = numExtRegs;
    devObj->portObjs = NULL;

    devObj->link = deviceObjList;
    deviceObjList = devObj;
    prevPortObj = (PPORT_OBJ)&devObj->portObjs;
    
    // Setup the port objects for this device
    for ( x = 0; x < numPorts; x++)
    {
        portObj = (PPORT_OBJ)OAIAlloc( sizeof( PORT_OBJ));
        if ( portObj == NULL)
            return (PEPL_DEV_HANDLE)NULL;
            
        portObj->oaiDevHandle = oaiDevHandle;
        portObj->deviceObj = devObj;
        portObj->portMdioAddress = deviceMdioAddress + x;
		portObj->ifType = enumType;
        portObj->psfList = NULL;
        portObj->pktList = NULL;

        if( oaiDevHandle->pcfDefault ) {
            portObj->usePhyControlFrames = TRUE;
            portObj->psfConfigOptions = 0;
            portObj->pcfDA_SEL = 0;

            // Setup PSFs so we can do reads
            PTPSetPhyStatusFrameConfig( portObj, 
                                        (STSOPT_PCFR_EN | STSOPT_IPV4), 
                                        STS_SRC_ADDR_2, 
                                        7, 0x00, VERSION_PTP, 0x0F, 0x0F, 
                                        0x44332211 );
            // Force reads to MDIO for debug
            //portObj->psfConfigOptions &= ~STSOPT_PCFR_EN;
            EPLSetMgmtInterfaceConfig( portObj, TRUE, FALSE, 15 );
        }
        else {
            portObj->usePhyControlFrames = FALSE;
            portObj->psfConfigOptions = 0;
        }

        // Link the port on the end of the port list (ordered).
        portObj->link = NULL;
        prevPortObj->link = portObj;
        prevPortObj = portObj;
        
        // Make sure extended registers page 0 is selected
        EPLWriteReg( portObj, PHY_PAGESEL, P848_PAGESEL_PAGE_0);
    }

    return (PEPL_DEV_HANDLE)devObj;
}

       
//****************************************************************************
EXPORT PEPL_DEV_INFO 
    EPLGetDeviceInfo(
        IN PEPL_DEV_HANDLE deviceHandle)
        
//  Returns descriptive information about the specified device. 
//
//  deviceHandle
//      Handle that represents the device. This is obtained using the 
//      EPLEnumDevice function.
//
//  Returns:
//      A pointer to a EPL_DEV_INFO structure.
//****************************************************************************
{
    return &((PDEVICE_OBJ)deviceHandle)->devInfo;
}

        
//****************************************************************************
EXPORT NS_BOOL
    EPLIsDeviceCapable(
        IN PEPL_DEV_HANDLE deviceHandle,
        IN EPL_DEVICE_CAPA_ENUM capability)
        
//  Returns whether or not the specified device implements a particular 
//  feature. This function provides a method to write run-time selected 
//  device specific code.
//
//  deviceHandle
//      Handle that represents the device. This is obtained using the 
//      EPLEnumDevice function.
//  capability
//      One of the defined values in EPL_DEVICE_CAPA_ENUM (see below).
//
//  Returns:
//      TRUE if the device supports the specified feature, FALSE otherwise.
//****************************************************************************
{
PDEVICE_OBJ devObj = (PDEVICE_OBJ)deviceHandle;
    
    if ( devObj->capa & capability)
        return TRUE;
    return FALSE;
}

        
//****************************************************************************
EXPORT void
    EPLResetDevice(
        IN PEPL_DEV_HANDLE deviceHandle)
        
//  Resets the device. For multi-port devices this will cause the device as 
//  well as all of its ports to be reset. For single port devices this has 
//  the same affect as calling the ResetPort() method. This method does NOT 
//  return until the reset operation has completed (approximately 1.2ms).
//
//  deviceHandle
//      Handle that represents the device. This is obtained using the 
//      EPLEnumDevice function.
//
//  Returns:
//      Nothing
//****************************************************************************
{
PDEVICE_OBJ devObj = (PDEVICE_OBJ)deviceHandle;
PEPL_PORT_HANDLE portHandle;
NS_UINT bmcr;

    portHandle = devObj->portObjs;
    OAIBeginMultiCriticalSection( portHandle->oaiDevHandle);
    bmcr = EPLReadReg( portHandle, PHY_BMCR);
    bmcr |= BMCR_RESET;
    EPLWriteReg( portHandle, PHY_BMCR, bmcr);
    // Wait for the reset to finish.
    while ( EPLReadReg( portHandle, PHY_BMCR) & BMCR_RESET);
    OAIEndMultiCriticalSection( portHandle->oaiDevHandle);
    return;
}

        
//****************************************************************************
EXPORT PEPL_PORT_HANDLE
    EPLEnumPort(
        IN PEPL_DEV_HANDLE deviceHandle,
        IN NS_UINT portIndex)
        
//  Enumerate a device's ports.
//
//  deviceHandle
//      Handle that represents the device. This is obtained using the 
//      EPLEnumDevice function.
//  portIndex
//      Specifies the enumeration port index. To enumerate all ports on a 
//      device, start by calling this function with an index of 0, and 
//      continue to increment the value up to the number of ports the 
//      devices has, minus one. The number of ports can be obtained by 
//      calling EPLGetDeviceInfo.
//
//  Returns:
//      Returns NULL if the specified portIndex is invalid, otherwise an 
//      opaque handle is returned representing the port (portHandle). 
//      This handle can then be used in other EPL functions to query and 
//      interact with a particular port on a device.
//****************************************************************************
{
PDEVICE_OBJ devObj = (PDEVICE_OBJ)deviceHandle;
PPORT_OBJ portObj;
NS_UINT x;

    portObj = devObj->portObjs;
    for ( x = 0; x < portIndex; x++)
    {
        portObj = portObj->link;
        if ( portObj == NULL) return (PEPL_PORT_HANDLE)NULL;
    }
    
    return (PEPL_PORT_HANDLE)portObj;
}


//****************************************************************************
EXPORT void
    EPLSetMgmtInterfaceConfig(
        IN PEPL_PORT_HANDLE portHandle,
        IN NS_BOOL  usePhyControlFrames,
        IN NS_BOOL  pcfDA_SEL,
        IN NS_UINT8 pcfBufSize)
//  Used to configure EPL to use Phy Control Frames (PCF) or a direct 
//  interface to read and write Phy registers. If both parameters are
//  set to FALSE, then MDIO bit banging will be used (default).
//        
//  portHandle
//      Handle that represents a port. This is obtained using the EPLEnumPort 
//      function.
//  usePhyControlFrames
//      Set to TRUE to configure EPL to use the PCF mechanism for Phy register 
//      reads and writes.  Set to FALSE to use MDIO or the direct reg 
//      read/write interface.
//  pcfDA_SEL
//      Set to TRUE to use MAC address [0x08, 0x00, 0x17, 0x00, 0x00, 0x00]
//      Set to FALSE to use MAC address [0x08, 0x00, 0x17, 0x0B, 0x6B, 0x0F]
//  pcfBufSize
//      Value 0-15 determines the size of buffer to allow PHY to detect a PCF
//      The PHY will buffer this many bytes before sending the packet on.  This
//      can be used to prevent partial PCF frames from making it to the wire.
//
//  Returns
//      Nothing
//****************************************************************************
{
NS_UINT16 tPCFCR=0;

    if( usePhyControlFrames ) {
        // Enable PCF
        // Set buf size to max (mask has all bits set for 0xF)
        // Everything else at defaults for now.
        portHandle->pcfDA_SEL = pcfDA_SEL;

        //tPCFCR = EPLReadReg( portHandle, P640_PCFCR );
        tPCFCR |= P640_PCF_EN;
        tPCFCR &= ~P640_PCF_BUF_MASK;
        tPCFCR |= (pcfBufSize<<P640_PCF_BUF_SHIFT);
        if( pcfDA_SEL )
            tPCFCR |= P640_PCF_DA_SEL;
        else
            tPCFCR &= ~P640_PCF_DA_SEL;
        
        EPLWriteReg( portHandle, P640_PCFCR, tPCFCR );
    }
    else {
        // Disable, leave everything else alone
        tPCFCR = EPLReadReg( portHandle, P640_PCFCR );
        tPCFCR &= ~P640_PCF_EN;
        EPLWriteReg( portHandle, P640_PCFCR, tPCFCR );
    }

    portHandle->usePhyControlFrames = usePhyControlFrames;    
    return;
}
 
  
//****************************************************************************
EXPORT PEPL_DEV_HANDLE
    EPLGetDeviceHandle(
        IN PEPL_PORT_HANDLE portHandle)
        
//  Given a port handle, returns the associated (parent) device handle.
//
//  portHandle
//      Handle that represents a port. This is obtained using the 
//      EPLEnumPort function.
//
//  Returns:
//      Returns the device handle that is associated (parent) of the 
//      specified port.
//****************************************************************************
{
    return (PEPL_DEV_HANDLE)(((PPORT_OBJ)portHandle)->deviceObj);
}

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
PPORT_OBJ portHdl = (PPORT_OBJ)portHandle;
NS_UINT32 tPCF;

    // See if we need to do a page select, but not if we are using PCFs
    if( ((registerIndex & ~0x8000) > PHY_PAGESEL) && !portHdl->usePhyControlFrames ) {
        // Make sure correct register page is selected
        IntWriteReg( portHdl, (PHY_PAGESEL | (registerIndex & 0x8000)), (registerIndex & 0xE0) >> 5);
        registerIndex &= ~0xE0;
    }

    switch( portHdl->ifType ) {
    case EPL_ENUM_CYUSB_MDIO:
		// Send data out Cypress USB MDIO interface
        ifCyUSB_WriteMDIO( portHdl, registerIndex, value);
        break;
	
    case EPL_ENUM_DIRECT:
        // Using direct interface.  See if we should use PCFs
        if( portHdl->usePhyControlFrames ) {
            // Send data out "MAC" interface using PHY Control Frames

            // Create PCF packet
            tPCF = 0x40000000;                                  // [31:30] 01'b for write command
            tPCF |= ((portHdl->portMdioAddress & 0x1F) << 25);  // [29:25] PHY Address
            tPCF |= ((registerIndex>>5 & 0x0F) << 21);          // [24:21] Page
            tPCF |= ((registerIndex & 0x1F) << 16);             // [20:16] Register
            tPCF |= (value & 0xFFFF);                           // [15:00] value

            // PCFs are in network order, need to swap the bytes around
            tPCF = (((tPCF) >> 24) & 0x000000ff) | (((tPCF) >> 8 ) & 0x0000ff00) |
                   (((tPCF) << 8 ) & 0x00ff0000) | (((tPCF) << 24) & 0xff000000);

            MACMIIWriteReg( portHdl, (NS_UINT8 *)&tPCF, sizeof(tPCF) );
        }
        else {
            // Send data out direct "MAC" interface
            MACWriteReg( portHdl, registerIndex, value);
        }
        break;

    default:
        // Send data out bit bang interface on LPT
        ifLPTWriteReg( portHdl, registerIndex, value);
        break;
    }  // switch( portHdl->ifType )
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
PPORT_OBJ portHdl = (PPORT_OBJ)portHandle;
NS_UINT32 tPCF;

    OAIBeginRegCriticalSection( portHdl->oaiDevHandle);

    // See if we need to do a page select, but not if we are using PCFs/PSFs
    if( ( (registerIndex & ~0x8000) > PHY_PAGESEL) && 
          !(portHdl->usePhyControlFrames && 
           (portHdl->psfConfigOptions & STSOPT_PCFR_EN)) ) {

        // Make sure correct register page is selected
        IntWriteReg( portHandle, (PHY_PAGESEL | (registerIndex & 0x8000)), (registerIndex & 0x00E0) >> 5);
        registerIndex &= ~0xE0;
        // Preamble has been taken care of by the write operation
    }

    switch( portHdl->ifType ) {
    case EPL_ENUM_CYUSB_MDIO:
		// Send request to Cypress USB MDIO interface
        data = ifCyUSB_ReadMDIO( portHdl, registerIndex );
        break;

    case EPL_ENUM_DIRECT:
        // Using direct interface, See if we want to use PCFs
        // Only allow it if PSFs are enabled to allow read responses through
        if ( portHdl->usePhyControlFrames && (portHdl->psfConfigOptions & STSOPT_PCFR_EN) ) {
            // Send request to "MAC" using PHY Control Frames

            // Create PCF packet
            tPCF = 0x80000000;                                  // [31:30] 10'b for read command
            tPCF |= ((portHdl->portMdioAddress & 0x1F) << 25);  // [29:25] PHY Address
            tPCF |= ((registerIndex>>5 & 0x0F) << 21);          // [24:21] Page
            tPCF |= ((registerIndex & 0x1F) << 16);             // [20:16] Register
            //tPCF |= (value & 0xFFFF);                         // [15:00] value (Not used here, leave 0)

            // PCFs are in network order, need to swap the bytes around
            tPCF = (((tPCF) >> 24) & 0x000000ff) | (((tPCF) >> 8 ) & 0x0000ff00) |
                   (((tPCF) << 8 ) & 0x00ff0000) | (((tPCF) << 24) & 0xff000000);

            data = MACMIIReadReg( portHdl, (NS_UINT8 *)&tPCF, sizeof(tPCF) );
        }
        else {
            // Send request to direct "MAC" interface
            data = MACReadReg( portHdl, registerIndex );
        }
        break;

    default:
        // Send request using bit bang on LPT interface
        data = ifLPTReadReg( portHdl, registerIndex );
        break;
    }  // switch( portHdl->ifType )

    OAIEndRegCriticalSection( portHdl->oaiDevHandle);
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
