#ifndef __ESEM16_H__
#define __ESEM16_H__


#define __I volatile const /* defines 'read only' permissions */
#define __O volatile /* defines 'write only' permissions */
#define __IO volatile /* defines 'read / write' permissions */


#define __CM0_REV 0 /* Core Revision r0p0 */
#define __NVIC_PRIO_BITS 2 /* ESEM16 uses 2 Bits for the Priority Levels */
#define __Vendor_SysTickConfig 0 /* Set to 1 if different SysTick Config is used */

typedef enum IRQn
{
	/****** Cortex-M0 Processor Exceptions Numbers ******************************************************/
	RST_IRQn = -15,
	NonMaskableInt_IRQn = -14,
	HardFault_IRQn = -13,
	SVC_IRQn = -5,
	PendSV_IRQn = -2,
	SysTick_IRQn = -1,
	GPIO0INT_IRQn = 0,
	GPIO1INT_IRQn = 1,
	GPIO2INT_IRQn = 2,
	GPIO3INT_IRQn = 3,
	GPIO4INT_IRQn = 4,
	GPIO5INT_IRQn = 5,
	GPIO6INT_IRQn = 6,
	GPIO7INT_IRQn = 7,
	GPIO8INT_IRQn = 8,
	GPIO9INT_IRQn = 9,
	GPIO10INT_IRQn = 10,
	GPIO11INT_IRQn = 11,
	T16N0INT_IRQn = 12,
	T16N1INT_IRQn = 13,
	Reserved0_IRQn = 14,
	Reserved1_IRQn = 15,
	T32N0INT_IRQn = 16,
	Reserved2_IRQn = 17,
	Reserved3_IRQn = 18,
	Reserved4_IRQn = 19,
	WDTINT_IRQn = 20,
	Reserved5_IRQn = 21,
	Reserved6_IRQn = 22,
	ADCINT_IRQn = 23,
	Reserved7_IRQn = 24,
	Reserved8_IRQn = 25,
	Reserved9_IRQn = 26,
	UART0TINT_IRQn = 27,
	UART0RINT_IRQn = 28,
	Reserved10_IRQn = 29,
	Reserved11_IRQn = 30,
	EMINT_IRQn = 31,
} IRQn_Type;


#include "core_cm0.h"
#include <stdint.h>


/******************************************************************************/
/*                              设备特殊寄存器结构定义                        */
/******************************************************************************/

/*   允许匿名结构和匿名联合    */
#pragma anon_unions

typedef union
{
	struct
	{
		uint32_t PROT: 1;
		uint32_t RESERVED0: 31;
	};
	uint32_t Word;
} SCU_PROT_Typedef;

typedef union
{
	struct
	{
		uint32_t EN: 1;
		uint32_t CS: 5;
		uint32_t RESERVED0: 26;
	};
	uint32_t Word;
} SCU_NMIC_Typedef;

typedef union
{
	struct
	{
		uint32_t PORF: 1;
		uint32_t RESERVED0: 1;
		uint32_t RCPORF: 1;
		uint32_t BORF: 1;
		uint32_t WDTRSTF: 1;
		uint32_t MRSTF: 1;
		uint32_t SOFT_RSTF: 1;
		uint32_t POR_LOST: 1;
		uint32_t RESERVED1: 24;
	};
	uint32_t Word;
} SCU_PWRC_Typedef;

typedef union
{
	struct
	{
		uint32_t FLAG: 1;
		uint32_t RESERVED0: 31;
	};
	uint32_t Word;
} SCU_FAULTFLAG_Typedef;

typedef union
{
	struct
	{
		uint32_t ACCT: 4;
		uint32_t RESERVED0: 28;
	};
	uint32_t Word;
} SCU_FLASHW_Typedef;

typedef union
{
	struct
	{
		uint32_t MOSC: 1;
		uint32_t FLT: 1;
		uint32_t RESERVED0: 1;
		uint32_t EM: 1;
		uint32_t RESERVED1: 3;
		uint32_t SSE: 1;
		uint32_t RESERVED2: 24;
	};
	uint32_t Word;
} SCU_SCLKEN_Typedef;

typedef union
{
	struct
	{
		uint32_t SCU: 1;
		uint32_t GPIO: 1;
		uint32_t IAP: 1;
		uint32_t RESERVED0: 1;
		uint32_t ADC: 1;
		uint32_t RESERVED1: 2;
		uint32_t WDT: 1;
		uint32_t T16N0: 1;
		uint32_t T16N1: 1;
		uint32_t RESERVED2: 2;
		uint32_t T32N0: 1;
		uint32_t RESERVED3: 3;
		uint32_t UATR0: 1;
		uint32_t RESERVED4: 3;
		uint32_t EM: 1;
		uint32_t RESERVED5: 11;
	};
	uint32_t Word;
} SCU_PCLKEN_Typedef;

typedef union
{
	struct
	{
		uint32_t VALUE: 10;
		uint32_t RESERVED0: 22;
	};
	uint32_t Word;
} SCU_WAKEUPTIME_Typedef;

typedef union
{
	struct
	{
		uint32_t SEL: 3;
		uint32_t RESERVED0: 29;
	};
	uint32_t Word;
} SCU_TESTCON_Typedef;

typedef union
{
	struct
	{
		uint32_t BOR: 8;
		uint32_t IOUT: 5;
		uint32_t RESERVED0: 19;
	};
	uint32_t Word;
} SCU_VRCAL0_Typedef;

typedef union
{
	struct
	{
		uint32_t BGR_R1CTL: 3;
		uint32_t RESERVED0: 1;
		uint32_t BGR_R2CTL: 3;
		uint32_t RESERVED1: 1;
		uint32_t LDO_CAL: 3;
		uint32_t RESERVED2: 21;
	};
	uint32_t Word;
} SCU_VRCAL1_Typedef;

typedef union
{
	struct
	{
		uint32_t XOSCRES: 4;
		uint32_t XOSCAMP: 4;
		uint32_t CLK_FLT_CAL: 2;
		uint32_t RESERVED0: 22;
	};
	uint32_t Word;
} SCU_MCLKCAL_Typedef;

typedef union
{
	struct
	{
		uint32_t WDT_CAL: 8;
		uint32_t RESERVED0: 24;
	};
	uint32_t Word;
} SCU_WDTCAL_Typedef;

typedef union
{
	struct
	{
		uint32_t VREF1_CAL: 3;
		uint32_t RESERVED0: 1;
		uint32_t VREF2_CAL: 3;
		uint32_t RESERVED1: 25;
	};
	uint32_t Word;
} SCU_TMPSCAL_Typedef;

typedef union
{
	struct
	{
		uint32_t VREF_CAL3: 6;
		uint32_t RESERVED0: 26;
	};
	uint32_t Word;
} SCU_AFECAL_Typedef;

