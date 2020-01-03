#include "esem16_scu.h"

/***************************************************************
  ��������SCU_Init
  ��  ����ϵͳʱ�ӳ�ʼ��
  ����ֵ����
  ���ֵ����
  ����ֵ����
***************************************************************/
void SCU_Init(void)
{
    SCU_RegUnLock();                    //�ر�д����

    /* ϵͳʱ�ӳ�ʼ�� */
    SCU_SYSCLKConfig(SCU_SYSCLKS_EXOSC);
    SCU_EXOSC_DeepSleep_Cmd(ENABLE);
    SCU_CLKFLT_Cmd(ENABLE);
    SCU_EMCLK_Cmd(ENABLE);
    //SCU_NMIC_Cofig(SCU_NMIC_IRQ9_GPIO9);
    //SCU_NMIC_Cmd(ENABLE);

    /* ����ʱ�ӳ�ʼ�� */
    SCU_PCLK_All_Enable();

    SCU_RegLock();                      //��д����
}
/***************************************************************
  ��������void SCU_SYSCLKConfig(uint8_t SCU_SYSCLK_Source)
  ��  ��������ϵͳʱ��Դ
  ����ֵ��SCU_TYPE_SYSCLK
  ���ֵ����
  ����ֵ����
***************************************************************/
void SCU_SYSCLKConfig(SCU_TYPE_SYSCLK SCU_SYSCLK_Source)
{
    SCU_RegUnLock();

    SCU->SCLKEN.SSE = SCU_SYSCLK_Source;

    SCU_RegLock();
}
/***************************************************************
  ��������void SCU_SYSCLKConfig(uint8_t SCU_SYSCLK_Source)
  ��  �����������˯�ߣ�������״̬
  ����ֵ��  Enables or disables �ⲿ�������˯����ģʽѡ��.
  *         NewState: new state of �ⲿ�������˯����ģʽ.
  *         This parameter can be: ENABLE or DISABLE.
  ���ֵ����
  ����ֵ����
***************************************************************/
void SCU_EXOSC_DeepSleep_Cmd(FunctionalState NewState)
{
    SCU_RegUnLock();

    /* Set the MOSC_EN bit to enable �ⲿ�������˯����ģʽ */
    SCU->SCLKEN.MOSC = NewState;

    SCU_RegLock();
}
/***************************************************************
  ��������SCU_CLKFLT_Cmd
  ��  ����ϵͳʱ��20ns�˲���״̬
  ����ֵ����
  ���ֵ����
  ����ֵ����
***************************************************************/
void SCU_CLKFLT_Cmd(FunctionalState NewState)
{
    SCU_RegUnLock();

    /* Set the PLL_EN bit to enable the CLKFLT */
    SCU->SCLKEN.FLT = NewState;

    SCU_RegLock();
}
/***************************************************************
  ��������SCU_EMCLK_Cmd
  ��  ��������ʱ��״̬
  ����ֵ����
  ���ֵ����
  ����ֵ����
***************************************************************/
void SCU_EMCLK_Cmd(FunctionalState NewState)
{
    SCU_RegUnLock();

    /* Set the LIOSC_EN bit to enable the EMCLK */
    SCU->SCLKEN.EMEN = NewState;

    SCU_RegLock();
}
/***************************************************************
  ��������SCU_NMIC_Cmd
  ��  ����NMIC����
  ����ֵ����
  ���ֵ����
  ����ֵ����
***************************************************************/
void SCU_NMIC_Cmd(FunctionalState NewState)
{
    SCU_RegUnLock();

    SCU->NMIC.EN |= NewState;

    SCU_RegLock();
}
/***************************************************************
  ��������SCU_NMIC_Cofig
  ��  ����NMI��ʼ��
  ����ֵ����
  ���ֵ����
  ����ֵ����
***************************************************************/
void SCU_NMIC_Cofig(SCU_TYPE_NMIC SCU_NMI_CS)
{
    SCU_RegUnLock();

    /* Write to SCU NMICS NMICS bits*/
    SCU->NMIC.CS = SCU_NMI_CS;

    SCU_RegLock();
}
/***************************************************************
  ��������FlagStatus SCU_Get_PWRC_Flag(SCU_TYPE_PWRC SCU_PWRC_FLAG)
  ��  ������ȡ��λ��־
  ����ֵ��SCU_TYPE_PWRC
  ���ֵ����
  ����ֵ����
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
  ��������FlagStatus SCU_Get_FAULTFLAG_Flag(void)
  ��  ������ȡӲ�������־
  ����ֵ����
  ���ֵ����
  ����ֵ����
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
  ��������FlagStatus SCU_Clear_FAULTFLAG_Flag(void)
  ��  �������Ӳ�������־
  ����ֵ����
  ���ֵ����
  ����ֵ����
***************************************************************/
void SCU_Clear_FAULTFLAG_Flag(void)
{
    SCU_RegUnLock();

    SCU->FAULTFLAG.Word = 0x00000000;

    SCU_RegLock();
}
/***************************************************************
  ��������void SCU_PCLK_Cmd(SUC_TYPE_PCLK SCU_PCLKx, FunctionalState NewState)
  ��  ������������ʱ��״̬
  ����ֵ��SCU_PCLKx,NewState
  ���ֵ����
  ����ֵ����
***************************************************************/
void SCU_PCLK_Cmd(SUC_TYPE_PCLK SCU_PCLKx, FunctionalState NewState)
{
    SCU_RegUnLock();

    if(NewState != DISABLE)
    {
        /* Set the PERIx bit to enable the peripheral ʱ�� */
        SCU->PCLKEN.Word |= SCU_PCLKx;
    }
    else
    {
        /* Disable the selected peripheral ʱ�� */
        SCU->PCLKEN.Word &= ~SCU_PCLKx;
    }

    SCU_RegLock();
}
/***************************************************************
  ��������SCU_PCLK_All_Enable
  ��  ��������������ʱ��
  ����ֵ����
  ���ֵ����
  ����ֵ����
 ***************************************************************/
