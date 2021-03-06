////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
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
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file   drvDscmb.h
/// @brief  Descrambler (Dscmb) Driver Interface
/// @author MStar Semiconductor,Inc.
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __DRV_DSCMB_H__
#define __DRV_DSCMB_H__

#include "MsTypes.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define MSIF_DSMB_LIB_CODE              {'D','S','M','B'}    //Lib code
#define MSIF_DSMB_LIBVER                {'0','2'}            //LIB version
#define MSIF_DSMB_BUILDNUM              {'1','8'}            //Build Number
#define MSIF_DSMB_CHANGELIST            {'0','0','5','6','5','9','8','0'} //P4 ChangeList Number

#define DSCMB_DRV_VERSION               /* Character String for DRV/API version             */  \
    MSIF_TAG,                           /* 'MSIF'                                           */  \
    MSIF_CLASS,                         /* '00'                                             */  \
    MSIF_CUS,                           /* 0x0000                                           */  \
    MSIF_MOD,                           /* 0x0000                                           */  \
    MSIF_CHIP,                                                                                  \
    MSIF_CPU,                                                                                   \
    MSIF_DSMB_LIB_CODE,                 /* IP__                                             */  \
    MSIF_DSMB_LIBVER,                   /* 0.0 ~ Z.Z                                        */  \
    MSIF_DSMB_BUILDNUM,                 /* 00 ~ 99                                          */  \
    MSIF_DSMB_CHANGELIST,               /* CL#                                              */  \
    MSIF_OS


#define DSCMB_ASSERT_AND_RETURN(x)             if (!(x)){printf ("ASSERT FAIL: %s %s %d\n", __FILE__, __FUNCTION__, __LINE__); return FALSE;}
#define DSCMB_ASSERT_NO_RETURN(x)             if (!(x)){printf ("ASSERT FAIL: %s %s %d\n", __FILE__, __FUNCTION__, __LINE__);}

#define DSCMB_LIB_TIME_MAX          16      ///< Maximum length of time
#define DSCMB_LIB_DATE_MAX          16      ///< Maximum length of date

typedef struct
{
    MS_U8   Time[DSCMB_LIB_TIME_MAX];       ///< Library Built Time
    MS_U8   Date[DSCMB_LIB_DATE_MAX];       ///< Library Built Date
} DSCMB_Info;

typedef struct
{
    MS_U32 u32Status;
} DSCMB_Status;

/// Descrambler null filter ID
#define DRV_DSCMB_FLT_NULL                      0xFFFFFFFF

/// Descrambler algorithm type
typedef enum
{
    /// Descrambler algorithm : CSA
    E_DSCMB_TYPE_CSA = 0,    // CSA
    /// Descrambler algorithm : NSA as ESA
    E_DSCMB_TYPE_NSA_AS_ESA, // NSA as ESA
    /// Descrambler algorithm : CI+ DES
    E_DSCMB_TYPE_DES,        // CI+ DES
    /// Descrambler algorithm : CI+ AES
    E_DSCMB_TYPE_AES,        // CI+ AES
    // E_DSCMB_TYPE_ESA,       // ESA
    // E_DSCMB_TYPE_NSAS,      // NSAS
    E_DSCMB_TYPE_AES_ECB,
    E_DSCMB_TYPE_AES_SCTE52,  // Descrambler algorithm : DBook, AES+CBC, S8 new, not support for all chips
    E_DSCMB_TYPE_AES_CTR,     // AES Counter mode
    E_DSCMB_TYPE_TDES_ECB,
    E_DSCMB_TYPE_TDES_SCTE52,

    // Synamedia AES
    E_DSCMB_TYPE_SYN_AES,    // AES Leading CLR EBC

    E_DSCMB_TYPE_MULTI2,    // Multi2

    /// Descrambler algorithm : CSA3
    E_DSCMB_TYPE_CSA3,    // CSA3
} DSCMB_Type;

/// Descrambler key type
typedef enum
{
    /// Descrambler key type : clear
    E_DSCMB_KEY_CLEAR = 0,
    /// Descrambler key type : even
    E_DSCMB_KEY_EVEN,
    /// Descrambler key type : odd
    E_DSCMB_KEY_ODD,
} DSCMB_Key_Type;

/// Scramble level
typedef enum
{
    /// Descrambler level : none
    E_DSCMB_NONE                    =   0x00000000,
    /// Descrambler level : TS level
    E_DSCMB_TS                      =   0x00000001,
    /// Descrambler level : PES level
    E_DSCMB_PES                     =   0x00000002,
    /// Descrambler level : TS and PES level
    E_DSCMB_TS_PES                  =   (E_DSCMB_TS | E_DSCMB_PES),
} SCMB_Level;

