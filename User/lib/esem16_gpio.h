#ifndef __ESEM16_GPIO_H
#define __ESEM16_GPIO_H

#include "esem16.h"
#include "system_esem16.h"

/* ���ŷ���ѡ�� */
typedef enum
{
    GPIO_DIR_OUT = 0,
    GPIO_DIR_IN  = 1,
}GPIO_TYPE_DIR;

/* ���Ź���ѡ�� */
typedef enum
{
    GPIO_Func_0 = 0x0,
    GPIO_Func_1 = 0x1,
    GPIO_Func_2 = 0x2,
    GPIO_Func_3 = 0x3,
}GPIO_TYPE_FUNC;

/*��������ѡ��*/
typedef enum
{
    GPIO_WPS_UP   = 0,
    GPIO_WPS_DOWN = 1,
}GPIO_TYPE_WPS;

typedef enum
{
    BIT_RESET = 0,
    BIT_SET   = 1,
}BitAction;

/*���Ŷ���*/
typedef enum
{
    GPIO_Pin_0 = 0x00,
    GPIO_Pin_1 = 0x01,
    GPIO_Pin_2 = 0x02,
    GPIO_Pin_3 = 0x03,
    GPIO_Pin_4 = 0x04,
    GPIO_Pin_5 = 0x05,
    GPIO_Pin_6 = 0x06,
    GPIO_Pin_7 = 0x07,
    GPIO_Pin_8 = 0x08,
    GPIO_Pin_9 = 0x09,
    GPIO_Pin_10 = 0x0A,
    GPIO_Pin_11 = 0x0B,
}GPIO_TYPE_PIN;

typedef struct
{
    GPIO_TYPE_PIN GPIO_Pin;             //ѡ��ܽ�
    GPIO_TYPE_FUNC GPIO_Func;           //���ù���
    GPIO_TYPE_DIR GPIO_Dir;             //�������
    FunctionalState GPIO_Ine;           //�ܽ����������Ƿ�ʹ��
    FunctionalState GPIO_Ode;           //��©ģʽʹ��
    FunctionalState GPIO_Wpe;           //���������Ƿ�ʹ��
    GPIO_TYPE_WPS GPIO_Wps;             //��������ѡ��
    FunctionalState GPIO_Ds;            //���ǿ���Ƿ�ʹ��
    FunctionalState GPIO_Flt;           //20ns�˲�ʹ��
}GPIO_InitTypeDef;

/* PINT Trigger */
typedef enum
{
    PINT_Trig_Rise   = 0x0 ,
    PINT_Trig_Fall   = 0x1 ,
    PINT_Trig_Change = 0x2 ,
}PINT_TYPE_TRIG;

void GPIO_Init(GPIO_InitTypeDef* GPIO_InitStruct);
uint32_t GPIO_DataRead(void);
void GPIO_DataWrite(uint32_t PortVal);
BitAction GPIO_BitRead(GPIO_TYPE_PIN PINx);
void GPIO_BitSet(GPIO_TYPE_PIN PINx);
void GPIO_BitClr(GPIO_TYPE_PIN PINx);
void GPIO_BitRev(GPIO_TYPE_PIN PINx);
void GPIO_BitInput(GPIO_TYPE_PIN PINx);
void GPIO_BitOutput(GPIO_TYPE_PIN PINx);
void GPIO_BitDirRev(GPIO_TYPE_PIN PINx);
void GPIO_PinFUNCConfig(GPIO_TYPE_PIN PINx, GPIO_TYPE_FUNC GPIO_FUNC);
void GOIO_PINT_Config(GPIO_TYPE_PIN PINx, PINT_TYPE_TRIG TRIGx, FunctionalState NewState);
ITStatus GPIO_PINT_GetITStatus(GPIO_TYPE_PIN PINx ,PINT_TYPE_TRIG TRIGx);
FlagStatus GPIO_PINT_GetIFStatus(GPIO_TYPE_PIN PINx ,PINT_TYPE_TRIG TRIGx);
void GPIO_PINT_ClearIFPendingBit(GPIO_TYPE_PIN PINx,PINT_TYPE_TRIG TRIGx);

#endif

/******************* (C) COPYRIGHT 2018 Eastsoft *****END OF FILE****/

