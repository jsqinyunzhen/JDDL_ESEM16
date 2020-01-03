#include "includes.h"
/* 	端口			功能
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
*	函 数 名: WDT_Init
*	功能说明: em初始化
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
#if 0
void WDT_Init(void)
{
	WDT->LOCK.Word = 0x1ACCE551;		//关闭写保护
	WDT->CON.CLKS = 1;					//WDT时钟 32K
	WDT->CON.RSTEN = 1;					//复位使能
	WDT->CON.EN = 1;					//WDT模块使能
	WDT->LOAD.Word = 0x00000FF;			//初始值	
}
#endif
/*
*********************************************************************************************************
*	函 数 名: SCU_Init
*	功能说明: 时钟初始化
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
void SCU_Init(void)
{
	SCU->PROT.Word = 0x55AA6996;		//关闭写保护
	// 系统时钟初始化 //
	SCU->SCLKEN.Word = 0x0B;		
	// 外设时钟初始化 //
	SCU->PCLKEN.Word = 0x110197;		//bit20:EM时钟、bit16:UART0、bit8:T0 bit7:WDT bit2:IAP bit1:GPIO
}

*/

/*
*********************************************************************************************************
*	函 数 名: LED_Init
*	功能说明: LED初始化
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void LED_Init(void)
{
	GPIO->MOD11.Word = 0x40;		
	GPIO->DIR.DIR_11 = 0;				//输出端口
    GPIO->MOD4.Word = 0x40;		
	GPIO->DIR.DIR_4 = 0;				//输出端口
	LED2_Off();
    LED_Off();
}
/*
*********************************************************************************************************
*	函 数 名: KEY_Init
*	功能说明: KEY初始化
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void KEY_Init(void)
{
    GPIO->MOD10.Word = 0x04;
	GPIO->DIR.DIR_10 = 1;			//输入端口
}

void RELAY_Init(void)
{
	//GPIO->MOD2.Word = 0x04;
	//GPIO->DIR.DIR_2 = 0;			//输出端口
	//GPIO->MOD3.Word = 0x04;
	//GPIO->DIR.DIR_3 = 0;			//输出端口
	GPIO->MOD8.Word = 0x04;
	GPIO->DIR.DIR_8 = 0;			//输出端口
}

/*
********************************************************************************************************
*	函 数 名: iic
*	功能说明: iic 初始化
*	形    参：无
*	返 回 值: 无
********************************************************************************************************
*/
void IIC_Init(void)
{
	/* WP --> GPIO5 */
	GPIO->MOD5.Word = 0x40;		
	GPIO->DIR.DIR_5 = 0;			//输出端口		
	
	GPIO->DATA.DATA_5 = 1;			//WP = 1	
	/* SDA --> GPIO3*/
	//GPIO->MOD3.Word = 0x04;			
	//GPIO->DIR.DIR_3 = 0;			//输出端口
	/* SCK --> GPIO4 */
	//GPIO->MOD4.Word = 0x00;			
	//GPIO->DIR.DIR_4 = 0;			//输出端口
	
	GPIO->DATA.DATA_5 = 0;			//WP = 0	
}
/*
*********************************************************************************************************
*	函 数 名: Timer0_Init
*	功能说明: T0初始化,10ms定时器
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void Timer0_Init(void)
{
	T16N0->CON0.Word = 0x208; 		//MAT0
	T16N0->PREMAT.PREMAT = 0x03;	//4分频
	T16N0->MAT0.Word = 49999;		//100hz	
	NVIC_EnableIRQ(T16N0INT_IRQn); //IRQ使能
	T16N0->CON0.EN = 1;				//T16N0使能
	T16N0->INT.MAT0IE = 1;			//T16N0匹配0中断使能
}
/*
*********************************************************************************************************
*	函 数 名: Uart_Init
*	功能说明: uart初始化.UART0接收使能发送使能、波特率UART_BAUD（9600），1位停止位、8位数据位、
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void Uart_Init(void)
{
	uint32_t temp;

	GPIO->DIR.DIR_5 = 0;


	GPIO->MOD6.Word = 0x05;
	GPIO->DIR.DIR_6 = 1;			//输入端口
	GPIO->FLTEN.FLTEN_6 = 0;		//端口输入滤波禁止	

	GPIO->MOD7.Word = 0x01;
	GPIO->DIR.DIR_7 = 0;			//输出端口
	GPIO->FLTEN.FLTEN_7 = 0;		//端口输入滤波禁止

	temp = PCLK/(64*UART_BAUD) -1;	
	UART0->BRR.CLKS = 0;			//64分频
	UART0->BRR.BRR = temp;			//buad = pclk/((BRR+1)*64)   
	UART0->CON.Word = 0xA3;			//UART0接收使能发送使能、1位停止位、8位数据位、偶校验
	UART0->INT.RXIE = 1;			//接收中断使能
	UART0->INT.TXIE = 0;			//发送中断失能
	/* 4. USART1接收中断使能,配置NVIC,使能USART1 */ 
	NVIC_EnableIRQ(UART0TINT_IRQn); //IRQ使能
	NVIC_EnableIRQ(UART0RINT_IRQn); //IRQ使能	
}

