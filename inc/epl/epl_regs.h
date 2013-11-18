//****************************************************************************
// epl_regs.h
// 
// Copyright (c) 2006-2008 National Semiconductor Corporation.
// All Rights Reserved
// 
// This module defines all of the registers and fields available
// in National Ethernet Phy devices.
// 
// The following devices are described here:
//      DP83848, DP83849, DP83640
//****************************************************************************

#ifndef _EPL_REGS_INCLUDE
#define	_EPL_REGS_INCLUDE

#include "epl.h"

// Phy Register Indexes - Common Across Device Types
#define PHY_BMCR            0x0000
#define PHY_BMSR            0x0001
#define PHY_IDR1            0x0002
#define PHY_IDR2            0x0003
#define PHY_ANAR            0x0004
#define PHY_ANLPAR          0x0005
#define PHY_ANER            0x0006
#define PHY_ANNPTR          0x0007
#define PHY_PHYSTS          0x0010
#define PHY_MICR            0x0011
#define PHY_MISR            0x0012
#define PHY_PAGESEL         0x0013
#define PHY_FCSCR           0x0014
#define PHY_RECR            0x0015
#define PHY_PCSR            0x0016
#define PHY_RBR             0x0017
#define PHY_LEDCR           0x0018
#define PHY_PHYCTRL         0x0019
#define PHY_10BTSCR         0x001A
#define PHY_CDCTRL1         0x001B
#define PHY_EDCR            0x001D

// DP83848 Specific Register Indexes
#define PHY_AFECR           0x001E
#define PHY_AFEAR           0x001F

// DP83849 / DP83640 Specific Register Indexes
// Note: Bits [6:5] specify the register page (00-pg0, 01-pg1, 10-pg2, 11-pg3)
#define PHY_PG0_PHYCR2      0x001C
#define PHY_PG1_PMDCNFG     0x0034
#define PHY_PG1_TMR1        0x0035
#define PHY_PG1_TMR2        0x0036
#define PHY_PG1_DSP_CTRL1   0x0037
#define PHY_PG1_DSP_CTRL2   0x0038
#define PHY_PG1_TRL_CTRL    0x0039
#define PHY_PG1_DEQ_CTRL    0x003A
#define PHY_PG1_ANEG_TST    0x003B
#define PHY_PG1_EXTCFG      0x003C
#define PHY_PG1_TST_CTRL    0x003D
#define PHY_PG1_SD_CNFG     0x003E
#define PHY_PG1_TSTDAT      0x003F
#define PHY_PG2_LEN100_DET  0x0054
#define PHY_PG2_FREQ100     0x0055
#define PHY_PG2_TDR_CTRL    0x0056
#define PHY_PG2_TDR_WIN     0x0057
#define PHY_PG2_TDR_PEAK    0x0058
#define PHY_PG2_TDR_THR     0x0059
#define PHY_PG2_VAR_CTRL    0x005A
#define PHY_PG2_VAR_DATA    0x005B
#define PHY_PG2_LQMR        0x005D
#define PHY_PG2_LQDR        0x005E

// DP83640 Specific Register Indexes
// Note: Bits [7:5] specify the register page (000-pg0, 001-pg1, 010-pg2, 011-pg3, etc.)
#define PHY_PG2_LQMR2       0x005F
#define PHY_PG3_CGCR        0x0074
#define PHY_PG3_PTPTR       0x0075
#define PHY_PG3_CDCR1       0x0077
#define PHY_PG3_CDCR2       0x0078
#define PHY_PG3_FCO1CR      0x0079
#define PHY_PG3_FCO2CR      0x007A
#define PHY_PG3_ADCCR1      0x007B
#define PHY_PG3_ADCCR2      0x007C
#define PHY_PG3_BGREGCR     0x007D
#define PHY_PG3_CGMCR       0x007E
#define PHY_PG3_PGMCR       0x007F
#define PHY_PG4_PTP_CTL     0x0094
#define PHY_PG4_PTP_TDR     0x0095
#define PHY_PG4_PTP_STS     0x0096
#define PHY_PG4_PTP_TSTS    0x0097
#define PHY_PG4_PTP_RATEL   0x0098
#define PHY_PG4_PTP_RATEH   0x0099
#define PHY_PG4_PTP_RDCKSUM 0x009A
#define PHY_PG4_PTP_WRCKSUM 0x009B
#define PHY_PG4_PTP_TXTS    0x009C
#define PHY_PG4_PTP_RXTS    0x009D
#define PHY_PG4_PTP_ESTS    0x009E
#define PHY_PG4_PTP_EDATA   0x009F
#define PHY_PG5_PTP_TRIG    0x00B4
#define PHY_PG5_PTP_EVNT    0x00B5
#define PHY_PG5_PTP_TXCFG0  0x00B6
#define PHY_PG5_PTP_TXCFG1  0x00B7
#define PHY_PG5_PSF_CFG0    0x00B8
#define PHY_PG5_PTP_RXCFG0  0x00B9
#define PHY_PG5_PTP_RXCFG1  0x00BA
#define PHY_PG5_PTP_RXCFG2  0x00BB
#define PHY_PG5_PTP_RXCFG3  0x00BC
#define PHY_PG5_PTP_RXCFG4  0x00BD
#define PHY_PG5_PTP_TRDL    0x00BE
#define PHY_PG5_PTP_TRDH    0x00BF
#define PHY_PG6_PTP_COC     0x00D4
#define PHY_PG6_PSF_CFG1    0x00D5
#define PHY_PG6_PSF_CFG2    0x00D6
#define PHY_PG6_PSF_CFG3    0x00D7
#define PHY_PG6_PSF_CFG4    0x00D8
#define PHY_PG6_PTP_SFDCFG  0x00D9
#define PHY_PG6_PTP_INTCTL  0x00DA
#define PHY_PG6_PTP_CLKSRC  0x00DB
#define PHY_PG6_PTP_ETR     0x00DC
#define PHY_PG6_PTP_OFF     0x00DD
#define PHY_PG6_PTP_GPIOMON 0x00DE
#define PHY_PG6_PTP_RXHASH  0x00DF


