//****************************************************************************
// epl_1588.h
// 
// Copyright (c) 2006-2008 National Semiconductor Corporation.
// All Rights Reserved
// 
// This file contains all of the 1588/PTP related definitions and prototypes
//
//****************************************************************************

#ifndef _EPL_1588_INCLUDE
#define _EPL_1588_INCLUDE

// Adj for pin input delay and edge detection time (35ns = 8ns(refclk) * 4 + 3)
#define	PIN_INPUT_DELAY		35

// 1588 Related Definitions
#define TRGOPT_PULSE        0x00000001
#define TRGOPT_PERIODIC     0x00000002
#define TRGOPT_TRG_IF_LATE  0x00000004
#define TRGOPT_NOTIFY_EN    0x00000008
#define TRGOPT_TOGGLE_EN    0x00000010

#define TXOPT_DR_INSERT     0x00000001
#define TXOPT_IGNORE_2STEP  0x00000002
#define TXOPT_CRC_1STEP     0x00000004
#define TXOPT_CHK_1STEP     0x00000008
#define TXOPT_IP1588_EN     0x00000010
#define TXOPT_L2_EN         0x00000020
#define TXOPT_IPV6_EN       0x00000040
#define TXOPT_IPV4_EN       0x00000080
#define TXOPT_TS_EN         0x00000100
#define TXOPT_SYNC_1STEP    0x00000200
#define TXOPT_NTP_TS_EN     0x00001000

#define STSOPT_LITTLE_ENDIAN    0x00000001
#define STSOPT_IPV4             0x00000002
#define STSOPT_TXTS_EN          0x00000004
#define STSOPT_RXTS_EN          0x00000008
#define STSOPT_TRIG_EN          0x00000010
#define STSOPT_EVENT_EN         0x00000020
#define STSOPT_ERR_EN           0x00000040
#define STSOPT_PCFR_EN          0x00000080

#define RXOPT_DOMAIN_EN         0x00000001
#define RXOPT_ALT_MAST_DIS      0x00000002
#define RXOPT_USER_IP_EN        0x00000008
#define RXOPT_RX_SLAVE          0x00000010
#define RXOPT_IP1588_EN0        0x00000020
#define RXOPT_IP1588_EN1        0x00000040
#define RXOPT_IP1588_EN2        0x00000080
#define RXOPT_RX_L2_EN          0x00000100
#define RXOPT_RX_IPV6_EN        0x00000200
#define RXOPT_RX_IPV4_EN        0x00000400
#define RXOPT_SRC_ID_HASH_EN    0x00000800
#define RXOPT_RX_TS_EN          0x00001000
#define RXOPT_ACC_UDP           0x00002000
#define RXOPT_ACC_CRC           0x00004000
#define RXOPT_TS_APPEND         0x00008000
#define RXOPT_TS_INSERT         0x00010000
#define RXOPT_IPV4_UDP_MOD      0x00020000
#define RXOPT_TS_SEC_EN         0x00040000

typedef enum
{
    STS_SRC_ADDR_1 = 0x00000003,
    STS_SRC_ADDR_2 = 0x00000000,
    STS_SRC_ADDR_3 = 0x00000001,
    STS_SRC_ADDR_USE_MC = 0x00000002
} MAC_SRC_ADDRESS_ENUM;


typedef struct RX_CFG_ITEMS
{
    NS_UINT ptpVersion;
    NS_UINT ptpFirstByteMask;
    NS_UINT ptpFirstByteData;
    NS_UINT32 ipAddrData;
    NS_UINT tsMinIFG;
    NS_UINT srcIdHash;
    NS_UINT ptpDomain;
    NS_UINT tsSecLen;
    NS_UINT rxTsNanoSecOffset;
    NS_UINT rxTsSecondsOffset;
} RX_CFG_ITEMS;

#define CLKOPT_CLK_OUT_EN           0x00000001
#define CLKOPT_CLK_OUT_SEL          0x00000002
#define CLKOPT_CLK_OUT_SPEED_SEL    0x00000004

typedef enum PHYMSG_MESSAGE_TYPE_ENUM {
    PHYMSG_STATUS_TX,
    PHYMSG_STATUS_RX,
    PHYMSG_STATUS_TRIGGER,
    PHYMSG_STATUS_EVENT,
    PHYMSG_STATUS_ERROR,
    PHYMSG_STATUS_REG_READ
} PHYMSG_MESSAGE_TYPE_ENUM;

