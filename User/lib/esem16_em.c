#include "esem16_em.h"

/***************************************************************
  函数名：void EM_Init(EM_InitTypeDef* EM_InitStruct)
  描  述：EM初始化
  输入值：无
  输出值：无
  返回值：无
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
  函数名：void EM_ParaInit(EM_ParaTypeDef* EM_ParaStruct)
  描  述：EM_Para初始化
  输入值：无
  输出值：无
  返回值：无
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
  函数名：void EM_ErclrConfig(EM_TYPE_ERCLR EnRegClrMod);
  描  述：EM_ErclrConfig初始化
  输入值：  EM_ERCLR_Clr: 读后清零
            EM_ERCLR_NoClr: 读后不清零
  输出值：无
  返回值：无
***************************************************************/
void EM_ErclrConfig(EM_TYPE_ERCLR EnRegClrMod)
{
    /* Write to EM ERCLR */
    EM->START.ERCLR = EnRegClrMod;
}
/***************************************************************
  函数名：void EM_CfSelConfig(EM_TYPE_CFSEL Cf_Sel);
  描  述：EM_CfSelConfig
  输入值：CF_SEL_DisOutput: 不输出
  *       CF_SEL_OutputPos: 输出正脉冲
  *       CF_SEL_OutputNeg: 输出负脉冲
  输出值：无
  返回值：无
***************************************************************/
void EM_CfSelConfig(EM_TYPE_CFSEL Cf_Sel)
{
    /* Write to EM CFSEL */
    EM->START.CF1SEL = Cf_Sel;
}
/***************************************************************
  函数名：void EM_CfModConfig(EM_TYPE_CFMOD Cf_Mod)
  描  述：EM_CfModConfig
  输入值：CF_MOD_AbsEnergy: 输出绝对值能量脉冲
  *       CF_MOD_NorEnergy: 输出正负向能量脉冲
  输出值：无
  返回值：无
***************************************************************/
void EM_CfModConfig(EM_TYPE_CFMOD Cf_Mod)
{
    /* Write to EM CFSEL */
    EM->START.CF1MOD = Cf_Mod;
}
/***************************************************************
  函数名：void EM_ZxSelConfig(EM_TYPE_ZXSEL ZX_Sel)
  描  述：EM_ZxSelConfig
  输入值：ZX_SEL_NoOutput:  禁止过零
  *       ZX_SEL_PosOutput: 正向过零 
  *       ZX_SEL_NegOutput: 负向过零
  *       ZX_SEL_AllOutput: 全过零
  输出值：无
  返回值：无
***************************************************************/
void EM_ZxSelConfig(EM_TYPE_ZXSEL ZX_Sel)
{
    /* Write to EM CFSEL */
    EM->START.ZXSEL = ZX_Sel;
}
/***************************************************************
  函数名：void EM_Set_PFSET(uint32_t Value)
  描  述：设置高频脉冲常数寄存器
  输入值：无
  输出值：无
  返回值：无
***************************************************************/
void EM_Set_PFSET(uint32_t Value)
{
    EM->PFSET.PFSET = Value;
}
/***************************************************************
  函数名：void EM_Set_PAGAIN(uint16_t Value)
  描  述：无
  输入值：无
  输出值：无
  返回值：无
***************************************************************/
void EM_Set_PAGAIN(uint16_t Value)
{
    EM->PAGAIN.PAGAIN = (uint32_t)Value;
}
/***************************************************************
  函数名：void EM_Set_IAGAIN(uint16_t Value)
  描  述：无
  输入值：无
  输出值：无
  返回值：无
***************************************************************/
void EM_Set_IAGAIN(uint16_t Value)
{
    EM->IAGAIN.IGAIN = (uint32_t)Value;
}
/***************************************************************
  函数名：void EM_Set_UGAIN(uint16_t Value)
  描  述：无
  输入值：无
  输出值：无
  返回值：无
***************************************************************/
void EM_Set_UGAIN(uint16_t Value)
{
    EM->UGAIN.UGAIN = (uint32_t)Value;
}
/***************************************************************
  函数名：void EM_Set_PAOFF(uint16_t Value)
  描  述：无
  输入值：无
  输出值：无
  返回值：无
***************************************************************/
void EM_Set_PAOFF(uint16_t Value)
{
    EM->PAOFF.PAOFF = (uint32_t)Value;
}
/***************************************************************
  函数名：void EM_Set_IAOFF(uint16_t Value)
  描  述：无
  输入值：无
  输出值：无
  返回值：无
***************************************************************/
void EM_Set_IAOFF(uint16_t Value)
{
    EM->IAOFF.IAOFF = (uint32_t)Value;
}
/***************************************************************
  函数名：void EM_Set_UOFF(uint16_t Value)
  描  述：无
  输入值：无
  输出值：无
  返回值：无
***************************************************************/
void EM_Set_UOFF(uint16_t Value)
{
    EM->UOFF.UOFF = (uint32_t)Value;
}
/***************************************************************
  函数名：void EM_Set_PSTART(uint16_t Value)
  描  述：启动功率门限
  输入值：无
  输出值：无
  返回值：无
***************************************************************/
void EM_Set_PSTART(uint16_t Value)
{
    EM->PSTART.PSTART = (uint32_t)Value;
}
/***************************************************************
  函数名：void EM_Set_APHCAL(uint16_t Value)
  描  述：无
  输入值：无
  输出值：无
  返回值：无
***************************************************************/
void EM_Set_APHCAL(uint8_t Value)
{
    EM->APHCAL.APHCAL = (uint32_t)Value;
}
/***************************************************************
  函数名：void EM_Set_CRC1Reg(void)
  描  述：无
  输入值：无
  输出值：无
  返回值：无
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
  函数名：void EM_Set_CRC2Reg(void)
  描  述：无
  输入值：无
  输出值：无
  返回值：无
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
  函数名：void EM_Set_VREFCAL(uint32_t Value)
  描  述：无
  输入值：无
  输出值：无
  返回值：无
***************************************************************/
void EM_Set_VREFCAL(uint32_t Value)
{
    EM->VREFCAL.VREF_CAL1 = (uint32_t)Value;
}
/***************************************************************
  函数名：void EM_Set_VREFCAL1(uint32_t Value)
  描  述：无
  输入值：无
  输出值：无
  返回值：无
***************************************************************/
void EM_Set_VREFCAL1(uint32_t Value)
{
    EM->VREFCAL.VREF_CAL1 = (uint32_t)Value;
}
/***************************************************************
  函数名：void EM_Set_VREFCAL2(uint32_t Value)
  描  述：无
  输入值：无
  输出值：无
  返回值：无
***************************************************************/
void EM_Set_VREFCAL2(uint32_t Value)
{
    EM->VREFCAL.VREF_CAL2 = (uint32_t)Value;
}
/***************************************************************
  函数名：uint32_t EM_Get_PE(void)
  描  述：无
  输入值：无
  输出值：正向能量寄存器
  返回值：无
***************************************************************/
uint32_t EM_Get_PE(void)
{
    return EM->PE.Word;
}
/***************************************************************
  函数名：uint32_t EM_Get_NE(void)
  描  述：无
  输入值：无
  输出值：负向能量寄存器
  返回值：无
***************************************************************/
uint32_t EM_Get_NE(void)
{
    return EM->NE.Word;
}
/***************************************************************
  函数名：uint32_t EM_Get_AE(void)
  描  述：获取电能计量脉冲。读取后寄存器自动清零，寄存器精度为0.1个电能脉冲。
  输入值：无
  输出值：绝对值能量寄存器
  返回值：无
***************************************************************/
uint32_t EM_Get_AE(void)
{
    return EM->AE.Word;
}
/***************************************************************
  函数名：uint32_t EM_Get_IARMS(void)
  描  述：无
  输入值：无
  输出值：电流有效值
  返回值：无
***************************************************************/
uint32_t EM_Get_IARMS(void)
{
    return EM->IARMS.Word;
}
/***************************************************************
  函数名：uint32_t EM_Get_URMS(void)
  描  述：无
  输入值：无
  输出值：电压有效值
  返回值：无
***************************************************************/
uint32_t EM_Get_URMS(void)
{
    return EM->URMS.Word;
}
/***************************************************************
  函数名：uint32_t EM_Get_PA(void)
  描  述：无
  输入值：无
  输出值：有功功率
  返回值：无
***************************************************************/
int32_t EM_Get_PA(void)
{
    return EM->PA.Word;
}
/***************************************************************
  函数名：uint32_t EM_Get_APHASE(void)
  描  述：无
  输入值：无
  输出值：相角
  返回值：无
***************************************************************/
uint16_t EM_Get_APHASE(void)
{
    return EM->APHASE.Word;
}
/***************************************************************
  函数名：uint32_t EM_Get_FRQ(void)
  描  述：无
  输入值：无
  输出值：电压频率
  返回值：无
***************************************************************/
uint16_t EM_Get_FRQ(void)
{
    return EM->FRQ.Word;
}
/***************************************************************
  函数名：uint32_t EM_Get_SA(void)
  描  述：无
  输入值：无
  输出值：视在功率
  返回值：无
***************************************************************/
uint32_t EM_Get_SA(void)
{
    return EM->SA.Word;
}
/***************************************************************
  函数名：uint32_t EM_Get_AFAC(void)
  描  述：无
  输入值：无
  输出值：功率因数
  返回值：无
***************************************************************/
int16_t EM_Get_AFAC(void)
{
    return EM->AFAC.Word;
}
/***************************************************************
  函数名：uint32_t EM_Get_PAGAIN(void)
  描  述：无
  输入值：无
  输出值：有功功率增益值
  返回值：无
***************************************************************/
uint16_t EM_Get_PAGAIN(void)
{
    return EM->PAGAIN.Word;
}
/***************************************************************
  函数名：uint32_t EM_Get_UGAIN(void)
  描  述：无
  输入值：无
  输出值：电压有效值增益值
  返回值：无
***************************************************************/
uint16_t EM_Get_UGAIN(void)
{
    return EM->UGAIN.Word;
}
/***************************************************************
  函数名：uint32_t EM_Get_IAGAIN(void)
  描  述：无
  输入值：无
  输出值：电流有效值增益值
  返回值：无
***************************************************************/
uint16_t EM_Get_IAGAIN(void)
{
    return EM->IAGAIN.Word;
}
/***************************************************************
  函数名：uint32_t EM_Get_PAOFF(void)
  描  述：无
  输入值：无
  输出值：有功功率失调补偿值
  返回值：无
***************************************************************/
uint16_t EM_Get_PAOFF(void)
{
    return EM->PAOFF.Word;
}
/***************************************************************
  函数名：uint32_t EM_Get_IAOFF(void)
  描  述：无
  输入值：无
  输出值：电流有效值失调补偿值
  返回值：无
***************************************************************/
uint16_t EM_Get_IAOFF(void)
{
    return EM->IAOFF.Word;
}
/***************************************************************
  函数名：uint32_t EM_Get_UOFF(void)
  描  述：无
  输入值：无
  输出值：电压有效值失调补偿值
  返回值：无
***************************************************************/
uint16_t EM_Get_UOFF(void)
{
    return EM->UOFF.Word;
}
/***************************************************************
  函数名：uint32_t EM_Get_APHCAL(void)
  描  述：无
  输入值：无
  输出值：角差校正值
  返回值：无
***************************************************************/
uint8_t EM_Get_APHCAL(void)
{
    return EM->APHCAL.Word;
}
/***************************************************************
  函数名：uint32_t EM_Get_PFSET(void)
  描  述：无
  输入值：无
  输出值：高频脉冲常数值
  返回值：无
***************************************************************/
uint32_t EM_Get_PFSET(void)
{
    return EM->PFSET.Word;
}
/***************************************************************
  函数名：void EM_ITConfig(EM_TYPE_IT EM_IT, FunctionalState NewState)
  描  述：EM_ITConfig
  输入值：    EM_IT_CRC1 = 0x00000001,    //CRC1中断
    EM_IT_CRC2 = 0x00000002,    //CRC2中断
    EM_IT_EDCH = 0x00000004,    //计量方向改变中断
    EM_IT_NOLD = 0x00000008,    //启动潜动改变中断
    EM_IT_PERO = 0x00000010,    //正向能量寄存器溢出中断
    EM_IT_NERO = 0x00000020,    //负向能量寄存器溢出中断
    EM_IT_AERO = 0x00000040,    //绝度值能量寄存器溢出中断
    EM_IT_UZX  = 0x00000080,    //电压过零中断
    EM_IT_CF1  = 0x00000100,    //CF1中断
  输出值：无
  返回值：无
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
  函数名：void EM_GetFlagStatus(EM_TYPE_IT EM_IT, FunctionalState NewState)
  描  述：EM_GetFlagStatus
  输入值：    EM_IT_CRC1 = 0x00000001,    //CRC1中断
    EM_IT_CRC2 = 0x00000002,    //CRC2中断
    EM_IT_EDCH = 0x00000004,    //计量方向改变中断
    EM_IT_NOLD = 0x00000008,    //启动潜动改变中断
    EM_IT_PERO = 0x00000010,    //正向能量寄存器溢出中断
    EM_IT_NERO = 0x00000020,    //负向能量寄存器溢出中断
    EM_IT_AERO = 0x00000040,    //绝度值能量寄存器溢出中断
    EM_IT_UZX  = 0x00000080,    //电压过零中断
    EM_IT_CF1  = 0x00000100,    //CF1中断
  输出值：无
  返回值：无
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
  函数名：void EM_ClearITPendingBit(EM_TYPE_IT EM_IT, FunctionalState NewState)
  描  述：EM_ClearITPendingBit
  输入值：    EM_IT_CRC1 = 0x00000001,    //CRC1中断
    EM_IT_CRC2 = 0x00000002,    //CRC2中断
    EM_IT_EDCH = 0x00000004,    //计量方向改变中断
    EM_IT_NOLD = 0x00000008,    //启动潜动改变中断
    EM_IT_PERO = 0x00000010,    //正向能量寄存器溢出中断
    EM_IT_NERO = 0x00000020,    //负向能量寄存器溢出中断
    EM_IT_AERO = 0x00000040,    //绝度值能量寄存器溢出中断
    EM_IT_UZX  = 0x00000080,    //电压过零中断
    EM_IT_CF1  = 0x00000100,    //CF1中断
  输出值：无
  返回值：无
***************************************************************/
void EM_ClearITPendingBit(EM_TYPE_IT EM_IT)
{
    EM->INT.Word &= ~((uint32_t)EM_IT);
}
/***************************************************************
  函数名：
  描  述：EM_GetEMStatus
  输入值：EM_STATA_CRC1S: EM CRC1校验状态位
  *       EM_STATA_CRC2S: EM CRC2校验状态位
  *       EM_STATA_PREV:  EM 上一次计量方向负标志位  
  *       EM_STATE_NOLOAD: EM 计量潜动标准位
  *       EM_STATE_ZXUS: EM 电压信号负标志位
  *       EM_STATE_ZXIAS: EM 电流信号负标志位
  输出值：无
  返回值：无
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