//****************************************************************************
// Common Register Bit Definitions
//****************************************************************************

// PHY_BMCR Defs
#define BMCR_FORCE_SPEED_1000    0x0040
#define BMCR_COLLISION_TEST      0x0080
#define BMCR_FORCE_FULL_DUP      0x0100
#define BMCR_RESTART_AUTONEG     0x0200
#define BMCR_ISOLATE             0x0400
#define BMCR_POWER_DOWN          0x0800
#define BMCR_AUTO_NEG_ENABLE     0x1000
#define BMCR_FORCE_SPEED_100     0x2000
#define BMCR_FORCE_SPEED_10      0x0000
#define BMCR_FORCE_SPEED_MASK    0x2040
#define BMCR_LOOPBACK            0x4000
#define BMCR_RESET               0x8000

// PHY_BMSR Defs
#define BMSR_EXTENDED_CAPABLE    0x0001
#define BMSR_JABBER_DETECT       0x0002
#define BMSR_LINK_STATUS         0x0004
#define BMSR_AUTO_NEG_ABILITY    0x0008
#define BMSR_REMOTE_FAULT        0x0010
#define BMSR_AUTO_NEG_COMPLETE   0x0020
#define BMSR_PREAMBLE_SUPPRESS   0x0040
#define BMSR_RESERVED            0x0080
#define BMSR_1000T_EXT_STATUS    0x0100
#define BMSR_100T2_HALF_DUP      0x0200
#define BMSR_100T2_FULL_DUP      0x0400
#define BMSR_10T_HALF_DUP        0x0800
#define BMSR_10T_FULL_DUP        0x1000
#define BMSR_100X_HALF_DUP       0x2000
#define BMSR_100X_FULL_DUP       0x4000
#define BMSR_100T4_CAPABLE       0x8000

// PHY_IDR1 Defs
#define IDR1_NATIONAL_OUI_VAL    0x2000    // OUI bits 3-18

// PHY_IDR2 Defs
#define IDR2_OUI_MASK            0xFC00
#define IDR2_MODEL_NUMBER_MASK   0x03F0
#define IDR2_REVISION_MASK       0x000F
#define IDR2_MODEL_SHIFT         4

#define IDR2_NATIONAL_OUI_VAL    0x5C00    // OUI bits 19-24 (15:10), Vendor Model (9:4), Revision (3:0)
#define IDR2_MODEL_DP83848_VAL   0x0090    // AspenPhy
#define IDR2_MODEL_DP48_MINI_VAL 0x00C0    // AspenPhy - Mini
#define IDR2_MODEL_DP83849_VAL   0x00A0    // Dual AspenPhy
#define IDR2_MODEL_DP83640_VAL   0x00E0    // High Precision Phy

#define IDR2_REV_DP83848E_VAL    0x0001    // DP83848 Enhanced version

// PHY_ANAR Defs
#define ANAR_PROTO_SEL_MASK      0x001F
#define ANAR_PROTO_8023          0x0001
#define ANAR_10T_HALF_DUP        0x0020
#define ANAR_10T_FULL_DUP        0x0040
#define ANAR_100T_HALF_DUP       0x0080
#define ANAR_100T_FULL_DUP       0x0100
#define ANAR_100T4_SUPPORT       0x0200
#define ANAR_PAUSE_SUPPORT       0x0400
#define ANAR_ASY_PAUSE_SUPPORT   0x0800
#define ANAR_RESERVED0           0x1000
#define ANAR_REMOTE_FAULT        0x2000
#define ANAR_RESERVED1           0x4000
#define ANAR_NEXT_PAGE_IND       0x8000

// PHY_ANLPAR Defs
#define ANLPAR_PROTO_SEL_MASK    0x001F
#define ANLPAR_10T_HALF_DUP      0x0020
#define ANLPAR_10T_FULL_DUP      0x0040
#define ANLPAR_100T_HALF_DUP     0x0080
#define ANLPAR_100T_FULL_DUP     0x0100
#define ANLPAR_100T4_SUPPORT     0x0200
#define ANLPAR_PAUSE_SUPPORT     0x0400
#define ANLPAR_ASY_PAUSE         0x0800
#define ANLPAR_RESERVED0         0x1000
#define ANLPAR_REMOTE_FAULT      0x2000
#define ANLPAR_ACK               0x4000
#define ANLPAR_NEXT_PAGE_IND     0x8000

// PHY_ANER Defs
#define ANER_AUTO_NEG_CAPABLE    0x0001
#define ANER_PAGE_RX             0x0002
#define ANER_NEXT_PAGE_ABLE      0x0004
#define ANER_PRT_NEXT_PAGE_ABLE  0x0008
#define ANER_PARALLEL_DET_FAULT  0x0010

// PHY_ANNPTR Defs
#define ANNPTR_CODE_MASK         0x07FF
#define ANNPTR_TOGGLE            0x0800
#define ANNPTR_ACK2              0x1000
#define ANNPTR_MSG_PAGE          0x2000
#define ANNPTR_ACK               0x4000
#define ANNPTR_NEXT_PAGE_IND     0x8000


//****************************************************************************
// DP83848 Specific Register Bit Definitions
//****************************************************************************

