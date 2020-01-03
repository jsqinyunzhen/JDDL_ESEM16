#ifndef __ESEM16_EM_H
#define __ESEM16_EM_H

/* Includes ------------------------------------------------------------------*/
#include "esem16.h"
#include "system_esem16.h"

typedef enum
{
    EM_PGA1_CLOSE = 0x00,
    EM_PGA1_X1    = 0x01,
    EM_PGA1_X2    = 0x02,
    EM_PGA1_X4    = 0x03,
    EM_PGA1_X8    = 0x04,
    EM_PGA1_X16   = 0x05,
    EM_PGA1_X24   = 0x06,
    EM_PGA1_X32   = 0x07,
}EM_TYPE_PGA1;

typedef enum
{
    EM_PGA2_CLOSE = 0x00,
    EM_PGA2_X1    = 0x01,
    EM_PGA2_X2    = 0x02,
    EM_PGA2_X4    = 0x03,
    EM_PGA2_X8    = 0x04,
}EM_TYPE_PGA2;

typedef enum
{
    EM_CHOP_EN  = 0x00,
    EM_CHOP_DIS = 0x01,
}EM_TYPE_CHOP;

typedef enum
{
    EM_ERCLR_Clr   = 0x01,      //��������
    EM_ERCLR_NoClr = 0x00,      //��������
}EM_TYPE_ERCLR;

typedef enum
{
    CF_SEL_DisOutput = 0x00,    //�����
    CF_SEL_OutputPos = 0x02,    //���������
    CF_SEL_OutputNeg = 0x03,    //���������
}EM_TYPE_CFSEL;

typedef enum
{
    CF_MOD_AbsEnergy = 0x00,    //�������ֵ��������
    CF_MOD_NorEnergy = 0x01,    //�����������������
}EM_TYPE_CFMOD;

typedef enum
{
    ZX_SEL_NoOutput  = 0x00,    //��ֹ����
    ZX_SEL_PosOutput = 0x01,    //�������
    ZX_SEL_NegOutput = 0x02,    //�������
    ZX_SEL_AllOutput = 0x03,    //ȫ����
}EM_TYPE_ZXSEL;

typedef enum
{
    EM_IT_CRC1 = 0x00000001,    //CRC1�ж�
    EM_IT_CRC2 = 0x00000002,    //CRC2�ж�
    EM_IT_EDCH = 0x00000004,    //��������ı��ж�
    EM_IT_NOLD = 0x00000008,    //����Ǳ���ı��ж�
    EM_IT_PERO = 0x00000010,    //���������Ĵ�������ж�
    EM_IT_NERO = 0x00000020,    //���������Ĵ�������ж�
    EM_IT_AERO = 0x00000040,    //����ֵ�����Ĵ�������ж�
    EM_IT_UZX  = 0x00000080,    //��ѹ�����ж�
    EM_IT_CF1  = 0x00000100,    //CF1�ж�
}EM_TYPE_IT;

typedef enum
{
    EM_STATA_CRC1S  = 0x00000001,   //CRC1У��״̬λ
    EM_STATA_CRC2S  = 0x00000002,   //CRC2У��״̬λ
    EM_STATA_PREV   = 0x00000004,   //��һ�μ������򸺱�־λ
    EM_STATE_NOLOAD = 0x00000008,   //����Ǳ����׼λ
    EM_STATE_ZXUS   = 0x00010000,   //��ѹ�źŸ���־λ
    EM_STATE_ZXIAS  = 0x00020000,   //�����źŸ���־λ
}EM_TYPE_STATE;

typedef struct
{
  EM_TYPE_PGA1 EM_PGA1_Config;                      //PGA1����ѡ��
  EM_TYPE_PGA2 EM_PGA2_Config;                      //PGA2����ѡ��
  FunctionalState EM_ADC1_Config;                   //ADC1ʹ��
  FunctionalState EM_ADC2_Config;                   //ADC2ʹ��
  FunctionalState EM_BGR_Config;                    //Bandgapʹ��
  EM_TYPE_CHOP EM_CHOP1_Config;                     //chop1ʱ��ʹ��
  EM_TYPE_CHOP EM_CHOP2_Config;                     //chop2ʱ��ʹ��
  FunctionalState EM_HPF_Config;                    //HPFʹ��.
  FunctionalState EM_EM_EN_Config;                  //EMʹ��
  FunctionalState EM_RMS_EN_Config;                 //RMSʹ��
  FunctionalState EM_CF_EN_Config;                  //CFʹ��
  FunctionalState EM_EA_EN_Config;                  //EAʹ��
  FunctionalState EM_APPF_EN_Config;                //APPFʹ��
  FunctionalState EM_ZX_EN_Config;                  //ZXʹ��
  FunctionalState EM_FP_EN_Config;                  //FPʹ��
  EM_TYPE_ERCLR EM_ERCLR_Config;                    //ERCLRģʽ
  FunctionalState EM_CRC1_EN_Config;                //CRC1ʹ��
  FunctionalState EM_CRC2_EN_Config;                //CRC2ʹ��
  EM_TYPE_CFSEL EM_CF1SEL_Config;                   //CF1ѡ��
  EM_TYPE_CFMOD EM_CF1MOD_Config;                   //CF1ģʽ
  EM_TYPE_ZXSEL EM_ZXSEL_Config;                    //ZXѡ��
  FunctionalState EM_POFF_MOD_Config;               //POFFģʽ
}EM_InitTypeDef;

