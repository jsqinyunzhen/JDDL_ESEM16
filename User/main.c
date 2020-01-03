#include "includes.h"

/* 全局变量 */
volatile uint8_t  g_Tasks_Flag = 0;		//任务标志
volatile uint16_t g_SysTick    = 0;		//系统时间
uint32_t gId = 0;
B32_B16 gCurrentUsedID = {0};

/*
********************************************************************************************************
*	函 数 名: main
*	功能说明: 系统入口函数
*	形    参：无
*	返 回 值: 错误代码(无需处理)
********************************************************************************************************
*/
void Relay_init(void) //初始化设置，继电默认常开或者常闭
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