void SCU_PCLK_All_Enable(void)
{
    SCU_RegUnLock();

    SCU->PCLKEN.Word = 0x00111397;     //����������ʱ��(Ĭ��ֵȫ����)

    SCU_RegLock();
}
/***************************************************************
  ��������SCU_PCLK_All_Disable
  ��  �����ر���������ʱ��
  ����ֵ����
  ���ֵ����
  ����ֵ����
 ***************************************************************/
void SCU_PCLK_All_Disable(void)
{
    SCU_RegUnLock();

    SCU->PCLKEN.Word = 0x00000000;     //�ر���������ʱ�ӣ�scu�޷��ر�

    SCU_RegLock();
}
/***************************************************************
  ��������void SCU_Wakeuptime_Cmd(uint16_t time)
  ��  ��������ϵͳ����ʱ��
  ����ֵ��
  ���ֵ����
  ����ֵ����
***************************************************************/
void SCU_Wakeuptime_Cmd(uint16_t time)
{
    SCU_RegUnLock();

    SCU->WAKEUPTIME.VALUE = time;

    SCU_RegLock();
}
/***************************************************************
  ��������void SCU_Testcon_Cmd(SCU_TYPE_TESTCON type)
  ��  �������ò���ģʽ
  ����ֵ��
  ���ֵ����
  ����ֵ����
***************************************************************/
void SCU_Testcon_Cmd(SCU_TYPE_TESTCON type)
{
    SCU_RegUnLock();

    SCU->TESTCON.SEL = type;

    SCU_RegLock();
}
/***************************************************************
  ��������void SCU_VRCal_Bor_Cmd(uint16_t temp)
  ��  ����VRУ׼
  ����ֵ��
  ���ֵ����
  ����ֵ����
***************************************************************/
void SCU_VR0Cal_Bor_Cmd(uint16_t temp)
{
    SCU_RegUnLock();

    SCU->VRCAL0.BOR = temp;

    SCU_RegLock();
}
/***************************************************************
  ��������void SCU_VRCal_Iout_Cmd(uint16_t temp)
  ��  ����VRУ׼
  ����ֵ��
  ���ֵ����
  ����ֵ����
***************************************************************/
void SCU_VR0Cal_Iout_Cmd(uint16_t temp)
{
    SCU_RegUnLock();

    SCU->VRCAL0.IOUT = temp;

    SCU_RegLock();
}
/***************************************************************
  ��������void SCU_VR1Cal_Bgr1_Cmd(uint16_t temp)
  ��  ����VRУ׼
  ����ֵ��
  ���ֵ����
  ����ֵ����
***************************************************************/
void SCU_VR1Cal_Bgr1_Cmd(uint16_t temp)
{
    SCU_RegUnLock();

    SCU->VRCAL1.BGR_R1CTL = temp;

    SCU_RegLock();
}
/***************************************************************
  ��������void SCU_VR1Cal_Bgr2_Cmd(uint16_t temp)
  ��  ����VRУ׼
  ����ֵ��
  ���ֵ����
  ����ֵ����
***************************************************************/
void SCU_VR1Cal_Bgr2_Cmd(uint16_t temp)
{
    SCU_RegUnLock();

    SCU->VRCAL1.BGR_R2CTL = temp;

    SCU_RegLock();
}
/***************************************************************
  ��������void SCU_MCLKCal_XOSCRES_Cmd(uint16_t temp)
  ��  ����VRУ׼
  ����ֵ��
  ���ֵ����
  ����ֵ����
***************************************************************/
void SCU_MCLKCal_XOSCRES_Cmd(uint16_t temp)
{
    SCU_RegUnLock();

    SCU->MCLKCAL.XOSCRES = temp;

    SCU_RegLock();
}
/***************************************************************
  ��������void SCU_MCLKCal_XOSCAMP_Cmd(uint16_t temp)
  ��  ����VRУ׼
  ����ֵ��
  ���ֵ����
  ����ֵ����
***************************************************************/
void SCU_MCLKCal_XOSCAMP_Cmd(uint16_t temp)
{
    SCU_RegUnLock();

    SCU->MCLKCAL.XOSCAMP = temp;

    SCU_RegLock();
}
/***************************************************************
  ��������void SCU_MCLKCal_CLKFLT_Cmd(uint16_t temp)
  ��  ����VRУ׼
  ����ֵ��
  ���ֵ����
  ����ֵ����
***************************************************************/
void SCU_MCLKCal_CLKFLT_Cmd(uint16_t temp)
{
    SCU_RegUnLock();

    SCU->MCLKCAL.CLK_FLT_CAL = temp;

    SCU_RegLock();
}
/***************************************************************
  ��������void SCU_WDTCal_Cmd(uint16_t temp)
  ��  ����WDTУ׼
  ����ֵ��
  ���ֵ����
  ����ֵ����
***************************************************************/
void SCU_WDTCal_Cmd(uint16_t temp)
{
    SCU_RegUnLock();

    SCU->WDTCAL.WDT_CAL = temp;

    SCU_RegLock();
}
/***************************************************************
  ��������void SCU_TEMPSCal_Cmd(uint16_t temp)
  ��  �����¶ȴ�����У׼
  ����ֵ��
  ���ֵ����
  ����ֵ����
***************************************************************/
void SCU_TEMPSCal_Vref1_Cmd(uint16_t temp)
{
    SCU_RegUnLock();

    SCU->TMPSCAL.VREF1_CAL = temp;

    SCU_RegLock();
}
/***************************************************************
  ��������void SCU_TEMPSCal_Vref2_Cmd(uint16_t temp)
  ��  �����¶ȴ�����У׼
  ����ֵ��
  ���ֵ����
  ����ֵ����
***************************************************************/
void SCU_TEMPSCal_Vref2_Cmd(uint16_t temp)
{
    SCU_RegUnLock();

    SCU->TMPSCAL.VREF2_CAL = temp;

    SCU_RegLock();
}
/***************************************************************
  ��������void SCU_AFECal_Cmd(uint16_t temp)
  ��  ��������ǰ��У׼
  ����ֵ��
  ���ֵ����
  ����ֵ����
***************************************************************/
void SCU_AFECal_Cmd(uint16_t temp)
{
    SCU_RegUnLock();

    SCU->AFECAL.VREF_CAL3 = temp;

    SCU_RegLock();
}
/***************************************************************
  ��������void SCU_ADCCal_Cmd(uint16_t temp)
  ��  ����ADCƫ��У׼
  ����ֵ��
  ���ֵ����
  ����ֵ����
***************************************************************/
void SCU_ADCCal_Cmd(uint16_t temp)
{
    SCU_RegUnLock();

    //SCU->ADCCAL.ADC_CAL = temp;

    SCU_RegLock();
}

/******************* (C) COPYRIGHT 2018 Eastsoft *****END OF FILE****/

