#ifndef _VARIABLE_H
#define _VARIABLE_H

extern volatile B32_B08 g_Energy ;	
extern const EM_GainPara_TypeDef ADJ_DEFAULT;
extern volatile uint8_t g_Tasks_Flag;
extern volatile uint16_t g_SysTick;

extern MeterVariable_TypeDef g_Emu_Data;
extern EM_GainPara_TypeDef g_EM_GainPara;
extern EP_Data_TypeDef g_EP_Data;

extern uint8_t g_RxDelayTimer;
extern uint32_t gId;
extern uint8_t gEMUprint;
extern uint8_t gGainPrint;
extern B32_B16 gCurrentUsedID;//设置id使用，记录当前被设置的id数
extern uint32_t gSecond;

/*
* 其他函数调用
*/
void MCU_Init(void);
void SYS_Init(void);

#endif

