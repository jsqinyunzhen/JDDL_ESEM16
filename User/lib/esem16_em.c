#include "esem16_em.h"

/***************************************************************
  ��������void EM_Init(EM_InitTypeDef* EM_InitStruct)
  ��  ����EM��ʼ��
  ����ֵ����
  ���ֵ����
  ����ֵ����
***************************************************************/
void EM_Init(EM_InitTypeDef* EM_InitStruct)
{
    EM_RegUnLock();

    EM->AFEC.Word  = (((uint32_t)EM_InitStruct->EM_PGA1_Config)<<0) |
                   (((uint32_t)EM_InitStruct->EM_PGA2_Config)<<4)   |
                   (((uint32_t)EM_InitStruct->EM_ADC1_Config)<<8)   |
                   (((uint32_t)EM_InitStruct->EM_ADC2_Config)<<9)   |
                   (((uint32_t)EM_InitStruct->EM_BGR_Config)<<12)   |
                   (((uint32_t)EM_InitStruct->EM_CHOP1_Config)<<13) |
                   (((uint32_t)EM_InitStruct->EM_CHOP2_Config)<<14) | 
                   (((uint32_t)EM_InitStruct->EM_HPF_Config)<<16);

    EM->START.Word = (((uint32_t)EM_InitStruct->EM_EM_EN_Config)<<0)  |
                   (((uint32_t)EM_InitStruct->EM_RMS_EN_Config)<<1)   |
                   (((uint32_t)EM_InitStruct->EM_CF_EN_Config)<<2)    |
                   (((uint32_t)EM_InitStruct->EM_EA_EN_Config)<<3)    |
                   (((uint32_t)EM_InitStruct->EM_APPF_EN_Config)<<4)  |
                   (((uint32_t)EM_InitStruct->EM_ZX_EN_Config)<<5)    |
                   (((uint32_t)EM_InitStruct->EM_FP_EN_Config)<<6)    |
                   (((uint32_t)EM_InitStruct->EM_ERCLR_Config)<<7)    |
                   (((uint32_t)EM_InitStruct->EM_CRC1_EN_Config)<<8)  |
                   (((uint32_t)EM_InitStruct->EM_CRC2_EN_Config)<<9)  |
                   (((uint32_t)EM_InitStruct->EM_CF1SEL_Config)<<16)  |
                   (((uint32_t)EM_InitStruct->EM_CF1MOD_Config)<<18)  |
                   (((uint32_t)EM_InitStruct->EM_ZXSEL_Config)<<20)   |
                   (((uint32_t)EM_InitStruct->EM_POFF_MOD_Config)<<22);
    //EM_RegLock();
}
/***************************************************************
  ��������void EM_ParaInit(EM_ParaTypeDef* EM_ParaStruct)
  ��  ����EM_Para��ʼ��
  ����ֵ����
  ���ֵ����
  ����ֵ����
***************************************************************/
void EM_ParaInit(EM_ParaTypeDef* EM_ParaStruct)
{
    EM_RegUnLock();
    EM->PFSET.PFSET = EM_ParaStruct->EM_PFSET_Config;
    EM->PAGAIN.PAGAIN = EM_ParaStruct->EM_PAGAIN_Config;
    EM->IAGAIN.IGAIN = EM_ParaStruct->EM_IAGAIN_Config;
    EM->UGAIN.UGAIN = EM_ParaStruct->EM_UGAIN_Config;
    EM->APHCAL.APHCAL = EM_ParaStruct->EM_APHCAL_Config;
    EM->PAOFF.PAOFF = EM_ParaStruct->EM_PAOFF_Config;
    EM->IAOFF.IAOFF = EM_ParaStruct->EM_IAOFF_Config;
    EM->UOFF.UOFF =  EM_ParaStruct->EM_UOFF_Config;
    EM->PSTART.PSTART = EM_ParaStruct->EM_PSTART_Config;
    //EM_RegLock();
}
/***************************************************************
  ��������void EM_ErclrConfig(EM_TYPE_ERCLR EnRegClrMod);
  ��  ����EM_ErclrConfig��ʼ��
  ����ֵ��  EM_ERCLR_Clr: ��������
            EM_ERCLR_NoClr: ��������
  ���ֵ����
  ����ֵ����
***************************************************************/
void EM_ErclrConfig(EM_TYPE_ERCLR EnRegClrMod)
{
    /* Write to EM ERCLR */
    EM->START.ERCLR = EnRegClrMod;
}
/***************************************************************
  ��������void EM_CfSelConfig(EM_TYPE_CFSEL Cf_Sel);
  ��  ����EM_CfSelConfig
  ����ֵ��CF_SEL_DisOutput: �����
  *       CF_SEL_OutputPos: ���������
  *       CF_SEL_OutputNeg: ���������
  ���ֵ����
  ����ֵ����
***************************************************************/
void EM_CfSelConfig(EM_TYPE_CFSEL Cf_Sel)
{
    /* Write to EM CFSEL */
    EM->START.CF1SEL = Cf_Sel;
}
/***************************************************************
  ��������void EM_CfModConfig(EM_TYPE_CFMOD Cf_Mod)
  ��  ����EM_CfModConfig
  ����ֵ��CF_MOD_AbsEnergy: �������ֵ��������
  *       CF_MOD_NorEnergy: �����������������
  ���ֵ����
  ����ֵ����
***************************************************************/
void EM_CfModConfig(EM_TYPE_CFMOD Cf_Mod)
{
    /* Write to EM CFSEL */
    EM->START.CF1MOD = Cf_Mod;
}
/***************************************************************
  ��������void EM_ZxSelConfig(EM_TYPE_ZXSEL ZX_Sel)
  ��  ����EM_ZxSelConfig
  ����ֵ��ZX_SEL_NoOutput:  ��ֹ����
  *       ZX_SEL_PosOutput: ������� 
  *       ZX_SEL_NegOutput: �������
  *       ZX_SEL_AllOutput: ȫ����
  ���ֵ����
  ����ֵ����
***************************************************************/
void EM_ZxSelConfig(EM_TYPE_ZXSEL ZX_Sel)
{
    /* Write to EM CFSEL */
    EM->START.ZXSEL = ZX_Sel;
}
/***************************************************************
  ��������void EM_Set_PFSET(uint32_t Value)
  ��  �������ø�Ƶ���峣���Ĵ���
  ����ֵ����
  ���ֵ����
  ����ֵ����
***************************************************************/
void EM_Set_PFSET(uint32_t Value)
{
    EM->PFSET.PFSET = Value;
}
/***************************************************************
  ��������void EM_Set_PAGAIN(uint16_t Value)
  ��  ������
  ����ֵ����
  ���ֵ����
  ����ֵ����
***************************************************************/
void EM_Set_PAGAIN(uint16_t Value)
{
    EM->PAGAIN.PAGAIN = (uint32_t)Value;
}
/***************************************************************
  ��������void EM_Set_IAGAIN(uint16_t Value)
  ��  ������
  ����ֵ����
  ���ֵ����
  ����ֵ����
***************************************************************/
void EM_Set_IAGAIN(uint16_t Value)
{
    EM->IAGAIN.IGAIN = (uint32_t)Value;
}
/***************************************************************
  ��������void EM_Set_UGAIN(uint16_t Value)
  ��  ������
  ����ֵ����
  ���ֵ����
  ����ֵ����
***************************************************************/
void EM_Set_UGAIN(uint16_t Value)
{
    EM->UGAIN.UGAIN = (uint32_t)Value;
}
/***************************************************************
  ��������void EM_Set_PAOFF(uint16_t Value)
  ��  ������
  ����ֵ����
  ���ֵ����
  ����ֵ����
***************************************************************/
void EM_Set_PAOFF(uint16_t Value)
{
    EM->PAOFF.PAOFF = (uint32_t)Value;
}
/***************************************************************
  ��������void EM_Set_IAOFF(uint16_t Value)
  ��  ������
  ����ֵ����
  ���ֵ����
  ����ֵ����
***************************************************************/
void EM_Set_IAOFF(uint16_t Value)
{
    EM->IAOFF.IAOFF = (uint32_t)Value;
}
/***************************************************************
  ��������void EM_Set_UOFF(uint16_t Value)
  ��  ������
  ����ֵ����
  ���ֵ����
  ����ֵ����
***************************************************************/
void EM_Set_UOFF(uint16_t Value)
{
    EM->UOFF.UOFF = (uint32_t)Value;
}
/***************************************************************
  ��������void EM_Set_PSTART(uint16_t Value)
  ��  ����������������
  ����ֵ����
  ���ֵ����
  ����ֵ����
***************************************************************/
void EM_Set_PSTART(uint16_t Value)
{
    EM->PSTART.PSTART = (uint32_t)Value;
}
/***************************************************************
  ��������void EM_Set_APHCAL(uint16_t Value)
  ��  ������
  ����ֵ����
  ���ֵ����
  ����ֵ����
***************************************************************/
void EM_Set_APHCAL(uint8_t Value)
{
    EM->APHCAL.APHCAL = (uint32_t)Value;
}
/***************************************************************
  ��������void EM_Set_CRC1Reg(void)
  ��  ������
  ����ֵ����
  ���ֵ����
  ����ֵ����
***************************************************************/
void EM_Set_CRC1Reg(void)
{
    EM->CRC1.CRC1 = EM->PFSET.PFSET     ^
                EM->PAGAIN.PAGAIN       ^
                EM->PSTART.PSTART       ^
                EM->APHCAL.APHCAL       ^
                EM->AFEC.Word;
}
/***************************************************************
  ��������void EM_Set_CRC2Reg(void)
  ��  ������
  ����ֵ����
  ���ֵ����
  ����ֵ����
***************************************************************/
void EM_Set_CRC2Reg(void)
{
    EM->CRC2.CRC2 = EM->UGAIN.UGAIN     ^
                EM->IAGAIN.IGAIN        ^
                EM->UOFF.UOFF           ^
                EM->IAOFF.IAOFF         ^
                EM->PAOFF.PAOFF;
}
/***************************************************************
  ��������void EM_Set_VREFCAL(uint32_t Value)
  ��  ������
  ����ֵ����
  ���ֵ����
  ����ֵ����
***************************************************************/
void EM_Set_VREFCAL(uint32_t Value)
{
    EM->VREFCAL.VREF_CAL1 = (uint32_t)Value;
}
/***************************************************************
  ��������void EM_Set_VREFCAL1(uint32_t Value)
  ��  ������
  ����ֵ����
  ���ֵ����
  ����ֵ����
***************************************************************/
void EM_Set_VREFCAL1(uint32_t Value)
{
    EM->VREFCAL.VREF_CAL1 = (uint32_t)Value;
}
/***************************************************************
  ��������void EM_Set_VREFCAL2(uint32_t Value)
  ��  ������
  ����ֵ����
  ���ֵ����
  ����ֵ����
***************************************************************/
void EM_Set_VREFCAL2(uint32_t Value)
{
    EM->VREFCAL.VREF_CAL2 = (uint32_t)Value;
}
/***************************************************************
  ��������uint32_t EM_Get_PE(void)
  ��  ������
  ����ֵ����
  ���ֵ�����������Ĵ���
  ����ֵ����
***************************************************************/
uint32_t EM_Get_PE(void)
{
    return EM->PE.Word;
}
/***************************************************************
  ��������uint32_t EM_Get_NE(void)
  ��  ������
  ����ֵ����
  ���ֵ�����������Ĵ���
  ����ֵ����
***************************************************************/
uint32_t EM_Get_NE(void)
{
    return EM->NE.Word;
}
/***************************************************************
  ��������uint32_t EM_Get_AE(void)
  ��  ������ȡ���ܼ������塣��ȡ��Ĵ����Զ����㣬�Ĵ�������Ϊ0.1���������塣
  ����ֵ����
  ���ֵ������ֵ�����Ĵ���
  ����ֵ����
***************************************************************/
uint32_t EM_Get_AE(void)
{
    return EM->AE.Word;
}
/***************************************************************
  ��������uint32_t EM_Get_IARMS(void)
  ��  ������
  ����ֵ����
  ���ֵ��������Чֵ
  ����ֵ����
***************************************************************/
uint32_t EM_Get_IARMS(void)
{
    return EM->IARMS.Word;
}
/***************************************************************
  ��������uint32_t EM_Get_URMS(void)
  ��  ������
  ����ֵ����
  ���ֵ����ѹ��Чֵ
  ����ֵ����
***************************************************************/
uint32_t EM_Get_URMS(void)
{
    return EM->URMS.Word;
}
/***************************************************************
  ��������uint32_t EM_Get_PA(void)
  ��  ������
  ����ֵ����
  ���ֵ���й�����
  ����ֵ����
***************************************************************/
int32_t EM_Get_PA(void)
{
    return EM->PA.Word;
}
/***************************************************************
  ��������uint32_t EM_Get_APHASE(void)
  ��  ������
  ����ֵ����
  ���ֵ�����
  ����ֵ����
***************************************************************/
uint16_t EM_Get_APHASE(void)
{
    return EM->APHASE.Word;
}
/***************************************************************
  ��������uint32_t EM_Get_FRQ(void)
  ��  ������
  ����ֵ����
  ���ֵ����ѹƵ��
  ����ֵ����
***************************************************************/
uint16_t EM_Get_FRQ(void)
{
    return EM->FRQ.Word;
}
/***************************************************************
  ��������uint32_t EM_Get_SA(void)
  ��  ������
  ����ֵ����
  ���ֵ�����ڹ���
  ����ֵ����
***************************************************************/
uint32_t EM_Get_SA(void)
{
    return EM->SA.Word;
}
/***************************************************************
  ��������uint32_t EM_Get_AFAC(void)
  ��  ������
  ����ֵ����
  ���ֵ����������
  ����ֵ����
***************************************************************/
int16_t EM_Get_AFAC(void)
{
    return EM->AFAC.Word;
}
/***************************************************************
  ��������uint32_t EM_Get_PAGAIN(void)
  ��  ������
  ����ֵ����
  ���ֵ���й���������ֵ
  ����ֵ����
***************************************************************/
uint16_t EM_Get_PAGAIN(void)
{
    return EM->PAGAIN.Word;
}
/***************************************************************
  ��������uint32_t EM_Get_UGAIN(void)
  ��  ������
  ����ֵ����
  ���ֵ����ѹ��Чֵ����ֵ
  ����ֵ����
***************************************************************/
uint16_t EM_Get_UGAIN(void)
{
    return EM->UGAIN.Word;
}
/***************************************************************
  ��������uint32_t EM_Get_IAGAIN(void)
  ��  ������
  ����ֵ����
  ���ֵ��������Чֵ����ֵ
  ����ֵ����
***************************************************************/
uint16_t EM_Get_IAGAIN(void)
{
    return EM->IAGAIN.Word;
}
/***************************************************************
  ��������uint32_t EM_Get_PAOFF(void)
  ��  ������
  ����ֵ����
  ���ֵ���й�����ʧ������ֵ
  ����ֵ����
***************************************************************/
uint16_t EM_Get_PAOFF(void)
{
    return EM->PAOFF.Word;
}
/***************************************************************
  ��������uint32_t EM_Get_IAOFF(void)
  ��  ������
  ����ֵ����
  ���ֵ��������Чֵʧ������ֵ
  ����ֵ����
***************************************************************/
uint16_t EM_Get_IAOFF(void)
{
    return EM->IAOFF.Word;
}
/***************************************************************
  ��������uint32_t EM_Get_UOFF(void)
  ��  ������
  ����ֵ����
  ���ֵ����ѹ��Чֵʧ������ֵ
  ����ֵ����
***************************************************************/
uint16_t EM_Get_UOFF(void)
{
    return EM->UOFF.Word;
}
/***************************************************************
  ��������uint32_t EM_Get_APHCAL(void)
  ��  ������
  ����ֵ����
  ���ֵ���ǲ�У��ֵ
  ����ֵ����
***************************************************************/
uint8_t EM_Get_APHCAL(void)
{
    return EM->APHCAL.Word;
}
/***************************************************************
  ��������uint32_t EM_Get_PFSET(void)
  ��  ������
  ����ֵ����
  ���ֵ����Ƶ���峣��ֵ
  ����ֵ����
***************************************************************/
uint32_t EM_Get_PFSET(void)
{
    return EM->PFSET.Word;
}
/***************************************************************
  ��������void EM_ITConfig(EM_TYPE_IT EM_IT, FunctionalState NewState)
  ��  ����EM_ITConfig
  ����ֵ��    EM_IT_CRC1 = 0x00000001,    //CRC1�ж�
    EM_IT_CRC2 = 0x00000002,    //CRC2�ж�
    EM_IT_EDCH = 0x00000004,    //��������ı��ж�
    EM_IT_NOLD = 0x00000008,    //����Ǳ���ı��ж�
    EM_IT_PERO = 0x00000010,    //���������Ĵ�������ж�
    EM_IT_NERO = 0x00000020,    //���������Ĵ�������ж�
    EM_IT_AERO = 0x00000040,    //����ֵ�����Ĵ�������ж�
    EM_IT_UZX  = 0x00000080,    //��ѹ�����ж�
    EM_IT_CF1  = 0x00000100,    //CF1�ж�
  ���ֵ����
  ����ֵ����
***************************************************************/
void EM_ITConfig(EM_TYPE_IT EM_IT, FunctionalState NewState)
{
    if (NewState != DISABLE)
    {
        /* Enable the Interrupt sources */
        EM->INT.Word |= ((uint32_t)EM_IT << 16);
    }
    else
    {
        /* Disable the Interrupt sources */
        EM->INT.Word &= ~((uint32_t)EM_IT << 16);
    }
}
/***************************************************************
  ��������void EM_GetFlagStatus(EM_TYPE_IT EM_IT, FunctionalState NewState)
  ��  ����EM_GetFlagStatus
  ����ֵ��    EM_IT_CRC1 = 0x00000001,    //CRC1�ж�
    EM_IT_CRC2 = 0x00000002,    //CRC2�ж�
    EM_IT_EDCH = 0x00000004,    //��������ı��ж�
    EM_IT_NOLD = 0x00000008,    //����Ǳ���ı��ж�
    EM_IT_PERO = 0x00000010,    //���������Ĵ�������ж�
    EM_IT_NERO = 0x00000020,    //���������Ĵ�������ж�
    EM_IT_AERO = 0x00000040,    //����ֵ�����Ĵ�������ж�
    EM_IT_UZX  = 0x00000080,    //��ѹ�����ж�
    EM_IT_CF1  = 0x00000100,    //CF1�ж�
  ���ֵ����
  ����ֵ����
***************************************************************/
FlagStatus EM_GetFlagStatus(EM_TYPE_IT EM_IT)
{  
    FlagStatus bitstatus = RESET;
    uint32_t itstatus = 0x0;

    itstatus = EM->INT.Word & (uint32_t)EM_IT;
    if (itstatus != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    return bitstatus;
}
/***************************************************************
  ��������void EM_ClearITPendingBit(EM_TYPE_IT EM_IT, FunctionalState NewState)
  ��  ����EM_ClearITPendingBit
  ����ֵ��    EM_IT_CRC1 = 0x00000001,    //CRC1�ж�
    EM_IT_CRC2 = 0x00000002,    //CRC2�ж�
    EM_IT_EDCH = 0x00000004,    //��������ı��ж�
    EM_IT_NOLD = 0x00000008,    //����Ǳ���ı��ж�
    EM_IT_PERO = 0x00000010,    //���������Ĵ�������ж�
    EM_IT_NERO = 0x00000020,    //���������Ĵ�������ж�
    EM_IT_AERO = 0x00000040,    //����ֵ�����Ĵ�������ж�
    EM_IT_UZX  = 0x00000080,    //��ѹ�����ж�
    EM_IT_CF1  = 0x00000100,    //CF1�ж�
  ���ֵ����
  ����ֵ����
***************************************************************/
void EM_ClearITPendingBit(EM_TYPE_IT EM_IT)
{
    EM->INT.Word &= ~((uint32_t)EM_IT);
}
/***************************************************************
  ��������
  ��  ����EM_GetEMStatus
  ����ֵ��EM_STATA_CRC1S: EM CRC1У��״̬λ
  *       EM_STATA_CRC2S: EM CRC2У��״̬λ
  *       EM_STATA_PREV:  EM ��һ�μ������򸺱�־λ  
  *       EM_STATE_NOLOAD: EM ����Ǳ����׼λ
  *       EM_STATE_ZXUS: EM ��ѹ�źŸ���־λ
  *       EM_STATE_ZXIAS: EM �����źŸ���־λ
  ���ֵ����
  ����ֵ����
***************************************************************/
FlagStatus EM_GetEMStatus(EM_TYPE_STATE EM_STATE)
{
    FlagStatus bitstatus = RESET;
    uint32_t status = 0x0;

    status = EM->ESR.Word & (uint32_t)EM_STATE;

    if (status != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    return bitstatus;
}

/******************* (C) COPYRIGHT 2018 Eastsoft *****END OF FILE****/