typedef union
{
	struct
	{
		uint32_t ADC_CAL: 16;
		uint32_t RESERVED0: 16;
	};
	uint32_t Word;
} SCU_ADCCAL_Typedef;

typedef struct
{
	__IO SCU_PROT_Typedef PROT;
	__IO SCU_NMIC_Typedef NMIC;
	__IO SCU_PWRC_Typedef PWRC;
	__IO SCU_FAULTFLAG_Typedef FAULTFLAG;
	uint32_t RESERVED0[4] ;
	__IO SCU_FLASHW_Typedef FLASHW;
	uint32_t RESERVED1[7] ;
	__IO SCU_SCLKEN_Typedef SCLKEN;
	uint32_t RESERVED2 ;
	__IO SCU_PCLKEN_Typedef PCLKEN;
	__IO SCU_WAKEUPTIME_Typedef WAKEUPTIME;
	uint32_t RESERVED3[4] ;
	__IO SCU_TESTCON_Typedef TESTCON;
	__IO SCU_VRCAL0_Typedef VRCAL0;
	__IO SCU_VRCAL1_Typedef VRCAL1;
	__IO SCU_MCLKCAL_Typedef MCLKCAL;
	__IO SCU_WDTCAL_Typedef WDTCAL;
	__IO SCU_TMPSCAL_Typedef TMPSCAL;
	__IO SCU_AFECAL_Typedef AFECAL;
	__I SCU_ADCCAL_Typedef ADCCAL;
} SCU_TypeDef;

typedef union
{
	struct
	{
		uint32_t DATA_0: 1;
		uint32_t DATA_1: 1;
		uint32_t DATA_2: 1;
		uint32_t DATA_3: 1;
		uint32_t DATA_4: 1;
		uint32_t DATA_5: 1;
		uint32_t DATA_6: 1;
		uint32_t DATA_7: 1;
		uint32_t DATA_8: 1;
		uint32_t DATA_9: 1;
		uint32_t DATA_10: 1;
		uint32_t DATA_11: 1;
		uint32_t RESERVED0: 20;
	};
	uint32_t Word;
} GPIO_DATA_Typedef;

typedef union
{
	struct
	{
		uint32_t DATABSR_0: 1;
		uint32_t DATABSR_1: 1;
		uint32_t DATABSR_2: 1;
		uint32_t DATABSR_3: 1;
		uint32_t DATABSR_4: 1;
		uint32_t DATABSR_5: 1;
		uint32_t DATABSR_6: 1;
		uint32_t DATABSR_7: 1;
		uint32_t DATABSR_8: 1;
		uint32_t DATABSR_9: 1;
		uint32_t DATABSR_10: 1;
		uint32_t DATABSR_11: 1;
		uint32_t RESERVED0: 20;
	};
	uint32_t Word;
} GPIO_DATABSR_Typedef;

typedef union
{
	struct
	{
		uint32_t DATABCR_0: 1;
		uint32_t DATABCR_1: 1;
		uint32_t DATABCR_2: 1;
		uint32_t DATABCR_3: 1;
		uint32_t DATABCR_4: 1;
		uint32_t DATABCR_5: 1;
		uint32_t DATABCR_6: 1;
		uint32_t DATABCR_7: 1;
		uint32_t DATABCR_8: 1;
		uint32_t DATABCR_9: 1;
		uint32_t DATABCR_10: 1;
		uint32_t DATABCR_11: 1;
		uint32_t RESERVED0: 20;
	};
	uint32_t Word;
} GPIO_DATABCR_Typedef;

typedef union
{
	struct
	{
		uint32_t DATABRR_0: 1;
		uint32_t DATABRR_1: 1;
		uint32_t DATABRR_2: 1;
		uint32_t DATABRR_3: 1;
		uint32_t DATABRR_4: 1;
		uint32_t DATABRR_5: 1;
		uint32_t DATABRR_6: 1;
		uint32_t DATABRR_7: 1;
		uint32_t DATABRR_8: 1;
		uint32_t DATABRR_9: 1;
		uint32_t DATABRR_10: 1;
		uint32_t DATABRR_11: 1;
		uint32_t RESERVED0: 20;
	};
	uint32_t Word;
} GPIO_DATABRR_Typedef;

typedef union
{
	struct
	{
		uint32_t DIR_0: 1;
		uint32_t DIR_1: 1;
		uint32_t DIR_2: 1;
		uint32_t DIR_3: 1;
		uint32_t DIR_4: 1;
		uint32_t DIR_5: 1;
		uint32_t DIR_6: 1;
		uint32_t DIR_7: 1;
		uint32_t DIR_8: 1;
		uint32_t DIR_9: 1;
		uint32_t DIR_10: 1;
		uint32_t DIR_11: 1;
		uint32_t RESERVED0: 20;
	};
	uint32_t Word;
} GPIO_DIR_Typedef;

typedef union
{
	struct
	{
		uint32_t DIRBSR_0: 1;
		uint32_t DIRBSR_1: 1;
		uint32_t DIRBSR_2: 1;
		uint32_t DIRBSR_3: 1;
		uint32_t DIRBSR_4: 1;
		uint32_t DIRBSR_5: 1;
		uint32_t DIRBSR_6: 1;
		uint32_t DIRBSR_7: 1;
		uint32_t DIRBSR_8: 1;
		uint32_t DIRBSR_9: 1;
		uint32_t DIRBSR_10: 1;
		uint32_t DIRBSR_11: 1;
		uint32_t RESERVED0: 20;
	};
	uint32_t Word;
} GPIO_DIRBSR_Typedef;

typedef union
{
	struct
	{
		uint32_t DIRBCR_0: 1;
		uint32_t DIRBCR_1: 1;
		uint32_t DIRBCR_2: 1;
		uint32_t DIRBCR_3: 1;
		uint32_t DIRBCR_4: 1;
		uint32_t DIRBCR_5: 1;
		uint32_t DIRBCR_6: 1;
		uint32_t DIRBCR_7: 1;
		uint32_t DIRBCR_8: 1;
		uint32_t DIRBCR_9: 1;
		uint32_t DIRBCR_10: 1;
		uint32_t DIRBCR_11: 1;
		uint32_t RESERVED0: 20;
	};
	uint32_t Word;
} GPIO_DIRBCR_Typedef;

typedef union
{
	struct
	{
		uint32_t DIRBRR_0: 1;
		uint32_t DIRBRR_1: 1;
		uint32_t DIRBRR_2: 1;
		uint32_t DIRBRR_3: 1;
		uint32_t DIRBRR_4: 1;
		uint32_t DIRBRR_5: 1;
		uint32_t DIRBRR_6: 1;
		uint32_t DIRBRR_7: 1;
		uint32_t DIRBRR_8: 1;
		uint32_t DIRBRR_9: 1;
		uint32_t DIRBRR_10: 1;
		uint32_t DIRBRR_11: 1;
		uint32_t RESERVED0: 20;
	};
	uint32_t Word;
} GPIO_DIRBRR_Typedef;