/// Key ladder input source
typedef enum
{
    /// Key ladder source from ACPU
    E_DSCMB_KL_SRC_ACPU             =   0,
    /// Key ladder source from SECRET_1
    E_DSCMB_KL_SRC_SECRET_1         =   1,
    /// Key ladder source from SECRET_2
    E_DSCMB_KL_SRC_SECRET_2         =   2,
    /// Key ladder source from SECRET_3
    E_DSCMB_KL_SRC_SECRET_3         =   3,
    /// Key ladder source from SECRET_4
    E_DSCMB_KL_SRC_SECRET_4         =   4,
    /// Key ladder source from VGK
    E_DSCMB_KL_SRC_VGK              =   7,

} DSCMB_KLSrc;

/// Key ladder output destination
typedef enum
{
    /// Key ladder destination to ACPU
    E_DSCMB_KL_DST_ACPU             =   0x1,
    /// Key ladder destination to key table (ESA)
    E_DSCMB_KL_DST_KT_ESA           =   0x4,
    /// Key ladder destination to key table (NSA)
    E_DSCMB_KL_DST_KT_NSA           =   0x2,
    /// Key ladder destination to DMA (AES)
    E_DSCMB_KL_DST_DMA_AES          =   0x8,
    /// Key ladder destination to DMA (TDES)
    E_DSCMB_KL_DST_DMA_TDES         =   0x10,

} DSCMB_KLDst;

typedef enum
{
    // descrambler engine
    E_DSCMB_CAP_ENGINE_NUM,
    // descrambler slot
    E_DSCMB_CAP_FLT_NUM,
    // descrambler type supported
    E_DSCMB_CAP_SUPPORT_ALGORITHM,
    // descrambler key type supported
    E_DSCMB_CAP_SUPPORT_KEY_TYPE,
    // descrambler mapping, start tsp pid filter
    E_DSCMB_CAP_PIDFILTER_MAP_START,
    // descrambler mapping, end tsp pid filter
    E_DSCMB_CAP_PIDFILTER_MAP_END,
} DSCMB_Query_Type;

typedef enum
{
    E_DSCMB_KL_TDES                 =   0x00000000,
    E_DSCMB_KL_AES                  =   0x0000003F,
} DSCMB_KLEng;

/// Key ladder configurations
typedef struct
{
    MS_BOOL     bDecrypt;
    MS_BOOL     bInverse;
    MS_BOOL     bKeepRound;
    MS_U32      u32Round;
    MS_U32      u32EngMode;

} DSCMB_KLCfg;

// Backward compatible
typedef DSCMB_KLSrc          DSCMB_KLadderSrc;
#define E_DSCMB_KLAD_SRC_ACPU               E_DSCMB_KL_SRC_ACPU
#define E_DSCMB_KLAD_SRC_SECRET_KEY1        E_DSCMB_KL_SRC_SECRET_1
#define E_DSCMB_KLAD_SRC_SECRET_KEY2        E_DSCMB_KL_SRC_SECRET_2
#define E_DSCMB_KLAD_SRC_SECRET_KEY3        E_DSCMB_KL_SRC_SECRET_3
#define E_DSCMB_KLAD_SRC_SECRET_KEY4        E_DSCMB_KL_SRC_SECRET_4
#define E_DSCMB_KLAD_SRC_VGK                E_DSCMB_KL_SRC_VGK

typedef DSCMB_KLDst          DSCMB_KLadderDst;
#define E_DSCMB_KLAD_DST_KTAB_ESA           E_DSCMB_KL_DST_KT_ESA
#define E_DSCMB_KLAD_DST_KTAB_NSA =         E_DSCMB_KL_DST_KT_NSA
#define E_DSCMB_KLAD_DST_AESDMA_AES =       E_DSCMB_KL_DST_DMA_AES
#define E_DSCMB_KLAD_DST_AESDMA_TDES =      E_DSCMB_KL_DST_DMA_TDES
#define E_DSCMB_KLAD_DST_ACPU =             E_DSCMB_KL_DST_ACPU

typedef DSCMB_KLCfg          DSCMB_KLadderConfig;
// Backward compatible

// wrapper function
#define MDrv_DSCMB_FltAlloc(void)   \
    MDrv_DSCMB2_FltAlloc(0)
#define MDrv_DSCMB_FltFree(u32DscmbId)   \
    MDrv_DSCMB2_FltFree(0, u32DscmbId)
#define MDrv_DSCMB_FltConnectPid(u32DscmbId, u32Pid)  \
    MDrv_DSCMB2_FltConnectPid(0, u32DscmbId, u32Pid)
