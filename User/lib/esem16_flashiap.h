#ifndef __LIBIAP_H__
#define __LIBIAP_H__

#include "esem16.h"
#include "system_esem16.h"

/* Register UnLock */
#define IAP_RegUnLock()     (IAP->UL.Word = 0x000000A5)
#define IAP_RegLock()       (IAP->UL.Word = 0x0)

/* IAP Enable */
#define IAP_Enable()        (IAP->CON.EN = 1)
#define IAP_Disable()       (IAP->CON.EN = 0)

/* Flash IAP request */
#define IAP_REQ()       (IAP->CON.FLASH_REQ = 1)
#define IAP_REQ_END()   (IAP->CON.FLASH_REQ = 0)

/* IAP Function */
ErrorStatus IAP_Unlock(void);
ErrorStatus IAP_WriteEnd(void);
ErrorStatus IAP_ErasePage(uint8_t Page_Addr);
ErrorStatus IAP_WriteCont(uint8_t Unit_addr, uint8_t Page_addr, uint32_t Data32);
ErrorStatus IAP_WriteWord(uint8_t Unit_addr, uint8_t Page_addr, uint32_t Data32);
ErrorStatus IAP_Read(uint32_t *Ram_Addr, uint32_t Flash_Addr, uint8_t Len);
ErrorStatus IAP_ReadId( uint32_t * Id);
ErrorStatus IAP_WriteId( uint32_t Id);
ErrorStatus IAP_WriteUGAIN( uint32_t Id);
ErrorStatus IAP_ReadUGAIN( uint32_t *Id);

#endif