// PHY_PHYSTS Defs
#define P848_STS_LINK            0x0001
#define P848_STS_SPEED           0x0002
#define P848_STS_DUPLEX          0x0004
#define P848_STS_LOOPBACK        0x0008
#define P848_STS_AUTO_NEG_DONE   0x0010
#define P848_STS_JABBER_DETECT   0x0020
#define P848_STS_REMOTE_FAULT    0x0040
#define P848_STS_MII_INTERRUPT   0x0080
#define P848_STS_PAGE_RXED       0x0100
#define P848_STS_DESCRAMBLER     0x0200
#define P848_STS_SIGNAL_DETECT   0x0400
#define P848_STS_FALSE_CARRIER   0x0800
#define P848_STS_POLARITY        0x1000
#define P848_STS_RX_ERROR_LATCH  0x2000
#define P848_STS_MDIX_MODE       0x4000

// PHY_MICR Defs
#define P848_MICR_INTEN          0x0001
#define P848_MICR_UNMSK_INT      0x0002
#define P848_MICR_TINT           0x0004

// PHY_MISR Defs
#define P848_MISR_UNMSK_RHF      0x0001
#define P848_MISR_UNMSK_FHF      0x0002
#define P848_MISR_UNMSK_ANC      0x0004
#define P848_MISR_UNMSK_RF       0x0008
#define P848_MISR_UNMSK_JAB      0x0010
#define P848_MISR_UNMSK_LINK     0x0020
#define P848_MISR_UNMSK_ED       0x0040
#define P848_MISR_MSK_RHF        0x0100
#define P848_MISR_MSK_FHF        0x0200
#define P848_MISR_MSK_ANC        0x0400
#define P848_MISR_MSK_RF         0x0800
#define P848_MISR_MSK_JAB        0x1000
#define P848_MISR_MSK_LINK       0x2000
#define P848_MISR_MSK_ED         0x4000

// PHY_PAGESEL Defs
#define P848_PAGESEL_PAGE_SEL    0x0001
#define P848_PAGESEL_PAGE_0      0x0000
#define P848_PAGESEL_PAGE_1      0x0001
#define P848_PAGESEL_PAGE_2      0x0002
#define P848_PAGESEL_PAGE_3      0x0003

// PHY_FCSCR Defs
#define P848_FCSCR_FCSCNT_MASK   0x00FF

// PHY_RECR Defs
#define P848_RECR_RXERRCNT_MASK  0x00FF

// PHY_PCSR Defs
#define P848_PCSR_DESCRAM_BYP    0x0001
#define P848_PCSR_SCRAM_BYP      0x0002
#define P848_PCSR_NRZI_BYP       0x0004
#define P848_PCSR_FEFI_EN        0x0008
#define P848_PCSR_FEFI_TST       0x0010
#define P848_PCSR_FORCE_100_OK   0x0020
#define P848_PCSR_FX_EN          0x0040
#define P848_PCSR_SD_OPTION      0x0100
#define P848_PCSR_SD_FORCE_PMA   0x0200
#define P848_PCSR_TQ_EN          0x0400
#define P848_PCSR_FREE_CLK       0x0800
#define P848_PCSR_BYP_4B5B       0x1000

// PHY_RBR Defs
#define P848_RBR_RX_RD_4         0x0000
#define P848_RBR_RX_RD_1         0x0001
#define P848_RBR_RX_RD_2         0x0002
#define P848_RBR_RX_RD_3         0x0003
#define P848_RBR_RX_UNF_STS      0x0004
#define P848_RBR_RX_OVF_STS      0x0008
#define P848_RBR_RMII_REV1_0     0x0010
#define P848_RBR_RMII_MODE       0x0020

// PHY_LEDCR Defs
#define P848_LED_ACTLED          0x0001
#define P848_LED_LNKLED          0x0002
#define P848_LED_SPDLED          0x0004
#define P848_LED_DRV_ACTLED      0x0008
#define P848_LED_DRV_LNKLED      0x0010
#define P848_LED_DRV_SPDLED      0x0020

// PHY_PHYCTRL Defs
#define P848_PHYCTRL_ADDR_MASK   0x001F
#define P848_PHYCTRL_LED_CFG0    0x0020
#define P848_PHYCTRL_LED_CFG1    0x0040
#define P848_PHYCTRL_BP_STRETCH  0x0080
#define P848_PHYCTRL_BIST_START  0x0100
#define P848_PHYCTRL_BIST_STS    0x0200
#define P848_PHYCTRL_PSR_15      0x0400
#define P848_PHYCTRL_BIST_FE     0x0800
#define P848_PHYCTRL_PAUSE_TX    0x1000
#define P848_PHYCTRL_PAUSE_RX    0x2000
#define P848_PHYCTRL_FORCE_MDIX  0x4000
#define P848_PHYCTRL_MDIX_EN     0x8000

// PHY_10BTSCR Defs
#define P848_10BTSCR_JABBER_DIS  0x0001
#define P848_10BTSCR_HRTBT_DIS   0x0002
#define P848_10BTSCR_SCALE_MSB   0x0004
#define P848_10BTSCR_ATDIS       0x0008
#define P848_10BTSCR_POLARITY    0x0010
#define P848_10BTSCR_FORCEPOL    0x0020
#define P848_10BTSCR_FRC_10      0x0040
#define P848_10BTSCR_LP_DIS      0x0080
#define P848_10BTSCR_LP_10_DIS   0x0100
#define P848_10BTSCR_SQLCH_MASK  0x0E00
#define P848_10BTSCR_ERRRG_MASK  0x3000
#define P848_10BTSCR_REJECT100T  0x4000
#define P848_10BTSCR_10BT_SER    0x8000

