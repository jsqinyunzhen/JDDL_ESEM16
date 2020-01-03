#include "includes.h"
#include <stdio.h>

EM_GainPara_TypeDef g_EM_GainPara={0};
EP_Data_TypeDef g_EP_Data= {0};
MeterVariable_TypeDef g_Emu_Data={0};
uint8_t gGainPrint = 0;
uint8_t gEMUprint = 0;

//const EM_GainPara_TypeDef ADJ_DEFAULT = {0xFFF3, 0x3c4, 0x240, 0x00, 0xffe6, 0x05DD};         //Ĭ��У׼����

/*********************************************************************************************************
*   �� �� ��: Init_User_EMU
*   ����˵��: em��ʼ��
*   ��    �Σ���
*   �� �� ֵ: ��
*********************************************************************************************************/
void Init_User_EMU(void)
{
    //uint8_t buf_Adjust[2];

    EMU_Init();

#if 1                                           //��E2ȡ��У׼ֵ 

    GloableVar_Init();
    EM_Config();

#else                                           //̨��У׼

    buf_Adjust[0] = 0xDC;
    buf_Adjust[1] = 0x00;
    UGAIN_Adjust(buf_Adjust);

    buf_Adjust[0] = 0x7E;
    buf_Adjust[1] = 0x00;
    IAGAIN_Adjust(buf_Adjust);

    buf_Adjust[0] = 0x00;
    buf_Adjust[1] = 0x00;
    PAGAIN_Adjust(buf_Adjust);

    buf_Adjust[0] = 0x00;
    buf_Adjust[1] = 0x00;
    APHCAL_Adjust(buf_Adjust);

    buf_Adjust[0] = 0x00;
    buf_Adjust[1] = 0x00;
    PAOFF_Adjust(buf_Adjust);

    //g_EM_GainPara.U_Gain.B16 = 0xFE4D;
    //g_EM_GainPara.I_Gain.B16 = 0xF011;
    //g_EM_GainPara.P_Gain.B16 = 0xF08B;
    //g_EM_GainPara.Phase_Gain.B16 = 0x0037;
    //g_EM_GainPara.Paoff_Gain.B16 = 0x0000;
    //g_EM_GainPara.Check_Sum.B16 = 0xDF20;

    EM_Set_PSTART(PSTART_DATA);
    EM_Set_PFSET(PFSET_DATA);
    //EM_Set_UGAIN(g_EM_GainPara.U_Gain.B16);
    //EM_Set_IAGAIN(g_EM_GainPara.I_Gain.B16);
    //EM_Set_PAGAIN(g_EM_GainPara.P_Gain.B16);
    //EM_Set_APHCAL(g_EM_GainPara.Phase_Gain.B16);
    //EM_Set_PAOFF(g_EM_GainPara.Paoff_Gain.B16);

#endif
}
/*********************************************************************************************************
*   �� �� ��: EM_Init
*   ����˵��: em��ʼ��
*   ��    �Σ���
*   �� �� ֵ: ��
*********************************************************************************************************/
void EMU_Init(void)
{
    EM_InitTypeDef EM_InitStruct;
    EM_ParaTypeDef EM_ParaStruct;

    EM_RegUnLock();
    EM_InitStruct.EM_PGA1_Config = EM_PGA1_X16;                 //PGA1����ѡ��
    EM_InitStruct.EM_PGA2_Config = EM_PGA2_X2;                  //PGA2����ѡ��
    EM_InitStruct.EM_ADC1_Config = ENABLE;                      //ADC1ʹ��
    EM_InitStruct.EM_ADC2_Config = ENABLE;                      //ADC2ʹ��
    EM_InitStruct.EM_BGR_Config = ENABLE;                       //Bandgapʹ��
    EM_InitStruct.EM_CHOP1_Config = EM_CHOP_EN;                 //chop1ʱ��ʹ��
    EM_InitStruct.EM_CHOP2_Config = EM_CHOP_EN;                 //chop2ʱ��ʹ��
    EM_InitStruct.EM_HPF_Config = ENABLE;                       //HPFʹ��
    EM_InitStruct.EM_EM_EN_Config = ENABLE;                     //EMʹ��
    EM_InitStruct.EM_RMS_EN_Config = ENABLE;                    //RMSʹ��
    EM_InitStruct.EM_CF_EN_Config = ENABLE;                     //CFʹ��
    EM_InitStruct.EM_EA_EN_Config = ENABLE;                     //EAʹ��
    EM_InitStruct.EM_APPF_EN_Config = ENABLE;                   //APPFʹ��
    EM_InitStruct.EM_ZX_EN_Config = ENABLE;                     //ZXʹ��
    EM_InitStruct.EM_FP_EN_Config = ENABLE;                     //FPʹ��
    EM_InitStruct.EM_ERCLR_Config = EM_ERCLR_Clr;               //ERCLRģʽ
    EM_InitStruct.EM_CRC1_EN_Config = DISABLE;                  //CRC1ʹ��
    EM_InitStruct.EM_CRC2_EN_Config = DISABLE;                  //CRC2ʹ��
    EM_InitStruct.EM_CF1SEL_Config = CF_SEL_OutputPos;          //CF1ѡ��
    EM_InitStruct.EM_CF1MOD_Config = CF_MOD_AbsEnergy;          //CF1ģʽ
    EM_InitStruct.EM_ZXSEL_Config = ZX_SEL_PosOutput;           //ZXѡ��
    EM_InitStruct.EM_POFF_MOD_Config = DISABLE;                 //POFFģʽ
    EM_Init(&EM_InitStruct);

    EM_ParaStruct.EM_PFSET_Config = 0x00010000;                 //PFSET
    EM_ParaStruct.EM_PAGAIN_Config = 0;                         //PAGAIN
    EM_ParaStruct.EM_IAGAIN_Config = 0;                         //IAGAIN
    EM_ParaStruct.EM_UGAIN_Config = 0;                          //UAGAIN
    EM_ParaStruct.EM_APHCAL_Config = 0;                         //APHCAL
    EM_ParaStruct.EM_PAOFF_Config = 0;                          //PAOFF
    EM_ParaStruct.EM_IAOFF_Config = 0;                          //IAOFF
    EM_ParaStruct.EM_UOFF_Config = 0;                           //UOFF
    EM_ParaStruct.EM_PSTART_Config = 0;                         //PSTART
    EM_ParaInit(&EM_ParaStruct);
}
void Emu_GainRead(void)
{
    uint32_t gain = 0;
    
    gain = 0; 
    IAP_ReadUGAIN( &gain);
    g_EM_GainPara.U_Gain.B16 = gain;

    gain = 0;
    IAP_ReadIGAIN( &gain);
    g_EM_GainPara.I_Gain.B16 = gain;
   
    gain = 0;
    IAP_ReadPAGAIN( &gain);
    g_EM_GainPara.P_Gain.B16 = gain;
    
    gain = 0;
    IAP_ReadAPHCAL( &gain);
    g_EM_GainPara.Phase_Gain.B16 = gain;
    
    gain = 0;
    IAP_ReadPAOFF( &gain);
    g_EM_GainPara.Paoff_Gain.B16 = gain;
    
    gain = 0;
    IAP_ReadCHECKSUM(&gain);
    g_EM_GainPara.Check_Sum.B16 = gain;
}
/*********************************************************************************************************
*   �� �� ��: GloableVar_Init
*   ����˵��: ��EEPROM��У׼���������������Ϊ0xFF������Ϊ��оƬ��һ���ϵ磬����Ĭ��ֵ��EEPROM��RAM�С�
*   ��    �Σ���
*   �� �� ֵ: ��
*********************************************************************************************************/
void GloableVar_Init(void)
{
    EM_GainPara_TypeDef ptr;
    uint8_t adjust_first = 0;
    uint16_t checksum = 0;

    Emu_GainRead();
    
    memset(ptr.U_Gain.B08, 0xFF, EE_PARAM_SUM*2);
    adjust_first = memcmp(ptr.U_Gain.B08, g_EM_GainPara.U_Gain.B08, EE_PARAM_SUM*2);
    checksum = SumCheck(g_EM_GainPara.U_Gain.B08, EE_CHECK_SUM*2);

    if (!adjust_first || checksum == 0 || checksum != g_EM_GainPara.Check_Sum.B16)
    {
        memset(g_EM_GainPara.U_Gain.B08,0,sizeof(g_EM_GainPara));
        #if 0
        g_EM_GainPara.U_Gain.B16 = 0xFF44;
        g_EM_GainPara.I_Gain.B16 = 0xfAED;
        g_EM_GainPara.P_Gain.B16 = 0xfc61;
        g_EM_GainPara.Phase_Gain.B16 = 0x0;
        g_EM_GainPara.Paoff_Gain.B16 = 0xffe6;
        //g_EM_GainPara.Check_Sum.B16 = 0x05DD;
        #endif

        g_EP_Data.energy.B32 = 0;
        g_EP_Data.pulse = 0;
        Emu_Adjust_Save();
    }
    else
    {
        //IAP_ReadEnergy(&g_EP_Data);
    }
    //gGainPrin                                                                                                                                                                                                                                                                                                                                                                                                                                                                         t = 1;
    return ;

}
/*********************************************************************************************************
*   �� �� ��: EM_Config
*   ����˵��: EMУ׼ֵ�ȳ�ʼ������
*   ��    ��: д��Ĵ���ֵ
*   �� �� ֵ: ��
*********************************************************************************************************/
void EM_Config(void)
{
    EM_Set_PSTART(PSTART_DATA);
    EM_Set_PFSET(PFSET_DATA);
    EM_Set_UGAIN(g_EM_GainPara.U_Gain.B16);
    EM_Set_IAGAIN(g_EM_GainPara.I_Gain.B16);
    EM_Set_PAGAIN(g_EM_GainPara.P_Gain.B16);
    EM_Set_APHCAL(g_EM_GainPara.Phase_Gain.B16);
    EM_Set_PAOFF(g_EM_GainPara.Paoff_Gain.B16);
}
/*********************************************************************************************************
*   �� �� ��: Get_URMS
*   ����˵��: �õ�������ѹֵ
*   ��    ��: ��
*   �� �� ֵ: ʵ�ʵ�ѹֵ(����10��)
*********************************************************************************************************/
uint32_t Get_URMS(void)
{
    uint32_t urms;

    urms = EM_Get_URMS();
    urms = urms *_U_C;
    return urms;
}
/*********************************************************************************************************
*   �� �� ��: Get_IRMS
*   ����˵��: �õ�ʵ�ʵ���ֵ
*   ��    ��: ��
*   �� �� ֵ: ʵ�ʵ���ֵ(����1000��)
*********************************************************************************************************/
uint32_t Get_IRMS(void)
{
    uint32_t irms;

    irms = EM_Get_IARMS();
    irms = irms * _I_C;
    return irms;
}
/*********************************************************************************************************
*   �� �� ��: Get_FRQ
*   ����˵��: �õ�ʵ��Ƶ��
*   ��    ��: ��
*   �� �� ֵ: ʵ��Ƶ��
*********************************************************************************************************/
uint16_t Get_FRQ(void)
{
    uint16_t hz;

    hz = EM_Get_FRQ();
    hz = hz * 100 / 256;
    return (uint16_t)hz;
}
/*********************************************************************************************************
*   �� �� ��: Get_PHASE
*   ����˵��: �õ�ʵ�����
*   ��    ��: ��
*   �� �� ֵ: ʵ�����
*********************************************************************************************************/
uint16_t Get_PHASE(void)
{
    uint16_t ph;

    ph = EM_Get_APHASE();
    ph = ph / (1<<7);

    return ph;
}
/*********************************************************************************************************
*   �� �� ��: Get_PRMS
*   ����˵��: �õ�ʵ�ʹ���
*   ��    ��: ��
*   �� �� ֵ: ����ֵ,��λ��(0.0001w)
*********************************************************************************************************/
uint32_t Get_PRMS(void)
{
    uint32_t prms;

    prms = EM_Get_PA();         //���з���32λ��
    if (prms & 0x80000000)      //����
    {
        prms = ~prms + 1;
    }
    prms = prms * _P_C ;
    return prms;
}
/*********************************************************************************************************
*   �� �� ��: Get_Factor
*   ����˵��: �õ���������
*   ��    ��: ��
*   �� �� ֵ: ��������* 1000
*********************************************************************************************************/
uint16_t Get_Factor(void)
{
    uint16_t frms;

    frms = EM_Get_AFAC();
    if (frms & 0x8000)
    {
        frms = ~frms + 1;
    }
    frms = (frms*1000)/32768;
    return frms;
}
/*********************************************************************************************************
*   �� �� ��: GetErrData
*   ����˵��: ����оƬ���� (ʵ�ʲ�������-̨����ʵ����)/(̨����ʵ����)   
*   ��    ��: ��
*   �� �� ֵ: 
*********************************************************************************************************/
double GetErrData(uint8_t *uBuf)
{
    B32_B08 temp32_p;                      //̨�幦��
    uint32_t power;
    double err_data;                      //�������

    Bcd2Hex_4(uBuf, temp32_p.B08);          //��ǰ����ת����HEX 
    power = Get_PRMS();
    err_data = (double)power / temp32_p.B32 - 1;    //������ (ʵ�ʲ�������-̨����ʵ����)/(̨����ʵ����)   
    return err_data;
}
/*********************************************************************************************************
*   �� �� ��: UGAIN_Adjust
*   ����˵��: ��ѹУ׼
*   ��    ��: ̨��ʵ�ʵ�ѹֵ
*   �� �� ֵ: ��
*********************************************************************************************************/
void UGAIN_Adjust(uint8_t *uBuf)
{
    uint16_t u_gain;
    uint32_t v_data;
    double err_data;
    B32_B08 temp32_Un;                                  //̨���ѹ

    Bcd2Hex_4(uBuf, temp32_Un.B08);
    //У׼ǰ������Ĵ���
    EM_Set_UGAIN(0);
    DelayMs(1000);                                      //Ҫ���Ӽ��ʱ�䡣
    //v_data = EM_Get_UGAIN();                            //����ѹ��Чֵ�Ĵ���
    v_data =EM_Get_URMS();

    err_data = temp32_Un.B32 / _U_C / v_data - 1;       //��� = (Ų�� - U����)/U����
    if (err_data >= 0)                                  //ת���ɲ�����ʽ ��������ֲ�/Ӧ�ñʼ�
    {
        u_gain = (uint16_t)(err_data * 32768);
    }
    else
    {
        u_gain = (uint16_t)(err_data * 32768 + 65536);
    }

    //����У����
    EM_Set_UGAIN(u_gain);
    g_EM_GainPara.U_Gain.B16 = u_gain;
    Emu_Adjust_Save();                                      //EEPROM����
}
/*********************************************************************************************************
*   �� �� ��: IAGAIN_Adjust
*   ����˵��: ����У׼
*   ��    ��: ̨��ʵ�ʵ���ֵ
*   �� �� ֵ: ��
*********************************************************************************************************/
void IAGAIN_Adjust(uint8_t *uBuf)
{
    uint16_t i_gain;
    uint32_t i_data;
    double err_data;
    B32_B08 temp32_Ia;                               //̨�����

    Bcd2Hex_4(uBuf, temp32_Ia.B08);
    //У׼ǰ������Ĵ���
    EM_Set_IAGAIN(0);

    DelayMs(1000);
    i_data = EM_Get_IARMS();                            //��������Чֵ�Ĵ���
    err_data = temp32_Ia.B32 / _I_C / i_data - 1;       //��� = (Į��-I����)/I����
    if (err_data >= 0)
    {
        i_gain = (uint16_t)(err_data * 32768);
    }
    else
    {
        i_gain = (uint16_t)(err_data * 32768 + 65536);
    }

    //����У����
    EM_Set_IAGAIN(i_gain);
    g_EM_GainPara.I_Gain.B16 = i_gain;
    Emu_Adjust_Save();
}
/*********************************************************************************************************
*   �� �� ��: PAGAIN_Adjust
*   ����˵��: �й�����У׼
*   ��    ��: ̨��ʵ�ʹ���ֵ
*   �� �� ֵ: ��
*********************************************************************************************************/
void PAGAIN_Adjust(uint8_t *uBuf)
{
    double err_data;
    uint32_t gain;

    //У׼ǰ������Ĵ���
    EM_Set_PAGAIN(0);

    err_data = GetErrData(uBuf);                //�������
    err_data = -err_data / (1 + err_data);      //������ΪG-1 = (1/(1+err_data))-1
    //��(G-1)����Ϊ*2^15�Ĳ�����ʽ  ��������ֲ�/Ӧ�ñʼ�
    if (err_data >= 0)
        gain = (uint16_t)(err_data * 32768);
    else
        gain = (uint16_t)(err_data * 32768 + 65536);

    //����У����
    EM_Set_PAGAIN(gain);
    g_EM_GainPara.P_Gain.B16 = gain;
    Emu_Adjust_Save();
}
/*********************************************************************************************************
*   �� �� ��: APHCAL_Adjust
*   ����˵��: �ǲ�У׼
*   ��    ��: ��
*   �� �� ֵ: ��
*********************************************************************************************************/
void APHCAL_Adjust(uint8_t *uBuf)
{
    uint8_t aphcal;
    double err_data;

    //У׼ǰ������Ĵ���
    EM_Set_APHCAL(0);
    DelayMs(1000);

    err_data = GetErrData(uBuf);                     //�������
    err_data = err_data * APHCAL_C / 50;             //��������Ϊ3675.52�Ĳ�����ʽ

    if (err_data >= 0)
        aphcal = (uint8_t)err_data;
    else
        aphcal = (uint8_t)(256 + err_data);

    //����У����
    EM_Set_APHCAL(aphcal);
    g_EM_GainPara.Phase_Gain.B16 = aphcal;
    Emu_Adjust_Save();
}
/*********************************************************************************************************
*   �� �� ��: PAOFF_Adjust
*   ����˵��: ����ʧ��У׼
*   ��    ��: ̨�幦��
*   �� �� ֵ: ��
*********************************************************************************************************/
void PAOFF_Adjust(uint8_t *uBuf)
{
    double err_data;
    uint16_t gain;
    B32_B08 temp32_p;
    B32_B08 temp32;

    Bcd2Hex_4(uBuf, temp32_p.B08);                  //̨�幦��
    //У׼ǰ������Ĵ���
    EM_Set_PAOFF(0);

    err_data = GetErrData(uBuf);                    //�������
    if (err_data >= 0)
    {
        temp32.B32 = (double)temp32_p.B32 * err_data / 32;
        temp32.B32 = (~temp32.B32) + 1;
    }
    else
    {
        temp32.B32 = (double)temp32_p.B32 * (-err_data) / 16;
    }
    gain = (uint16_t)temp32.B32;

    //����У����
    EM_Set_PAOFF(gain);
    g_EM_GainPara.Paoff_Gain.B16 = gain;
    Emu_Adjust_Save();
}
/*********************************************************************************************************
*   �� �� ��: Energy_Save()
*   ����˵��: �������������ݱ���
*   ��    ��: ��
*   �� �� ֵ: ��
*********************************************************************************************************/
void Energy_Save(void)
{
    IAP_WriteEnergy(&g_EP_Data);
    //EEP_WriteStr(EE_DI_ADDR, (uint8_t*)g_EP_Data.energy.B08, sizeof(g_EP_Data));
}
/*********************************************************************************************************
*   �� �� ��: Energy_Reset()
*   ����˵��: �����������������
*   ��    ��: ��
*   �� �� ֵ: ��
*********************************************************************************************************/
void Energy_Reset(void)
{
    g_EP_Data.energy.B32 = 0;
    g_EP_Data.pulse = 0;
    IAP_WriteEnergy(&g_EP_Data);
    //EEP_WriteStr(EE_DI_ADDR, (uint8_t*)g_EP_Data.energy.B08, sizeof(g_EP_Data));
}
/*********************************************************************************************************
*   �� �� ��: Energy_Add()
*   ����˵��: �����ۼӣ���С����0.01KWh.��1s�������е��á�
*   ��    ��: 
*   �� �� ֵ: ��
********************************************************************************************************/
void Energy_Add(void)
{
    //g_EP_Data.pulse += pulse_cnt;
    if (g_EP_Data.pulse < MINOR_PULSE_CNT)
        return;
    g_EP_Data.pulse -= MINOR_PULSE_CNT;
    g_EP_Data.energy.B32++;
    if (g_EP_Data.energy.B32 > 99999999)        //���ܴ���999999.99
    {
        //Energy_Reset();
    }
    else
    {
        //Energy_Save();
    }
}
/*********************************************************************************************************
*   �� �� ��: Emu_Adjust_Save()
*   ����˵��: ��У�����ݱ��浽EEPROM
*   ��    ��: ��
*   �� �� ֵ: ��
********************************************************************************************************/
void Emu_Adjust_Save(void)
{
    IAP_ErasePage(EMU_DATA_PA);
    IAP_WriteUGAIN(g_EM_GainPara.U_Gain.B16);
    IAP_WriteIGAIN(g_EM_GainPara.I_Gain.B16);
    IAP_WritePAGAIN(g_EM_GainPara.P_Gain.B16);
    IAP_WriteAPHCAL(g_EM_GainPara.Phase_Gain.B16);
    IAP_WritePAOFF(g_EM_GainPara.Paoff_Gain.B16);
    
    g_EM_GainPara.Check_Sum.B16 = SumCheck(g_EM_GainPara.U_Gain.B08, EE_CHECK_SUM*2);
    IAP_WriteCHECKSUM(g_EM_GainPara.Check_Sum.B16);
    gGainPrint = 1;

    //EEP_WriteStr(EE_ADJ_BASEADDR, g_EM_GainPara.U_Gain.B08, EE_PARAM_SUM*2);
    //EEP_WriteStr(EE_ADJ_BASEADDR+EE_BACKUPS_OFFSET, g_EM_GainPara.U_Gain.B08, EE_PARAM_SUM*2);
}