typedef struct
{
  uint32_t EM_PFSET_Config;                         //PFSET
  uint16_t EM_PAGAIN_Config;                        //PAGAIN
  uint16_t EM_IAGAIN_Config;                        //IAGAIN
  uint16_t EM_UGAIN_Config;                         //UAGAIN
  uint8_t  EM_APHCAL_Config;                        //APHCAL
  uint16_t EM_PAOFF_Config;                         //PAOFF
  uint16_t EM_IAOFF_Config;                         //IAOFF
  uint16_t EM_UOFF_Config;                          //UOFF
  uint16_t EM_PSTART_Config;                        //PSTART
}EM_ParaTypeDef;

/* EMд�������� */
#define EM_RegUnLock()          (EM->PROT.Word = 0x78879669)
#define EM_RegLock()            (EM->PROT.Word = 0x00000000)

#define EM_Enable()             (EM->START.EM_EN = 1)   //EM����
#define EM_Disable()            (EM->START.EM_EN = 0)

#define EM_RMS_Enable()         (EM->START.RMS_EN = 1)  //��Чֵ����
#define EM_RMS_Disable()        (EM->START.RMS_EN = 0)

#define EM_CF_Enable()          (EM->START.CF_EN = 1)   //��������
#define EM_CF_Disable()         (EM->START.CF_EN = 0)

#define EM_ABS_Enable()         (EM->START.EA_EN = 1)   //����ֵ����
#define EM_ABS_Disable()        (EM->START.EA_EN = 0)

#define EM_APP_Enable()         (EM->START.APPF_EN = 1) //���ڹ��ʹ�����������
#define EM_APP_Disable()        (EM->START.APPF_EN = 0)

#define EM_ZX_Enable()          (EM->START.ZX_EN = 1)   //���㹦��
#define EM_ZX_Disable()         (EM->START.ZX_EN = 0)

#define EM_FP_Enable()          (EM->START.FP_EN = 1)   //��ǵ�ѹƵ�ʲ���
#define EM_FP_Disable()         (EM->START.FP_EN = 0)

#define EM_CRC1_Enable()        (EM->START.CRC1_EN = 1) //CRC1У��
#define EM_CRC1_Disable()       (EM->START.CRC1_EN = 0)

#define EM_CRC2_Enable()        (EM->START.CRC2_EN = 1) //CRC2У��
#define EM_CRC2_Disable()       (EM->START.CRC2_EN = 0)

#define EM_POFF_Enable()        (EM->START.POFF_MOD = 1)//����ʧ��ģʽ
#define EM_POFF_Disable()       (EM->START.POFF_MOD = 0)

void EM_Init(EM_InitTypeDef* EM_InitStruct);
void EM_ParaInit(EM_ParaTypeDef* EM_ParaStruct);
void EM_ErclrConfig(EM_TYPE_ERCLR EnRegClrMod);
void EM_CfSelConfig(EM_TYPE_CFSEL Cf_Sel);
void EM_CfModConfig(EM_TYPE_CFMOD Cf_Mod);
void EM_ZxSelConfig(EM_TYPE_ZXSEL ZX_Sel);
void EM_Set_PFSET(uint32_t Value);
void EM_Set_PAGAIN(uint16_t Value);
void EM_Set_IAGAIN(uint16_t Value);
void EM_Set_UGAIN(uint16_t Value);
void EM_Set_PAOFF(uint16_t Value);
void EM_Set_IAOFF(uint16_t Value);
void EM_Set_UOFF(uint16_t Value);
void EM_Set_PSTART(uint16_t Value);
void EM_Set_APHCAL(uint8_t Value);
void EM_Set_CRC1Reg(void);
void EM_Set_CRC2Reg(void);
void EM_Set_VREFCAL1(uint32_t Value);
void EM_Set_VREFCAL2(uint32_t Value);
uint32_t EM_Get_PE(void);
uint32_t EM_Get_NE(void);
uint32_t EM_Get_AE(void);
uint32_t EM_Get_IARMS(void);
uint32_t EM_Get_URMS(void);
int32_t EM_Get_PA(void);
uint16_t EM_Get_APHASE(void);
uint16_t EM_Get_FRQ(void);
uint32_t EM_Get_SA(void);
int16_t EM_Get_AFAC(void);
uint16_t EM_Get_PAGAIN(void);
uint16_t EM_Get_UGAIN(void);
uint16_t EM_Get_IAGAIN(void);
uint16_t EM_Get_PAOFF(void);
uint16_t EM_Get_IAOFF(void);
uint16_t EM_Get_UOFF(void);
uint8_t EM_Get_APHCAL(void);
uint32_t EM_Get_PFSET(void);
void EM_ITConfig(EM_TYPE_IT EM_IT, FunctionalState NewState);
ITStatus EM_GetFlagStatus(EM_TYPE_IT EM_IT);
void EM_ClearITPendingBit(EM_TYPE_IT EM_IT);
FlagStatus EM_GetEMStatus(EM_TYPE_STATE EM_STATE);

#endif

/******************* (C) COPYRIGHT 2018 Eastsoft *****END OF FILE****/