// PHY_CDCTRL1 Defs
#define P848_CDCTRL1_CDPATTSEL0  0x0001
#define P848_CDCTRL1_CDPATTSEL1  0x0002
#define P848_CDCTRL1_10MEG_PG    0x0004
#define P848_CDCTRL1_CDPATTEN10  0x0010
#define P848_CDCTRL1_BIST_CONT   0x0020
#define P848_CDCTRL1_BIST_EC_MSK 0xFF00

// PHY_EDCR Defs
#define P848_EDCR_DATA_CNT_MASK  0x000F
#define P848_EDCR_ERR_CNT_MASK   0x00F0
#define P848_EDCR_DATA_MET       0x0100
#define P848_EDCR_ERR_MET        0x0200
#define P848_EDCR_PWR_STATE      0x0400
#define P848_EDCR_BURST_DIS      0x0800
#define P848_EDCR_MANUAL_POWER   0x1000
#define P848_EDCR_AUTO_DOWN      0x2000
#define P848_EDCR_AUTO_UP        0x4000
#define P848_EDCR_ENABLE         0x8000

//****************************************************************************
// DP83849 Dual Specific Register Bit Definitions
//****************************************************************************

// PHY_RBR Defs Specific to this device
#define P849_RBR_ELAST_BUF_MASK  0x0003
#define P849_RBR_ELAST_14_BIT    0x0000
#define P849_RBR_ELAST_2_BIT     0x0001
#define P849_RBR_ELAST_6_BIT     0x0002
#define P849_RBR_ELAST_10_BIT    0x0003
#define P849_RBR_SINGLE_CLK_TX   0x0040
#define P849_RBR_SINGLE_CLK_RX   0x0080
#define P849_RBR_PMD_LOOP        0x0100
#define P849_RBR_TX_SOURCE_MASK  0x0600
#define P849_RBR_TX_NORMAL       0x0000
#define P849_RBR_TX_OPPOSITE     0x0200
#define P849_RBR_TX_OPPOSITE_RX  0x0400
#define P849_RBR_TX_DISABLED     0x0600
#define P849_RBR_RX_PORT_MASK    0x1800
#define P849_RBR_RX_NORMAL       0x0000
#define P849_RBR_RX_OPPOSITE     0x0800
#define P849_RBR_RX_BOTH_PORTS   0x1000
#define P849_RBR_RX_DISABLED     0x1800
#define P849_RBR_DIS_TX_LAT_OPT  0x2000
#define P849_RBR_SIM_WRITE_EN    0x8000

#define P849_RBR_NORMAL (P849_RBR_RX_NORMAL | P849_RBR_TX_NORMAL)
#define P849_RBR_SWAP   (P849_RBR_RX_OPPOSITE | P849_RBR_TX_OPPOSITE)
#define P849_RBR_EXT    (P849_RBR_RX_DISABLED | P849_RBR_TX_OPPOSITE_RX)

// PHY_PG0_PHYCR2 Def's
#define P849_FAST_ADAPT          0x0001
#define P849_SOFT_RESET          0x0200
#define PHYCR2_SYNC_ENET_EN      0x2000
#define PHYCR2_CLK_OUT_RX_EN     0x1000
#define PHYCR2_BC_WRITE_EN       0x0800
#define PHYCR2_PHY_CMP_MD        0x0400
#define PHYCR2_SOFT_RESET        0x0200
#define PHYCR2_CLK_OUT_DIS       0x0002

// PHY_PG1_PMDCNFG Def's
#define P849_TEST_MODE_MASK      0x0003
#define P849_TEST_MODE_NORMAL    0x0000
#define P849_TEST_MODE_ED_OB     0x0001
#define P849_TEST_MODE_MDIX_OB   0x0002
#define P849_TEST_MODE_FXC_OB    0x0003
#define P849_LEN100_AEQ          0x0100
#define P849_PMD_SOFT_RESET      0x0200
#define P849_AUTO_NEG_LOOPBACK   0x8000

// PHY_PG1_TMR1 Def's
#define P849_TEST_SEL_MASK       0x0007
#define P849_TEST_SEL_NORMAL     0x0000
#define P849_TEST_SEL_ADC        0x0001
#define P849_TEST_SEL_CD_OB      0x0002
#define P849_TEST_SEL_AN_RX_SM   0x0004
#define P849_TEST_SEL_AN_TX_SM   0x0005
#define P849_TEST_SEL_AN_ARM_SM  0x0006
#define P849_TEST_SEL_NLPLIT_SM  0x0007
#define P849_NRZ_OBSERVE         0x0008
#define P849_BYP_PLLS            0x0010
#define P849_BYP_ADC             0x0020
#define P849_DIS_IO_TURBO        0x0040
#define P849_ATP0_EN             0x0080
#define P849_ATP1_EN             0x0100
#define P849_SD_OBSERVE          0x0200
#define P849_PWRUP_OBSERVE       0x0400
#define P849_FCO_CTL_EN_OB       0x0800
#define P849_INVERT_ADC_CLK      0x1000
#define P849_MDIX_TX_INV         0x2000
#define P849_ADC_CLK_BYPASS      0x4000
#define P849_ADC_CLK_OE          0x8000

// PHY_PG1_TMR2 Def's
#define P849_PGM_VFILTER_LOW     0x0001
#define P849_PGM_VFILTER_HIGH    0x0002
#define P849_CGM_VFILTER_LOW     0x0004
#define P849_CGM_VFILTER_HIGH    0x0008
#define P849_MR_AAGC_10MB_MASK   0x00F0
#define P849_MR_AAGC_10MB_SHIFT  4
#define P849_MR_TM_RXSEL_MASK    0x0C00
#define P849_MR_TM_RXSEL_SHIFT   8
#define P849_MR_TM_TXSEL_MASK    0xF000
#define P849_MR_TM_TXSEL_SHIFT   12