typedef union
{
	struct
	{
		uint32_t ERIF_0: 1;
		uint32_t ERIF_1: 1;
		uint32_t ERIF_2: 1;
		uint32_t ERIF_3: 1;
		uint32_t ERIF_4: 1;
		uint32_t ERIF_5: 1;
		uint32_t ERIF_6: 1;
		uint32_t ERIF_7: 1;
		uint32_t ERIF_8: 1;
		uint32_t ERIF_9: 1;
		uint32_t ERIF_10: 1;
		uint32_t ERIF_11: 1;
		uint32_t RESERVED0: 20;
	};
	uint32_t Word;
} GPIO_ERIF_Typedef;

typedef union
{
	struct
	{
		uint32_t EFIF_0: 1;
		uint32_t EFIF_1: 1;
		uint32_t EFIF_2: 1;
		uint32_t EFIF_3: 1;
		uint32_t EFIF_4: 1;
		uint32_t EFIF_5: 1;
		uint32_t EFIF_6: 1;
		uint32_t EFIF_7: 1;
		uint32_t EFIF_8: 1;
		uint32_t EFIF_9: 1;
		uint32_t EFIF_10: 1;
		uint32_t EFIF_11: 1;
		uint32_t RESERVED0: 20;
	};
	uint32_t Word;
} GPIO_EFIF_Typedef;

typedef union
{
	struct
	{
		uint32_t LVIF_0: 1;
		uint32_t LVIF_1: 1;
		uint32_t LVIF_2: 1;
		uint32_t LVIF_3: 1;
		uint32_t LVIF_4: 1;
		uint32_t LVIF_5: 1;
		uint32_t LVIF_6: 1;
		uint32_t LVIF_7: 1;
		uint32_t LVIF_8: 1;
		uint32_t LVIF_9: 1;
		uint32_t LVIF_10: 1;
		uint32_t LVIF_11: 1;
		uint32_t RESERVED0: 20;
	};
	uint32_t Word;
} GPIO_LVIF_Typedef;

typedef union
{
	struct
	{
		uint32_t ERIE_0: 1;
		uint32_t ERIE_1: 1;
		uint32_t ERIE_2: 1;
		uint32_t ERIE_3: 1;
		uint32_t ERIE_4: 1;
		uint32_t ERIE_5: 1;
		uint32_t ERIE_6: 1;
		uint32_t ERIE_7: 1;
		uint32_t ERIE_8: 1;
		uint32_t ERIE_9: 1;
		uint32_t ERIE_10: 1;
		uint32_t ERIE_11: 1;
		uint32_t RESERVED0: 20;
	};
	uint32_t Word;
} GPIO_ERIE_Typedef;

typedef union
{
	struct
	{
		uint32_t EFIE_0: 1;
		uint32_t EFIE_1: 1;
		uint32_t EFIE_2: 1;
		uint32_t EFIE_3: 1;
		uint32_t EFIE_4: 1;
		uint32_t EFIE_5: 1;
		uint32_t EFIE_6: 1;
		uint32_t EFIE_7: 1;
		uint32_t EFIE_8: 1;
		uint32_t EFIE_9: 1;
		uint32_t EFIE_10: 1;
		uint32_t EFIE_11: 1;
		uint32_t RESERVED0: 20;
	};
	uint32_t Word;
} GPIO_EFIE_Typedef;

typedef union
{
	struct
	{
		uint32_t LVIE_0: 1;
		uint32_t LVIE_1: 1;
		uint32_t LVIE_2: 1;
		uint32_t LVIE_3: 1;
		uint32_t LVIE_4: 1;
		uint32_t LVIE_5: 1;
		uint32_t LVIE_6: 1;
		uint32_t LVIE_7: 1;
		uint32_t LVIE_8: 1;
		uint32_t LVIE_9: 1;
		uint32_t LVIE_10: 1;
		uint32_t LVIE_11: 1;
		uint32_t RESERVED0: 20;
	};
	uint32_t Word;
} GPIO_LVIE_Typedef;

typedef union
{
	struct
	{
		uint32_t FLT_TIME: 10;
		uint32_t FLT_EN: 1;
		uint32_t FLT_STAT: 1;
		uint32_t FLT_CHS: 3;
		uint32_t RESERVED0: 17;
	};
	uint32_t Word;
} GPIO_FLTCON_Typedef;

typedef union
{
	struct
	{
		uint32_t FLTEN_0: 1;
		uint32_t FLTEN_1: 1;
		uint32_t FLTEN_2: 1;
		uint32_t FLTEN_3: 1;
		uint32_t FLTEN_4: 1;
		uint32_t FLTEN_5: 1;
		uint32_t FLTEN_6: 1;
		uint32_t FLTEN_7: 1;
		uint32_t FLTEN_8: 1;
		uint32_t FLTEN_9: 1;
		uint32_t FLTEN_10: 1;
		uint32_t FLTEN_11: 1;
		uint32_t RESERVED0: 20;
	};
	uint32_t Word;
} GPIO_FLTEN_Typedef;

typedef union
{
	struct
	{
		uint32_t PEN: 1;
		uint32_t PLV: 1;
		uint32_t PS: 3;
		uint32_t RESERVED0: 27;
	};
	uint32_t Word;
} GPIO_TXPC_Typedef;

typedef union
{
	struct
	{
		uint32_t FUNC: 2;
		uint32_t INE: 1;
		uint32_t RESERVED0: 1;
		uint32_t ODE: 1;
		uint32_t WPE: 1;
		uint32_t WPS: 1;
		uint32_t DS: 1;
		uint32_t RESERVED1: 24;
	};
	uint32_t Word;
} GPIO_MOD0_Typedef;

typedef union
{
	struct
	{
		uint32_t FUNC: 2;
		uint32_t INE: 1;
		uint32_t RESERVED0: 1;
		uint32_t ODE: 1;
		uint32_t WPE: 1;
		uint32_t WPS: 1;
		uint32_t DS: 1;
		uint32_t RESERVED1: 24;
	};
	uint32_t Word;
} GPIO_MOD1_Typedef;

typedef union
{
	struct
	{
		uint32_t FUNC: 2;
		uint32_t INE: 1;
		uint32_t RESERVED0: 1;
		uint32_t ODE: 1;
		uint32_t WPE: 1;
		uint32_t WPS: 1;
		uint32_t DS: 1;
		uint32_t RESERVED1: 24;
	};
	uint32_t Word;
} GPIO_MOD2_Typedef;

typedef union
{
	struct
	{
		uint32_t FUNC: 2;
		uint32_t INE: 1;
		uint32_t RESERVED0: 1;
		uint32_t ODE: 1;
		uint32_t WPE: 1;
		uint32_t WPS: 1;
		uint32_t DS: 1;
		uint32_t RESERVED1: 24;
	};
	uint32_t Word;
} GPIO_MOD3_Typedef;