/*
*********************************************************************************************************
*	函 数 名: EM_Init
*	功能说明: em初始化
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
#if 0
void EM_Init(void)
{
	SCU->PCLKEN.Word |= 1<<20;		//EM时钟使能
	EM->PROT.Word = 0x78879669;		//关闭计量配置保护
	//EM初始化	
/*	EM->AFEC.PGA1C = 0x05;			//PAG1 16倍增益
	EM->AFEC.PGA2C = 0x02;			//PAG2 2倍增益
	EM->AFEC.ADC1_EN = 1;			//ADC1 使能
	EM->AFEC.ADC2_EN = 1;			//ADC2 使能
	EM->AFEC.BGR_EN = 1;			//VREF 使能
	EM->AFEC.CHOP1_PD = 0;			//chop1 clk失能
	EM->AFEC.CHOP2_PD = 0;			//chop2 clk失能
	EM->AFEC.HPF_EN = 1;			//HPF 滤波器使能*/
	EM->AFEC.Word = 0x11345; 		//模拟前端控制寄存器

/*	EM->START.EM_EN = 1;			//计量使能
	EM->START.RMS_EN = 1;			//有效值测量 使能
	EM->START.CF_EN = 1;			//能量计量 使能
	EM->START.EA_EN = 1;			//绝对值计量 使能
	EM->START.APPF_EN = 1;			//视在功率测量 使能
	EM->START.ZX_EN = 1;			//过零 使能
	EM->START.FP_EN = 1;			//相角和电压频率 使能
	EM->START.ERCLR = 1;			//能量寄存器清零 使能
	EM->START.CRC1_EN = 0;			//CRC1校验失能
	EM->START.CRC2_EN = 0;			//CRC1校验失能
	EM->START.CF1SEL = 0x02;		//CF1正脉冲 平时为低 脉冲为上升沿
	EM->START.CF1MOD = 0;			//输出有功绝对值能量脉冲
	EM->START.ZXSEL = 0x01;			//正向过零信号
	EM->START.POFF_MOD = 0;			//功率失调模式 禁止 */
	EM->START.Word = 0x1200FF;		

	EM->PFSET.Word = 0x00010000;	//高频脉冲常数
	EM->PAGAIN.Word = 0;			//有功功率增益
	EM->IAGAIN.Word = 0;			//电流有效值增益
	EM->UGAIN.Word = 0;				//电压有效值增益
	EM->APHCAL.Word = 0;			//角差较正值
	EM->PAOFF.Word = 0;				//功率失调补偿
	EM->IAOFF.Word = 0;				//电流失调补偿
	EM->UOFF.Word = 0;				//电压失调补偿
	EM->PSTART.Word = 0;			//启动功率门限寄存器
	
	//GPIO->MOD10.Word = 0x01;
	//GPIO->DIR.DIR_10 = 0;			//输出端口
	//GPIO->FLTEN.FLTEN_6 = 0;		//端口输入滤波禁止	
}
#endif
/*
*********************************************************************************************************
*	函 数 名: GloableVar_Init
*	功能说明: 读EEPROM中校准参数，如果参数都为0xFF，则认为是芯片第一次上电，加载默认值到EEPROM和RAM中。
*	形    参：无
*	返 回 值: 无
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
		//EEPROM都为0xFF,第一次上电
		memcpy(g_EM_GainPara.U_Gain.B08, ADJ_DEFAULT, EE_PARAM_SUM);
		EEP_WriteStr(EE_ADJ_BASEADDR, (uint8_t *)ADJ_DEFAULT[0].B08 ,EE_PARAM_SUM*2);	
		EEP_WriteStr(EE_ADJ_BASEADDR+EE_BACKUPS_OFFSET, (uint8_t *)ADJ_DEFAULT[0].B08 ,EE_PARAM_SUM*2);	
		
		//电能数据写0
		g_EP_Data.energy.B32 = 0;
		g_EP_Data.pulse = 0;
		EEP_WriteStr(EE_DI_ADDR, (uint8_t *)g_EP_Data.energy.B08 ,sizeof(g_EP_Data));	
	}
	else
	{
		//不是第一次上电，读取EEPZROM中的电能数据
		EEP_ReadStr(EE_DI_ADDR, (uint8_t*)g_EP_Data.energy.B08 , sizeof(g_EP_Data));		
	}
#endif
}
#endif
/*
*********************************************************************************************************
*	函 数 名: MCU_Init
*	功能说明: mcu初始化
*	形    参：无
*	返 回 值: 无
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
	GPIO->DIR.DIR_2 = 0;			//输出端口

    GPIO_PINT_ClearIFPendingBit(GPIO_Pin_3,PINT_Trig_Rise);
}
void Init_User_WDT(void)
{
    WDT_InitTypeDef WDT_InitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;

#if 0
    void WDT_Init(void)
    {
        WDT->LOCK.Word = 0x1ACCE551;        //关闭写保护
        WDT->CON.CLKS = 1;                  //WDT时钟 32K
        WDT->CON.RSTEN = 1;                 //复位使能
        WDT->CON.EN = 1;                    //WDT模块使能
        WDT->LOAD.Word = 0x00000FF;         //初始值    
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
*	函 数 名: SYS_Init
*	功能说明: 系统参数初始化
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void SYS_Init(void)
{
	GloableVar_Init();	
    //g_u_gain
	EM_Config();
}
