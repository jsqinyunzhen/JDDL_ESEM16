#ifndef _EMU_H
#define _EMU_H

#include "esem16.h"
#include "string.h"

#define VREF                1.3                         //基准电压
#define Gu                  2                           //电压采样增益
#define Gi                  16                          //电流采样增益
#define APHCAL_C            (183776.2985)               //常数
#define K_V                 1081                        //电压通道分压比 采样电阻/分压电阻
#define R_I                 0.002                       //电流采样电阻（欧）
#define MC                  1200                        //电表常数imp/kWh
#define _PFSET_C            2359296000000000            //有功功率校准常数(P93)
#define MINOR_PULSE_CNT     (MC/10)                     //最小精度0.01KWh

#if 0

#define VREF                1.3                         //基准电压
#define Gu                  2                           //电压采样增益
#define Gi                  16                          //电流采样增益
#define APHCAL_C            (183776.2985)               //常数
#define K_V                 1081                        //电压通道分压比 采样电阻/分压电阻
#define R_I                 0.002                       //电流采样电阻（欧）
#define MC                  1200                        //电表常数imp/kWh
#define _PFSET_C            2359296000000000            //有功功率校准常数(P93)
#define MINOR_PULSE_CNT     (MC/10)                     //最小精度0.01KWh

#endif
/**********************EEPROM 定义**************************/
#define EE_ADJ_BASEADDR         0x00            //计量参数保存地址
#define EE_BACKUPS_OFFSET       0x20            //计量参数备份地址
#define EE_DI_ADDR              0x40            //电能数据保存地址

/*********************************************************************************************************
电压计算公式    单位：(0.1V)
 u = (DATA * K_V * VREF)/(Gu*2^24)  DATA为电压有效值寄存器值
*********************************************************************************************************/
#define _U_C        ((double)10.0*VREF*K_V/Gu/(1<<24))

/*********************************************************************************************************
电流计算公式    单位：(0.001A)
 i = (DATA * VREF)/(R_I*Gu*2^24)    DATA为电流有效值寄存器值
*********************************************************************************************************/
#define _I_C        ((double)1000.0*VREF/R_I/Gi/(1<<24))

/*********************************************************************************************************
功率计算公式    单位：(0.0001w)
 p = (DATA *K_V*VREF*VREF )/(R_I*Gi*Gu*2^31)   DATA为有功率寄存器值
*********************************************************************************************************/
#define _P_C        ((double)10000*VREF*VREF*K_V/R_I/Gi/Gu/(1<<21)/(1<<10))

/*********************************************************************************************************
高频脉冲常数    (P93)
Vu/Un = 1/K_V   Via/Ib = R_I
 PFSET =  (_PFSET_C*Gi*Gu*R_I)/(K_V*MC*VREF*VREF)
*********************************************************************************************************/
#define PFSET_DATA      ((double)_PFSET_C*Gi*Gu*R_I/K_V/MC/(VREF*VREF))

/*********************************************************************************************************
启动门限功率
 启动功率 = (K_V*VREF*VREF)/(256*R_I*Gu*Gi)
 
#define P_START         7       //启动功率7w
*********************************************************************************************************/
#define P_START         1       //启动功率7w
#define PSTART_DATA     ((double)P_START*R_I*Gu*Gi/K_V/(VREF*VREF)*(1<<24))

void Init_User_EMU(void);
void EMU_Init(void);
void GloableVar_Init(void);
void EM_Config(void);
uint32_t Get_URMS(void);
uint32_t Get_IRMS(void);
uint16_t Get_FRQ(void);
uint16_t Get_PHASE(void);
uint32_t Get_PRMS(void);
uint16_t Get_Factor(void);
double GetErrData(uint8_t *uBuf);
void UGAIN_Adjust(uint8_t *uBuf);
void IAGAIN_Adjust(uint8_t *uBuf);
void PAGAIN_Adjust(uint8_t *uBuf);
void APHCAL_Adjust(uint8_t *uBuf);
void PAOFF_Adjust(uint8_t *uBuf);
void Energy_Save(void);
void Energy_Reset(void);
void Energy_Add(void);
void Emu_Adjust_Save(void);
void Read_UIP(void);
void Emu_Adjust_Check(void);

void EMU_print(void);
#endif


