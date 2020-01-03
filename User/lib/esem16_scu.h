#ifndef __ESEM16_SCU_H
#define __ESEM16_SCU_H

/* Includes ------------------------------------------------------------------*/
#include "esem16.h"
#include "system_esem16.h"

typedef struct
{
    FunctionalState MOSC_EN;                              /*!< Configures 深度睡眠主竞争使能位*/
    FunctionalState CLKFLT_EN;                          /*!< Configures 系统时钟滤波使能位*/
    FunctionalState EM_CLKEN;                               /*!< Configures 计量时钟使能位*/    
    uint8_t SYSCLK_SSE;                                         /*!< Configures 系统时钟选择位*/        
}SYSCLK_InitTypeDef;

/* 时钟选择 */
typedef enum
{
    SCU_SYSCLKS_EXOSC = 0x0 ,      //外部主晶振作为主时钟
    SCU_SYSCLKS_WDCLK = 0x1 ,      //WDT时钟作为主时钟
}SCU_TYPE_SYSCLK;

/* 外设时钟 */
typedef enum
{
    SCU_PCLKEN_SCU     = 0x00000001,
    SCU_PCLKEN_GPIO    = 0x00000002,
    SCU_PCLKEN_IAP     = 0x00000004,
    SCU_PCLKEN_ADC     = 0x00000010,
    SCU_PCLKEN_WDT     = 0x00000080,
    SCU_PCLKEN_T16N0   = 0x00000100,
    SCU_PCLKEN_T16N1   = 0x00000200,
    SCU_PCLKEN_T32N0   = 0x00001000,
    SCU_PCLKEN_UART0   = 0x00010000,
    SCU_PCLKEN_EM      = 0x00100000,
}SUC_TYPE_PCLK;

/* NMI不可屏蔽中断选择 */
typedef enum
{
    SCU_NMIC_IRQ0_GPIO0         = 0x00,
    SCU_NMIC_IRQ1_GPIO1         = 0x01,
    SCU_NMIC_IRQ2_GPIO2         = 0x02,
    SCU_NMIC_IRQ3_GPIO3         = 0x03,
    SCU_NMIC_IRQ4_GPIO4         = 0x04,
    SCU_NMIC_IRQ5_GPIO5         = 0x05,
    SCU_NMIC_IRQ6_GPIO6         = 0x06,
    SCU_NMIC_IRQ7_GPIO7         = 0x07,
    SCU_NMIC_IRQ8_GPIO8         = 0x08,
    SCU_NMIC_IRQ9_GPIO9         = 0x09,
    SCU_NMIC_IRQ10_GPIO10       = 0x0A,
    SCU_NMIC_IRQ11_GPIO11       = 0x0B,
    SCU_NMIC_IRQ12_T16N0        = 0x0C,
    SCU_NMIC_IRQ13_T16N1        = 0x0D,
    SCU_NMIC_IRQ14              = 0x0E,
    SCU_NMIC_IRQ15              = 0x0F,
    SCU_NMIC_IRQ16_T32N0        = 0x10,
    SCU_NMIC_IRQ17              = 0x11,
    SCU_NMIC_IRQ18              = 0x12,
    SCU_NMIC_IRQ19              = 0x13,
    SCU_NMIC_IRQ20_WDT          = 0x14,
    SCU_NMIC_IRQ21              = 0x15,
    SCU_NMIC_IRQ22              = 0x16,
    SCU_NMIC_IRQ23_ADC          = 0x17,
    SCU_NMIC_IRQ24              = 0x18,
    SCU_NMIC_IRQ25              = 0x19,
    SCU_NMIC_IRQ26              = 0x1A,
    SCU_NMIC_IRQ27_UART0TX      = 0x1B,
    SCU_NMIC_IRQ28_UART0RX      = 0x1C,
    SCU_NMIC_IRQ29              = 0x1D,
    SCU_NMIC_IRQ30              = 0x1E,
    SCU_NMIC_IRQ31_EM           = 0x1F,
}SCU_TYPE_NMIC;

/* PWRC复位状态寄存器标志位 */
typedef enum
{
    SCU_PWRC_FLAG_PORF     = 0x00000001,        //POR总复位标志
    SCU_PWRC_FLAG_RCPORF   = 0x00000004,        //PORRC复位标志
    SCU_PWRC_FLAG_BORF     = 0x00000008,        //PORRST复位标志
    SCU_PWRC_FLAG_WDTF     = 0x00000010,        //WDT复位标志
    SCU_PWRC_FLAG_MRSTF    = 0x00000020,        //MRST复位标志
    SCU_PWRC_FLAG_SOFTRSTF = 0x00000040,        //SOFT复位标志位
    SCU_PWRC_FLAG_PORLOST  = 0x00000080,        //软件丢失标志位
}SCU_TYPE_PWRC;

