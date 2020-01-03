#ifndef __ESEM16_SCS_H
#define __ESEM16_SCS_H

#include "esem16.h"
#include "system_esem16.h"

typedef enum
{
    NVIC_LP_SLEEPONEXIT = 0x02,         //从ISR中断处理程序返回到线程模式时，是否休眠
    NVIC_LP_SLEEPDEEP   = 0x04 ,        //深度睡眠
    NVIC_LP_SEVONPEND   = 0x10 ,        //中断挂起时是否作为唤醒的选择位
}NVIC_TYPE_LP;

/* 中断源选择*/
typedef enum
{
    NVIC_IRQ0_GPIO0          = 0x00,
    NVIC_IRQ1_GPIO1          = 0x01,
    NVIC_IRQ2_GPIO2          = 0x02,
    NVIC_IRQ3_GPIO3          = 0x03,
    NVIC_IRQ4_GPIO4          = 0x04,
    NVIC_IRQ5_GPIO5          = 0x05,
    NVIC_IRQ6_GPIO6          = 0x06,
    NVIC_IRQ7_GPIO7          = 0x07,
    NVIC_IRQ8_GPIO8          = 0x08,
    NVIC_IRQ9_GPIO9          = 0x09,
    NVIC_IRQ10_GPIO10        = 0x0A,
    NVIC_IRQ11_GPIO11        = 0x0B,
    NVIC_IRQ12_T16N0         = 0x0C,
    NVIC_IRQ13_T16N1         = 0x0D,
    NVIC_IRQ14               = 0x0E,
    NVIC_IRQ15               = 0x0F,
    NVIC_IRQ16_T32N0         = 0x10,
    NVIC_IRQ17               = 0x11,
    NVIC_IRQ18               = 0x12,
    NVIC_IRQ19               = 0x13,
    NVIC_IRQ20_WDT           = 0x14,
    NVIC_IRQ21               = 0x15,
    NVIC_IRQ22               = 0x16,
    NVIC_IRQ23_ADC           = 0x17,
    NVIC_IRQ24               = 0x18,
    NVIC_IRQ25               = 0x19,
    NVIC_IRQ26               = 0x1A,
    NVIC_IRQ27_UART0TX       = 0x1B,
    NVIC_IRQ28_UART0RX       = 0x1C,
    NVIC_IRQ29               = 0x1D,
    NVIC_IRQ30               = 0x1E,
    NVIC_IRQ31_EM            = 0x1F,
}NVIC_IRQChannel;

/* 中断优先级 */
typedef enum
{
    NVIC_Priority_0 = 0x0 ,
    NVIC_Priority_1 = 0x1 ,
    NVIC_Priority_2 = 0x2 ,
    NVIC_Priority_3 = 0x3 ,
}NVIC_IRQPriority;

/*NVIC初始化结构体定义*/
typedef struct
{
    NVIC_IRQChannel NVIC_IRQChannel;                //中断通道
    NVIC_IRQPriority NVIC_IRQChannelPriority;       //中断优先级 0 ~ 3
    FunctionalState NVIC_IRQChannelCmd;             //中断状态
}NVIC_InitTypeDef;

/*Systick时钟源选择*/
typedef enum
{
    SysTick_ClkS_Base = 0x0 ,       //基准时钟(Hclk/3)
    SysTick_ClkS_Cpu  = 0x1 ,       //处理器时钟(Hclk)
}SYST_TYPE_CLKS;

/*SysTick初始化结构体定义*/
typedef struct
{
    uint32_t            SysTick_Value;       //递减计数24位，右对齐
    SYST_TYPE_CLKS      SysTick_ClkSource;   //时钟源选择
    FunctionalState     SysTick_ITEnable;    //中断是否使能
}SYSTICK_InitStruType;

/*SysTick*/
#define SysTick_Enable()    (SysTick->CTRL |= 0x00000001)
#define SysTick_Disable()   (SysTick->CTRL &= 0xFFFFFFFE)

void NVIC_Init(NVIC_InitTypeDef* NVIC_InitStruct);
void NVIC_SystemLPConfig(uint8_t LowPowerMode, FunctionalState NewState);
void SysTickCmd(FunctionalState NewState);
void SysTick_CLKSourceConfig(SYST_TYPE_CLKS SysTick_CLKSource);
void SysTick_LoadValueConfig(uint32_t Value);
uint32_t SysTick_GetValue(void);
FlagStatus SysTick_GetCountFlag(void);
void SysTick_Init(SYSTICK_InitStruType* SysT_InitStruct);

#endif

/******************* (C) COPYRIGHT 2018 Eastsoft *****END OF FILE****/