void EMU_print(void)
{
    if(gGainPrint)
    {
        uint8_t buf[UART_BUF_LEN] = {0};
        gGainPrint = 0;
        sprintf((char*)buf,"U=%X,I=%x,P=%x,PhG=%x,PoG=%x\r\n",
            g_EM_GainPara.U_Gain.B16,
            g_EM_GainPara.I_Gain.B16,
            g_EM_GainPara.P_Gain.B16,
            g_EM_GainPara.Phase_Gain.B16,
            g_EM_GainPara.Paoff_Gain.B16);
        RS485_Send_DataToBuf(buf,strlen((char*)buf));
    }
    else if(gEMUprint)
    {
        uint8_t buf[UART_BUF_LEN] = {0};
        sprintf((char*)buf,"NL%d,U%d,I%d,P%d,F%d,EP%d\r\n",EM->ESR.NO_LOAD,Get_URMS(),Get_IRMS(),Get_PRMS(),Get_Factor(),g_EP_Data.pulse);//g_EP_Data.energy.B32
        RS485_Send_DataToBuf(buf,strlen((char*)buf));
    }
    //sprintf(buf,"EM->ESR.NO_LOAD=%X,URMS=%x,IRMS=%x,PRMS=%x,AE=%x\r\n",EM->ESR.NO_LOAD,Get_URMS(),Get_IRMS(),Get_PRMS(),EM_Get_AE());
    //sprintf(buf,"EM->ESR.NO_LOAD=%X,URMS=%x,u_gain=%x\r\n",EM->ESR.NO_LOAD,Get_URMS(),g_u_gain);

}
/*********************************************************************************************************
*   �� �� ��: ReadUIP()
*   ����˵��: ������оƬ����
*   ��    ��: ��
*   �� �� ֵ: ��
********************************************************************************************************/
void Read_UIP(void)
{
    B32_B08 temp32;

    /***********************Ƶ��**************************/
    temp32.B32 = Get_FRQ();
    //Hex2Bcd(temp32.B32, g_Emu_Data.Freq.B08, 4);
    g_Emu_Data.Freq.B32 = temp32.B32;
    /******************* ��ѹ��Чֵ *********************/
    temp32.B32 = Get_URMS();
    //Hex2Bcd(temp32.B08, g_Emu_Data.U.B08, 4);
    g_Emu_Data.U.B32 = temp32.B32;

    if(EM->ESR.NO_LOAD == 1)     //����Ǳ�������������ʣ�����������ʾΪ0
    {
        g_Emu_Data.I.B32 = 0;
        g_Emu_Data.P.B32 = 0;
        g_Emu_Data.Fac.B32 = 0;
    }
    else
    {
        /******************* ����  ********************/
        temp32.B32 = Get_IRMS();
        //Hex2Bcd(temp32.B08, g_Emu_Data.I.B08, 4);           //3λС��
        g_Emu_Data.I.B32 = temp32.B32;
        /**********************����********************/
        temp32.B32 = Get_PRMS();
        //Hex2Bcd(temp32.B08, g_Emu_Data.P.B08, 4);           //4λС��
        g_Emu_Data.P.B32 = temp32.B32;
        /******************* ��������******************/
        temp32.B32 = Get_Factor();
        //Hex2Bcd(temp32.B08, g_Emu_Data.Fac.B08, 4);
        g_Emu_Data.Fac.B32 = temp32.B32;
    }
}
/********************************************************************************************************
*   �� �� ��: Emu_Adjust_Check
*   ����˵��: ��֤����У׼�Ĵ�����ֵ�Ƿ���У׼�����Ƿ�һ�£�����һ������д
*   ��    ��:  ��
*   �� �� ֵ:  ��
*******************************************************************************************************/
void Emu_Adjust_Check(void)
{
    B16_B08 check;
    //EM_GainPara_TypeDef *ptr;
    uint16_t temp;

    check.B16 = SumCheck(g_EM_GainPara.U_Gain.B08, EE_CHECK_SUM*2);
    temp = g_EM_GainPara.Check_Sum.B16;
    
    if (temp != check.B16)              //ram����
    {
        Emu_GainRead();
        check.B16 = SumCheck(g_EM_GainPara.U_Gain.B08, EE_CHECK_SUM*2);
        temp = g_EM_GainPara.Check_Sum.B16;
        if (temp != check.B16)          //eeprom1����
        {
            Emu_GainRead();
            check.B16 = SumCheck(g_EM_GainPara.U_Gain.B08, EE_CHECK_SUM*2);
            temp = g_EM_GainPara.Check_Sum.B16;
            if (temp != check.B16)      //eeprom2����
            {
                g_EM_GainPara.U_Gain.B16 = 0;
                g_EM_GainPara.I_Gain.B16 = 0;
                g_EM_GainPara.P_Gain.B16 = 0;
                g_EM_GainPara.Phase_Gain.B16 = 0;
                g_EM_GainPara.Paoff_Gain.B16 = 0;
                g_EM_GainPara.Check_Sum.B16 = 0;
            }
        }
    }

    if (g_EM_GainPara.P_Gain.B16 != EM_Get_PAGAIN())
    {
        EM_Set_PAGAIN(g_EM_GainPara.P_Gain.B16);
    }

    if (g_EM_GainPara.U_Gain.B16 != EM_Get_UGAIN())
    {
        EM_Set_UGAIN(g_EM_GainPara.U_Gain.B16);
    }

    if (g_EM_GainPara.I_Gain.B16 != EM_Get_IAGAIN())
    {
        EM_Set_IAGAIN(g_EM_GainPara.I_Gain.B16);
    }

    if (g_EM_GainPara.Phase_Gain.B16 != EM_Get_APHCAL())
    {
        EM_Set_APHCAL(g_EM_GainPara.Phase_Gain.B16);
    }
}