typedef union
{
	struct
	{
		uint32_t FUNC: 2;
		uint32_t INE: 1;
		uint32_t RESERVED0: 1;
		uint32_t ODE: 1;
		uint32_t WPE: 1;
		uint32_t WPS: 1;
		uint32_t DS: 1;
		uint32_t RESERVED1: 24;
	};
	uint32_t Word;
} GPIO_MOD4_Typedef;

typedef union
{
	struct
	{
		uint32_t FUNC: 2;
		uint32_t INE: 1;
		uint32_t RESERVED0: 1;
		uint32_t ODE: 1;
		uint32_t WPE: 1;
		uint32_t WPS: 1;
		uint32_t DS: 1;
		uint32_t RESERVED1: 24;
	};
	uint32_t Word;
} GPIO_MOD5_Typedef;

typedef union
{
	struct
	{
		uint32_t FUNC: 2;
		uint32_t INE: 1;
		uint32_t RESERVED0: 1;
		uint32_t ODE: 1;
		uint32_t WPE: 1;
		uint32_t WPS: 1;
		uint32_t DS: 1;
		uint32_t RESERVED1: 24;
	};
	uint32_t Word;
} GPIO_MOD6_Typedef;

typedef union
{
	struct
	{
		uint32_t FUNC: 2;
		uint32_t INE: 1;
		uint32_t RESERVED0: 1;
		uint32_t ODE: 1;
		uint32_t WPE: 1;
		uint32_t WPS: 1;
		uint32_t DS: 1;
		uint32_t RESERVED1: 24;
	};
	uint32_t Word;
} GPIO_MOD7_Typedef;

typedef union
{
	struct
	{
		uint32_t FUNC: 2;
		uint32_t INE: 1;
		uint32_t RESERVED0: 1;
		uint32_t ODE: 1;
		uint32_t WPE: 1;
		uint32_t WPS: 1;
		uint32_t DS: 1;
		uint32_t RESERVED1: 24;
	};
	uint32_t Word;
} GPIO_MOD8_Typedef;

typedef union
{
	struct
	{
		uint32_t FUNC: 2;
		uint32_t INE: 1;
		uint32_t RESERVED0: 1;
		uint32_t ODE: 1;
		uint32_t WPE: 1;
		uint32_t WPS: 1;
		uint32_t DS: 1;
		uint32_t RESERVED1: 24;
	};
	uint32_t Word;
} GPIO_MOD9_Typedef;

typedef union
{
	struct
	{
		uint32_t FUNC: 2;
		uint32_t INE: 1;
		uint32_t RESERVED0: 1;
		uint32_t ODE: 1;
		uint32_t WPE: 1;
		uint32_t WPS: 1;
		uint32_t DS: 1;
		uint32_t RESERVED1: 24;
	};
	uint32_t Word;
} GPIO_MOD10_Typedef;

typedef union
{
	struct
	{
		uint32_t FUNC: 2;
		uint32_t INE: 1;
		uint32_t RESERVED0: 1;
		uint32_t ODE: 1;
		uint32_t WPE: 1;
		uint32_t WPS: 1;
		uint32_t DS: 1;
		uint32_t RESERVED1: 24;
	};
	uint32_t Word;
} GPIO_MOD11_Typedef;

typedef struct
{
	__IO GPIO_DATA_Typedef DATA;
	__O GPIO_DATABSR_Typedef DATABSR;
	__O GPIO_DATABCR_Typedef DATABCR;
	__O GPIO_DATABRR_Typedef DATABRR;
	__O GPIO_DIR_Typedef DIR;
	__O GPIO_DIRBSR_Typedef DIRBSR;
	__O GPIO_DIRBCR_Typedef DIRBCR;
	__O GPIO_DIRBRR_Typedef DIRBRR;
	__IO GPIO_ERIF_Typedef ERIF;
	__IO GPIO_EFIF_Typedef EFIF;
	__IO GPIO_LVIF_Typedef LVIF;
	uint32_t RESERVED0 ;
	__IO GPIO_ERIE_Typedef ERIE;
	__IO GPIO_EFIE_Typedef EFIE;
	__IO GPIO_LVIE_Typedef LVIE;
	uint32_t RESERVED1 ;
	__IO GPIO_FLTCON_Typedef FLTCON;
	__IO GPIO_FLTEN_Typedef FLTEN;
	__IO GPIO_TXPC_Typedef TXPC;
	uint32_t RESERVED2[13] ;
	__IO GPIO_MOD0_Typedef MOD0;
	__IO GPIO_MOD1_Typedef MOD1;
	__IO GPIO_MOD2_Typedef MOD2;
	__IO GPIO_MOD3_Typedef MOD3;
	__IO GPIO_MOD4_Typedef MOD4;
	__IO GPIO_MOD5_Typedef MOD5;
	__IO GPIO_MOD6_Typedef MOD6;
	__IO GPIO_MOD7_Typedef MOD7;
	__IO GPIO_MOD8_Typedef MOD8;
	__IO GPIO_MOD9_Typedef MOD9;
	__IO GPIO_MOD10_Typedef MOD10;
	__IO GPIO_MOD11_Typedef MOD11;
} GPIO_TypeDef;

typedef union
{
	struct
	{
		uint32_t EN: 1;
		uint32_t RST: 1;
		uint32_t RESERVED0: 2;
		uint32_t FLASH_REQ: 1;
		uint32_t FLASH_ACK: 1;
		uint32_t FLASH_SEL: 1;
		uint32_t RESERVED1: 25;
	};
	uint32_t Word;
} IAP_CON_Typedef;

typedef union
{
	struct
	{
		uint32_t RESERVED0: 2;
		uint32_t CA: 8;
		uint32_t PA: 6;
		uint32_t RESERVED1: 16;
	};
	uint32_t Word;
} IAP_ADDR_Typedef;

typedef union
{
	struct
	{
		uint32_t DATA: 32;
	};
	uint32_t Word;
} IAP_DATA_Typedef;

typedef union
{
	struct
	{
		uint32_t TRIG: 32;
	};
	uint32_t Word;
} IAP_TRIG_Typedef;

typedef union
{
	struct
	{
		uint32_t UL: 32;
	};
	uint32_t Word;
} IAP_UL_Typedef;

typedef union
{
	struct
	{
		uint32_t BSY: 1;
		uint32_t ERASE_END: 1;
		uint32_t PROG_END: 1;
		uint32_t TIMEOUT_ERR: 1;
		uint32_t RESERVED0: 28;
	};
	uint32_t Word;
} IAP_STA_Typedef;

