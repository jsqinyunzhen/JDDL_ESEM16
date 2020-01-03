#include "includes.h"
#include <stdio.h>

EM_GainPara_TypeDef g_EM_GainPara={0};
EP_Data_TypeDef g_EP_Data= {0};
MeterVariable_TypeDef g_Emu_Data={0};
uint8_t gGainPrint = 0;
uint8_t gEMUprint = 0;

//const EM_GainPara_TypeDef ADJ_DEFAULT = {0xFFF3, 0x3c4, 0x240, 0x00, 0xffe6, 0x05DD};         //默认校准参数

/*********************************************************************************************************
*   函 数 名: Init_User_EMU
*   功能说明: em初始化
*   形    参：无
*   返 回 值: 无
*********************************************************************************************************/
void Init_User_EMU(void)
{
    //uint8_t buf_Adjust[2];

    EMU_Init();

#if 1                                           //从E2取出校准值 

    GloableVar_Init();
    EM_Config();

#else                                           //台体校准

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
*   函 数 名: EM_Init
*   功能说明: em初始化
*   形    参：无
*   返 回 值: 无
*********************************************************************************************************/
void EMU_Init(void)
{
    EM_InitTypeDef EM_InitStruct;
    EM_ParaTypeDef EM_ParaStruct;

    EM_RegUnLock();
    EM_InitStruct.EM_PGA1_Config = EM_PGA1_X16;                 //PGA1增益选择
    EM_InitStruct.EM_PGA2_Config = EM_PGA2_X2;                  //PGA2增益选择
    EM_InitStruct.EM_ADC1_Config = ENABLE;                      //ADC1使能
    EM_InitStruct.EM_ADC2_Config = ENABLE;                      //ADC2使能
    EM_InitStruct.EM_BGR_Config = ENABLE;                       //Bandgap使能
    EM_InitStruct.EM_CHOP1_Config = EM_CHOP_EN;                 //chop1时钟使能
    EM_InitStruct.EM_CHOP2_Config = EM_CHOP_EN;                 //chop2时钟使能
    EM_InitStruct.EM_HPF_Config = ENABLE;                       //HPF使能
    EM_InitStruct.EM_EM_EN_Config = ENABLE;                     //EM使能
    EM_InitStruct.EM_RMS_EN_Config = ENABLE;                    //RMS使能
    EM_InitStruct.EM_CF_EN_Config = ENABLE;                     //CF使能
    EM_InitStruct.EM_EA_EN_Config = ENABLE;                     //EA使能
    EM_InitStruct.EM_APPF_EN_Config = ENABLE;                   //APPF使能
    EM_InitStruct.EM_ZX_EN_Config = ENABLE;                     //ZX使能
    EM_InitStruct.EM_FP_EN_Config = ENABLE;                     //FP使能
    EM_InitStruct.EM_ERCLR_Config = EM_ERCLR_Clr;               //ERCLR模式
    EM_InitStruct.EM_CRC1_EN_Config = DISABLE;                  //CRC1使能
    EM_InitStruct.EM_CRC2_EN_Config = DISABLE;                  //CRC2使能
    EM_InitStruct.EM_CF1SEL_Config = CF_SEL_OutputPos;          //CF1选择
    EM_InitStruct.EM_CF1MOD_Config = CF_MOD_AbsEnergy;          //CF1模式
    EM_InitStruct.EM_ZXSEL_Config = ZX_SEL_PosOutput;           //ZX选择
    EM_InitStruct.EM_POFF_MOD_Config = DISABLE;                 //POFF模式
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
*   函 数 名: GloableVar_Init
*   功能说明: 读EEPROM中校准参数，如果参数都为0xFF，则认为是芯片第一次上电，加载默认值到EEPROM和RAM中。
*   形    参：无
*   返 回 值: 无
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
*   函 数 名: EM_Config
*   功能说明: EM校准值等初始化设置
*   形    参: 写入寄存器值
*   返 回 值: 无
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
*   函 数 名: Get_URMS
*   功能说明: 得到测量电压值
*   形    参: 无
*   返 回 值: 实际电压值(扩大10倍)
*********************************************************************************************************/
uint32_t Get_URMS(void)
{
    uint32_t urms;

    urms = EM_Get_URMS();
    urms = urms *_U_C;
    return urms;
}
/*********************************************************************************************************
*   函 数 名: Get_IRMS
*   功能说明: 得到实际电流值
*   形    参: 无
*   返 回 值: 实际电流值(扩大1000倍)
*********************************************************************************************************/
uint32_t Get_IRMS(void)
{
    uint32_t irms;

    irms = EM_Get_IARMS();
    irms = irms * _I_C;
    return irms;
}
/*********************************************************************************************************
*   函 数 名: Get_FRQ
*   功能说明: 得到实际频率
*   形    参: 无
*   返 回 值: 实际频率
*********************************************************************************************************/
uint16_t Get_FRQ(void)
{
    uint16_t hz;

    hz = EM_Get_FRQ();
    hz = hz * 100 / 256;
    return (uint16_t)hz;
}
/*********************************************************************************************************
*   函 数 名: Get_PHASE
*   功能说明: 得到实际相角
*   形    参: 无
*   返 回 值: 实际相角
*********************************************************************************************************/
uint16_t Get_PHASE(void)
{
    uint16_t ph;

    ph = EM_Get_APHASE();
    ph = ph / (1<<7);

    return ph;
}
/*********************************************************************************************************
*   函 数 名: Get_PRMS
*   功能说明: 得到实际功率
*   形    参: 无
*   返 回 值: 功率值,单位：(0.0001w)
*********************************************************************************************************/
uint32_t Get_PRMS(void)
{
    uint32_t prms;

    prms = EM_Get_PA();         //（有符号32位）
    if (prms & 0x80000000)      //负数
    {
        prms = ~prms + 1;
    }
    prms = prms * _P_C ;
    return prms;
}
/*********************************************************************************************************
*   函 数 名: Get_Factor
*   功能说明: 得到功率因数
*   形    参: 无
*   返 回 值: 功率因数* 1000
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
*   函 数 名: GetErrData
*   功能说明: 计量芯片常数 (实际测量功率-台体真实功率)/(台体真实功率)   
*   形    参: 无
*   返 回 值: 
*********************************************************************************************************/
double GetErrData(uint8_t *uBuf)
{
    B32_B08 temp32_p;                      //台体功率
    uint32_t power;
    double err_data;                      //功率误差

    Bcd2Hex_4(uBuf, temp32_p.B08);          //当前功率转换成HEX 
    power = Get_PRMS();
    err_data = (double)power / temp32_p.B32 - 1;    //误差计算 (实际测量功率-台体真实功率)/(台体真实功率)   
    return err_data;
}
/*********************************************************************************************************
*   函 数 名: UGAIN_Adjust
*   功能说明: 电压校准
*   形    参: 台体实际电压值
*   返 回 值: 无
*********************************************************************************************************/
void UGAIN_Adjust(uint8_t *uBuf)
{
    uint16_t u_gain;
    uint32_t v_data;
    double err_data;
    B32_B08 temp32_Un;                                  //台体电压

    Bcd2Hex_4(uBuf, temp32_Un.B08);
    //校准前，清除寄存器
    EM_Set_UGAIN(0);
    DelayMs(1000);                                      //要增加间隔时间。
    //v_data = EM_Get_UGAIN();                            //读电压有效值寄存器
    v_data =EM_Get_URMS();

    err_data = temp32_Un.B32 / _U_C / v_data - 1;       //误差 = (U台体 - U测量)/U测量
    if (err_data >= 0)                                  //转换成补码形式 详见数据手册/应用笔记
    {
        u_gain = (uint16_t)(err_data * 32768);
    }
    else
    {
        u_gain = (uint16_t)(err_data * 32768 + 65536);
    }

    //保存校表结果
    EM_Set_UGAIN(u_gain);
    g_EM_GainPara.U_Gain.B16 = u_gain;
    Emu_Adjust_Save();                                      //EEPROM保存
}
/*********************************************************************************************************
*   函 数 名: IAGAIN_Adjust
*   功能说明: 电流校准
*   形    参: 台体实际电流值
*   返 回 值: 无
*********************************************************************************************************/
void IAGAIN_Adjust(uint8_t *uBuf)
{
    uint16_t i_gain;
    uint32_t i_data;
    double err_data;
    B32_B08 temp32_Ia;                               //台体电流

    Bcd2Hex_4(uBuf, temp32_Ia.B08);
    //校准前，清除寄存器
    EM_Set_IAGAIN(0);

    DelayMs(1000);
    i_data = EM_Get_IARMS();                            //读电流有效值寄存器
    err_data = temp32_Ia.B32 / _I_C / i_data - 1;       //误差 = (I台体-I测量)/I测量
    if (err_data >= 0)
    {
        i_gain = (uint16_t)(err_data * 32768);
    }
    else
    {
        i_gain = (uint16_t)(err_data * 32768 + 65536);
    }

    //保存校表结果
    EM_Set_IAGAIN(i_gain);
    g_EM_GainPara.I_Gain.B16 = i_gain;
    Emu_Adjust_Save();
}
/*********************************************************************************************************
*   函 数 名: PAGAIN_Adjust
*   功能说明: 有功功率校准
*   形    参: 台体实际功率值
*   返 回 值: 无
*********************************************************************************************************/
void PAGAIN_Adjust(uint8_t *uBuf)
{
    double err_data;
    uint32_t gain;

    //校准前，清除寄存器
    EM_Set_PAGAIN(0);

    err_data = GetErrData(uBuf);                //计算误差
    err_data = -err_data / (1 + err_data);      //误差调整为G-1 = (1/(1+err_data))-1
    //将(G-1)调整为*2^15的补码形式  详见数据手册/应用笔记
    if (err_data >= 0)
        gain = (uint16_t)(err_data * 32768);
    else
        gain = (uint16_t)(err_data * 32768 + 65536);

    //保存校表结果
    EM_Set_PAGAIN(gain);
    g_EM_GainPara.P_Gain.B16 = gain;
    Emu_Adjust_Save();
}
/*********************************************************************************************************
*   函 数 名: APHCAL_Adjust
*   功能说明: 角差校准
*   形    参: 无
*   返 回 值: 无
*********************************************************************************************************/
void APHCAL_Adjust(uint8_t *uBuf)
{
    uint8_t aphcal;
    double err_data;

    //校准前，清除寄存器
    EM_Set_APHCAL(0);
    DelayMs(1000);

    err_data = GetErrData(uBuf);                     //计算误差
    err_data = err_data * APHCAL_C / 50;             //将误差调整为3675.52的补码形式

    if (err_data >= 0)
        aphcal = (uint8_t)err_data;
    else
        aphcal = (uint8_t)(256 + err_data);

    //保存校表结果
    EM_Set_APHCAL(aphcal);
    g_EM_GainPara.Phase_Gain.B16 = aphcal;
    Emu_Adjust_Save();
}
/*********************************************************************************************************
*   函 数 名: PAOFF_Adjust
*   功能说明: 功率失调校准
*   形    参: 台体功率
*   返 回 值: 无
*********************************************************************************************************/
void PAOFF_Adjust(uint8_t *uBuf)
{
    double err_data;
    uint16_t gain;
    B32_B08 temp32_p;
    B32_B08 temp32;

    Bcd2Hex_4(uBuf, temp32_p.B08);                  //台体功率
    //校准前，清除寄存器
    EM_Set_PAOFF(0);

    err_data = GetErrData(uBuf);                    //计算误差
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

    //保存校表结果
    EM_Set_PAOFF(gain);
    g_EM_GainPara.Paoff_Gain.B16 = gain;
    Emu_Adjust_Save();
}
/*********************************************************************************************************
*   函 数 名: Energy_Save()
*   功能说明: 电量、脉冲数据保存
*   形    参: 无
*   返 回 值: 无
*********************************************************************************************************/
void Energy_Save(void)
{
    IAP_WriteEnergy(&g_EP_Data);
    //EEP_WriteStr(EE_DI_ADDR, (uint8_t*)g_EP_Data.energy.B08, sizeof(g_EP_Data));
}
/*********************************************************************************************************
*   函 数 名: Energy_Reset()
*   功能说明: 清除电量、脉冲数据
*   形    参: 无
*   返 回 值: 无
*********************************************************************************************************/
void Energy_Reset(void)
{
    g_EP_Data.energy.B32 = 0;
    g_EP_Data.pulse = 0;
    IAP_WriteEnergy(&g_EP_Data);
    //EEP_WriteStr(EE_DI_ADDR, (uint8_t*)g_EP_Data.energy.B08, sizeof(g_EP_Data));
}
/*********************************************************************************************************
*   函 数 名: Energy_Add()
*   功能说明: 电量累加，最小精度0.01KWh.在1s的任务中调用。
*   形    参: 
*   返 回 值: 无
********************************************************************************************************/
void Energy_Add(void)
{
    //g_EP_Data.pulse += pulse_cnt;
    if (g_EP_Data.pulse < MINOR_PULSE_CNT)
        return;
    g_EP_Data.pulse -= MINOR_PULSE_CNT;
    g_EP_Data.energy.B32++;
    if (g_EP_Data.energy.B32 > 99999999)        //电能大于999999.99
    {
        //Energy_Reset();
    }
    else
    {
        //Energy_Save();
    }
}
/*********************************************************************************************************
*   函 数 名: Emu_Adjust_Save()
*   功能说明: 将校表数据保存到EEPROM
*   形    参: 无
*   返 回 值: 无
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
*   函 数 名: ReadUIP()
*   功能说明: 读计量芯片数据
*   形    参: 无
*   返 回 值: 无
********************************************************************************************************/
void Read_UIP(void)
{
    B32_B08 temp32;

    /***********************频率**************************/
    temp32.B32 = Get_FRQ();
    //Hex2Bcd(temp32.B32, g_Emu_Data.Freq.B08, 4);
    g_Emu_Data.Freq.B32 = temp32.B32;
    /******************* 电压有效值 *********************/
    temp32.B32 = Get_URMS();
    //Hex2Bcd(temp32.B08, g_Emu_Data.U.B08, 4);
    g_Emu_Data.U.B32 = temp32.B32;

    if(EM->ESR.NO_LOAD == 1)     //发生潜动，电流，功率，功率因数显示为0
    {
        g_Emu_Data.I.B32 = 0;
        g_Emu_Data.P.B32 = 0;
        g_Emu_Data.Fac.B32 = 0;
    }
    else
    {
        /******************* 电流  ********************/
        temp32.B32 = Get_IRMS();
        //Hex2Bcd(temp32.B08, g_Emu_Data.I.B08, 4);           //3位小数
        g_Emu_Data.I.B32 = temp32.B32;
        /**********************功率********************/
        temp32.B32 = Get_PRMS();
        //Hex2Bcd(temp32.B08, g_Emu_Data.P.B08, 4);           //4位小数
        g_Emu_Data.P.B32 = temp32.B32;
        /******************* 功率因数******************/
        temp32.B32 = Get_Factor();
        //Hex2Bcd(temp32.B08, g_Emu_Data.Fac.B08, 4);
        g_Emu_Data.Fac.B32 = temp32.B32;
    }
}
/********************************************************************************************************
*   函 数 名: Emu_Adjust_Check
*   功能说明: 验证计量校准寄存器的值是否与校准参数是否一致，若不一致则重写
*   形    参:  无
*   返 回 值:  无
*******************************************************************************************************/
void Emu_Adjust_Check(void)
{
    B16_B08 check;
    //EM_GainPara_TypeDef *ptr;
    uint16_t temp;

    check.B16 = SumCheck(g_EM_GainPara.U_Gain.B08, EE_CHECK_SUM*2);
    temp = g_EM_GainPara.Check_Sum.B16;
    
    if (temp != check.B16)              //ram出错
    {
        Emu_GainRead();
        check.B16 = SumCheck(g_EM_GainPara.U_Gain.B08, EE_CHECK_SUM*2);
        temp = g_EM_GainPara.Check_Sum.B16;
        if (temp != check.B16)          //eeprom1出错
        {
            Emu_GainRead();
            check.B16 = SumCheck(g_EM_GainPara.U_Gain.B08, EE_CHECK_SUM*2);
            temp = g_EM_GainPara.Check_Sum.B16;
            if (temp != check.B16)      //eeprom2出错
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

