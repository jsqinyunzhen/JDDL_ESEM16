#include "includes.h"

/*
*********************************************************************************************************
*	�� �� ��: T16N0INT_IRQHandler
*	����˵��: UART�жϷ������
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void T16N0INT_IRQHandler(void)
{
	if (T16N0->INT.MAT0IF == 1)
	{
		T16N0->INT.MAT0IF = 0;		
		Basic_Timer();
	}
}
/*
*********************************************************************************************************
*	�� �� ��: UART0TINT_IRQHandler
*	����˵��: UART�����жϷ������
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void UART0TINT_IRQHandler(void)
{
	if (UART0->INT.TXIF)
	{
		UART0->INT.TXIF = 0;		
	
        Uart_Tx();
	
	}
}
/*
*********************************************************************************************************
*	�� �� ��: UART0TINT_IRQHandler
*	����˵��: UART�����жϷ������
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void UART0RINT_IRQHandler(void)
{
	if(UART0->INT.RXIF)   
	{
		UART0->INT.RXIF = 0;
		Uart_Rx(UART0->RXBUF0.RXBUF0);
	}
}
#if 0
void GPIO9INT_IRQHandler(void)
{
    if( GPIO_PINT_GetIFStatus(GPIO_Pin_9 ,PINT_Trig_Rise) != RESET)
    {
        g_EP_Data.pulse ++;
        GPIO_PINT_ClearIFPendingBit(GPIO_Pin_9,PINT_Trig_Rise);
    }
    if( GPIO_PINT_GetIFStatus(GPIO_Pin_9 ,PINT_Trig_Fall) != RESET)
    {
    //g_EP_Data.pulse ++;
    GPIO_PINT_ClearIFPendingBit(GPIO_Pin_9,PINT_Trig_Fall);
    }
        if( GPIO_PINT_GetIFStatus(GPIO_Pin_9 ,PINT_Trig_Change) != RESET)
    {
    //g_EP_Data.pulse ++;
    GPIO_PINT_ClearIFPendingBit(GPIO_Pin_9,PINT_Trig_Change);
    }
}


#else
void GPIO3INT_IRQHandler(void)
{
    if( GPIO_PINT_GetIFStatus(GPIO_Pin_3 ,PINT_Trig_Rise) != RESET)
    {
        g_EP_Data.pulse ++;
        GPIO_PINT_ClearIFPendingBit(GPIO_Pin_3,PINT_Trig_Rise);
    }
    
    if( GPIO_PINT_GetIFStatus(GPIO_Pin_3,PINT_Trig_Fall) != RESET)
    {
    //g_EP_Data.pulse ++;
    GPIO_PINT_ClearIFPendingBit(GPIO_Pin_3,PINT_Trig_Fall);
    }
    
    if( GPIO_PINT_GetIFStatus(GPIO_Pin_3,PINT_Trig_Change) != RESET)
    {
    //g_EP_Data.pulse ++;
    GPIO_PINT_ClearIFPendingBit(GPIO_Pin_3,PINT_Trig_Change);
    }
}

#endif
