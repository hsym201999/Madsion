////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2008-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
////////////////////////////////////////////////////////////////////////////////

#ifndef _DRVBDMA_H_
#define _DRVBDMA_H_

////////////////////////////////////////////////////////////////////////////////
/// @file drvBDMA.h
/// @author MStar Semiconductor Inc.
/// @brief Byte DMA control driver
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C"
{
#endif

#include "MsTypes.h"

////////////////////////////////////////////////////////////////////////////////
// Define & data type
////////////////////////////////////////////////////////////////////////////////
#define MSIF_BDMA_LIB_CODE	{'B','D','M','A'}    //Lib code
#define MSIF_BDMA_LIBVER		{'0','3'}            //LIB version
#define MSIF_BDMA_BUILDNUM      {'0','1'}            //Build Number
#define MSIF_BDMA_CHANGELIST   {'0','0','3','4','8','0','3','3'} //P4 ChangeList Number

#define BDMA_DRV_VERSION                /* Character String for DRV/API version             */  \
    MSIF_TAG,                           /* 'MSIF'                                           */  \
    MSIF_CLASS,                         /* '00'                                             */  \
    MSIF_CUS,                           /* 0x0000                                           */  \
    MSIF_MOD,                           /* 0x0000                                           */  \
    MSIF_CHIP,                                                                                  \
    MSIF_CPU,                                                                                   \
    MSIF_BDMA_LIB_CODE,                  /* IP__                                             */  \
    MSIF_BDMA_LIBVER,                    /* 0.0 ~ Z.Z                                        */  \
    MSIF_BDMA_BUILDNUM,                  /* 00 ~ 99                                          */  \
    MSIF_BDMA_CHANGELIST,                /* CL#                                              */  \
    MSIF_OS

//v: value n: shift n bits
#define _LShift(v, n)           ((v) << (n))
#define _RShift(v, n)           ((v) >> (n))

#define BDMA_SEARCH_ALL_MATCHED (0)
#define BDMA_CRC32_POLY         (0x04C11DB7)
#define BDMA_CRC16_POLY         (0x8005)
#define BDMA_CRC_SEED_0         (0)
#define BDMA_CRC_SEED_F         (0xFFFFFFFF)

/// Operation cfg
#define BDMA_OPCFG_DEF          		(0)
#define BDMA_OPCFG_INV_COPY     	(0x01)
#define BDMA_OPCFG_CRC_REFLECT  	(0x02)      //bit reflection of each input byte
#define BDMA_OPCFG_CRC_COPY     	(0x04)      //copy then crc check
#define BDMA_OPCFG_NOWAIT_COPY  	(0x08)      //copy then quit
#define BDMA_OPCFG_MOBF_PS  		(0x10)      //copy then quit

typedef enum _BDMA_DbgLv
{
    E_BDMA_DBGLV_NONE           //no debug message
    ,E_BDMA_DBGLV_PERFORMANCE   //show performance only
    ,E_BDMA_DBGLV_ERR_ONLY      //show error only
    ,E_BDMA_DBGLV_REG_DUMP      //show error & reg dump
    ,E_BDMA_DBGLV_INFO          //show error & informaiton
    ,E_BDMA_DBGLV_ALL           //show error, information & funciton name
}BDMA_DbgLv;

typedef enum _BDMA_Dev
{
    E_BDMA_DEV_MIU0
    ,E_BDMA_DEV_MIU1
    ,E_BDMA_DEV_SEARCH
    ,E_BDMA_DEV_CRC32
    ,E_BDMA_DEV_MEM_FILL
    ,E_BDMA_DEV_FLASH
    ,E_BDMA_DEV_DMDMCU
    ,E_BDMA_DEV_VDMCU
    ,E_BDMA_DEV_DSP
    ,E_BDMA_DEV_TSP
    ,E_BDMA_DEV_1KSRAM_HK51
    ,E_BDMA_DEV_NOT_SUPPORT
}BDMA_Dev;

typedef enum _BDMA_SrcDev
{
    E_BDMA_SRCDEV_MIU0          = E_BDMA_DEV_MIU0
    ,E_BDMA_SRCDEV_MIU1         = E_BDMA_DEV_MIU1
    ,E_BDMA_SRCDEV_MEM_FILL     = E_BDMA_DEV_MEM_FILL
    ,E_BDMA_SRCDEV_FLASH        = E_BDMA_DEV_FLASH
    ,E_BDMA_SRCDEV_NOT_SUPPORT  = E_BDMA_DEV_NOT_SUPPORT
}BDMA_SrcDev;

typedef enum _BDMA_DstDev
{
    E_BDMA_DSTDEV_MIU0          = E_BDMA_DEV_MIU0
    ,E_BDMA_DSTDEV_MIU1         = E_BDMA_DEV_MIU1
    ,E_BDMA_DSTDEV_SEARCH       = E_BDMA_DEV_SEARCH
    ,E_BDMA_DSTDEV_CRC32        = E_BDMA_DEV_CRC32
    ,E_BDMA_DSTDEV_DMDMCU       = E_BDMA_DEV_DMDMCU         //Demod
    ,E_BDMA_DSTDEV_VDMCU        = E_BDMA_DEV_VDMCU          //VD
    ,E_BDMA_DSTDEV_DSP          = E_BDMA_DEV_DSP
    ,E_BDMA_DSTDEV_TSP          = E_BDMA_DEV_TSP
    ,E_BDMA_DSTDEV_HK51_1KSRAM  = E_BDMA_DEV_1KSRAM_HK51
    ,E_BDMA_DSTDEV_NOT_SUPPORT  = E_BDMA_DEV_NOT_SUPPORT
}BDMA_DstDev;

#define BDMA_SET_CPYTYPE(src, dst) ((src & 0x0F) | _LShift((dst &0x0F), 8))

typedef enum _BDMA_CpyType
{
    E_BDMA_SDRAM2SDRAM          = BDMA_SET_CPYTYPE(E_BDMA_DEV_MIU0, E_BDMA_DEV_MIU0)
    ,E_BDMA_SDRAM2SDRAM1        = BDMA_SET_CPYTYPE(E_BDMA_DEV_MIU0, E_BDMA_DEV_MIU1)
    ,E_BDMA_SDRAM2DMDMCU        = BDMA_SET_CPYTYPE(E_BDMA_DEV_MIU0, E_BDMA_DEV_DMDMCU)
    ,E_BDMA_SDRAM2VDMCU         = BDMA_SET_CPYTYPE(E_BDMA_DEV_MIU0, E_BDMA_DEV_VDMCU)
    ,E_BDMA_SDRAM2DSP           = BDMA_SET_CPYTYPE(E_BDMA_DEV_MIU0, E_BDMA_DEV_DSP)
    ,E_BDMA_SDRAM2TSP           = BDMA_SET_CPYTYPE(E_BDMA_DEV_MIU0, E_BDMA_DEV_TSP)
    ,E_BDMA_SDRAM2SRAM1K_HK51   = BDMA_SET_CPYTYPE(E_BDMA_DEV_MIU0, E_BDMA_DEV_1KSRAM_HK51)
    ,E_BDMA_SDRAM12SDRAM        = BDMA_SET_CPYTYPE(E_BDMA_DEV_MIU1, E_BDMA_DEV_MIU0)
    ,E_BDMA_SDRAM12SDRAM1       = BDMA_SET_CPYTYPE(E_BDMA_DEV_MIU1, E_BDMA_DEV_MIU1)
    ,E_BDMA_SDRAM12DMDMCU       = BDMA_SET_CPYTYPE(E_BDMA_DEV_MIU1, E_BDMA_DEV_DMDMCU)
    ,E_BDMA_SDRAM12VDMCU        = BDMA_SET_CPYTYPE(E_BDMA_DEV_MIU1, E_BDMA_DEV_VDMCU)
    ,E_BDMA_SDRAM12DSP          = BDMA_SET_CPYTYPE(E_BDMA_DEV_MIU1, E_BDMA_DEV_DSP)
    ,E_BDMA_SDRAM12TSP          = BDMA_SET_CPYTYPE(E_BDMA_DEV_MIU1, E_BDMA_DEV_TSP)
    ,E_BDMA_SDRAM12SRAM1K_HK51  = BDMA_SET_CPYTYPE(E_BDMA_DEV_MIU1, E_BDMA_DEV_1KSRAM_HK51)
    ,E_BDMA_FLASH2SDRAM         = BDMA_SET_CPYTYPE(E_BDMA_DEV_FLASH, E_BDMA_DEV_MIU0)
    ,E_BDMA_FLASH2SDRAM1        = BDMA_SET_CPYTYPE(E_BDMA_DEV_FLASH, E_BDMA_DEV_MIU1)
    ,E_BDMA_FLASH2DMDMCU        = BDMA_SET_CPYTYPE(E_BDMA_DEV_FLASH, E_BDMA_DEV_DMDMCU)
    ,E_BDMA_FLASH2VDMCU         = BDMA_SET_CPYTYPE(E_BDMA_DEV_FLASH, E_BDMA_DEV_VDMCU)
    ,E_BDMA_FLASH2DSP           = BDMA_SET_CPYTYPE(E_BDMA_DEV_FLASH, E_BDMA_DEV_DSP)
    ,E_BDMA_FLASH2TSP           = BDMA_SET_CPYTYPE(E_BDMA_DEV_FLASH, E_BDMA_DEV_TSP)
    ,E_BDMA_FLASH2SRAMHK51      = BDMA_SET_CPYTYPE(E_BDMA_DEV_FLASH, E_BDMA_DEV_1KSRAM_HK51)
    ,E_BDMA_CPYTYPE_MAX
}BDMA_CpyType;

typedef enum _BDMA_Result
{
    E_BDMA_NOT_SUPPORT = -1
    ,E_BDMA_FAIL = 0
    ,E_BDMA_OK = 1
    ,E_BDMA_TIMEOUT
    ,E_BDMA_QUEUE_FULL
    ,E_BDMA_BUSY
}BDMA_Result;

typedef struct _BDMA_HwInfo
{
    MS_BOOL bEnMIU1;        //MIU1
    MS_BOOL bEnHost;        //bdma host
    MS_BOOL bEnMemFill;     //memory fill
    MS_BOOL bEnFlsCpy;      //flash copy
    MS_BOOL bEnDevDw;       //bdma device data width
    MS_BOOL bEnDmyWrCnt;    //bdma dummy wr count
    MS_BOOL bEnDMDMCU;      //bdma to DeMod MCU
    MS_BOOL bEnTSP;         //bdma to TSP
    MS_BOOL bEnDSP;         //bdma to DSP
    MS_BOOL bEnHK51_1KSRAM; //bdma to HK51_1KSRAM
}BDMA_HwInfo;

typedef struct _BDMA_Info
{
    MS_U8       u8ChNum;
    MS_U16      u16ChipVer;
    MS_U32      u32IOMap;
    MS_U32      u32MIU1Base;
    MS_S32      s32Mutex;
    MS_BOOL     bInit;
    BDMA_DbgLv  eDbgLv;
    BDMA_HwInfo sHwCap;
}BDMA_Info;

typedef struct _BDMA_ChStatus
{
    MS_BOOL bIsBusy;
    MS_BOOL bIsInt;
    MS_BOOL bIsFound;
}BDMA_ChStatus;

typedef struct _BDMA_Status
{
    MS_BOOL         bInit;
    BDMA_DbgLv      eDbgLv;
    BDMA_ChStatus   sChSta[2];
}BDMA_Status;

#ifdef MOBF_ENABLE

typedef struct _BDMA_MOBF_PS
{
    MS_U32 u32Pattern;
    MS_U32 u32ExcluBit;
    MS_U32 u32MobfKey;
}BDMA_MOBF_PS;

#endif

typedef void (*BDMA_ISR_CBF)(BDMA_Result eRet);
////////////////////////////////////////////////////////////////////////////////
// Extern Function
////////////////////////////////////////////////////////////////////////////////

// status check & dbg level
BDMA_Result MDrv_BDMA_GetLibVer(const MSIF_Version **ppVersion);
void MDrv_BDMA_GetStatus(BDMA_Status *pStatus);
const BDMA_Info* MDrv_BDMA_GetInfo(void);
MS_U32 MDrv_BDMA_GetMinSize(void);
BDMA_Result MDrv_BDMA_SetDbgLevel(BDMA_DbgLv eLevel);

BDMA_Result MDrv_BDMA_Init(MS_U32 u32Miu1Base);

MS_U32 MDrv_BDMA_Search(MS_PHYADDR u32Addr, MS_U32 u32Len, MS_U32 u32Pattern, MS_U32 u32ExcluBit, BDMA_SrcDev eDev);
#ifdef MOBF_ENABLE
MS_U32 MDrv_BDMA_MOBFSearch(MS_PHYADDR u32Addr, MS_U32 u32Len, BDMA_MOBF_PS *pMobfPsCfg, BDMA_SrcDev eDev);
#endif
MS_U32 MDrv_BDMA_CRC32(MS_PHYADDR u32Addr, MS_U32 u32Len, MS_U32 u32Poly, MS_U32 u32Seed, BDMA_SrcDev eDev, MS_BOOL bReflect);
BDMA_Result MDrv_BDMA_PatternFill(MS_PHYADDR u32Addr, MS_U32 u32Len, MS_U32 u32Pattern, BDMA_DstDev eDev);

BDMA_Result MDrv_BDMA_MemCopy(MS_PHYADDR u32SrcAddr, MS_PHYADDR u32DstAddr, MS_U32 u32Len);
BDMA_Result MDrv_BDMA_FlashCopy2Dram(MS_PHYADDR u32FlashAddr, MS_PHYADDR u32DramAddr, MS_U32 u32Len);
BDMA_Result MDrv_BDMA_CopyHnd(MS_PHYADDR u32SrcAddr, MS_PHYADDR u32DstAddr, MS_U32 u32Len, BDMA_CpyType eCpyType, MS_U8 u8OpCfg);

BDMA_Result MDrv_BDMA_WaitFlashDone(void);

void MDrv_BDMA_SetSPIOffsetForMCU(void);

// status
void MDrv_BDMA_DumpCB(void *pvOpCB);

BDMA_Result MDrv_BDMA_Stop_All(void);
BDMA_Result MDrv_BDMA_Stop(MS_U8 u8Ch);

BDMA_Result MDrv_BDMA_Exit(void);


#ifdef __cplusplus
}
#endif
#endif
