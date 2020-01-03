#include "includes.h"

/* ȫ�ֱ��� */
volatile uint8_t  g_Tasks_Flag = 0;		//�����־
volatile uint16_t g_SysTick    = 0;		//ϵͳʱ��
uint32_t gId = 0;
B32_B16 gCurrentUsedID = {0};

/*
********************************************************************************************************
*	�� �� ��: main
*	����˵��: ϵͳ��ں���
*	��    �Σ���
*	�� �� ֵ: �������(���账��)
********************************************************************************************************
*/
void Relay_init(void) //��ʼ�����ã��̵�Ĭ�ϳ������߳���
{
#if RELAY_DEFUALT_STATUS
    RELAY_On();
#else
    RELAY_Off();
#endif
    if(RELAY_IsOn())
    {
        LED_On();
        LED2_Off();
    }
    else
    {
        LED_Off();
        LED2_On();
    }
}
int main(void)
{	
    DISABLE_INTERRUPT();
    MCU_Init();
    IAP_ReadId(&gId);
    ENABLE_INTERRUPT();
    
    Relay_init();

    while(1)
    {
        WDT_CLEAR();
        SysTick_Task();
        Key_Task();
        Uart_Task();
        Sec_Task() ;	
        //Minut_Task();
        Read_UIP();	
    }	
}
