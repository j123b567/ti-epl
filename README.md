Ethernet PHYTER Library
======

Library for DP83630 and DP83640 modified to be used with FreeRTOS and STM32Fxx7


DP83630: http://www.ti.com/product/DP83630

Original library: http://www.ti.com/litv/zip/snlc036


Usage example:
You should have MAC initialised prior calling PHY_PTPStart()

```c
#include "epl/epl.h"

#define PHY_ADDRESS       0x01

static OAI_DEV_HANDLE_STRUCT dObj = {
    .regularMutex = 0,
    .multiOpMutex = 0,
};

static PORT_OBJ pObj = {
    .oaiDevHandle = &dObj,
    .portMdioAddress = PHY_ADDRESS,
};

const PEPL_PORT_HANDLE pEPL_HANDLE = &pObj;

void PHY_Init(void) {
    OAIInitialize(pEPL_HANDLE->oaiDevHandle);
}

/*******************************************************************************
 * Function Name  : PHY_PTPStart
 * Description    : Initialize timestamping ability of PHY
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void PHY_PTPStart(void) {
    RX_CFG_ITEMS rx_cfg_items = {
        .ptpVersion = 0x02,
        .ptpFirstByteMask = 0x00,
        .ptpFirstByteData = 0x00,
        .ipAddrData = 0,
        .tsMinIFG = 0x00,
        .srcIdHash = 0,
        .ptpDomain = 0,
        .tsSecLen = 0, //0; // DRs option
        .rxTsNanoSecOffset = 0, //0x24; // DRs option
        .rxTsSecondsOffset = 0, //0x21; // DRs option
    };

    PHY_Init();

    PTPEnable(pEPL_HANDLE, TRUE);
    PTPSetTransmitConfig(pEPL_HANDLE, TXOPT_TS_EN | TXOPT_IPV4_EN, 2, 0, 0);
    PTPSetReceiveConfig(pEPL_HANDLE, RXOPT_RX_TS_EN | RXOPT_RX_IPV4_EN, &rx_cfg_items);
}

```
