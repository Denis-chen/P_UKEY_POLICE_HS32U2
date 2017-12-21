// +FHDR -----------------------------------------------------------------------
// Copyright (c) 2009, Hongsi.
// Hongsi Confidential Proprietary
// 2009/7/15
//
// -----------------------------------------------------------------------------
// File Name: ssf33.h
// Type: C Language 
//
// -----------------------------------------------------------------------------
// Header:
// This header file is definitions for SSF33 Function of HS32U2.
//
// -----------------------------------------------------------------------------
// Detailed Func Description:
// 1. Data Type Definitions.
// 2. Constant Definitions.
// 3. Register Definitions.
// 4. Function Declarations.
//
// -----------------------------------------------------------------------------
// Revision History
// DATE         AUTHOR          DESCRIPTION
// 2009/7/15 					V1.0
// -FHDR -----------------------------------------------------------------------

// ---------------------------------------------------------------------  
// Data Type Definitions 
// ---------------------------------------------------------------------  

typedef unsigned int U32;
typedef unsigned char U8;

// ---------------------------------------------------------------------  
// Constant Definitions 
// ---------------------------------------------------------------------  

#define BUSY  0x00000001

#define OPERATION_ENCODE	0x00
#define OPERATION_DECODE	0x01

#define MODE_ECB			0x00
#define MODE_CBC			0x01

// ---------------------------------------------------------------------  
// Register Definitions
// ---------------------------------------------------------------------  

#define FAEDINR  ( U32 *)0x00b40000
#define FAEKINR  ( U32 *)0x00b40010
#define FAEIVINR ( U32 *)0x00b40020
#define FAEDOUTR ( U32 *)0x00b40030
#define FAECSR   (*( U32 *)0x00b40040)

// ---------------------------------------------------------------------  
// Function Declarations
// ---------------------------------------------------------------------  
#define SSF33_ENCKEY(key,keyout) ((void (*)())(0x0003F000))(key,keyout)
#define SSF33_DECKEY(key,keyout) ((void (*)())(0x0003F964))(key,keyout)	    	    
void SSX33_GENERATE_KEY(U32 *x, U32 *key);
void SSF33_CRYPT(U8 *in, U32 bytes, U32 * key, U8 *iv, U8 operation, U8 mode, U8 *out);


/***************************************************************
*
*摘要：本函数配置SSF33模块
*
*参数：
*		CSR[in]：状态寄存器的配置
*		pKey[in]：密钥，其长度由CSR决定，不能为NULL
*		pIV[in]：IV数据指针，当不需要IV时，无意义，可为NULL
*返回值：无
*
*备注：	本函数没有进行参数合法性检测，调用时需要确保参数的合法性
*
***************************************************************/
asm void SSF33_Setup(unsigned int CSR, unsigned int *pKey, unsigned int *pIV);

/***************************************************************
*
*摘要：本函数计算BlockNum块SSF33
*
*参数：
*		pInData[in]：待运算的数据
*		pOutData[out]：计算结果
*		BlockNum[in]：待运算的块数
*
*返回值：无
*
*备注：	1、本函数没有检测pInData和pOutData所指区域是否有效
*		2、若pInData和pOutData有重合，则必须满足pInData >=  pOutData
*		3、本函数必须在SSF33_Setup之后运行
*		4、本函数不能做多于1块的CBC模式的SM1解密
*
***************************************************************/
asm void SSF33_Run(unsigned int *pInData, unsigned int *pOutData, unsigned int BlockNum);

asm void SSF33_Run_CBC_Decrypt(unsigned int *pInData, unsigned int *pOutData, unsigned int BlockNum);