/* 测试模式 */
typedef enum
{
    SCU_TESTCON_GPIO     = 0,        //GPIO模式
    SCU_TESTCON_SYSCLK   = 1,        //系统时钟模式
    SCU_TESTCON_FLASH    = 2,        //FLASH模式
    SCU_TESTCON_EM       = 3,        //EM模式
    SCU_TESTCON_SRAM1    = 4,        //SRAM1模式
    SCU_TESTCON_SRAM2    = 5,        //SRAM2模式
    SCU_TESTCON_SRAM3    = 6,        //SRAM3模式
    SCU_TESTCON_SRAM4    = 7,        //SRAM4模式
}SCU_TYPE_TESTCON;

/* SCU写保护控制 */
#define SCU_RegUnLock()         (SCU->PROT.Word = 0x55AA6996)
#define SCU_RegLock()           (SCU->PROT.Word = 0x00000000)

/* FLASH访问等待时间选择 */
#define SCU_FlashWait_2Tclk()   (SCU->FLASHW.ACCT = 0x0)
#define SCU_FlashWait_3Tclk()   (SCU->FLASHW.ACCT = 0x1)
#define SCU_FlashWait_4Tclk()   (SCU->FLASHW.ACCT = 0x2)
#define SCU_FlashWait_5Tclk()   (SCU->FLASHW.ACCT = 0x3)
#define SCU_FlashWait_6Tclk()   (SCU->FLASHW.ACCT = 0x4)
#define SCU_FlashWait_7Tclk()   (SCU->FLASHW.ACCT = 0x5)
#define SCU_FlashWait_8Tclk()   (SCU->FLASHW.ACCT = 0x6)
#define SCU_FlashWait_9Tclk()   (SCU->FLASHW.ACCT = 0x7)
#define SCU_FlashWait_10Tclk()  (SCU->FLASHW.ACCT = 0x8)
#define SCU_FlashWait_11Tclk()  (SCU->FLASHW.ACCT = 0x9)
#define SCU_FlashWait_12Tclk()  (SCU->FLASHW.ACCT = 0xA)
#define SCU_FlashWait_13Tclk()  (SCU->FLASHW.ACCT = 0xB)
#define SCU_FlashWait_14Tclk()  (SCU->FLASHW.ACCT = 0xC)
#define SCU_FlashWait_15Tclk()  (SCU->FLASHW.ACCT = 0xD)
#define SCU_FlashWait_16Tclk()  (SCU->FLASHW.ACCT = 0xE)
#define SCU_FlashWait_17Tclk()  (SCU->FLASHW.ACCT = 0xF)

void SCU_Init(void);
void SCU_SYSCLKConfig(SCU_TYPE_SYSCLK SCU_SYSCLK_Source);
void SCU_EXOSC_DeepSleep_Cmd(FunctionalState NewState);
void SCU_CLKFLT_Cmd(FunctionalState NewState);
void SCU_EMCLK_Cmd(FunctionalState NewState);
void SCU_NMIC_Cmd(FunctionalState NewState);
void SCU_NMIC_Cofig(SCU_TYPE_NMIC SCU_NMI_CS);
FlagStatus SCU_Get_PWRC_Flag(SCU_TYPE_PWRC SCU_PWRC_FLAG);
FlagStatus SCU_Get_FAULTFLAG_Flag(void);
void SCU_Clear_FAULTFLAG_Flag(void);
void SCU_PCLK_Cmd(SUC_TYPE_PCLK SCU_PCLKx, FunctionalState NewState);
void SCU_PCLK_All_Enable(void);
void SCU_PCLK_All_Disable(void);
void SCU_Wakeuptime_Cmd(uint16_t time);
void SCU_Testcon_Cmd(SCU_TYPE_TESTCON type);
void SCU_VR0Cal_Bor_Cmd(uint16_t temp);
void SCU_VR0Cal_Iout_Cmd(uint16_t temp);
void SCU_VR1Cal_Bgr1_Cmd(uint16_t temp);
void SCU_VR1Cal_Bgr2_Cmd(uint16_t temp);
void SCU_VR1Cal_Ldo_Cmd(uint16_t temp);
void SCU_TEMPSCal_Vref1_Cmd(uint16_t temp);
void SCU_TEMPSCal_Vref2_Cmd(uint16_t temp);
void SCU_MCLKCal_XOSCRES_Cmd(uint16_t temp);
void SCU_MCLKCal_XOSCAMP_Cmd(uint16_t temp);
void SCU_MCLKCal_CLKFLT_Cmd(uint16_t temp);
void SCU_WDTCal_Cmd(uint16_t temp);
void SCU_AFECal_Cmd(uint16_t temp);
void SCU_ADCCal_Cmd(uint16_t temp);
#endif

/******************* (C) COPYRIGHT 2018 Eastsoft *****END OF FILE****/