typedef struct
{
	__IO IAP_CON_Typedef CON;
	__IO IAP_ADDR_Typedef ADDR;
	__IO IAP_DATA_Typedef DATA;
	__IO IAP_TRIG_Typedef TRIG;
	__IO IAP_UL_Typedef UL;
	__IO IAP_STA_Typedef STA;
} IAP_TypeDef;

typedef union
{
	struct
	{
		uint32_t DR: 12;
		uint32_t RESERVED0: 20;
	};
	uint32_t Word;
} ADC_DR_Typedef;

typedef union
{
	struct
	{
		uint32_t ADEN: 1;
		uint32_t ADTRG: 1;
		uint32_t RESERVED0: 30;
	};
	uint32_t Word;
} ADC_CON0_Typedef;

typedef union
{
	struct
	{
		uint32_t CLKDIV: 3;
		uint32_t CLKS: 1;
		uint32_t HS_EN: 1;
		uint32_t RESERVED0: 3;
		uint32_t VREFP: 2;
		uint32_t VREFN: 1;
		uint32_t VDET_SEL: 1;
		uint32_t VDET_EN: 1;
		uint32_t IREF_EN: 1;
		uint32_t TMPS_EN: 1;
		uint32_t TS_TEST_EN: 1;
		uint32_t STIME: 4;
		uint32_t SFLAG: 1;
		uint32_t RESERVED1: 11;
	};
	uint32_t Word;
} ADC_CON1_Typedef;

typedef union
{
	struct
	{
		uint32_t CHS: 4;
		uint32_t RESERVED0: 28;
	};
	uint32_t Word;
} ADC_CHS_Typedef;

typedef union
{
	struct
	{
		uint32_t IF: 1;
		uint32_t IE: 1;
		uint32_t RESERVED0: 30;
	};
	uint32_t Word;
} ADC_INT_Typedef;

typedef struct
{
	__I ADC_DR_Typedef DR;
	__IO ADC_CON0_Typedef CON0;
	__IO ADC_CON1_Typedef CON1;
	__IO ADC_CHS_Typedef CHS;
	__IO ADC_INT_Typedef INT;
} ADC_TypeDef;

typedef union
{
	struct
	{
		uint32_t LOAD: 32;
	};
	uint32_t Word;
} WDT_LOAD_Typedef;

typedef union
{
	struct
	{
		uint32_t VALUE: 32;
	};
	uint32_t Word;
} WDT_VALUE_Typedef;

typedef union
{
	struct
	{
		uint32_t EN: 1;
		uint32_t IE: 1;
		uint32_t RSTEN: 1;
		uint32_t CLKS: 1;
		uint32_t RESERVED0: 28;
	};
	uint32_t Word;
} WDT_CON_Typedef;

typedef union
{
	struct
	{
		uint32_t INTCLR: 32;
	};
	uint32_t Word;
} WDT_INTCLR_Typedef;

typedef union
{
	struct
	{
		uint32_t IF: 1;
		uint32_t RESERVED0: 31;
	};
	uint32_t Word;
} WDT_RIS_Typedef;

typedef union
{
	struct
	{
		uint32_t LOCK: 1;
		uint32_t RESERVED0: 31;
	};
	uint32_t Word;
} WDT_LOCK_Typedef;

typedef union
{
	struct
	{
		uint32_t TSTEN: 1;
		uint32_t RESERVED0: 31;
	};
	uint32_t Word;
} WDT_TSCON_Typedef;

typedef union
{
	struct
	{
		uint32_t TSTRES: 1;
		uint32_t TSTINT: 1;
		uint32_t RESERVED0: 30;
	};
	uint32_t Word;
} WDT_TSOP_Typedef;

typedef struct
{
	__IO WDT_LOAD_Typedef LOAD;
	__I WDT_VALUE_Typedef VALUE;
	__IO WDT_CON_Typedef CON;
	__O WDT_INTCLR_Typedef INTCLR;
	__I WDT_RIS_Typedef RIS;
	uint32_t RESERVED0[59] ;
	__IO WDT_LOCK_Typedef LOCK;
	uint32_t RESERVED1[127] ;
	__IO WDT_TSCON_Typedef TSCON;
	__O WDT_TSOP_Typedef TSOP;
} WDT_TypeDef;

typedef union
{
	struct
	{
		uint32_t CNT: 16;
		uint32_t RESERVED0: 16;
	};
	uint32_t Word;
} T16N_CNT_Typedef;

typedef union
{
	struct
	{
		uint32_t EN: 1;
		uint32_t CS: 2;
		uint32_t SYNC: 1;
		uint32_t EDGE: 2;
		uint32_t MOD: 2;
		uint32_t MAT0S: 2;
		uint32_t MAT1S: 2;
		uint32_t MAT2S: 2;
		uint32_t MAT3S: 2;
		uint32_t ASYWEN: 1;
		uint32_t RESERVED0: 15;
	};
	uint32_t Word;
} T16N_CON0_Typedef;

typedef union
{
	struct
	{
		uint32_t CAPPE: 1;
		uint32_t CAPNE: 1;
		uint32_t CAPIS0: 1;
		uint32_t CAPIS1: 1;
		uint32_t CAPT: 4;
		uint32_t RESERVED0: 8;
		uint32_t MOE0: 1;
		uint32_t MOE1: 1;
		uint32_t RESERVED1: 6;
		uint32_t MOM0: 2;
		uint32_t MOM1: 2;
		uint32_t MOM2: 2;
		uint32_t MOM3: 2;
	};
	uint32_t Word;
} T16N_CON1_Typedef;

typedef union
{
	struct
	{
		uint32_t MAT0IF: 1;
		uint32_t MAT1IF: 1;
		uint32_t MAT2IF: 1;
		uint32_t MAT3IF: 1;
		uint32_t IF: 1;
		uint32_t CAP0IF: 1;
		uint32_t CAP1IF: 1;
		uint32_t RESERVED0: 9;
		uint32_t MAT0IE: 1;
		uint32_t MAT1IE: 1;
		uint32_t MAT2IE: 1;
		uint32_t MAT3IE: 1;
		uint32_t IE: 1;
		uint32_t CAP0IE: 1;
		uint32_t CAP1IE: 1;
		uint32_t RESERVED1: 9;
	};
	uint32_t Word;
} T16N_INT_Typedef;

typedef union
{
	struct
	{
		uint32_t PRECNT: 8;
		uint32_t RESERVED0: 24;
	};
	uint32_t Word;
} T16N_PRECNT_Typedef;

typedef union
{
	struct
	{
		uint32_t PREMAT: 8;
		uint32_t RESERVED0: 24;
	};
	uint32_t Word;
} T16N_PREMAT_Typedef;

typedef union
{
	struct
	{
		uint32_t MAT0: 16;
		uint32_t RESERVED0: 16;
	};
	uint32_t Word;
} T16N_MAT0_Typedef;

typedef union
{
	struct
	{
		uint32_t MAT1: 16;
		uint32_t RESERVED0: 16;
	};
	uint32_t Word;
} T16N_MAT1_Typedef;