// PHY_PG1_DSP_CTRL1 Def's
#define P849_AGC_ALPHA_MASK      0x0003
#define P849_FREEZE_AGC          0x0004
#define P849_LOAD_AGC            0x0008
#define P849_FREEZE_BLW          0x0010
#define P849_LOAD_BLW            0x0020
#define P849_FORCE_MSE_NOTOK     0x0040
#define P849_FORCE_MSE_OK        0x0080
#define P849_INIT_MSE            0x0100
#define P849_MSE_THSEL           0x0200
#define P849_AGC_7BITS           0x0400
#define P849_BLW_8BITS           0x0800
#define P849_IGNORE_MSEOK        0x2000
#define P849_DIS_PMD_INIT        0x4000
#define P849_PMD_INIT_TEST       0x8000

// PHY_PG1_DSP_CTRL2 Def's
#define P849_AAGC_THRESH_MASK    0x001F
#define P849_AAGC_FREEZE         0x0020
#define P849_LOAD_AAGC_ACC       0x0040
#define P849_LOAD_AAGC_TMR       0x0080
#define P849_FORCE_AEQ           0x0100
#define P849_FORCE_AEQ_VAL_MASK  0x0600
#define P849_FORCE_AEQ_VAL_SHIFT 9
#define P849_MAX_AEQ_MASK        0x1800
#define P849_MAX_AEQ_SHIFT       11
#define P849_DIS_AEQ_DECR        0x2000
#define P849_LOAD_AEQ_THRESH     0x4000

// PHY_PG1_TRL_CTRL Def's
#define P849_TRL_ALPHA_MASK      0x0003
#define P849_TRL_ALPHA_SHIFT     0
#define P849_TRL_BETA_MASK       0x000C
#define P849_TRL_BETA_SHIFT      2
#define P849_TRL_THRESH_MASK     0x00F0
#define P849_TRL_THRESH_SHIFT    4
#define P849_TRL_KILLREG         0x0100
#define P849_TRL_SEL_REG         0x0200
#define P849_RST_TRL_ON_ERR      0x0400
#define P849_TRL_FRZ_ACC         0x0800
#define P849_TRL_FRZ_LFO         0x1000
#define P849_LOAD_TRL_PHASE      0x2000
#define P849_LOAD_TRL_LFO        0x4000
#define P849_LOAD_TRL_BETA       0x8000

// PHY_PG1_DEQ_CTRL Def's
#define P849_KILL_COEFF_N1       0x0001
#define P849_KILL_EQ_TAP0        0x0002
#define P849_KILL_COEF1          0x0004
#define P849_KILL_COEF2          0x0008
#define P849_KILL_COEF3          0x0010
#define P849_FREEZE_COEF         0x0020
#define P849_NOSHIFT_N1          0x0040
#define P849_EQ_LOAD_COEF1       0x0080
#define P849_EQ_LOAD_COEF2       0x0100
#define P849_EQ_LOAD_COEF3       0x0200
#define P849_COEF1_9BITS         0x0400
#define P849_COEF2_8BITS         0x0800
#define P849_COEF3_7BITS         0x1000
#define P849_ALLOW_POS_C1        0x2000

// PHY_PG1_ANEG_TST Def's
#define P849_LOAD_ARB_TIMER      0x0100
#define P849_LOAD_TX_TIMER       0x0200
#define P849_LOAD_FLP_DATA_TIMER 0x0400
#define P849_LOAD_NLP_MIN_TIMER  0x0800
#define P849_LOAD_NLP_MAX_TIMER  0x1000
#define P849_LOAD_NLP_RX_TIMER   0x2000
#define P849_LOAD_ED_TIMER       0x4000

// PHY_PG1_EXTCFG Def's
#define P849_ADC_WATCHDOG_EN     0x0001
#define P849_ADC_WATCHDOG_TO_EN  0x0002
#define P849_ADC_WATCHDOG_ERR    0x0004
#define P849_MR_10BT_LR_MASK     0x0018
#define P849_MR_10BT_LR_SHIFT    3
#define P849_MR_NLP_RX_FIX       0x0020
#define P849_ADC_WD_THRESH_MASK  0x07C0
#define P849_ADC_WD_THRESH_SHIFT 6
#define P849_LP_THRESHOLD_MASK   0xF800
#define P849_LP_THRESHOLD_SHIFT  11

// PHY_PG1_TST_CTRL Def's
#define P849_SAMPLE_DATA         0x0001
#define P849_PLLBIST_RSTN        0x0002
#define P849_PLLBIST_EN          0x0004
#define P849_PLLBIST_MODE        0x0008
#define P849_PLLBIST_DONE        0x0010
#define P849_TEST_DATA_SEL_MASK  0xF800
#define P849_TEST_DATA_SEL_SHIFT 11

// PHY_PG1_SD_CNFG Def's
#define P849_SDOFFT_MASK         0x000F
#define P849_SDOFFT_SHIFT        0
#define P849_SDONT_MASK          0x00F0
#define P849_SDONT_SHIFT         4
#define P849_SIG_DET_TIME        0x0100
#define P849_FORCE_SIG_DET_PMD   0x0200
#define P849_10B_SCALE_LSB       0x0400
#define P849_MR_SHORT_CABLE      0x0800
#define P849_SIG_DET_TH_DELTA    0x1000
#define P849_100B_PMA_TEST_EN    0x2000
#define P849_AUTO_NEG_TEST_EN    0x4000
#define P849_SIG_DET_PTOP        0x8000

