#include "includes.h"

/*
********************************************************************************************************
*	�� �� ��: KeyScan
*	����˵��: ɨ�����а���������������T0�ж������Եĵ���
*	��    ��:  ��
*	�� �� ֵ:  1���������� 0������δ����
********************************************************************************************************
*/
uint8_t KeyScan(void)
{
	if (KEY0 == 0)
		return 1;
	else
		return 0;
}

/*
*********************************************************************************************************
*	�� �� ��: BasicTimer
*	����˵��: ʱ�����ڶ�ʱ������
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Basic_Timer(void)
{	
	static uint32_t Key_Down_Count = 0;
	static uint32_t Key_Up_Count = 0xffffffff;
	
	g_SysTick ++;	
	
	/***********************�������**********************/
	if (FlagGet(g_Tasks_Flag, TASK_FLAG_KEYDOWN) == 0 && Key_Down_Count != 0xffffffff)    		//�����¼�����ʱ�������¼�����ֹ�ڰ�������ʱ�ٴ���Ӧ
	{
		if (KeyScan() == 1)
		{
			//if (Key_Down_Count < 3)        					//ֻ�ӵ�3
			Key_Down_Count++;
		}

		if (Key_Down_Count == 2)  //���̧��Ӷ�ΰ��²�����Ч
		{
			FlagSet(g_Tasks_Flag, TASK_FLAG_KEYDOWN);			//�����¼���־��������������
			Key_Up_Count = 0;
		}
        if (Key_Down_Count == 200)  //���̧��Ӷ�ΰ��²�����Ч
		{
			FlagSet(g_Tasks_Flag, TASK_FLAG_KEYDOWN2S);			//�����¼���־��������������
		}
        if (Key_Down_Count >= 500)  //���̧��Ӷ�ΰ��²�����Ч
		{
			FlagSet(g_Tasks_Flag, TASK_FLAG_KEYDOWN5S);			//�����¼���־��������������
			Key_Down_Count = 0xffffffff;
		}
	}
    
    if(FlagGet(g_Tasks_Flag, TASK_FLAG_KEYUP) == 0 && Key_Up_Count < 3)
    {
		if (KeyScan() == 0)
		{ 
			//if (Key_Up_Count < 3)         					//ֻ�ӵ�3
			Key_Up_Count++;
		}

		if (Key_Up_Count >= 2)  //���̧��Ӷ�ΰ��²�����Ч
		{
			FlagSet(g_Tasks_Flag, TASK_FLAG_KEYUP);			//�����¼���־��������������
			Key_Up_Count = 0xffffffff;
			Key_Down_Count = 0;
		}	
    }
    
    if (g_RxDelayTimer != 0)            //����ʱ��ʱ
    {
        g_RxDelayTimer--;
        if (g_RxDelayTimer == 0)
        {
			FlagSet(g_Tasks_Flag, TASK_FLAG_UART_RX);			//�����¼���־��������������
        }       
    }
	#ifdef xxxx
	/******** ���մ��� uart�ֽڼ����ʱ��MCU��ʱ���½������״̬ ********/
	if (g_dl645.Overtimr_Timer != 0)			//����ʱ��ʱ
	{
		g_dl645.Overtimr_Timer--;
		if (g_dl645.Overtimr_Timer == 0)
		{
			g_dl645.Step = ST_START;  			//��ʱ�����½���ȴ�����ǰ����
			UART_RX_ENABLE;						//�����ж�ʹ��
			UART_TX_DISABLE;					//�����жϽ�ֹ
		}		
	}
	/******** ���ʹ��� uart ������ʱʱ�䵽���͵�һ��ǰ���� **********/
	if (g_dl645.TxDelay_Timer != 0)				//����ʱ��ʱ
	{
		g_dl645.TxDelay_Timer--;
		if (g_dl645.TxDelay_Timer == 0)
		{			
			UART0->TXBUF0.TXBUF0 = 0xFE;
			UART_RX_DISABLE;					//�����жϽ�ֹ
			UART_TX_ENABLE;						//�����ж�ʹ��(����һ�������ж�)	
		}
	}	

    
    if (g_dl645.RxFinish_Timer != 0)			//����ʱ��ʱ
    {
        g_dl645.RxFinish_Timer--;
        if (g_dl645.RxFinish_Timer == 0)
        {
            RS485_Send_Data();
        }		
    }
#endif
}