#define MDrv_DSCMB_FltDisconnectPid(u32DscmbId, u32Pid) \
    MDrv_DSCMB2_FltDisconnectPid(0, u32DscmbId, u32Pid)
#define MDrv_DSCMB_FltConnectFltId(u32DscmbId, u32FltId)    \
    MDrv_DSCMB2_FltConnectFltId(0, u32DscmbId, u32FltId)
#define MDrv_DSCMB_FltDscmb(u32DscmbId, bDscmb) \
    MDrv_DSCMB2_FltDscmb(0, u32DscmbId, bDscmb)
#define MDrv_DSCMB_FltTypeSet(u32DscmbId, eType)    \
    MDrv_DSCMB2_FltTypeSet(0, u32DscmbId, eType)
#define MDrv_DSCMB_Multi2_SetRound(u32Round)    \
    MDrv_DSCMB2_Multi2_SetRound(0, u32Round)
#define MDrv_DSCMB_FltKeySet(u32DscmbId, eKeyType, pu8Key)  \
    MDrv_DSCMB2_FltKeySet(0, u32DscmbId, eKeyType, pu8Key)
#define MDrv_DSCMB_FltKeyReset(u32DscmbId, eKeyType)    \
    MDrv_DSCMB2_FltKeyReset(0, u32DscmbId, eKeyType)
#define MDrv_DSCMB_FltIVSet(u32DscmbId, eKeyType, pu8IV)    \
    MDrv_DSCMB2_FltIVSet(0, u32DscmbId, eKeyType, pu8IV)
#define MDrv_DSCMB_PidFlt_ScmbStatus(u32PidFltId, pScmbLevel)    \
    MDrv_DSCMB2_PidFlt_ScmbStatus(0, u32PidFltId, pScmbLevel)
#define MDrv_DSCMB_FltKeyReset(u32DscmbId, eKeyType)    \
    MDrv_DSCMB2_FltKeyReset(0, u32DscmbId, eKeyType)

// descrambler initial function
MS_BOOL MDrv_DSCMB_Init(void);

// descrambler query function
MS_BOOL MDrv_DSCMB2_GetCap(MS_U32 u32EngId, DSCMB_Query_Type eQueryType, void* pInput, void* pOutput);

const DSCMB_Info* MDrv_DSCMB_GetInfo(void);
MS_BOOL MDrv_DSCMB_GetLibVer(const MSIF_Version **ppVersion);
MS_BOOL MDrv_DSCMB_GetStatus(DSCMB_Status *pStatus);
MS_BOOL MDrv_DSCMB_SetDBGLevel(MS_U32 u32Level);

// descrambler filter management
MS_U32 MDrv_DSCMB2_FltAlloc(MS_U32 u32EngId);
MS_BOOL MDrv_DSCMB2_FltFree(MS_U32 u32EngId, MS_U32 u32DscmbId);

// descrambler filter maps to TSP pid
MS_BOOL MDrv_DSCMB2_FltConnectPid(MS_U32 u32EngId, MS_U32 u32DscmbId, MS_U32 u32Pid);
MS_BOOL MDrv_DSCMB2_FltDisconnectPid(MS_U32 u32EngId, MS_U32 u32DscmbId, MS_U32 u32Pid);

// descrambler filter maps to TSP filter id
MS_BOOL MDrv_DSCMB2_FltConnectFltId(MS_U32 u32EngId, MS_U32 u32DscmbId, MS_U32 u32FltId);

// Set descrambler filter as scrambling/decrambling mode
// Default filter mode is descrambling if this function is not specified
// This function should be invoked before MDrv_DSCMB_FltTypeSet
MS_BOOL MDrv_DSCMB2_FltDscmb(MS_U32 u32EngId, MS_U32 u32DscmbId, MS_BOOL bDscmb);

// descrambler algorithm
MS_BOOL MDrv_DSCMB_SlotSwitchWrite(MS_U32 u32DscmbId, DSCMB_Key_Type eKeyType, MS_U32 u32SW0, MS_U32 u32SW1, MS_U32 u32SW2);
MS_BOOL MDrv_DSCMB2_FltTypeSet(MS_U32 u32EngId, MS_U32 u32DscmbId, DSCMB_Type);

MS_BOOL MDrv_DSCMB2_PVR_RecCtrl(MS_U32 u32EngId, MS_BOOL Enable);

// descrambler altorithm related
#if defined(DSCMB_MULTI2_ENABLE)
MS_BOOL MDrv_DSCMB2_Multi2_SetRound(MS_U32 u32EngId, MS_U32 u32Round);
#endif