typedef union PHYMSG_MESSAGE {
    struct {
        NS_UINT32 txTimestampSecs;
        NS_UINT32 txTimestampNanoSecs;
        NS_UINT8  txOverflowCount;          // 2-bit value in 8-bit variable
    } TxStatus;

    struct {
        NS_UINT32 rxTimestampSecs;
        NS_UINT32 rxTimestampNanoSecs;
        NS_UINT8  rxOverflowCount;          // 2-bits data in 8-bit variable
        NS_UINT16 sequenceId;               // 16-bits
        NS_UINT8  messageType;              // 4-bits data in 8 bit variable
        NS_UINT16 sourceHash;               // 12-bit data in 16-bit variable
    } RxStatus;

    struct {
        NS_UINT16 triggerStatus;            // Bits [11:0] indicating what triggers occurred (12 - 1 respectively).
    } TriggerStatus;

    struct {
        NS_UINT16 ptpEstsRegBits;           // 12-bits - See PTP_ESTS register for bit definitions
        NS_BOOL   extendedEventStatusFlag;  // 8-bits  - Set to TRUE if ext. info available
        NS_UINT16 extendedEventInfo;        // See register definition for more info
        NS_UINT32 evtTimestampSecs;
        NS_UINT32 evtTimestampNanoSecs;
    } EventStatus;

    struct {
        NS_BOOL frameBufOverflowFlag;       // 8-bits
        NS_BOOL frameCounterOverflowFlag;   // 8-bits
    } ErrorStatus;

    struct {
        NS_UINT8 regIndex;                  // 5-bits data in 8-bit variable
        NS_UINT8 regPage;                   // 3-bits data in 8-bit variable
        NS_UINT16 readRegisterValue;        // 16-bits
    } RegReadStatus;
} PHYMSG_MESSAGE;

typedef struct PHYMSG_LIST {
    PHYMSG_MESSAGE_TYPE_ENUM msgType;
    PHYMSG_MESSAGE      phyMsg;
    struct PHYMSG_LIST  *nxtMsg;
} PHYMSG_LIST;

#define PTPEVT_TRANSMIT_TIMESTAMP_BIT   0x00000001
#define PTPEVT_RECEIVE_TIMESTAMP_BIT    0x00000002
#define PTPEVT_EVENT_TIMESTAMP_BIT      0x00000004
#define PTPEVT_TRIGGER_DONE_BIT         0x00000008

#define PTP_EVENT_PACKET_LENGTH         93