typedef union
{
	struct
	{
		uint32_t MAT2: 16;
		uint32_t RESERVED0: 16;
	};
	uint32_t Word;
} T16N_MAT2_Typedef;

typedef union
{
	struct
	{
		uint32_t MAT3: 16;
		uint32_t RESERVED0: 16;
	};
	uint32_t Word;
} T16N_MAT3_Typedef;

typedef struct
{
	__IO T16N_CNT_Typedef CNT;
	__IO T16N_CON0_Typedef CON0;
	__IO T16N_CON1_Typedef CON1;
	__IO T16N_INT_Typedef INT;
	__IO T16N_PRECNT_Typedef PRECNT;
	__IO T16N_PREMAT_Typedef PREMAT;
	uint32_t RESERVED0[2] ;
	__IO T16N_MAT0_Typedef MAT0;
	__IO T16N_MAT1_Typedef MAT1;
	__IO T16N_MAT2_Typedef MAT2;
	__IO T16N_MAT3_Typedef MAT3;
} T16N_TypeDef;

typedef union
{
	struct
	{
		uint32_t CNT: 32;
	};
	uint32_t Word;
} T32N_CNT_Typedef;

typedef union
{
	struct
	{
		uint32_t EN: 1;
		uint32_t CS: 2;
		uint32_t SYNC: 1;
		uint32_t EDGE: 2;
		uint32_t MOD: 2;
		uint32_t MAT0S: 2;
		uint32_t MAT1S: 2;
		uint32_t MAT2S: 2;
		uint32_t MAT3S: 2;
		uint32_t ASYNC_WREN: 1;
		uint32_t RESERVED0: 15;
	};
	uint32_t Word;
} T32N_CON0_Typedef;

typedef union
{
	struct
	{
		uint32_t CAPPE: 1;
		uint32_t CAPNE: 1;
		uint32_t CAPIS0: 1;
		uint32_t CAPIS1: 1;
		uint32_t CAPT: 4;
		uint32_t RESERVED0: 8;
		uint32_t MOE0: 1;
		uint32_t MOE1: 1;
		uint32_t RESERVED1: 6;
		uint32_t MOM0: 2;
		uint32_t MOM1: 2;
		uint32_t MOM2: 2;
		uint32_t MOM3: 2;
	};
	uint32_t Word;
} T32N_CON1_Typedef;

typedef union
{
	struct
	{
		uint32_t MAT0IF: 1;
		uint32_t MAT1IF: 1;
		uint32_t MAT2IF: 1;
		uint32_t MAT3IF: 1;
		uint32_t IF: 1;
		uint32_t CAP0IF: 1;
		uint32_t CAP1IF: 1;
		uint32_t RESERVED0: 9;
		uint32_t MAT0IE: 1;
		uint32_t MAT1IE: 1;
		uint32_t MAT2IE: 1;
		uint32_t MAT3IE: 1;
		uint32_t IE: 1;
		uint32_t CAP0IE: 1;
		uint32_t CAP1IE: 1;
		uint32_t RESERVED1: 9;
	};
	uint32_t Word;
} T32N_INT_Typedef;

typedef union
{
	struct
	{
		uint32_t PRECNT: 8;
		uint32_t RESERVED0: 24;
	};
	uint32_t Word;
} T32N_PRECNT_Typedef;

typedef union
{
	struct
	{
		uint32_t PREMAT: 8;
		uint32_t RESERVED0: 24;
	};
	uint32_t Word;
} T32N_PREMAT_Typedef;

typedef union
{
	struct
	{
		uint32_t MAT0: 32;
	};
	uint32_t Word;
} T32N_MAT0_Typedef;

typedef union
{
	struct
	{
		uint32_t MAT1: 32;
	};
	uint32_t Word;
} T32N_MAT1_Typedef;

typedef union
{
	struct
	{
		uint32_t MAT2: 32;
	};
	uint32_t Word;
} T32N_MAT2_Typedef;

typedef union
{
	struct
	{
		uint32_t MAT3: 32;
	};
	uint32_t Word;
} T32N_MAT3_Typedef;

typedef struct
{
	__IO T32N_CNT_Typedef CNT;
	__IO T32N_CON0_Typedef CON0;
	__IO T32N_CON1_Typedef CON1;
	__IO T32N_INT_Typedef INT;
	__IO T32N_PRECNT_Typedef PRECNT;
	__IO T32N_PREMAT_Typedef PREMAT;
	uint32_t RESERVED0[2] ;
	__IO T32N_MAT0_Typedef MAT0;
	__IO T32N_MAT1_Typedef MAT1;
	__IO T32N_MAT2_Typedef MAT2;
	__IO T32N_MAT3_Typedef MAT3;
} T32N_TypeDef;

typedef union
{
	struct
	{
		uint32_t TXEN: 1;
		uint32_t RXEN: 1;
		uint32_t TX9E: 1;
		uint32_t RX9E: 1;
		uint32_t TXPS: 2;
		uint32_t RXPS: 2;
		uint32_t TXFS: 1;
		uint32_t RESERVED0: 23;
	};
	uint32_t Word;
} UART_CON_Typedef;

typedef union
{
	struct
	{
		uint32_t TXBSY: 1;
		uint32_t RXFERR: 1;
		uint32_t RXOVERR: 1;
		uint32_t RXPERR: 1;
		uint32_t RESERVED0: 12;
		uint32_t TXFIFO: 3;
		uint32_t RESERVED1: 5;
		uint32_t RXFIFO: 3;
		uint32_t RESERVED2: 5;
	};
	uint32_t Word;
} UART_STAT_Typedef;

typedef union
{
	struct
	{
		uint32_t BRR: 10;
		uint32_t CLKS: 6;
		uint32_t RESERVED0: 16;
	};
	uint32_t Word;
} UART_BRR_Typedef;

typedef union
{
	struct
	{
		uint32_t TXIF: 1;
		uint32_t TXBUFIF: 1;
		uint32_t RXIF: 1;
		uint32_t RXBUFIF: 1;
		uint32_t TXIE: 1;
		uint32_t TXBUFIE: 1;
		uint32_t RXIE: 1;
		uint32_t RXBUFIE: 1;
		uint32_t RESERVED0: 24;
	};
	uint32_t Word;
} UART_INT_Typedef;

typedef union
{
	struct
	{
		uint32_t TXBUF0: 8;
		uint32_t TX9D0: 1;
		uint32_t RESERVED0: 23;
	};
	uint32_t Word;
} UART_TXBUF0_Typedef;

typedef union
{
	struct
	{
		uint32_t TXBUF1: 8;
		uint32_t TX9D1: 1;
		uint32_t RESERVED0: 23;
	};
	uint32_t Word;
} UART_TXBUF1_Typedef;