void SysTick_Task(void)
{
	static uint8_t t_1s = 0;
	static uint8_t t_1min = 0;    

	if (g_SysTick < 100)		
		return;
	g_SysTick = 0;
	/**********************1s�¼�***********************/		
	FlagSet(g_Tasks_Flag, TASK_FLAG_SEC);			//�����¼���־��������������
	if (++t_1s < 60)
		return;
	t_1s = 0;
	/**********************1min�¼�***********************/				
	FlagSet(g_Tasks_Flag, TASK_FLAG_MINUTE);		//�����¼���־��������������
	if (++t_1min < 10)
		return;			
	t_1min = 0;	    
	/**********************10min�¼�**********************/		
	
}
/*
********************************************************************************************************
*	�� �� ��: KeyTask
*	����˵��: �����¼�
*	��    ��:  ��
*	�� �� ֵ:  ��
********************************************************************************************************
*/
void Key_Task(void)
{
	if (FlagGet(g_Tasks_Flag, TASK_FLAG_KEYDOWN))
	{
        if(Breaker_NeedSetId())
        {
            if(gCurrentUsedID.B16[0] == 0)
            {
                gCurrentUsedID.B16[0] = gCurrentUsedID.B16[1]+1;
            }
            Breaker_ReportId(gCurrentUsedID.B16[0]);
        }
		FlagClr(g_Tasks_Flag, TASK_FLAG_KEYDOWN);	//���־
	}
    
	if (FlagGet(g_Tasks_Flag, TASK_FLAG_KEYUP))
	{
		FlagClr(g_Tasks_Flag, TASK_FLAG_KEYUP);	//���־
	}
    
    if (FlagGet(g_Tasks_Flag, TASK_FLAG_KEYDOWN2S))
	{
		FlagClr(g_Tasks_Flag, TASK_FLAG_KEYDOWN2S);	//���־
	}
    
	if (FlagGet(g_Tasks_Flag, TASK_FLAG_KEYDOWN5S))
	{
        RS485_Send_DataToBuf(SETALLID,strlen(SETALLID));
        Breaker_InitDeviceID();
		FlagClr(g_Tasks_Flag, TASK_FLAG_KEYDOWN5S);	//���־
	}
}
void Led_Task(void)
{
    if(Breaker_NeedSetId())
    {
        if(LED_IsOff())
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
    else if(RELAY_IsOn())
    {
        LED_On();
        LED2_Off();
    }
    else
    {
        LED_Off();
        LED2_On();
    }
    //LED_Toggle();
    //LED_On();
}

/*
********************************************************************************************************
*	�� �� ��: SecTask
*	����˵��: ÿ�봦����¼���LED�Ʒ�ת����������ѹ����Ϣ��
*	��    ��:  ��
*	�� �� ֵ:  ��
********************************************************************************************************
*/
uint32_t gSecond = 0;
uint8_t poweron_report = 1;
void Sec_Task(void)	
{
	if (FlagGet(g_Tasks_Flag, TASK_FLAG_SEC))
	{
        Led_Task();
        /*if(poweron_report)
        {
            uint8_t Txbuf[15] = {0x5A,0x0F,0xA1,0,0,0,0, 0,0,0,0,0,0,0,0};
            poweron_report = 0;
            Txbuf[6] = gId;
            Txbuf[14] = Breaker_CRC8(Txbuf,Txbuf[1]-1);
            RS485_Send_DataToBuf(Txbuf,sizeof(Txbuf));
        }*/
        
        gSecond++;
        if((gSecond%4) == 0)
        {
            //RELAY_On();
            EMU_print();
            //GPIO->DATABCR.DATABCR_2 = 1;
            //GPIO->DATABSR.DATABSR_3 = 1;
            //DelayMs(55);
            //GPIO->DATABCR.DATABCR_3 = 1;
            //GPIO->DATABRR.DATABRR_10 = 1;
        }
        else if((gSecond%2) == 0)
        {
            //RELAY_Off();
            //GPIO->DATABCR.DATABCR_3 = 1;
            //GPIO->DATABSR.DATABSR_2 = 1;
            //DelayMs(55);
            //GPIO->DATABCR.DATABCR_2 = 1;
        }
		Energy_Add();
		FlagClr(g_Tasks_Flag, TASK_FLAG_SEC);	//���־
	}
}
/*
********************************************************************************************************
*	�� �� ��: MinutTask
*	����˵��: ÿ���Ӵ�����¼���������֤
*	��    ��:  ��
*	�� �� ֵ:  ��
********************************************************************************************************
*/
void Minut_Task(void)
{
	if (FlagGet(g_Tasks_Flag, TASK_FLAG_MINUTE))
	{
		Emu_Adjust_Check();    
		FlagClr(g_Tasks_Flag, TASK_FLAG_MINUTE);	//���־
	}
}

/*
********************************************************************************************************
*	�� �� ��: Uart_Task
*	����˵��: ��������
*	��    ��:  ��
*	�� �� ֵ:  ��
********************************************************************************************************
*/
void Uart_Task(void)
{
	if (FlagGet(g_Tasks_Flag, TASK_FLAG_UART_TX))
	{
		Uart_Tx();
		FlagClr(g_Tasks_Flag, TASK_FLAG_UART_TX);	//���־
	}
    if (FlagGet(g_Tasks_Flag, TASK_FLAG_UART_RX))
	{
		Uart_Proc();                    		//���ڴ������  
		FlagClr(g_Tasks_Flag, TASK_FLAG_UART_RX);	//���־
	}
    
}


