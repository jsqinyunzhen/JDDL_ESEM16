#ifndef __ESEM16_WDT_H
#define __ESEM16_WDT_H

/* Includes ------------------------------------------------------------------*/
#include "esem16.h"
#include "system_esem16.h"

#define WDOGCLK             32000

typedef enum
{
    WDT_CLK_PCLK    = 0,
    WDT_CLK_WDOGCLK = 1,
}WDT_CLK_TypeDef;

typedef struct
{
    WDT_CLK_TypeDef WDT_Clk;                //WDT时钟源
    FunctionalState WDT_REST;               //复位使能
    FunctionalState WDT_IE;                 //中断使能
    uint32_t        WDT_Tms;                //WDT定时时间,单位为ms
}WDT_InitTypeDef;

#define WDT_RegUnLock()         (WDT->LOCK.Word = 0x1ACCE551)
#define WDT_RegLock()           (WDT->LOCK.Word = 0x0)

#define WDT_Clear()             {WDT_RegUnLock();WDT->INTCLR.Word = 0;WDT_RegLock();}

#define WDT_Enable()            (WDT->CON.EN = 1)
#define WDT_Disable()           (WDT->CON.EN = 0)

#define WDT_IEEnable()          (WDT->CON.IE = 1)
#define WDT_IEDisable()         (WDT->CON.IE = 0)

#define WDT_RstEnable()         (WDT->CON.RSTEN = 1)
#define WDT_RstDisable()        (WDT->CON.RSTEN = 0)

#define WDT_TEST_EN_Enable()    (WDT->TSCON.TSTEN = 1)
#define WDT_TEST_EN_Disable()   (WDT->TSCON.TSTEN = 0)

#define WDT_TEST_IE_Enable()    (WDT->TSOP.TSTINT = 1)
#define WDT_TEST_IE_Disable()   (WDT->TSOP.TSTINT = 0)

#define WDT_TEST_RST_Enable()   (WDT->TSOP.TSTRES = 1)
#define WDT_TEST_RST_Disable()  (WDT->TSOP.TSTRES = 0)

void WDT_Init(WDT_InitTypeDef* WDT_InitStruct);
void WDT_SetReloadValue(uint32_t Reload);
uint32_t WDT_GetValue(void);
FlagStatus WDT_GetFlagStatus(void);

#endif

/******************* (C) COPYRIGHT 2018 Eastsoft *****END OF FILE****/