// PHY_PG2_LEN100_DET Def's
#define P849_CABLE_LEN_MASK      0x00FF
#define P849_CABLE_LEN_SHIFT     0
#define P849_AEQ_VAL_MASK        0x0300
#define P849_AEQ_VAL_SHIFT       8

// PHY_PG2_FREQ100 Def's
#define P849_FREQ_OFFSET_MASK    0x00FF
#define P849_FREQ_OFFSET_SHIFT   0
#define P849_SEL_FC              0x0100
#define P849_SAMPLE_FREQ         0x8000

// PHY_PG2_TDR_CTRL Def's
#define P849_RX_THRESHOLD_MASK   0x003F
#define P849_RX_THRESHOLD_SHIFT  0
#define P849_TDR_MIN_MODE        0x0080
#define P849_TDR_WIDTH_MASK      0x0700
#define P849_TDR_WIDTH_SHIFT     8
#define P849_SEND_TDR            0x0800
#define P849_RX_CHANNEL          0x1000
#define P849_TX_CHANNEL          0x2000
#define P849_TDR_100MB           0x4000
#define P849_TDR_ENABLE          0x8000

// PHY_PG2_TDR_WIN Def's
#define P849_TDR_STOP_MASK       0x00FF
#define P849_TDR_STOP_SHIFT      0
#define P849_TDR_START_MASK      0xFF00
#define P849_TDR_START_SHIFT     8

// PHY_PG2_TDR_PEAK Def's
#define P849_TDR_PEAK_TIME_MASK  0x00FF
#define P849_TDR_PEAK_TIME_SHIFT 0
#define P849_TDR_PEAK_MASK       0x3F00
#define P849_TDR_PEAK_SHIFT      8

// PHY_PG2_TDR_THR Def's
#define P849_TDR_THR_TIME_MASK   0x00FF
#define P849_TDR_THR_TIME_SHIFT  0
#define P849_TDR_THR_MET         0x0100

// PHY_PG2_VAR_CTRL Def's
#define P849_VAR_ENABLE          0x0001
#define P849_VAR_TIMER_MASK      0x0006
#define P849_VAR_FREEZE          0x0008
#define P849_VAR_RDY             0x8000

// PHY_PG2_LQMR Def's
#define P849_C1_LO_WARN          0x0001
#define P849_C1_HI_WARN          0x0002
#define P849_DAGC_LO_WARN        0x0004
#define P849_DAGC_HI_WARN        0x0008
#define P849_DBLW_LO_WARN        0x0010
#define P849_DBLW_HI_WARN        0x0020
#define P849_FREQ_LO_WARN        0x0040
#define P849_FREQ_HI_WARN        0x0080
#define P849_FC_LO_WARN          0x0100
#define P849_FC_HI_WARN          0x0200
#define P849_BRK_LNK_C1          0x0400
#define P849_BRK_LNK_DAGC        0x0800
#define P849_BRK_LNK_DBLW        0x1000
#define P849_BRK_LNK_FREQ        0x2000
#define P849_BRK_LNK_FC          0x4000
#define P849_LQM_ENABLE          0x8000

// PHY_PG2_LQDR Def's
#define P849_LQ_THR_DATA_MASK    0x00FF
#define P849_LQ_THR_DATA_SHIFT   0
#define P849_LQ_THR_SEL          0x0100
#define P849_LQ_PARAM_SEL_MASK   0x0E00
#define P849_LQ_PARAM_SEL_SHIFT  9
#define P849_WRITE_LQ_THR        0x1000
#define P849_SAMPLE_PARAM        0x2000


//****************************************************************************
// DP83640 Specific Register Bit Definitions
//****************************************************************************

// PHY_PG0_PCFCR Def's
#define P640_PCFCR              0x001F
#define P640_PCF_EN             0x0001
#define P640_PCF_BUF_SHIFT      1
#define P640_PCF_BUF_MASK       0x001E
#define P640_PCF_BC_DIS         0x0020
#define P640_PCF_INT_CTL_SHIFT  6
#define P640_PCF_INT_CTL_MASK   0x00C0
#define P640_PCF_DA_SEL         0x0100
#define P640_PCF_STS_OK         0x4000
#define P640_PCF_STS_ERR        0x8000

// PHY_PG2_LQMR2 Def's
#define P640_RESTART_ON_VAR     0x0400
#define P640_VAR_HIGH_WARN      0x0002

// PHY_PG3_CGCR Def's
#define P640_DIS_TRIG_UPD_GATE  0x8000
#define P640_DIS_TX_TS_GATE     0x4000
#define P640_DIS_RX_TS_GATE     0x2000
#define P640_DIS_RX_INFO_GATE   0x1000
#define P640_DIS_EVNT_GATE      0x0800
#define P640_DIS_CLK_UPD_GATE   0x0400
#define P640_DIS_REG125_GATE    0x0200
#define P640_DIS_CLKTX_GATE     0x0100
#define P640_DIS_CLKRX_GATE     0x0080
#define P640_DIS_CLK125_GATE    0x0040
#define P640_DIS_CLKDIV_GATE    0x0020
#define P640_DIS_ADC125_GATE    0x0004
#define P640_DIS_ADC80_GATE     0x0002
#define P640_DIS_REGCLK_GATE    0x0001

// PHY_PG4_PTP_CTL Def's
#define P640_TRIG_SEL_SHIFT     10
#define P640_TRIG_SEL_MASK      0x1C00
#define P640_TRIG_DIS           0x0200
#define P640_TRIG_EN            0x0100
#define P640_TRIG_READ          0x0080
#define P640_TRIG_LOAD          0x0040
#define P640_PTP_RD_CLK         0x0020
#define P640_PTP_LOAD_CLK       0x0010
#define P640_PTP_STEP_CLK       0x0008
#define P640_PTP_ENABLE         0x0004
#define P640_PTP_DISABLE        0x0002
#define P640_PTP_RESET          0x0001

