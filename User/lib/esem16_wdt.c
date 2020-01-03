#include "esem16_wdt.h"

extern uint32_t SystemCoreClock;          /*!< System Clock Frequency (Core Clock) */

/***************************************************************
  ��������void WDT_Init(WDT_InitTypeDef* WDT_InitStruct)
  ��  ����WDT��ʼ��
  ����ֵ����
  ���ֵ����
  ����ֵ����
***************************************************************/
void WDT_Init(WDT_InitTypeDef* WDT_InitStruct)
{
    uint32_t temp;

    WDT_RegUnLock();

    if(WDT_InitStruct->WDT_Clk == WDT_CLK_PCLK)
    {
        temp = (float)WDT_InitStruct->WDT_Tms / 1000 * SystemCoreClock;
    }
    else if(WDT_InitStruct->WDT_Clk == WDT_CLK_WDOGCLK)
    {
        temp = (float)WDT_InitStruct->WDT_Tms / 1000 * WDOGCLK;
    }

    WDT->CON.CLKS = WDT_InitStruct->WDT_Clk;
    WDT->LOAD.Word = temp;
    WDT->CON.RSTEN = WDT_InitStruct->WDT_REST;
    WDT->CON.IE = WDT_InitStruct->WDT_IE;
    WDT_RegLock();
}
/***************************************************************
  ��������void WDT_SetReloadValue(uint32_t Reload)
  ��  ����WDT��ʼֵ
  ����ֵ����
  ���ֵ����
  ����ֵ����
***************************************************************/
void WDT_SetReloadValue(uint32_t Reload)
{
    /* Write to WDT LOAD */
    WDT->LOAD.Word = Reload;
}
/***************************************************************
  ��������WDT_GetValue
  ��  ������ȡWDT��ǰֵ
  ����ֵ����
  ����ֵ����ǰֵ
***************************************************************/
uint32_t WDT_GetValue(void)
{
	return (uint32_t)WDT->VALUE.Word;
}
/***************************************************************
  ��������WDT_GetFlagStatus
  ��  ������ȡWDT�ж�״̬
  ����ֵ����
  ����ֵ��SET/RESET
***************************************************************/
FlagStatus WDT_GetFlagStatus(void)
{
    FlagStatus bitstatus = RESET;
    uint32_t flagstatus = 0x0;

    /* Check the status of the WDT Flag */
    flagstatus = WDT->RIS.IF;
    
    if (flagstatus != (uint32_t)RESET)
    {
      /* WDT_Flag is set */
      bitstatus = SET;
    }
    else
    {
      /* WDT_Flag is reset */
      bitstatus = RESET;
    }
    /* Return the WDT_Flag status */
    return  bitstatus;
}

/******************* (C) COPYRIGHT 2018 Eastsoft *****END OF FILE****/

