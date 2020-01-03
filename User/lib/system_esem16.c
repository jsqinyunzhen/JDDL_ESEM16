
#include "system_esem16.h"
#include "includes.h"

uint32_t SystemCoreClock = 20000000;          /*!< System Clock Frequency (Core Clock) */
static void SetSysClock(void);
extern void SCU_Init(void);;

/***************************************************************
  函数名：System_Init
  描  述：系统时钟初始化
  输入值：SCU_TYPE_EXOSC
  输出值：无
  返回值：无
***************************************************************/
void SystemInit(SCU_TYPE_EXOSC exosc)
{
    SetSysClock();
    SCU_Init();

    if(exosc == SCU_EXOSC_20MHz)
        SystemCoreClock = 20000000;         //20M晶振
    else
        SystemCoreClock = 10000000;         //10M晶振
}
/**
  * @brief  Configures the System clock frequency, AHB/APBx prescalers and Flash
  *         settings.
  * @note   This function should be called only once the RCC clock configuration
  *         is reset to the default reset state (done in SystemInit() function).
  * @param  None
  * @retval None
  */
static void SetSysClock (void)
{
    ;
}


ErrorStatus IAP_ReadId( uint32_t * pId)
{
    uint32_t rbuf = 0xffffffff;
    
    IAP_Read(&rbuf, ID_ADDRESS, 1);     //0x0000-0x8FFF
    *pId = rbuf;
    return SUCCESS ;
}
ErrorStatus IAP_WriteId( uint32_t Id)
{
    ErrorStatus ret = SUCCESS;
    uint32_t CurId = 0xFFFFFFFF;
    
    ret = IAP_WriteWord(ID_CA, EMU_ID_PA, Id);
    DelayMs(1);
    
    IAP_Read(&CurId, ID_ADDRESS, 1);    
    DelayMs(1);
    if(CurId != Id)
    {
        IAP_ErasePage(EMU_ID_PA);
        DelayMs(1);
    }
    ret = IAP_WriteWord(ID_CA, EMU_ID_PA, Id);
    DelayMs(1);
    return ret;
}
ErrorStatus IAP_WriteUGAIN( uint32_t Id)
{
    ErrorStatus rbuf = SUCCESS;
    
    rbuf = IAP_WriteWord(UGAIN_CA, EMU_DATA_PA, Id);
    DelayMs(1);
    return rbuf;
        
#if 0
    IAP_Read(&rbuf, UGAIN_ADDRESS, 1);     //0x0000-0x8FFF
    DelayMs(1);
    if(rbuf != Id)
    {
        IAP_ErasePage(EMU_DATA_PA);
        DelayMs(1);
    }
    IAP_WriteWord(UGAIN_CA, EMU_DATA_PA, Id);
    DelayMs(1);
    IAP_Read(&rbuf, UGAIN_ADDRESS, 1);
    DelayMs(1);
    return rbuf == Id;
#endif
}
ErrorStatus IAP_ReadUGAIN( uint32_t *pU)
{
    uint32_t rbuf = 0xffffffff;
    
    IAP_Read(&rbuf, UGAIN_ADDRESS, 1);     //0x0000-0x8FFF
    DelayMs(1);
    
    *pU = rbuf;
    return SUCCESS ;
}
ErrorStatus IAP_WriteIGAIN( uint32_t Id)
{
    ErrorStatus rbuf = SUCCESS;
    rbuf = IAP_WriteWord(IGAIN_CA, EMU_DATA_PA, Id);
    DelayMs(1);
    return rbuf;
        
#if 0
    IAP_Read(&rbuf, IGAIN_ADDRESS, 1);     //0x0000-0x8FFF
    DelayMs(1);
    if(rbuf != Id)
    {
        IAP_ErasePage(EMU_DATA_PA);
        DelayMs(1);
    }
    IAP_WriteWord(IGAIN_CA, EMU_DATA_PA, Id);
    DelayMs(1);
    IAP_Read(&rbuf, IGAIN_ADDRESS, 1);
    DelayMs(1);
    return rbuf == Id;
    #endif
}
ErrorStatus IAP_ReadIGAIN( uint32_t *pU)
{
    uint32_t rbuf = 0xffffffff;
    
    IAP_Read(&rbuf, IGAIN_ADDRESS, 1);     //0x0000-0x8FFF
    DelayMs(1);
    
    *pU = rbuf;
    return SUCCESS ;
}
ErrorStatus IAP_WritePAGAIN( uint32_t Id)
{
    ErrorStatus rbuf = SUCCESS;
    rbuf = IAP_WriteWord(PAGAIN_CA, EMU_DATA_PA, Id);
    DelayMs(1);
    return rbuf;
            
#if 0
    IAP_Read(&rbuf, PAGAIN_ADDRESS, 1);     //0x0000-0x8FFF
    DelayMs(1);
    if(rbuf != Id)
    {
        IAP_ErasePage(EMU_DATA_PA);
        DelayMs(1);
    }
    IAP_WriteWord(PAGAIN_CA, EMU_DATA_PA, Id);
    DelayMs(1);
    IAP_Read(&rbuf, PAGAIN_ADDRESS, 1);
    DelayMs(1);
    return rbuf == Id;
    #endif
}
ErrorStatus IAP_ReadPAGAIN( uint32_t *pU)
{
    uint32_t rbuf = 0xffffffff;
    
    IAP_Read(&rbuf, PAGAIN_ADDRESS, 1);     //0x0000-0x8FFF
    DelayMs(1);
    
    *pU = rbuf;
    return SUCCESS ;
}
ErrorStatus IAP_WriteAPHCAL( uint32_t Id)
{
    ErrorStatus rbuf = SUCCESS;
    rbuf = IAP_WriteWord(APHCAL_CA, EMU_DATA_PA, Id);
    DelayMs(1);
    return rbuf;
            
#if 0

    
    IAP_Read(&rbuf, APHCAL_ADDRESS, 1);     //0x0000-0x8FFF
    DelayMs(1);
    if(rbuf != Id)
    {
        IAP_ErasePage(EMU_DATA_PA);
        DelayMs(1);
    }
    IAP_WriteWord(APHCAL_CA, EMU_DATA_PA, Id);
    DelayMs(1);
    IAP_Read(&rbuf, APHCAL_ADDRESS, 1);
    DelayMs(1);
    return rbuf == Id;
    #endif
}
ErrorStatus IAP_ReadAPHCAL( uint32_t *pU)
{
    uint32_t rbuf = 0xffffffff;
    
    IAP_Read(&rbuf, APHCAL_ADDRESS, 1);     //0x0000-0x8FFF
    DelayMs(1);
    
    *pU = rbuf;
    return SUCCESS ;
}