// PHY_PG4_PTP_STS Def's
#define P640_TXTS_RDY           0x0800
#define P640_RXTS_RDY           0x0400
#define P640_TRIG_DONE          0x0200
#define P640_EVENT_RDY          0x0100
#define P640_TXTS_IE            0x0008
#define P640_RXTS_IE            0x0004
#define P640_TRIG_IE            0x0002
#define P640_EVENT_IE           0x0001

// PHY_PG4_PTP_TSTS Def's
#define P640_TRIG7_ERROR        0x8000
#define P640_TRIG7_ACTIVE       0x4000
#define P640_TRIG6_ERROR        0x2000
#define P640_TRIG6_ACTIVE       0x1000
#define P640_TRIG5_ERROR        0x0800
#define P640_TRIG5_ACTIVE       0x0400
#define P640_TRIG4_ERROR        0x0200
#define P640_TRIG4_ACTIVE       0x0100
#define P640_TRIG3_ERROR        0x0080
#define P640_TRIG3_ACTIVE       0x0040
#define P640_TRIG2_ERROR        0x0020
#define P640_TRIG2_ACTIVE       0x0010
#define P640_TRIG1_ERROR        0x0008
#define P640_TRIG1_ACTIVE       0x0004
#define P640_TRIG0_ERROR        0x0002
#define P640_TRIG0_ACTIVE       0x0001

// PHY_PG4_PTP_RATEH Def's
#define P640_PTP_RATE_DIR       0x8000
#define P640_PTP_TMP_RATE       0x4000
#define P640_PTP_RATE_HI_MASK   0x03FF
#define P640_PTP_RATE_HI_SHIFT  16

// PHY_PG4_PTP_ESTS Def's
#define P640_EVNTS_MISSED_SHIFT 8
#define P640_EVNTS_MISSED_MASK  0x0700
#define P640_EVNTS_TS_LEN_SHIFT 6
#define P640_EVNTS_TS_LEN_MASK  0x00C0
#define P640_EVNT_RF            0x0020
#define P640_EVNT_NUM_SHIFT     2
#define P640_EVNT_NUM_MASK      0x001C
#define P640_MULT_EVENT         0x0002
#define P640_EVENT_DET          0x0001

// PHY_PG4_PTP_EDATA Def's
#define P640_E7_RISE            0x8000
#define P640_E7_DET             0x4000
#define P640_E6_RISE            0x2000
#define P640_E6_DET             0x1000
#define P640_E5_RISE            0x0800
#define P640_E5_DET             0x0400
#define P640_E4_RISE            0x0200
#define P640_E4_DET             0x0100
#define P640_E3_RISE            0x0080
#define P640_E3_DET             0x0040
#define P640_E2_RISE            0x0020
#define P640_E2_DET             0x0010
#define P640_E1_RISE            0x0008
#define P640_E1_DET             0x0004
#define P640_E0_RISE            0x0002
#define P640_E0_DET             0x0001

// PHY_PG5_PTP_TRIG Def's
#define P640_TRIG_PULSE         0x8000
#define P640_TRIG_PER           0x4000
#define P640_TRIG_IF_LATE       0x2000
#define P640_TRIG_NOTIFY        0x1000
#define P640_TRIG_GPIO_SHIFT    8
#define P640_TRIG_GPIO_MASK     0x0F00
#define P640_TRIG_TOGGLE        0x0080
#define P640_TRIG_CSEL_SHIFT    1
#define P640_TRIG_CSEL_MASK     0x000E
#define P640_TRIG_WR            0x0001

// PHY_PG5_PTP_EVNT Def's
#define P640_EVNT_RISE          0x4000
#define P640_EVNT_FALL          0x2000
#define P640_EVNT_SINGLE        0x1000
#define P640_EVNT_GPIO_SHIFT    8
#define P640_EVNT_GPIO_MASK     0x0F00
#define P640_EVNT_SEL_SHIFT     1
#define P640_EVNT_SEL_MASK      0x000E
#define P640_EVNT_WR            0x0001

// PHY_PG5_PTP_TXCFG0 Def's
#define P640_SYNC_1STEP         0x8000
#define P640_DR_INSERT          0x2000
#define P640_NTP_TS_EN          0x1000
#define P640_IGNORE_2STEP       0x0800
#define P640_CRC_1STEP          0x0400
#define P640_CHK_1STEP          0x0200
#define P640_IP1588_EN          0x0100
#define P640_TX_L2_EN           0x0080
#define P640_TX_IPV6_EN         0x0040
#define P640_TX_IPV4_EN         0x0020
#define P640_TX_PTP_VER_SHIFT   1
#define P640_TX_PTP_VER_MASK    0x001E
#define P640_TX_TS_EN           0x0001

// PHY_PG5_PTP_TXCFG1 Def's
#define P640_BYTE0_MASK_SHIFT   8
#define P640_BYTE0_MASK_MASK    0xFF00
#define P640_BYTE0_DATA_SHIFT   0
#define P640_BYTE0_DATA_MASK    0x00FF