// EPL Function Prototypes
#ifdef __cplusplus
extern "C" {
#endif

EXPORT void
    PTPEnable(
        IN PEPL_PORT_HANDLE portHandle,
        IN NS_BOOL enableFlag);

EXPORT void
    PTPSetTriggerConfig(
        IN PEPL_PORT_HANDLE portHandle,
        IN NS_UINT trigger,
        IN NS_UINT triggerBehavior,
        IN NS_UINT gpioConnection);

EXPORT void
    PTPSetTriggerConfig(
        IN PEPL_PORT_HANDLE portHandle,
        IN NS_UINT trigger,
        IN NS_UINT triggerBehavior,
        IN NS_UINT gpioConnection);

EXPORT void
    PTPSetEventConfig (
        IN PEPL_PORT_HANDLE portHandle,
        IN NS_UINT event,
        IN NS_BOOL eventRiseFlag,
        IN NS_BOOL eventFallFlag,
        IN NS_BOOL eventSingle,
        IN NS_UINT gpioConnection);

EXPORT void
    PTPSetTransmitConfig (
        IN PEPL_PORT_HANDLE portHandle,
        IN NS_UINT txConfigOptions,
        IN NS_UINT ptpVersion,
        IN NS_UINT ptpFirstByteMask,
        IN NS_UINT ptpFirstByteData);

EXPORT void
    PTPSetPhyStatusFrameConfig (
        IN PEPL_PORT_HANDLE portHandle,
        IN NS_UINT statusConfigOptions,
        IN MAC_SRC_ADDRESS_ENUM srcAddrToUse,
        IN NS_UINT minPreamble,
        IN NS_UINT ptpReserved,
        IN NS_UINT ptpVersion,
        IN NS_UINT transportSpecific,
        IN NS_UINT8 messageType,
        IN NS_UINT32 sourceIpAddress);

EXPORT void
    PTPSetReceiveConfig (
        IN PEPL_PORT_HANDLE portHandle,
        IN NS_UINT rxConfigOptions,
        IN RX_CFG_ITEMS *rxConfigItems);

EXPORT NS_UINT
    PTPCalcSourceIdHash (
        IN NS_UINT8 *tenBytesData);

EXPORT void
    PTPSetTempRateDurationConfig (
        IN PEPL_PORT_HANDLE portHandle,
        IN NS_UINT32 duration);

EXPORT void
    PTPSetClockConfig (
        IN PEPL_PORT_HANDLE portHandle,
        IN NS_UINT clockConfigOptions,
        IN NS_UINT ptpClockDivideByValue,
        IN NS_UINT ptpClockSource,
        IN NS_UINT ptpClockSourcePeriod);

EXPORT void
    PTPSetGpioInterruptConfig (
        IN PEPL_PORT_HANDLE portHandle,
        IN NS_UINT gpioInt);

EXPORT void
    PTPSetMiscConfig (
        IN PEPL_PORT_HANDLE portHandle,
        IN NS_UINT ptpEtherType,
        IN NS_UINT ptpOffset,
        IN NS_UINT txSfdGpio,
        IN NS_UINT rxSfdGpio);

EXPORT void
    PTPClockStepAdjustment (
        IN PEPL_PORT_HANDLE portHandle,
        IN NS_UINT32 numberOfSeconds,
        IN NS_UINT32 numberOfNanoSeconds,
        IN NS_BOOL negativeAdj);

EXPORT void
    PTPClockSet (
        IN PEPL_PORT_HANDLE portHandle,
        IN NS_UINT32 numberOfSeconds,
        IN NS_UINT32 numberOfNanoSeconds);

EXPORT void
    PTPClockSetRateAdjustment (
        IN PEPL_PORT_HANDLE portHandle,
        IN NS_UINT32 rateAdjValue,
        IN NS_BOOL tempAdjFlag,
        IN NS_BOOL adjDirectionFlag);

EXPORT NS_UINT
    PTPCheckForEvents (
        IN PEPL_PORT_HANDLE portHandle);

EXPORT void
    PTPArmTrigger (
        IN PEPL_PORT_HANDLE portHandle,
        IN NS_UINT trigger,
        IN NS_UINT32 expireTimeSeconds,
        IN NS_UINT32 expireTimeNanoSeconds,
        IN NS_BOOL initialStateFlag,
        IN NS_BOOL waitForRolloverFlag,
        IN NS_UINT32 pulseWidth,
        IN NS_UINT32 pulseWidth2);

EXPORT NS_STATUS
    PTPHasTriggerExpired (
        IN PEPL_PORT_HANDLE portHandle,
        IN NS_UINT trigger);

EXPORT void
    PTPCancelTrigger (
        IN PEPL_PORT_HANDLE portHandle,
        IN NS_UINT trigger);

EXPORT NS_UINT
    MonitorGpioSignals (
        IN PEPL_PORT_HANDLE portHandle);

EXPORT void
    PTPClockReadCurrent (
        IN PEPL_PORT_HANDLE portHandle,
        IN OUT NS_UINT32 *retNumberOfSeconds,
        IN OUT NS_UINT32 *retNumberOfNanoSeconds);

EXPORT void
    PTPGetTransmitTimestamp (
        IN PEPL_PORT_HANDLE portHandle,
        IN OUT NS_UINT32 *retNumberOfSeconds,
        IN OUT NS_UINT32 *retNumberOfNanoSeconds,
        IN OUT NS_UINT   *overflowCount);

EXPORT void
    PTPGetReceiveTimestamp (
        IN PEPL_PORT_HANDLE portHandle,
        IN OUT NS_UINT32 *retNumberOfSeconds,
        IN OUT NS_UINT32 *retNumberOfNanoSeconds,
        IN OUT NS_UINT *overflowCount,
        IN OUT NS_UINT *sequenceId,
        IN OUT NS_UINT8 *messageType,
        IN OUT NS_UINT *hashValue);

EXPORT void
    PTPGetTimestampFromFrame (
        IN PEPL_PORT_HANDLE portHandle,
        IN NS_UINT8 *receiveFrameData,
        IN OUT NS_UINT32 *retNumberOfSeconds,
        IN OUT NS_UINT32 *retNumberOfNanoSeconds);

EXPORT NS_BOOL
    PTPGetEvent (
        IN PEPL_PORT_HANDLE portHandle,
        IN OUT NS_UINT   *eventBits,
        IN OUT NS_UINT   *riseFlags,
        IN OUT NS_UINT32 *eventTimeSeconds,
        IN OUT NS_UINT32 *eventTimeNanoSeconds,
        IN OUT NS_UINT   *eventsMissed);

EXPORT NS_UINT8 *
    IsPhyStatusFrame (
		IN PEPL_PORT_HANDLE portHandle,
        IN NS_UINT8 *frameBuffer,
        IN NS_UINT16 frameLength);

EXPORT NS_UINT8 *
    GetNextPhyMessage (
		IN PEPL_PORT_HANDLE portHandle,
        IN OUT NS_UINT8 *msgLocation,
        IN OUT PHYMSG_MESSAGE_TYPE_ENUM *messageType,
        IN OUT PHYMSG_MESSAGE *message);

#ifdef __cplusplus
}
#endif


#endif // _EPL_1588_INCLUDE