ErrorStatus IAP_WritePAOFF( uint32_t Id)
{
    ErrorStatus rbuf = SUCCESS;
    rbuf = IAP_WriteWord(PAOFF_CA, EMU_DATA_PA, Id);
    DelayMs(1);
    return rbuf;
#if 0

    IAP_Read(&rbuf, PAOFF_ADDRESS, 1);     //0x0000-0x8FFF
    DelayMs(1);
    if(rbuf != Id)
    {
        IAP_ErasePage(EMU_DATA_PA);
        DelayMs(1);
    }
    IAP_WriteWord(PAOFF_CA, EMU_DATA_PA, Id);
    DelayMs(1);
    IAP_Read(&rbuf, PAOFF_ADDRESS, 1);
    DelayMs(1);
    return rbuf == Id;
    #endif
}
ErrorStatus IAP_ReadPAOFF( uint32_t *pU)
{
    uint32_t rbuf = 0xffffffff;
    
    IAP_Read(&rbuf, PAOFF_ADDRESS, 1);     //0x0000-0x8FFF
    DelayMs(1);
    
    *pU = rbuf;
    return SUCCESS ;
}
ErrorStatus IAP_WriteCHECKSUM( uint32_t Id)
{
    ErrorStatus rbuf = SUCCESS;
    rbuf = IAP_WriteWord(CHECKSUM_CA, EMU_DATA_PA, Id);
    DelayMs(1);
    return rbuf;
#if 0
    IAP_Read(&rbuf, CHECKSUM_ADDRESS, 1);     //0x0000-0x8FFF
    DelayMs(1);
    if(rbuf != Id)
    {
        IAP_ErasePage(EMU_DATA_PA);
        DelayMs(1);
    }
    IAP_WriteWord(CHECKSUM_CA, EMU_DATA_PA, Id);
    DelayMs(1);
    IAP_Read(&rbuf, CHECKSUM_ADDRESS, 1);
    DelayMs(1);
    return rbuf == Id;
    #endif
}
ErrorStatus IAP_ReadCHECKSUM( uint32_t *pU)
{
    uint32_t rbuf = 0xffffffff;
    
    IAP_Read(&rbuf, CHECKSUM_ADDRESS, 1);     //0x0000-0x8FFF
    DelayMs(1);
    
    *pU = rbuf;
    return SUCCESS ;
}

ErrorStatus IAP_ReadEnergy( EP_Data_TypeDef *pEP)
{
    ErrorStatus ret = SUCCESS;

    IAP_Read((uint32_t *)pEP, EMU_ENERGY_BASEADDR, sizeof(EP_Data_TypeDef)/sizeof(uint32_t));     //0x0000-0x8FFF
    DelayMs(1);
    
    return ret ;
}
ErrorStatus IAP_WriteEnergy(EP_Data_TypeDef *pEP)
{
    ErrorStatus ret = SUCCESS;

    uint8_t i = 0;
    uint32_t *pbuf = (uint32_t *)pEP;
    
    ret = IAP_ErasePage(EMU_ENERGY_PA);
    DelayMs(1);
    if(ret != SUCCESS)
    {
        return ret;
    }
    for (i = 0; i < sizeof(EP_Data_TypeDef)/sizeof(uint32_t); ++i)
    {
        ret = IAP_WriteWord(i, EMU_ENERGY_PA, *(pbuf+i));
        DelayMs(1);
        if(ret != SUCCESS)
        {
            return ret;
        }
    }

    return ret ;
}


