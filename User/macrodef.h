#ifndef _MACRODEF_H
#define _MACRODEF_H

/*
*	系统宏定义
*/
#ifndef TRUE
	#define TRUE	1
#endif
#ifndef FALSE
	#define FALSE	0
#endif
#ifndef FAILED
	#define FAILED	0
#endif
#ifndef SUCCEED
	#define SUCCEED 1
#endif

#define mMemBitSet(c,b)			(c) |= (0x01 << (b))
#define mMemBitClr(c,b)			(c) &= ~(0x01 << (b))
#define mMemBitGet(c,b)			((c & (0x01 << (b)))>0)
#define mMemBitInv(c,b)			((c) ^= (0x01 << (b)))
#define mMemWrite (c,a)			(c)	 = (a)
#define FlagSet(c,b)			mMemBitSet(c,b)
#define FlagClr(c,b)			mMemBitClr(c,b)
#define FlagInv(c,b)			mMemBitInv(c,b)
#define FlagGet(c,b)		    mMemBitGet(c,b)		


/*
*	用户宏定义
*/
/****************************Cortex3****************************/
#define DISABLE_INTERRUPT()		__disable_irq()
#define ENABLE_INTERRUPT()		__enable_irq()

/****************************时钟 ****************************/
#define SYSCLK  20000000						//系统时钟,
#define PCLK	20000000						//芯片内部外设模块时钟

/****************************WDT****************************/
#define WDT_CLEAR()		((WDT->LOAD.Word = 0xffff))

/****************************KEY ****************************/
#define KEY0 	(GPIO->DATA.DATA_10)

#define Breaker_NeedSetId() (gId == 0xffffffff)
#define RELAY_IsOn() (GPIO->DATA.DATA_8)	
#define BREAKERFRAMELEN (15)
#define RELAY_DEFUALT_STATUS 1 //0代表默认关闭 1代表默认打开

/*
	按键滤波时间100ms, 单位10ms。
	只有连续检测到100ms状态不变才认为有效，包括弹起和按下两种事件	
*/
#define KEY_DOWN_PERIOD     10		//单位10ms， 持续80ms，认为按键按下
#define KEY_LONG_PERIOD     200		//单位10ms， 持续2秒，认为长按事件
#define KEY_REPEAT_PERIOD   5       //单位10ms， 连续按键周期为50ms
/****************************LED ****************************/
#if 1
#define LED_On()		(GPIO->DATABCR.DATABCR_11 = 1) //blue
#define LED_Off()		(GPIO->DATABSR.DATABSR_11 = 1)
#define LED_Toggle()	(GPIO->DATABRR.DATABRR_11 = 1)
#define LED_IsOff()     (GPIO->DATA.DATA_11 == 1)

#define LED2_On()		(GPIO->DATABCR.DATABCR_4 = 1) //red
#define LED2_Off()		(GPIO->DATABSR.DATABSR_4 = 1)
#define LED2_Toggle()	(GPIO->DATABRR.DATABRR_4 = 1)
#else
#define LED_On()		(GPIO->DATABCR.DATABCR_4 = 1) //blue
#define LED_Off()		(GPIO->DATABSR.DATABSR_4 = 1)
#define LED_Toggle()	(GPIO->DATABRR.DATABRR_4 = 1)
#define LED_IsOff()     (GPIO->DATA.DATA_4 == 1)

#define LED2_On()		(GPIO->DATABCR.DATABCR_11 = 1) //red
#define LED2_Off()		(GPIO->DATABSR.DATABSR_11 = 1)
#define LED2_Toggle()	(GPIO->DATABRR.DATABRR_11 = 1)
#endif
/****************************UART****************************/
#define UART_BAUD	4800						//波特率
#define UART_TX_ENABLE		UART0->INT.TXIE = 1	//发送中断使能
#define UART_TX_DISABLE		UART0->INT.TXIE = 0	//发送中断禁止
#define UART_RX_ENABLE		UART0->INT.RXIE = 1	//接收中断使能
#define UART_RX_DISABLE		UART0->INT.RXIE = 0	//接收中断禁止
#define UART_BUF_LEN 40
/****************************485 ****************************/

#define RS485_Send_On()		(GPIO->DATABSR.DATABSR_5 = 1)
#define RS485_Send_Off()	(GPIO->DATABCR.DATABCR_5 = 1)
/****************************CMD ****************************/
#define SETALLID "SETALLID\r\n"

/**********************EEPROM 定义**************************/
#define EE_ADJ_BASEADDR			0x00			//计量参数保存地址
#define EE_BACKUPS_OFFSET		0x20			//计量参数备份地址
#define EE_DI_ADDR			    0x40			//电能数据保存地址

#define EMU_DATA_BASEADDR			(0x00008C00)			//计量参数保存地址
#define UGAIN_ADDRESS               (0x00008C04)
#define IGAIN_ADDRESS               (0x00008C08)
#define PAGAIN_ADDRESS              (0x00008C0C)
#define APHCAL_ADDRESS              (0x00008C10)
#define PAOFF_ADDRESS               (0x00008C14)
#define CHECKSUM_ADDRESS            (0x00008C18)

#define EMU_DATA_PA                 (35)
#define ID_CA                       (0)
#define UGAIN_CA                    (1)
#define IGAIN_CA                    (2)
#define PAGAIN_CA                   (3)
#define APHCAL_CA                   (4)
#define PAOFF_CA                    (5)
#define CHECKSUM_CA                 (6)

#define EMU_ID_BASEADDR			(0x00008800)			//ID数保存地址
#define EMU_ID_PA               (34)
#define ID_CA                   (0)
#define ID_ADDRESS              (0x00008800)

#define EMU_ENERGY_BASEADDR			(0x00008400)			//电量数保存地址
#define EMU_ENERGY_PA               (33)
#endif