// PHY_PG5_PSF_CFG0 Def's
#define P640_MAC_SRC_ADD_SHIFT  11
#define P640_MAC_SRC_ADD_MASK   0x1800
#define P640_MIN_PRE_SHIFT      8
#define P640_MIN_PRE_MASK       0x0700
#define P640_PKT_ENDIAN         0x0080
#define P640_PKT_IPV4           0x0040
#define P640_PKT_PCFR_EN        0x0020
#define P640_PKT_ERR_EN         0x0010
#define P640_PKT_TXTS_EN        0x0008
#define P640_PKT_RXTS_EN        0x0004
#define P640_PKT_TRIG_EN        0x0002
#define P640_PKT_EVNT_EN        0x0001

// PHY_PG5_PTP_RXCFG0 Def's
#define P640_DOMAIN_EN          0x8000
#define P640_ALT_MAST_DIS       0x4000
#define P640_USER_IP_SEL        0x2000
#define P640_USER_IP_EN         0x1000
#define P640_RX_SLAVE           0x0800
#define P640_IP1588_EN2         0x0400
#define P640_IP1588_EN1         0x0200
#define P640_IP1588_EN0         0x0100
#define P640_RX_L2_EN           0x0080
#define P640_RX_IPV6_EN         0x0040
#define P640_RX_IPV4_EN         0x0020
#define P640_RX_PTP_VER_SHIFT   1
#define P640_RX_PTP_VER_MASK    0x001E
#define P640_RX_TS_EN           0x0001

// PHY_PG5_PTP_RXCFG1 Def's
#define P640_BYTE0_MASK_SHIFT   8
#define P640_BYTE0_MASK_MASK    0xFF00
#define P640_BYTE0_DATA_SHIFT   0
#define P640_BYTE0_DATA_MASK    0x00FF

// PHY_PG5_PTP_RXCFG3 Def's
#define P640_TS_MIN_IFG_SHIFT   12
#define P640_TS_MIN_IFG_MASK    0xF000
#define P640_ACC_UDP            0x0800
#define P640_ACC_CRC            0x0400
#define P640_TS_APPEND          0x0200
#define P640_TS_INSERT          0x0100
#define P640_PTP_DOMAIN_SHIFT   0
#define P640_PTP_DOMAIN_MASK    0x00FF

// PHY_PG5_PTP_RXCFG4 Def's
#define P640_IPV4_UDP_MOD       0x8000
#define P640_TS_SEC_EN          0x4000
#define P640_TS_SEC_LEN_SHIFT   12
#define P640_TS_SEC_LEN_MASK    0x3000
#define P640_RXTS_NS_OFF_SHIFT  6
#define P640_RXTS_NS_OFF_MASK   0x0FC0
#define P640_RXTS_SEC_OFF_SHIFT 0
#define P640_RXTS_SEC_OFF_MASK  0x003F

// PHY_PG5_PTP_TRDH Def's
#define P640_PTP_TR_DURH_SHIFT  0
#define P640_PTP_TR_DURH_MASK   0x03FF

// PHY_PG6_PTP_COC Def's
#define P640_PTP_CLKOUT_EN      0x8000
#define P640_PTP_CLKOUT_SEL     0x4000
#define P640_PTP_CLKOUT_SPSEL   0x2000
#define P640_PTP_CLKDIV_SHIFT   0
#define P640_PTP_CLKDIV_MASK    0x00FF

// PHY_PG6_PSF_CFG1 Def's
#define P640_PTP_RESERVED_SHIFT 12
#define P640_PTP_RESERVED_MASK  0xF000
#define P640_VERSION_PTP_SHIFT  8
#define P640_VERSION_PTP_MASK   0x0F00
#define P640_TRANSP_SPEC_SHIFT  4
#define P640_TRANSP_SPEC_MASK   0x00F0
#define P640_MESSAGE_TYPE_SHIFT 0
#define P640_MESSAGE_TYPE_MASK  0x000F

// PHY_PG6_PSF_CFG2 Def's
#define P640_IP_SA_BYTE1_SHIFT  8
#define P640_IP_SA_BYTE1_MASK   0xFF00
#define P640_IP_SA_BYTE0_SHIFT  0
#define P640_IP_SA_BYTE0_MASK   0x00FF

// PHY_PG6_PSF_CFG3 Def's
#define P640_IP_SA_BYTE3_SHIFT  8
#define P640_IP_SA_BYTE3_MASK   0xFF00
#define P640_IP_SA_BYTE2_SHIFT  0
#define P640_IP_SA_BYTE2_MASK   0x00FF

// PHY_PG6_PTP_SFDCFG Def's
#define P640_TX_SFD_GPIO_SHIFT  4
#define P640_TX_SFD_GPIO_MASK   0x00F0
#define P640_RX_SFD_GPIO_SHIFT  0
#define P640_RX_SFD_GPIO_MASK   0x000F

// PHY_PG6_PTP_INTCTL Def's
#define P640_PTP_INT_GPIO_SHIFT 0
#define P640_PTP_INT_GPIO_MASK  0x000F

// PHY_PG6_PTP_CLKSRC Def's
#define P640_CLK_SRC_SHIFT      14
#define P640_CLK_SRC_MASK       0xC000
#define P640_CLK_SRC_PER_SHIFT  0
#define P640_CLK_SRC_PER_MASK   0x007F

// PHY_PG6_PTP_OFF Def's
#define P640_PTP_OFFSET_SHIFT   0
#define P640_PTP_OFFSET_MASK    0x00FF

// PHY_PG6_PTP_GPIOMON Def's
#define P640_PTP_GPIO_IN_SHIFT  0
#define P640_PTP_GPIO_IN_MASK   0x0FFF

// PHY_PG6_PTP_RXHASH Def's
#define P640_RX_HASH_EN         0x1000
#define P640_PTP_RX_HASH_SHIFT  0
#define P640_PTP_RX_HASH_MASK   0x0FFF

#endif	// _EPL_REGS_INCLUDE