#if (!( defined(TSP_VERSION) && (TSP_VERSION == TSP_VER_2_0)))
//--------------------------------------------------------------------------------------------------
/// Set Riv of HDCP2, which is 64-bits number generated from transmitter
/// @param u32EngId \b IN: cipher engine index
/// @param pu8RIV \b IN: pointer to 64bit Riv buffer in BIG ENDIAN order
/// @return TRUE - Success
/// @return FALSE - Failure
/// @note
///
//--------------------------------------------------------------------------------------------------
MS_BOOL MDrv_DSCMB2_HDCP2_SetRIV(MS_U32 u32EngId, MS_U8* pu8RIV);
//--------------------------------------------------------------------------------------------------
/// IN/OUT path of cipher engine, inform only function
/// @param u32EngId \b IN: reserved
/// @param u32Flow \b IN: value of TSP CA_CTRL register
/// @return TRUE - Success
/// @return FALSE - Failure
/// @note
/// called from demux driver
//--------------------------------------------------------------------------------------------------
MS_BOOL MDrv_DSCMB2_SetFlow(MS_U32 u32EngId, MS_U32 u32Flow);
#endif
// descrambler key
MS_BOOL MDrv_DSCMB2_FltKeySet(MS_U32 u32EngId, MS_U32 u32DscmbId, DSCMB_Key_Type eKeyType, MS_U8* pu8Key);
MS_BOOL MDrv_DSCMB2_FltKeyReset(MS_U32 u32EngId, MS_U32 u32DscmbId, DSCMB_Key_Type eKeyType);
MS_BOOL MDrv_DSCMB2_FltIVSet(MS_U32 u32EngId, MS_U32 u32DscmbId, DSCMB_Key_Type eKeyType, MS_U8* pu8IV);
MS_BOOL MDrv_DSCMB2_FltKeyReset(MS_U32 u32EngId, MS_U32 u32DscmbId, DSCMB_Key_Type eKeyType);

// corrupt
//MS_BOOL MDrv_DSCMB_EcmCorruptSet(MS_U8 u8CorruptDataByte, MS_U8 u8FromByte);
//MS_BOOL MDrv_DSCMB_EcmCorruptEnable(MS_U32 u32Pid, MS_BOOL bEnable);

// scramble status
MS_BOOL MDrv_DSCMB2_PidFlt_ScmbStatus(MS_U32 u32EngId, MS_U32 u32PidFltId, SCMB_Level* pScmbLevel);

// Key ladder
MS_BOOL MDrv_DSCMB_KLadder_Reset(void);
MS_BOOL MDrv_DSCMB_KLadder_SetInput(MS_U32 u32Level, MS_U8* pu8In, MS_U32 u32InLen);
MS_BOOL MDrv_DSCMB_KLadder_SetKey(DSCMB_KLSrc KLSrc, MS_U8* pu8Key, MS_U32 u32KeyLen);
MS_BOOL MDrv_DSCMB_KLadder_SetDst(DSCMB_KLDst KLDst);
void MDrv_DSCMB_KLadder_SetConfig(DSCMB_KLCfg *KLCfg);
MS_BOOL MDrv_DSCMB_KLadder_Start(void);
MS_BOOL MDrv_DSCMB_KLadder_IsComplete(void);
MS_BOOL MDrv_DSCMB_KLadder_Output_Start(MS_U32 u32DscmbId, DSCMB_Key_Type eKeyType);
MS_BOOL MDrv_DSCMB_KLadder_Output_IsComplete(void);
MS_BOOL MDrv_DSCMB_KLadder_Output_Stop(void);
MS_BOOL MDrv_DSCMB_KLadder_ResetAcpuAck(void);
MS_BOOL MDrv_DSCMB_KLadder_ReadDataFromAcpu(MS_U8* pu8Out);
MS_BOOL MDrv_DSCMB_KLadder_Stop(void); // write KTE

// Only for scramble
MS_BOOL MDrv_DSCMB_2ndarySet(MS_U32 u32PidPrim, MS_U32 u32Pid2ndary);
MS_BOOL MDrv_DSCMB_2ndaryReset(MS_U32 u32PidPrim);

#if (( defined(TSP_VERSION) && (TSP_VERSION == TSP_VER_2_0)))
// PVR2 Setting //
MS_BOOL MDrv_DSCMB2_SetRecBuf(MS_U32 u32EngId , MS_U32 u32Start, MS_U32 u32Size);
MS_BOOL  MDrv_DSCMB2_RecCtrl(MS_U32 u32EngId, MS_BOOL bEnable);
MS_BOOL  MDrv_DSCMB2_GetRecWptr(MS_U32 u32EngId, MS_U32* pu32Write);
#endif


#ifdef __cplusplus
}
#endif

#endif
