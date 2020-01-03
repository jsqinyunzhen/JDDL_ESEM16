#include "esem16_scs.h"

/***************************************************************
  函数名：NVIC_Init
  描  述：NVIC初始化
  输入值：无
  输出值：无
  返回值：无
***************************************************************/
void NVIC_Init(NVIC_InitTypeDef* NVIC_InitStruct)
{
    uint32_t tmppriority = 0x00;

    if (NVIC_InitStruct->NVIC_IRQChannelCmd != DISABLE)
    {
        /* Compute the Corresponding IRQ Priority --------------------------------*/    
        tmppriority = NVIC->IP[NVIC_InitStruct->NVIC_IRQChannel >> 0x02];
        tmppriority &= (uint32_t)(~(((uint32_t)0xFF) << ((NVIC_InitStruct->NVIC_IRQChannel & 0x03) * 8)));
        tmppriority |= (uint32_t)((((uint32_t)NVIC_InitStruct->NVIC_IRQChannelPriority << 6) & 0xFF) << ((NVIC_InitStruct->NVIC_IRQChannel & 0x03) * 8));

        NVIC->IP[NVIC_InitStruct->NVIC_IRQChannel >> 0x02] = tmppriority;

        /* Enable the Selected IRQ Channels --------------------------------------*/
        NVIC->ISER[0] = (uint32_t)0x01 << (NVIC_InitStruct->NVIC_IRQChannel & (uint8_t)0x1F);
    }
    else
    {
        /* Disable the Selected IRQ Channels -------------------------------------*/
        NVIC->ICER[0] = (uint32_t)0x01 << (NVIC_InitStruct->NVIC_IRQChannel & (uint8_t)0x1F);
    }
}
/***************************************************************
  函数名：void NVIC_SystemLPConfig(NVIC_TYPE_LP LowPowerMode, FunctionalState NewState)
  描  述：NVIC LP选择
  输入值：NVIC_TYPE_LP LowPowerMode, FunctionalState NewState
  输出值：无
  返回值：无
***************************************************************/
void NVIC_SystemLPConfig(NVIC_TYPE_LP LowPowerMode, FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
      SCB->SCR |= LowPowerMode;
    }
    else
    {
      SCB->SCR &= (uint32_t)(~(uint32_t)LowPowerMode);
    }
}
/***************************************************************
  函数名：void SysTickCmd(FunctionalState NewState)
  描  述：系统时钟控制
  输入值：无
  输出值：无
  返回值：无
***************************************************************/
void SysTickCmd(FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
      SysTick->CTRL |= ((uint32_t)0x00000001);
    }
    else
    {
      SysTick->CTRL &= ~((uint32_t)0x00000001);
    }
}
/***************************************************************
  函数名：void SysTick_CLKSourceConfig(SysTick_CLKSource SysTick_CLKSource)
  描  述：系统时钟时钟选择
  输入值：
  输出值：无
  返回值：无
***************************************************************/
void SysTick_CLKSourceConfig(SYST_TYPE_CLKS SysTick_CLKSource)
{
    if (SysTick_CLKSource == SysTick_ClkS_Base)
    {
      SysTick->CTRL |= 0x00000004;
    }
    else
    {
      SysTick->CTRL &= 0xFFFFFFFB;
    }
}
/***************************************************************
  函数名：void SysTick_LoadValueConfig(uint32_t Value)
  描  述：设置系统时钟值
  输入值：无
  输出值：无
  返回值：无
***************************************************************/
void SysTick_LoadValueConfig(uint32_t Value)
{
    SysTick->LOAD = Value;
}
/***************************************************************
  函数名：uint32_t SysTick_GetValue(void)
  描  述：获取系统时钟值
  输入值：无
  输出值：无
  返回值：无
***************************************************************/
uint32_t SysTick_GetValue(void)
{
    return (SysTick->VAL);
}
/***************************************************************
  函数名：FlagStatus SysTick_GetCountFlag(void)
  描  述：获取系统时钟计数标志
  输入值：无
  输出值：无
  返回值：无
***************************************************************/
FlagStatus SysTick_GetCountFlag(void)
{
    FlagStatus bitstatus = RESET;

    /* Check the status of SysTick clock count flag */
    if((SysTick->CTRL & ((uint32_t)0x00010000)) != RESET)
    {
      bitstatus = SET;
    }
    else
    {
      bitstatus = RESET;
    }
    return bitstatus;
}
/***************************************************************
  函数名：SysTick_Init
  描  述：SysTick初始化
  输入值：无
  输出值：无
  返回值：无
***************************************************************/
void SysTick_Init(SYSTICK_InitStruType* SysT_InitStruct)
{
    uint32_t temp32 = 0;
    SysTick->LOAD = SysT_InitStruct->SysTick_Value;
    SysTick->VAL = (uint32_t)0;

    if (SysT_InitStruct->SysTick_ClkSource != SysTick_ClkS_Base)
        temp32 |= 0x00000004;
    else
        temp32 &= 0xFFFFFFFB;

    if (SysT_InitStruct->SysTick_ITEnable != DISABLE)
        temp32 |= 0x00000002;
    else
        temp32 &= 0xFFFFFFFD;

    SysTick->CTRL = temp32;
    return;
}
/******************* (C) COPYRIGHT 2018 Eastsoft *****END OF FILE****/

