#ifndef _MACRODEF_H
#define _MACRODEF_H

/*
*	ϵͳ�궨��
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
*	�û��궨��
*/
/****************************Cortex3****************************/
#define DISABLE_INTERRUPT()		__disable_irq()
#define ENABLE_INTERRUPT()		__enable_irq()

/****************************ʱ�� ****************************/
#define SYSCLK  20000000						//ϵͳʱ��,
#define PCLK	20000000						//оƬ�ڲ�����ģ��ʱ��

/****************************WDT****************************/
#define WDT_CLEAR()		((WDT->LOAD.Word = 0xffff))

/****************************KEY ****************************/
#define KEY0 	(GPIO->DATA.DATA_10)

#define Breaker_NeedSetId() (gId == 0xffffffff)
#define RELAY_IsOn() (GPIO->DATA.DATA_8)	
#define BREAKERFRAMELEN (15)
#define RELAY_DEFUALT_STATUS 1 //0����Ĭ�Ϲر� 1����Ĭ�ϴ�

/*
	�����˲�ʱ��100ms, ��λ10ms��
	ֻ��������⵽100ms״̬�������Ϊ��Ч����������Ͱ��������¼�	
*/
#define KEY_DOWN_PERIOD     10		//��λ10ms�� ����80ms����Ϊ��������
#define KEY_LONG_PERIOD     200		//��λ10ms�� ����2�룬��Ϊ�����¼�
#define KEY_REPEAT_PERIOD   5       //��λ10ms�� ������������Ϊ50ms
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
#define UART_BAUD	4800						//������
#define UART_TX_ENABLE		UART0->INT.TXIE = 1	//�����ж�ʹ��
#define UART_TX_DISABLE		UART0->INT.TXIE = 0	//�����жϽ�ֹ
#define UART_RX_ENABLE		UART0->INT.RXIE = 1	//�����ж�ʹ��
#define UART_RX_DISABLE		UART0->INT.RXIE = 0	//�����жϽ�ֹ
#define UART_BUF_LEN 40
/****************************485 ****************************/

#define RS485_Send_On()		(GPIO->DATABSR.DATABSR_5 = 1)
#define RS485_Send_Off()	(GPIO->DATABCR.DATABCR_5 = 1)
/****************************CMD ****************************/
#define SETALLID "SETALLID\r\n"

/**********************EEPROM ����**************************/
#define EE_ADJ_BASEADDR			0x00			//�������������ַ
#define EE_BACKUPS_OFFSET		0x20			//�����������ݵ�ַ
#define EE_DI_ADDR			    0x40			//�������ݱ����ַ

#define EMU_DATA_BASEADDR			(0x00008C00)			//�������������ַ
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

#define EMU_ID_BASEADDR			(0x00008800)			//ID�������ַ
#define EMU_ID_PA               (34)
#define ID_CA                   (0)
#define ID_ADDRESS              (0x00008800)

#define EMU_ENERGY_BASEADDR			(0x00008400)			//�����������ַ
#define EMU_ENERGY_PA               (33)
#endif

