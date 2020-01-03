#include "esem16_scs.h"

/***************************************************************
  ��������NVIC_Init
  ��  ����NVIC��ʼ��
  ����ֵ����
  ���ֵ����
  ����ֵ����
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
  ��������void NVIC_SystemLPConfig(NVIC_TYPE_LP LowPowerMode, FunctionalState NewState)
  ��  ����NVIC LPѡ��
  ����ֵ��NVIC_TYPE_LP LowPowerMode, FunctionalState NewState
  ���ֵ����
  ����ֵ����
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
  ��������void SysTickCmd(FunctionalState NewState)
  ��  ����ϵͳʱ�ӿ���
  ����ֵ����
  ���ֵ����
  ����ֵ����
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
  ��������void SysTick_CLKSourceConfig(SysTick_CLKSource SysTick_CLKSource)
  ��  ����ϵͳʱ��ʱ��ѡ��
  ����ֵ��
  ���ֵ����
  ����ֵ����
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
  ��������void SysTick_LoadValueConfig(uint32_t Value)
  ��  ��������ϵͳʱ��ֵ
  ����ֵ����
  ���ֵ����
  ����ֵ����
***************************************************************/
void SysTick_LoadValueConfig(uint32_t Value)
{
    SysTick->LOAD = Value;
}
/***************************************************************
  ��������uint32_t SysTick_GetValue(void)
  ��  ������ȡϵͳʱ��ֵ
  ����ֵ����
  ���ֵ����
  ����ֵ����
***************************************************************/
uint32_t SysTick_GetValue(void)
{
    return (SysTick->VAL);
}
/***************************************************************
  ��������FlagStatus SysTick_GetCountFlag(void)
  ��  ������ȡϵͳʱ�Ӽ�����־
  ����ֵ����
  ���ֵ����
  ����ֵ����
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
  ��������SysTick_Init
  ��  ����SysTick��ʼ��
  ����ֵ����
  ���ֵ����
  ����ֵ����
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

