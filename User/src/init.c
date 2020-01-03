#include "includes.h"
/* 	�˿�			����
	GPIO0			ISCK
	GPIO1			ISDA
	GPIO2			KEY0
	GPIO3			IIC_SDA
	GPIO4			IIC_SCL
	GPIO5			IIC_WP
	GPIO6			UART_RX
	GPIO7			UART_TX
	GPIO8			
	GPIO9			LED
	GPIO10			
	GPIO11			
*/

/*
*********************************************************************************************************
*	�� �� ��: WDT_Init
*	����˵��: em��ʼ��
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
#if 0
void WDT_Init(void)
{
	WDT->LOCK.Word = 0x1ACCE551;		//�ر�д����
	WDT->CON.CLKS = 1;					//WDTʱ�� 32K
	WDT->CON.RSTEN = 1;					//��λʹ��
	WDT->CON.EN = 1;					//WDTģ��ʹ��
	WDT->LOAD.Word = 0x00000FF;			//��ʼֵ	
}
#endif
/*
*********************************************************************************************************
*	�� �� ��: SCU_Init
*	����˵��: ʱ�ӳ�ʼ��
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
void SCU_Init(void)
{
	SCU->PROT.Word = 0x55AA6996;		//�ر�д����
	// ϵͳʱ�ӳ�ʼ�� //
	SCU->SCLKEN.Word = 0x0B;		
	// ����ʱ�ӳ�ʼ�� //
	SCU->PCLKEN.Word = 0x110197;		//bit20:EMʱ�ӡ�bit16:UART0��bit8:T0 bit7:WDT bit2:IAP bit1:GPIO
}

*/

/*
*********************************************************************************************************
*	�� �� ��: LED_Init
*	����˵��: LED��ʼ��
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void LED_Init(void)
{
	GPIO->MOD11.Word = 0x40;		
	GPIO->DIR.DIR_11 = 0;				//����˿�
    GPIO->MOD4.Word = 0x40;		
	GPIO->DIR.DIR_4 = 0;				//����˿�
	LED2_Off();
    LED_Off();
}
/*
*********************************************************************************************************
*	�� �� ��: KEY_Init
*	����˵��: KEY��ʼ��
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void KEY_Init(void)
{
    GPIO->MOD10.Word = 0x04;
	GPIO->DIR.DIR_10 = 1;			//����˿�
}

void RELAY_Init(void)
{
	//GPIO->MOD2.Word = 0x04;
	//GPIO->DIR.DIR_2 = 0;			//����˿�
	//GPIO->MOD3.Word = 0x04;
	//GPIO->DIR.DIR_3 = 0;			//����˿�
	GPIO->MOD8.Word = 0x04;
	GPIO->DIR.DIR_8 = 0;			//����˿�
}

/*
********************************************************************************************************
*	�� �� ��: iic
*	����˵��: iic ��ʼ��
*	��    �Σ���
*	�� �� ֵ: ��
********************************************************************************************************
*/
void IIC_Init(void)
{
	/* WP --> GPIO5 */
	GPIO->MOD5.Word = 0x40;		
	GPIO->DIR.DIR_5 = 0;			//����˿�		
	
	GPIO->DATA.DATA_5 = 1;			//WP = 1	
	/* SDA --> GPIO3*/
	//GPIO->MOD3.Word = 0x04;			
	//GPIO->DIR.DIR_3 = 0;			//����˿�
	/* SCK --> GPIO4 */
	//GPIO->MOD4.Word = 0x00;			
	//GPIO->DIR.DIR_4 = 0;			//����˿�
	
	GPIO->DATA.DATA_5 = 0;			//WP = 0	
}
/*
*********************************************************************************************************
*	�� �� ��: Timer0_Init
*	����˵��: T0��ʼ��,10ms��ʱ��
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Timer0_Init(void)
{
	T16N0->CON0.Word = 0x208; 		//MAT0
	T16N0->PREMAT.PREMAT = 0x03;	//4��Ƶ
	T16N0->MAT0.Word = 49999;		//100hz	
	NVIC_EnableIRQ(T16N0INT_IRQn); //IRQʹ��
	T16N0->CON0.EN = 1;				//T16N0ʹ��
	T16N0->INT.MAT0IE = 1;			//T16N0ƥ��0�ж�ʹ��
}
/*
*********************************************************************************************************
*	�� �� ��: Uart_Init
*	����˵��: uart��ʼ��.UART0����ʹ�ܷ���ʹ�ܡ�������UART_BAUD��9600����1λֹͣλ��8λ����λ��
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Uart_Init(void)
{
	uint32_t temp;

	GPIO->DIR.DIR_5 = 0;


	GPIO->MOD6.Word = 0x05;
	GPIO->DIR.DIR_6 = 1;			//����˿�
	GPIO->FLTEN.FLTEN_6 = 0;		//�˿������˲���ֹ	

	GPIO->MOD7.Word = 0x01;
	GPIO->DIR.DIR_7 = 0;			//����˿�
	GPIO->FLTEN.FLTEN_7 = 0;		//�˿������˲���ֹ

	temp = PCLK/(64*UART_BAUD) -1;	
	UART0->BRR.CLKS = 0;			//64��Ƶ
	UART0->BRR.BRR = temp;			//buad = pclk/((BRR+1)*64)   
	UART0->CON.Word = 0xA3;			//UART0����ʹ�ܷ���ʹ�ܡ�1λֹͣλ��8λ����λ��żУ��
	UART0->INT.RXIE = 1;			//�����ж�ʹ��
	UART0->INT.TXIE = 0;			//�����ж�ʧ��
	/* 4. USART1�����ж�ʹ��,����NVIC,ʹ��USART1 */ 
	NVIC_EnableIRQ(UART0TINT_IRQn); //IRQʹ��
	NVIC_EnableIRQ(UART0RINT_IRQn); //IRQʹ��	
}

