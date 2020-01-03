#include "esem16_gpio.h"

/***************************************************************
  ��������void GPIO_Init(GPIO_InitTypeDef* GPIO_InitStruct)
  ��  ����GPIO��ʼ��
  ����ֵ����
  ���ֵ����
  ����ֵ����
***************************************************************/
void GPIO_Init(GPIO_InitTypeDef* GPIO_InitStruct)
{
    uint32_t temp = 0x00;

    /*-------------------------- Configure the port pins -----------------------*/
    temp =  (((uint32_t)GPIO_InitStruct->GPIO_Func))    | \
        (((uint32_t)GPIO_InitStruct->GPIO_Ine)<<2)  | \
        (((uint32_t)GPIO_InitStruct->GPIO_Ode)<<4)  | \
        (((uint32_t)GPIO_InitStruct->GPIO_Wpe)<<5)  | \
        (((uint32_t)GPIO_InitStruct->GPIO_Wps)<<6)  | \
        (((uint32_t)GPIO_InitStruct->GPIO_Ds) <<7);

    /* �˿�ģʽ���� */
    switch(GPIO_InitStruct->GPIO_Pin)
    {
        case GPIO_Pin_0:
            GPIO->MOD0.Word = temp;break;
        case GPIO_Pin_1:
            GPIO->MOD1.Word = temp;break;
        case GPIO_Pin_2:
            GPIO->MOD2.Word = temp;break;
        case GPIO_Pin_3:
            GPIO->MOD3.Word = temp;break;
        case GPIO_Pin_4:
            GPIO->MOD4.Word = temp;break;
        case GPIO_Pin_5:
            GPIO->MOD5.Word = temp;break;
        case GPIO_Pin_6:
            GPIO->MOD6.Word = temp;break;
        case GPIO_Pin_7:
            GPIO->MOD7.Word = temp;break;
        case GPIO_Pin_8:
            GPIO->MOD8.Word = temp;break;
        case GPIO_Pin_9:
            GPIO->MOD9.Word = temp;break;
        case GPIO_Pin_10:
            GPIO->MOD10.Word = temp;break;
        case GPIO_Pin_11:
            GPIO->MOD11.Word = temp;break;
        default:break;
    }

    /* �˿������������ */
    if(GPIO_InitStruct->GPIO_Dir == GPIO_DIR_OUT)
        GPIO->DIR.Word &= ~((uint32_t)(0x1) << ((uint32_t)(GPIO_InitStruct->GPIO_Pin)));
    else
        GPIO->DIR.Word |= ((uint32_t)(0x1) << ((uint32_t)(GPIO_InitStruct->GPIO_Pin)));

    /* �˿������˲����� */
    if(GPIO_InitStruct->GPIO_Flt == DISABLE)
        GPIO->FLTEN.Word &= ~((uint32_t)(0x1) << ((uint32_t)(GPIO_InitStruct->GPIO_Pin)));
    else
        GPIO->FLTEN.Word |= ((uint32_t)(0x1) << ((uint32_t)(GPIO_InitStruct->GPIO_Pin)));
}
/***************************************************************
  ��������void GPIO_DataRead
  ��  ����GPIO�˿ڶ�����
  ����ֵ����
  ���ֵ����
  ����ֵ����
***************************************************************/
uint32_t GPIO_DataRead(void)
{
    return ((uint32_t)GPIO->DATA.Word);
}
/***************************************************************
  ��������void GPIO_DataWrite
  ��  ����GPIO�˿�д����
  ����ֵ����
  ���ֵ����
  ����ֵ����
***************************************************************/
void GPIO_DataWrite(uint32_t PortVal)
{
    GPIO->DATA.Word = PortVal;
}
/***************************************************************
  ��������void GPIO_BitRead
  ��  ����GPIO�˿ڶ�ĳλ����
  ����ֵ����
  ���ֵ����
  ����ֵ����
***************************************************************/
BitAction GPIO_BitRead(GPIO_TYPE_PIN PINx)
{
    BitAction bitstatus = BIT_RESET;

    if((GPIO->DATA.Word & ((uint32_t)0x1<<PINx)) != BIT_RESET)
        bitstatus = BIT_SET;
    else
        bitstatus = BIT_RESET;

    return bitstatus;
}
/***************************************************************
  ��������void GPIO_BitSet
  ��  ����GPIOλ�����
  ����ֵ����
  ���ֵ����
  ����ֵ����
***************************************************************/
void GPIO_BitSet(GPIO_TYPE_PIN PINx)
{
    GPIO->DATABSR.Word = ((uint32_t)(0x1) << ((uint32_t)PINx));
}
/***************************************************************
  ��������void GPIO_BitClr
  ��  ����GPIOλ�����
  ����ֵ����
  ���ֵ����
  ����ֵ����
***************************************************************/
void GPIO_BitClr(GPIO_TYPE_PIN PINx)
{
    GPIO->DATABCR.Word = ((uint32_t)(0x1) << ((uint32_t)PINx));
}
/***************************************************************
  ��������void GPIO_BitRev
  ��  ����GPIOλ�����ת
  ����ֵ����
  ���ֵ����
  ����ֵ����
***************************************************************/
void GPIO_BitRev(GPIO_TYPE_PIN PINx)
{
    GPIO->DATABRR.Word = ((uint32_t)(0x1) << ((uint32_t)PINx));
}
/***************************************************************
  ��������void GPIO_BitInput
  ��  ����GPIOλ������
  ����ֵ����
  ���ֵ����
  ����ֵ����
***************************************************************/
void GPIO_BitInput(GPIO_TYPE_PIN PINx)
{
    GPIO->DIRBSR.Word = ((uint32_t)(0x1) << ((uint32_t)PINx));
}
/***************************************************************
  ��������void GPIO_BitOutput
  ��  ����GPIOλ�����
  ����ֵ����
  ���ֵ����
  ����ֵ����
***************************************************************/
void GPIO_BitOutput(GPIO_TYPE_PIN PINx)
{
    GPIO->DIRBCR.Word = ((uint32_t)(0x1) << ((uint32_t)PINx));
}
/***************************************************************
  ��������void GPIO_BitDirRev
  ��  ����GPIOλ�跽��ת
  ����ֵ����
  ���ֵ����
  ����ֵ����
***************************************************************/
void GPIO_BitDirRev(GPIO_TYPE_PIN PINx)
{
    GPIO->DIRBRR.Word = ((uint32_t)(0x1) << ((uint32_t)PINx));
}
/***************************************************************
  ��������void GPIO_PinFUNCConfig
  ��  ����GPIOλ���ܸ��ö���
  ����ֵ����
  ���ֵ����
  ����ֵ����
***************************************************************/
void GPIO_PinFUNCConfig(GPIO_TYPE_PIN PINx, GPIO_TYPE_FUNC GPIO_FUNC)
{
    switch(PINx)
    {
      case GPIO_Pin_0:
          GPIO->MOD0.Word &= ~0x03;
          GPIO->MOD0.Word |= GPIO_FUNC;
          break;
      case GPIO_Pin_1:
          GPIO->MOD1.Word &= ~0x03;
          GPIO->MOD1.Word |= GPIO_FUNC;
          break;
      case GPIO_Pin_2:
          GPIO->MOD2.Word &= ~0x03;
          GPIO->MOD2.Word |= GPIO_FUNC;
          break;
      case GPIO_Pin_3:
          GPIO->MOD3.Word &= ~0x03;
          GPIO->MOD3.Word |= GPIO_FUNC;
          break;
      case GPIO_Pin_4:
          GPIO->MOD4.Word &= ~0x03;
          GPIO->MOD4.Word |= GPIO_FUNC;
          break;
      case GPIO_Pin_5:
          GPIO->MOD5.Word &= ~0x03;
          GPIO->MOD5.Word |= GPIO_FUNC;
          break;
      case GPIO_Pin_6:
          GPIO->MOD6.Word &= ~0x03;
          GPIO->MOD6.Word |= GPIO_FUNC;
          break;
      case GPIO_Pin_7:
          GPIO->MOD7.Word &= ~0x03;
          GPIO->MOD7.Word |= GPIO_FUNC;
          break;
      case GPIO_Pin_8:
          GPIO->MOD8.Word &= ~0x03;
          GPIO->MOD8.Word |= GPIO_FUNC;
          break;
      case GPIO_Pin_9:
          GPIO->MOD9.Word &= ~0x03;
          GPIO->MOD9.Word |= GPIO_FUNC;
          break;
      case GPIO_Pin_10:
          GPIO->MOD10.Word &= ~0x03;
          GPIO->MOD10.Word |= GPIO_FUNC;
          break;
      case GPIO_Pin_11:
          GPIO->MOD11.Word &= ~0x03;
          GPIO->MOD11.Word |= GPIO_FUNC;
          break;
      default:break;
    }
}
/***************************************************************
  ��������void GOIO_PINT_Config
  ��  ����GPIO�ж϶���
  ����ֵ����
  ���ֵ����
  ����ֵ����
***************************************************************/
void GOIO_PINT_Config(GPIO_TYPE_PIN PINx, PINT_TYPE_TRIG TRIGx, FunctionalState NewState)
{
    switch(TRIGx)
    {
        case PINT_Trig_Rise:
            if(NewState != DISABLE)
            {
                /* Set the x bit to enable the GOIOxERINT */
                GPIO->ERIE.Word |= ((uint32_t)(0x1) << ((uint32_t)PINx));
            }
            else
            {
                /* Disable the selected GOIOxERINT */
                GPIO->ERIE.Word &= ~((uint32_t)(0x1) << ((uint32_t)PINx));
            }
            break;
        case PINT_Trig_Fall:
            if (NewState != DISABLE)
            {
                /* Set the x bit to enable the GOIOxEFINT */
                GPIO->EFIE.Word |= ((uint32_t)(0x1) << ((uint32_t)PINx));
            }
            else
            {
                /* Disable the selected GOIOxEFINT */
                GPIO->EFIE.Word &= ~((uint32_t)(0x1) << ((uint32_t)PINx));
            }
            break;
        case PINT_Trig_Change:
            if (NewState != DISABLE)
            {
                /* Set the x bit to enable the GOIOxLVINT */
                GPIO->LVIE.Word |= ((uint32_t)(0x1) << ((uint32_t)PINx));
            }
            else
            {
                /* Disable the selected GOIOxLVINT */
                GPIO->LVIE.Word &= ~((uint32_t)(0x1) << ((uint32_t)PINx));
            }
            break;
        default:break;
    }
}
/***************************************************************
  ��������void GPIO_PINT_GetITStatus
  ��  ����GPIO�ж�ʹ��״̬��ȡ
  ����ֵ����
  ���ֵ����
  ����ֵ����
***************************************************************/
ITStatus GPIO_PINT_GetITStatus(GPIO_TYPE_PIN PINx ,PINT_TYPE_TRIG TRIGx)
{
    ITStatus bitstatus = RESET;
    uint32_t itstatus = 0x0;

    switch(TRIGx)
    {
        case PINT_Trig_Rise:
            itstatus = GPIO->ERIE.Word & ((uint32_t)(0x1) << ((uint32_t)PINx));
            break;
        case PINT_Trig_Fall:
            itstatus = GPIO->EFIE.Word & ((uint32_t)(0x1) << ((uint32_t)PINx));
            break;
        case PINT_Trig_Change:
            itstatus = GPIO->LVIE.Word & ((uint32_t)(0x1) << ((uint32_t)PINx));
            break;
        default:break;
    }

    if(itstatus != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}
/***************************************************************
  ��������void GPIO_PINT_GetIFStatus
  ��  ����GPIO�жϱ�־״̬��ȡ
  ����ֵ����
  ���ֵ����
  ����ֵ����
***************************************************************/
FlagStatus GPIO_PINT_GetIFStatus(GPIO_TYPE_PIN PINx ,PINT_TYPE_TRIG TRIGx)
{
    FlagStatus bitstatus = RESET;
    uint32_t itstatus = 0x0;

    switch(TRIGx)
    {
        case PINT_Trig_Rise:
            itstatus = GPIO->ERIF.Word & ((uint32_t)(0x1) << ((uint32_t)PINx));
            break;
        case PINT_Trig_Fall:
            itstatus = GPIO->EFIF.Word & ((uint32_t)(0x1) << ((uint32_t)PINx));
            break;
        case PINT_Trig_Change:
            itstatus = GPIO->LVIF.Word & ((uint32_t)(0x1) << ((uint32_t)PINx));
            break;
        default:break;
    }

    if(itstatus != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}
/***************************************************************
  ��������void GPIO_PINT_ClearIFPendingBit
  ��  ����GPIO�жϱ�־���
  ����ֵ����
  ���ֵ����
  ����ֵ����
***************************************************************/
void GPIO_PINT_ClearIFPendingBit(GPIO_TYPE_PIN PINx,PINT_TYPE_TRIG TRIGx)
{
    switch(TRIGx)
    {
        case PINT_Trig_Rise:
            GPIO->ERIF.Word &= ~((uint32_t)(0x1) << ((uint32_t)PINx));
            break;
        case PINT_Trig_Fall:
            GPIO->EFIF.Word &= ~((uint32_t)(0x1) << ((uint32_t)PINx));
            break;
        case PINT_Trig_Change:
            GPIO->LVIF.Word &= ~((uint32_t)(0x1) << ((uint32_t)PINx));
            break;
        default:break;
    }
}

/******************* (C) COPYRIGHT 2018 Eastsoft *****END OF FILE****/

