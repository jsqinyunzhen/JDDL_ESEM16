#include "esem16_scu.h"

/***************************************************************
  函数名：SCU_Init
  描  述：系统时钟初始化
  输入值：无
  输出值：无
  返回值：无
***************************************************************/
void SCU_Init(void)
{
    SCU_RegUnLock();                    //关闭写保护

    /* 系统时钟初始化 */
    SCU_SYSCLKConfig(SCU_SYSCLKS_EXOSC);
    SCU_EXOSC_DeepSleep_Cmd(ENABLE);
    SCU_CLKFLT_Cmd(ENABLE);
    SCU_EMCLK_Cmd(ENABLE);
    //SCU_NMIC_Cofig(SCU_NMIC_IRQ9_GPIO9);
    //SCU_NMIC_Cmd(ENABLE);

    /* 外设时钟初始化 */
    SCU_PCLK_All_Enable();

    SCU_RegLock();                      //打开写保护
}
/***************************************************************
  函数名：void SCU_SYSCLKConfig(uint8_t SCU_SYSCLK_Source)
  描  述：配置系统时钟源
  输入值：SCU_TYPE_SYSCLK
  输出值：无
  返回值：无
***************************************************************/
void SCU_SYSCLKConfig(SCU_TYPE_SYSCLK SCU_SYSCLK_Source)
{
    SCU_RegUnLock();

    SCU->SCLKEN.SSE = SCU_SYSCLK_Source;

    SCU_RegLock();
}
/***************************************************************
  函数名：void SCU_SYSCLKConfig(uint8_t SCU_SYSCLK_Source)
  描  述：配置深度睡眠，主晶振状态
  输入值：  Enables or disables 外部振荡器深度睡眠下模式选择.
  *         NewState: new state of 外部振荡器深度睡眠下模式.
  *         This parameter can be: ENABLE or DISABLE.
  输出值：无
  返回值：无
***************************************************************/
void SCU_EXOSC_DeepSleep_Cmd(FunctionalState NewState)
{
    SCU_RegUnLock();

    /* Set the MOSC_EN bit to enable 外部振荡器深度睡眠下模式 */
    SCU->SCLKEN.MOSC = NewState;

    SCU_RegLock();
}
/***************************************************************
  函数名：SCU_CLKFLT_Cmd
  描  述：系统时钟20ns滤波器状态
  输入值：无
  输出值：无
  返回值：无
***************************************************************/
void SCU_CLKFLT_Cmd(FunctionalState NewState)
{
    SCU_RegUnLock();

    /* Set the PLL_EN bit to enable the CLKFLT */
    SCU->SCLKEN.FLT = NewState;

    SCU_RegLock();
}
/***************************************************************
  函数名：SCU_EMCLK_Cmd
  描  述：计量时钟状态
  输入值：无
  输出值：无
  返回值：无
***************************************************************/
void SCU_EMCLK_Cmd(FunctionalState NewState)
{
    SCU_RegUnLock();

    /* Set the LIOSC_EN bit to enable the EMCLK */
    SCU->SCLKEN.EMEN = NewState;

    SCU_RegLock();
}
/***************************************************************
  函数名：SCU_NMIC_Cmd
  描  述：NMIC控制
  输入值：无
  输出值：无
  返回值：无
***************************************************************/
void SCU_NMIC_Cmd(FunctionalState NewState)
{
    SCU_RegUnLock();

    SCU->NMIC.EN |= NewState;

    SCU_RegLock();
}
/***************************************************************
  函数名：SCU_NMIC_Cofig
  描  述：NMI初始化
  输入值：无
  输出值：无
  返回值：无
***************************************************************/
void SCU_NMIC_Cofig(SCU_TYPE_NMIC SCU_NMI_CS)
{
    SCU_RegUnLock();

    /* Write to SCU NMICS NMICS bits*/
    SCU->NMIC.CS = SCU_NMI_CS;

    SCU_RegLock();
}
/***************************************************************
  函数名：FlagStatus SCU_Get_PWRC_Flag(SCU_TYPE_PWRC SCU_PWRC_FLAG)
  描  述：获取复位标志
  输入值：SCU_TYPE_PWRC
  输出值：无
  返回值：无
***************************************************************/
FlagStatus SCU_Get_PWRC_Flag(SCU_TYPE_PWRC SCU_PWRC_FLAG)
{
    uint32_t tmpreg = 0;
    FlagStatus bitstatus = RESET;

    SCU_RegUnLock();

    /* Get the flag position */
    tmpreg = SCU->PWRC.Word & SCU_PWRC_FLAG;

    if (tmpreg != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    SCU_RegLock();

    return bitstatus;
}
/***************************************************************
  函数名：FlagStatus SCU_Get_FAULTFLAG_Flag(void)
  描  述：获取硬件错误标志
  输入值：无
  输出值：无
  返回值：无
***************************************************************/
FlagStatus SCU_Get_FAULTFLAG_Flag(void)
{
    FlagStatus bitstatus = RESET;

    SCU_RegUnLock();

    if (SCU->FAULTFLAG.FLAG != RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    SCU_RegLock();

    return bitstatus;
}
/***************************************************************
  函数名：FlagStatus SCU_Clear_FAULTFLAG_Flag(void)
  描  述：清除硬件错误标志
  输入值：无
  输出值：无
  返回值：无
***************************************************************/
void SCU_Clear_FAULTFLAG_Flag(void)
{
    SCU_RegUnLock();

    SCU->FAULTFLAG.Word = 0x00000000;

    SCU_RegLock();
}
/***************************************************************
  函数名：void SCU_PCLK_Cmd(SUC_TYPE_PCLK SCU_PCLKx, FunctionalState NewState)
  描  述：配置外设时钟状态
  输入值：SCU_PCLKx,NewState
  输出值：无
  返回值：无
***************************************************************/
void SCU_PCLK_Cmd(SUC_TYPE_PCLK SCU_PCLKx, FunctionalState NewState)
{
    SCU_RegUnLock();

    if(NewState != DISABLE)
    {
        /* Set the PERIx bit to enable the peripheral 时钟 */
        SCU->PCLKEN.Word |= SCU_PCLKx;
    }
    else
    {
        /* Disable the selected peripheral 时钟 */
        SCU->PCLKEN.Word &= ~SCU_PCLKx;
    }

    SCU_RegLock();
}
/***************************************************************
  函数名：SCU_PCLK_All_Enable
  描  述：打开所有外设时钟
  输入值：无
  输出值：无
  返回值：无
 ***************************************************************/
void SCU_PCLK_All_Enable(void)
{
    SCU_RegUnLock();

    SCU->PCLKEN.Word = 0x00111397;     //打开所有外设时钟(默认值全部打开)

    SCU_RegLock();
}
/***************************************************************
  函数名：SCU_PCLK_All_Disable
  描  述：关闭所有外设时钟
  输入值：无
  输出值：无
  返回值：无
 ***************************************************************/
void SCU_PCLK_All_Disable(void)
{
    SCU_RegUnLock();

    SCU->PCLKEN.Word = 0x00000000;     //关闭所有外设时钟，scu无法关闭

    SCU_RegLock();
}
/***************************************************************
  函数名：void SCU_Wakeuptime_Cmd(uint16_t time)
  描  述：配置系统唤醒时间
  输入值：
  输出值：无
  返回值：无
***************************************************************/
void SCU_Wakeuptime_Cmd(uint16_t time)
{
    SCU_RegUnLock();

    SCU->WAKEUPTIME.VALUE = time;

    SCU_RegLock();
}
/***************************************************************
  函数名：void SCU_Testcon_Cmd(SCU_TYPE_TESTCON type)
  描  述：配置测试模式
  输入值：
  输出值：无
  返回值：无
***************************************************************/
void SCU_Testcon_Cmd(SCU_TYPE_TESTCON type)
{
    SCU_RegUnLock();

    SCU->TESTCON.SEL = type;

    SCU_RegLock();
}
/***************************************************************
  函数名：void SCU_VRCal_Bor_Cmd(uint16_t temp)
  描  述：VR校准
  输入值：
  输出值：无
  返回值：无
***************************************************************/
void SCU_VR0Cal_Bor_Cmd(uint16_t temp)
{
    SCU_RegUnLock();

    SCU->VRCAL0.BOR = temp;

    SCU_RegLock();
}
/***************************************************************
  函数名：void SCU_VRCal_Iout_Cmd(uint16_t temp)
  描  述：VR校准
  输入值：
  输出值：无
  返回值：无
***************************************************************/
void SCU_VR0Cal_Iout_Cmd(uint16_t temp)
{
    SCU_RegUnLock();

    SCU->VRCAL0.IOUT = temp;

    SCU_RegLock();
}
/***************************************************************
  函数名：void SCU_VR1Cal_Bgr1_Cmd(uint16_t temp)
  描  述：VR校准
  输入值：
  输出值：无
  返回值：无
***************************************************************/
void SCU_VR1Cal_Bgr1_Cmd(uint16_t temp)
{
    SCU_RegUnLock();

    SCU->VRCAL1.BGR_R1CTL = temp;

    SCU_RegLock();
}
/***************************************************************
  函数名：void SCU_VR1Cal_Bgr2_Cmd(uint16_t temp)
  描  述：VR校准
  输入值：
  输出值：无
  返回值：无
***************************************************************/
void SCU_VR1Cal_Bgr2_Cmd(uint16_t temp)
{
    SCU_RegUnLock();

    SCU->VRCAL1.BGR_R2CTL = temp;

    SCU_RegLock();
}
/***************************************************************
  函数名：void SCU_MCLKCal_XOSCRES_Cmd(uint16_t temp)
  描  述：VR校准
  输入值：
  输出值：无
  返回值：无
***************************************************************/
void SCU_MCLKCal_XOSCRES_Cmd(uint16_t temp)
{
    SCU_RegUnLock();

    SCU->MCLKCAL.XOSCRES = temp;

    SCU_RegLock();
}
/***************************************************************
  函数名：void SCU_MCLKCal_XOSCAMP_Cmd(uint16_t temp)
  描  述：VR校准
  输入值：
  输出值：无
  返回值：无
***************************************************************/
void SCU_MCLKCal_XOSCAMP_Cmd(uint16_t temp)
{
    SCU_RegUnLock();

    SCU->MCLKCAL.XOSCAMP = temp;

    SCU_RegLock();
}
/***************************************************************
  函数名：void SCU_MCLKCal_CLKFLT_Cmd(uint16_t temp)
  描  述：VR校准
  输入值：
  输出值：无
  返回值：无
***************************************************************/
void SCU_MCLKCal_CLKFLT_Cmd(uint16_t temp)
{
    SCU_RegUnLock();

    SCU->MCLKCAL.CLK_FLT_CAL = temp;

    SCU_RegLock();
}
/***************************************************************
  函数名：void SCU_WDTCal_Cmd(uint16_t temp)
  描  述：WDT校准
  输入值：
  输出值：无
  返回值：无
***************************************************************/
void SCU_WDTCal_Cmd(uint16_t temp)
{
    SCU_RegUnLock();

    SCU->WDTCAL.WDT_CAL = temp;

    SCU_RegLock();
}
/***************************************************************
  函数名：void SCU_TEMPSCal_Cmd(uint16_t temp)
  描  述：温度传感器校准
  输入值：
  输出值：无
  返回值：无
***************************************************************/
void SCU_TEMPSCal_Vref1_Cmd(uint16_t temp)
{
    SCU_RegUnLock();

    SCU->TMPSCAL.VREF1_CAL = temp;

    SCU_RegLock();
}
/***************************************************************
  函数名：void SCU_TEMPSCal_Vref2_Cmd(uint16_t temp)
  描  述：温度传感器校准
  输入值：
  输出值：无
  返回值：无
***************************************************************/
void SCU_TEMPSCal_Vref2_Cmd(uint16_t temp)
{
    SCU_RegUnLock();

    SCU->TMPSCAL.VREF2_CAL = temp;

    SCU_RegLock();
}
/***************************************************************
  函数名：void SCU_AFECal_Cmd(uint16_t temp)
  描  述：计量前端校准
  输入值：
  输出值：无
  返回值：无
***************************************************************/
void SCU_AFECal_Cmd(uint16_t temp)
{
    SCU_RegUnLock();

    SCU->AFECAL.VREF_CAL3 = temp;

    SCU_RegLock();
}
/***************************************************************
  函数名：void SCU_ADCCal_Cmd(uint16_t temp)
  描  述：ADC偏移校准
  输入值：
  输出值：无
  返回值：无
***************************************************************/
void SCU_ADCCal_Cmd(uint16_t temp)
{
    SCU_RegUnLock();

    //SCU->ADCCAL.ADC_CAL = temp;

    SCU_RegLock();
}

/******************* (C) COPYRIGHT 2018 Eastsoft *****END OF FILE****/