typedef union
{
	struct
	{
		uint32_t TXBUF2: 8;
		uint32_t TX9D2: 1;
		uint32_t RESERVED0: 23;
	};
	uint32_t Word;
} UART_TXBUF2_Typedef;

typedef union
{
	struct
	{
		uint32_t TXBUF3: 8;
		uint32_t TX9D3: 1;
		uint32_t RESERVED0: 23;
	};
	uint32_t Word;
} UART_TXBUF3_Typedef;

typedef union
{
	struct
	{
		uint32_t RXBUF0: 8;
		uint32_t RX9D0: 1;
		uint32_t RESERVED0: 23;
	};
	uint32_t Word;
} UART_RXBUF0_Typedef;

typedef union
{
	struct
	{
		uint32_t RXBUF1: 8;
		uint32_t RX9D1: 1;
		uint32_t RESERVED0: 23;
	};
	uint32_t Word;
} UART_RXBUF1_Typedef;

typedef union
{
	struct
	{
		uint32_t RXBUF2: 8;
		uint32_t RX9D2: 1;
		uint32_t RESERVED0: 23;
	};
	uint32_t Word;
} UART_RXBUF2_Typedef;

typedef union
{
	struct
	{
		uint32_t RXBUF3: 8;
		uint32_t RX9D3: 1;
		uint32_t RESERVED0: 23;
	};
	uint32_t Word;
} UART_RXBUF3_Typedef;

typedef struct
{
	__IO UART_CON_Typedef CON;
	__I UART_STAT_Typedef STAT;
	__IO UART_BRR_Typedef BRR;
	__IO UART_INT_Typedef INT;
	__IO UART_TXBUF0_Typedef TXBUF0;
	__IO UART_TXBUF1_Typedef TXBUF1;
	__IO UART_TXBUF2_Typedef TXBUF2;
	__IO UART_TXBUF3_Typedef TXBUF3;
	__I UART_RXBUF0_Typedef RXBUF0;
	__I UART_RXBUF1_Typedef RXBUF1;
	__I UART_RXBUF2_Typedef RXBUF2;
	__I UART_RXBUF3_Typedef RXBUF3;
} UART_TypeDef;

typedef union
{
	struct
	{
		uint32_t PROT: 1;
		uint32_t RESERVED0: 31;
	};
	uint32_t Word;
} EM_PROT_Typedef;

typedef union
{
	struct
	{
		uint32_t CRC1S: 1;
		uint32_t CRC2S: 1;
		uint32_t PREV: 1;
		uint32_t NO_LOAD: 1;
		uint32_t RESERVED0: 12;
		uint32_t ZXUS: 1;
		uint32_t ZXIAS: 1;
		uint32_t RESERVED1: 14;
	};
	uint32_t Word;
} EM_ESR_Typedef;

typedef union
{
	struct
	{
		uint32_t EM_EN: 1;
		uint32_t RMS_EN: 1;
		uint32_t CF_EN: 1;
		uint32_t EA_EN: 1;
		uint32_t APPF_EN: 1;
		uint32_t ZX_EN: 1;
		uint32_t FP_EN: 1;
		uint32_t ERCLR: 1;
		uint32_t CRC1_EN: 1;
		uint32_t CRC2_EN: 1;
		uint32_t RESERVED0: 6;
		uint32_t CF1SEL: 2;
		uint32_t CF1MOD: 1;
		uint32_t RESERVED1: 1;
		uint32_t ZXSEL: 2;
		uint32_t POFF_MOD: 1;
		uint32_t RESERVED2: 9;
	};
	uint32_t Word;
} EM_START_Typedef;

typedef union
{
	struct
	{
		uint32_t CRC1IF: 1;
		uint32_t CRC2IF: 1;
		uint32_t EDCHIF: 1;
		uint32_t NOLDIF: 1;
		uint32_t PEROIF: 1;
		uint32_t NEROIF: 1;
		uint32_t AEROIF: 1;
		uint32_t UZXIF: 1;
		uint32_t CF1IF: 1;
		uint32_t RESERVED0: 7;
		uint32_t CRC1IE: 1;
		uint32_t CRC2IE: 1;
		uint32_t EDCHIE: 1;
		uint32_t NOLDIE: 1;
		uint32_t PEROIE: 1;
		uint32_t NEROIE: 1;
		uint32_t AEROIE: 1;
		uint32_t UZXIE: 1;
		uint32_t CF1E: 1;
		uint32_t RESERVED1: 7;
	};
	uint32_t Word;
} EM_INT_Typedef;

typedef union
{
	struct
	{
		uint32_t PECNT: 32;
	};
	uint32_t Word;
} EM_PE_Typedef;

typedef union
{
	struct
	{
		uint32_t NECNT: 32;
	};
	uint32_t Word;
} EM_NE_Typedef;

typedef union
{
	struct
	{
		uint32_t AECNT: 32;
	};
	uint32_t Word;
} EM_AE_Typedef;

typedef union
{
	struct
	{
		uint32_t PFSET: 32;
	};
	uint32_t Word;
} EM_PFSET_Typedef;

typedef union
{
	struct
	{
		uint32_t PAGAIN: 16;
		uint32_t RESERVED0: 16;
	};
	uint32_t Word;
} EM_PAGAIN_Typedef;

typedef union
{
	struct
	{
		uint32_t APHCAL: 8;
		uint32_t RESERVED0: 24;
	};
	uint32_t Word;
} EM_APHCAL_Typedef;

typedef union
{
	struct
	{
		uint32_t PSTART: 16;
		uint32_t RESERVED0: 16;
	};
	uint32_t Word;
} EM_PSTART_Typedef;

typedef union
{
	struct
	{
		uint32_t PGA1C: 3;
		uint32_t RESERVED0: 1;
		uint32_t PGA2C: 3;
		uint32_t RESERVED1: 1;
		uint32_t ADC1_EN: 1;
		uint32_t ADC2_EN: 1;
		uint32_t RESERVED2: 2;
		uint32_t BGR_EN: 1;
		uint32_t CHOP1_PD: 1;
		uint32_t CHOP2_PD: 1;
		uint32_t RESERVED3: 1;
		uint32_t HPF_EN: 1;
		uint32_t RESERVED4: 15;
	};
	uint32_t Word;
} EM_AFEC_Typedef;

typedef union
{
	struct
	{
		uint32_t CRC1: 16;
		uint32_t RESERVED0: 16;
	};
	uint32_t Word;
} EM_CRC1_Typedef;

typedef union
{
	struct
	{
		uint32_t IRMS: 24;
		uint32_t RESERVED0: 8;
	};
	uint32_t Word;
} EM_IARMS_Typedef;

typedef union
{
	struct
	{
		uint32_t URMS: 24;
		uint32_t RESERVED0: 8;
	};
	uint32_t Word;
} EM_URMS_Typedef;