/*
*********************************************************************************************************
*	�� �� ��: EM_Init
*	����˵��: em��ʼ��
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
#if 0
void EM_Init(void)
{
	SCU->PCLKEN.Word |= 1<<20;		//EMʱ��ʹ��
	EM->PROT.Word = 0x78879669;		//�رռ������ñ���
	//EM��ʼ��	
/*	EM->AFEC.PGA1C = 0x05;			//PAG1 16������
	EM->AFEC.PGA2C = 0x02;			//PAG2 2������
	EM->AFEC.ADC1_EN = 1;			//ADC1 ʹ��
	EM->AFEC.ADC2_EN = 1;			//ADC2 ʹ��
	EM->AFEC.BGR_EN = 1;			//VREF ʹ��
	EM->AFEC.CHOP1_PD = 0;			//chop1 clkʧ��
	EM->AFEC.CHOP2_PD = 0;			//chop2 clkʧ��
	EM->AFEC.HPF_EN = 1;			//HPF �˲���ʹ��*/
	EM->AFEC.Word = 0x11345; 		//ģ��ǰ�˿��ƼĴ���

/*	EM->START.EM_EN = 1;			//����ʹ��
	EM->START.RMS_EN = 1;			//��Чֵ���� ʹ��
	EM->START.CF_EN = 1;			//�������� ʹ��
	EM->START.EA_EN = 1;			//����ֵ���� ʹ��
	EM->START.APPF_EN = 1;			//���ڹ��ʲ��� ʹ��
	EM->START.ZX_EN = 1;			//���� ʹ��
	EM->START.FP_EN = 1;			//��Ǻ͵�ѹƵ�� ʹ��
	EM->START.ERCLR = 1;			//�����Ĵ������� ʹ��
	EM->START.CRC1_EN = 0;			//CRC1У��ʧ��
	EM->START.CRC2_EN = 0;			//CRC1У��ʧ��
	EM->START.CF1SEL = 0x02;		//CF1������ ƽʱΪ�� ����Ϊ������
	EM->START.CF1MOD = 0;			//����й�����ֵ��������
	EM->START.ZXSEL = 0x01;			//��������ź�
	EM->START.POFF_MOD = 0;			//����ʧ��ģʽ ��ֹ */
	EM->START.Word = 0x1200FF;		

	EM->PFSET.Word = 0x00010000;	//��Ƶ���峣��
	EM->PAGAIN.Word = 0;			//�й���������
	EM->IAGAIN.Word = 0;			//������Чֵ����
	EM->UGAIN.Word = 0;				//��ѹ��Чֵ����
	EM->APHCAL.Word = 0;			//�ǲ����ֵ
	EM->PAOFF.Word = 0;				//����ʧ������
	EM->IAOFF.Word = 0;				//����ʧ������
	EM->UOFF.Word = 0;				//��ѹʧ������
	EM->PSTART.Word = 0;			//�����������޼Ĵ���
	
	//GPIO->MOD10.Word = 0x01;
	//GPIO->DIR.DIR_10 = 0;			//����˿�
	//GPIO->FLTEN.FLTEN_6 = 0;		//�˿������˲���ֹ	
}
#endif
/*
*********************************************************************************************************
*	�� �� ��: GloableVar_Init
*	����˵��: ��EEPROM��У׼���������������Ϊ0xFF������Ϊ��оƬ��һ���ϵ磬����Ĭ��ֵ��EEPROM��RAM�С�
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
#if 0
void GloableVar_Init(void)
{
#ifdef EEP_SAVE_EP
	EM_GainPara_TypeDef *ptr;
	uint8_t adjust_first = 0;
	
	memset(ptr->U_Gain.B08, 0xFF, EE_PARAM_SUM*2);	
	EEP_ReadStr(EE_ADJ_BASEADDR, g_EM_GainPara.U_Gain.B08, EE_PARAM_SUM*2);
	adjust_first = memcmp(ptr->U_Gain.B08, g_EM_GainPara.U_Gain.B08,EE_PARAM_SUM*2);
	if (!adjust_first)	
	{
		//EEPROM��Ϊ0xFF,��һ���ϵ�
		memcpy(g_EM_GainPara.U_Gain.B08, ADJ_DEFAULT, EE_PARAM_SUM);
		EEP_WriteStr(EE_ADJ_BASEADDR, (uint8_t *)ADJ_DEFAULT[0].B08 ,EE_PARAM_SUM*2);	
		EEP_WriteStr(EE_ADJ_BASEADDR+EE_BACKUPS_OFFSET, (uint8_t *)ADJ_DEFAULT[0].B08 ,EE_PARAM_SUM*2);	
		
		//��������д0
		g_EP_Data.energy.B32 = 0;
		g_EP_Data.pulse = 0;
		EEP_WriteStr(EE_DI_ADDR, (uint8_t *)g_EP_Data.energy.B08 ,sizeof(g_EP_Data));	
	}
	else
	{
		//���ǵ�һ���ϵ磬��ȡEEPZROM�еĵ�������
		EEP_ReadStr(EE_DI_ADDR, (uint8_t*)g_EP_Data.energy.B08 , sizeof(g_EP_Data));		
	}
#endif
}
#endif
/*
*********************************************************************************************************
*	�� �� ��: MCU_Init
*	����˵��: mcu��ʼ��
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Init_CF1_GPIO(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;

    GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_3;
    GPIO_InitStruct.GPIO_Func = GPIO_Func_0;
    GPIO_InitStruct.GPIO_Dir  = GPIO_DIR_IN;
    GPIO_InitStruct.GPIO_Ine  = ENABLE;
    GPIO_InitStruct.GPIO_Ode  = DISABLE;
    GPIO_InitStruct.GPIO_Wpe  = DISABLE;
    GPIO_InitStruct.GPIO_Wps  = GPIO_WPS_UP;
    GPIO_InitStruct.GPIO_Ds   = DISABLE;
    GPIO_InitStruct.GPIO_Flt  = DISABLE;
    GPIO_Init(&GPIO_InitStruct);

    GOIO_PINT_Config(GPIO_Pin_3, PINT_Trig_Rise, ENABLE);

    NVIC_InitStruct.NVIC_IRQChannel = NVIC_IRQ3_GPIO3;
    NVIC_InitStruct.NVIC_IRQChannelPriority = NVIC_Priority_0;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);
       //NVIC_EnableIRQ(GPIO8INT_IRQn);

    GPIO->MOD2.Word = 0x03;
	GPIO->DIR.DIR_2 = 0;			//����˿�

    GPIO_PINT_ClearIFPendingBit(GPIO_Pin_3,PINT_Trig_Rise);
}
void Init_User_WDT(void)
{
    WDT_InitTypeDef WDT_InitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;

#if 0
    void WDT_Init(void)
    {
        WDT->LOCK.Word = 0x1ACCE551;        //�ر�д����
        WDT->CON.CLKS = 1;                  //WDTʱ�� 32K
        WDT->CON.RSTEN = 1;                 //��λʹ��
        WDT->CON.EN = 1;                    //WDTģ��ʹ��
        WDT->LOAD.Word = 0x00000FF;         //��ʼֵ    
    }
#endif

    WDT_RegUnLock();

    WDT_InitStruct.WDT_Clk = WDT_CLK_WDOGCLK;
    WDT_InitStruct.WDT_REST = ENABLE;
    WDT_InitStruct.WDT_IE = ENABLE;
    WDT_InitStruct.WDT_Tms = 2000;
    WDT_Init(&WDT_InitStruct);

    WDT_IEEnable();
    WDT_RstEnable();

    WDT_Enable();
    WDT_RegLock();

    NVIC_InitStruct.NVIC_IRQChannel = NVIC_IRQ20_WDT;
    NVIC_InitStruct.NVIC_IRQChannelPriority = NVIC_Priority_1;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);
}
void MCU_Init(void)
{
    SystemInit(SCU_EXOSC_20MHz);

	//SCU_Init();
	
    Init_User_WDT();

    RELAY_Init();
	LED_Init();


    KEY_Init();
	//IIC_Init();
	Timer0_Init();

	Uart_Init();
    Init_User_EMU();
    Init_CF1_GPIO();
}

/*
*********************************************************************************************************
*	�� �� ��: SYS_Init
*	����˵��: ϵͳ������ʼ��
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void SYS_Init(void)
{
	GloableVar_Init();	
    //g_u_gain
	EM_Config();
}
