#ifndef __SYSTEM_ESEM16_H
#define __SYSTEM_ESEM16_H

#include "esem16.h"
#include "typedef.h"

typedef signed long  s32;
typedef signed short s16;
typedef signed char  s8;

typedef signed long  const sc32;  /* Read Only */
typedef signed short const sc16;  /* Read Only */
typedef signed char  const sc8;   /* Read Only */

typedef volatile signed long  vs32;
typedef volatile signed short vs16;
typedef volatile signed char  vs8;

typedef volatile signed long  const vsc32;  /* Read Only */
typedef volatile signed short const vsc16;  /* Read Only */
typedef volatile signed char  const vsc8;       /* Read Only */

typedef unsigned long  u32;
typedef unsigned short u16;
typedef unsigned char  u8;

typedef unsigned long  const uc32;  /* Read Only */
typedef unsigned short const uc16;  /* Read Only */
typedef unsigned char  const uc8;       /* Read Only */

typedef volatile unsigned long  vu32;
typedef volatile unsigned short vu16;
typedef volatile unsigned char  vu8;

typedef volatile unsigned long  const vuc32;  /* Read Only */
typedef volatile unsigned short const vuc16;  /* Read Only */
typedef volatile unsigned char  const vuc8;   /* Read Only */

typedef enum
{
    RESET = 0,
    SET = !RESET
}FlagStatus, ITStatus;

typedef enum
{
    DISABLE = 0,
    ENABLE = !DISABLE
}FunctionalState;

typedef enum
{
    ERROR = 0,
    SUCCESS = !ERROR
}ErrorStatus;

typedef enum
{
    FALSE = 0,
    TRUE = !FALSE
}BoolType;

typedef enum
{
    UNLOCK = 0,
    LOCK = !UNLOCK
} LockState;

/* 晶振选择 */
typedef enum
{
    SCU_EXOSC_20MHz = 0x0 ,      //外部主晶振20M作为主时钟
    SCU_EXOSC_10MHz = 0x1 ,      //外部主晶振10M作为主时钟
}SCU_TYPE_EXOSC;

void SystemInit(SCU_TYPE_EXOSC exosc);


ErrorStatus IAP_ReadId( uint32_t * pId);
ErrorStatus IAP_WriteId( uint32_t Id);
ErrorStatus IAP_WriteUGAIN( uint32_t Id);
ErrorStatus IAP_ReadUGAIN( uint32_t *pU);
ErrorStatus IAP_WriteIGAIN( uint32_t Id);
ErrorStatus IAP_ReadIGAIN( uint32_t *pU);
ErrorStatus IAP_WritePAGAIN( uint32_t Id);
ErrorStatus IAP_ReadPAGAIN( uint32_t *pU);
ErrorStatus IAP_WriteAPHCAL( uint32_t Id);
ErrorStatus IAP_ReadAPHCAL( uint32_t *pU);
ErrorStatus IAP_WritePAOFF( uint32_t Id);
ErrorStatus IAP_ReadPAOFF( uint32_t *pU);
ErrorStatus IAP_WriteCHECKSUM( uint32_t Id);
ErrorStatus IAP_ReadCHECKSUM( uint32_t *pU);
ErrorStatus IAP_WriteEnergy(EP_Data_TypeDef *pEP);

#endif

/******************* (C) COPYRIGHT 2018 Eastsoft *****END OF FILE****/