typedef union
{
	struct
	{
		uint32_t PA: 32;
	};
	uint32_t Word;
} EM_PA_Typedef;

typedef union
{
	struct
	{
		uint32_t APHASE: 16;
		uint32_t RESERVED0: 16;
	};
	uint32_t Word;
} EM_APHASE_Typedef;

typedef union
{
	struct
	{
		uint32_t FRQ: 16;
		uint32_t RESERVED0: 16;
	};
	uint32_t Word;
} EM_FRQ_Typedef;

typedef union
{
	struct
	{
		uint32_t SA: 32;
	};
	uint32_t Word;
} EM_SA_Typedef;

typedef union
{
	struct
	{
		uint32_t FAC: 16;
		uint32_t RESERVED0: 16;
	};
	uint32_t Word;
} EM_AFAC_Typedef;

typedef union
{
	struct
	{
		uint32_t UGAIN: 16;
		uint32_t RESERVED0: 16;
	};
	uint32_t Word;
} EM_UGAIN_Typedef;

typedef union
{
	struct
	{
		uint32_t IGAIN: 16;
		uint32_t RESERVED0: 16;
	};
	uint32_t Word;
} EM_IAGAIN_Typedef;

typedef union
{
	struct
	{
		uint32_t UOFF: 16;
		uint32_t RESERVED0: 16;
	};
	uint32_t Word;
} EM_UOFF_Typedef;

typedef union
{
	struct
	{
		uint32_t IAOFF: 16;
		uint32_t RESERVED0: 16;
	};
	uint32_t Word;
} EM_IAOFF_Typedef;

typedef union
{
	struct
	{
		uint32_t PAOFF: 16;
		uint32_t RESERVED0: 16;
	};
	uint32_t Word;
} EM_PAOFF_Typedef;

typedef union
{
	struct
	{
		uint32_t CRC2: 16;
		uint32_t RESERVED0: 16;
	};
	uint32_t Word;
} EM_CRC2_Typedef;

typedef union
{
	struct
	{
		uint32_t TMOD_SEL: 3;
		uint32_t TMOD_EN: 1;
		uint32_t RESERVED0: 28;
	};
	uint32_t Word;
} EM_TESTMOD_Typedef;

typedef union
{
	struct
	{
		uint32_t VREF_CAL1: 8;
		uint32_t VREF_CAL2: 4;
		uint32_t RESERVED0: 20;
	};
	uint32_t Word;
} EM_VREFCAL_Typedef;

typedef union
{
	struct
	{
		uint32_t UZFMOD: 1;
		uint32_t RESERVED0: 3;
		uint32_t GLITCHS: 2;
		uint32_t RESERVED1: 2;
		uint32_t VTHRHD: 8;
		uint32_t RESERVED2: 16;
	};
	uint32_t Word;
} EM_ZXFLT_Typedef;

typedef union
{
	struct
	{
		uint32_t IA_DATA: 24;
		uint32_t RESERVED0: 8;
	};
	uint32_t Word;
} EM_IADATA_Typedef;

typedef union
{
	struct
	{
		uint32_t U_DATA: 24;
		uint32_t RESERVED0: 8;
	};
	uint32_t Word;
} EM_UDATA_Typedef;

typedef struct
{
	__IO EM_PROT_Typedef PROT;
	uint32_t RESERVED0 ;
	__I EM_ESR_Typedef ESR;
	__IO EM_START_Typedef START;
	__IO EM_INT_Typedef INT;
	uint32_t RESERVED1[3] ;
	__I EM_PE_Typedef PE;
	__I EM_NE_Typedef NE;
	__I EM_AE_Typedef AE;
	uint32_t RESERVED2 ;
	__IO EM_PFSET_Typedef PFSET;
	__IO EM_PAGAIN_Typedef PAGAIN;
	__IO EM_APHCAL_Typedef APHCAL;
	__IO EM_PSTART_Typedef PSTART;
	__IO EM_AFEC_Typedef AFEC;
	__IO EM_CRC1_Typedef CRC1;
	uint32_t RESERVED3[2] ;
	__I EM_IARMS_Typedef IARMS;
	__I EM_URMS_Typedef URMS;
	__I EM_PA_Typedef PA;
	__I EM_APHASE_Typedef APHASE;
	__I EM_FRQ_Typedef FRQ;
	__I EM_SA_Typedef SA;
	__I EM_AFAC_Typedef AFAC;
	uint32_t RESERVED4 ;
	__IO EM_UGAIN_Typedef UGAIN;
	__IO EM_IAGAIN_Typedef IAGAIN;
	__IO EM_UOFF_Typedef UOFF;
	__IO EM_IAOFF_Typedef IAOFF;
	__IO EM_PAOFF_Typedef PAOFF;
	__IO EM_CRC2_Typedef CRC2;
	uint32_t RESERVED5[94] ;
	__IO EM_TESTMOD_Typedef TESTMOD;
	__IO EM_VREFCAL_Typedef VREFCAL;
	uint32_t RESERVED6 ;
	__IO EM_ZXFLT_Typedef ZXFLT;
	__I EM_IADATA_Typedef IADATA;
	__I EM_UDATA_Typedef UDATA;
} EM_TypeDef;

/******************************************************************************/
/* 物理地址映射 */
/******************************************************************************/

/* Base addresses */
#define FLASH_BASE (0x00000000UL)
#define SRAM_BASE (0x20000000UL)
#define APB_BASE (0x40000000UL)
#define RAM_BASE (0x60000000UL)

/* APB peripherals */
#define SCU_BASE (APB_BASE + 0x00000)
#define GPIO_BASE (APB_BASE + 0x00400)
#define IAP_BASE (APB_BASE + 0x00800)
#define ADC_BASE (APB_BASE + 0x01000)
#define WDT_BASE (APB_BASE + 0x01C00)
#define T16N0_BASE (APB_BASE + 0x02000)
#define T16N1_BASE (APB_BASE + 0x02400)
#define T32N0_BASE (APB_BASE + 0x04000)
#define UART0_BASE (APB_BASE + 0x06000)
#define EM_BASE (APB_BASE + 0x0A000)


/******************************************************************************/
/* 外设定义 */
/******************************************************************************/
#define SCU ((SCU_TypeDef *) SCU_BASE )
#define GPIO ((GPIO_TypeDef *) GPIO_BASE )
#define IAP ((IAP_TypeDef *) IAP_BASE )
#define ADC ((ADC_TypeDef *) ADC_BASE )
#define WDT ((WDT_TypeDef *) WDT_BASE )
#define T16N0 ((T16N_TypeDef *) T16N0_BASE )
#define T16N1 ((T16N_TypeDef *) T16N1_BASE )
#define T32N0 ((T32N_TypeDef *) T32N0_BASE )
#define UART0 ((UART_TypeDef *) UART0_BASE )
#define EM ((EM_TypeDef *) EM_BASE )


#endif
