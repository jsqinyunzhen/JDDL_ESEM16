#include "includes.h"
/*
*********************************************************************************************************
*	�� �� ��: HexToBcd
*	����˵��: HEX��ת��ΪBCD    
*	��    ��: Ҫת����ֵ 
*	�� �� ֵ: ת��ֵ  
*********************************************************************************************************
*/
uint8_t HexToBcd( uint8_t value ) 
{
    return ( ((value/10) << 4) + (value % 10) );
}
/*
*********************************************************************************************************
*	�� �� ��: BcdToHex
*	����˵��: BCD��ת��ΪHEX    
*	��    ��: Ҫת����ֵ   
*	�� �� ֵ: ת��ֵ   
*********************************************************************************************************
*/
uint8_t BcdToHex( uint8_t value ) 
{
    return ( ((value&0xF0) >> 4) * 10 + (value & 0x0F) );
}
/*
*********************************************************************************************************
*	�� �� ��: Hex2Bcd
*	����˵��: �����ֽ�HEX��ת��ΪBCD      
*	��    ��: Ҫת����HEX������      
*	�� �� ֵ: 
*********************************************************************************************************
*/
void Hex2Bcd( uint8_t *Hexopt, uint8_t *BCDopt, uint8_t Len ) //Ҫ��Len���ܴ���8
{ 
    uint8_t ucA,ucB;
    B32_B08 TempHex;
  
    TempHex.B32 = 0;
    for (ucA=0; ucA<Len; ucA++)
    { 
        TempHex.B08[ucA] = Hexopt[ucA];
    }
    
    for (ucA=0; ucA<Len; ucA++)
    {
        ucB = TempHex.B32%100;
        BCDopt[ucA] = HexToBcd(ucB);
        TempHex.B32 = TempHex.B32/100;
    }   
}
/*
*********************************************************************************************************
*	�� �� ��: Bcd2Hex
*	����˵��: �����ֽ�BCD��ת��ΪHEX      
*	��    ��: Ҫת����BCD������           
*	�� �� ֵ: 
*********************************************************************************************************
*/
void Bcd2Hex( uint8_t *BCDopt, uint8_t *HEXopt, uint8_t Len ) 
{
    uint8_t ucA;
    unsigned long bai_n;
    B32_B08 TempHex;
   
    TempHex.B32 = 0;
    bai_n = 1;
    for (ucA=0; ucA<Len; ucA++)
    {
				TempHex.B32 *= 100;
        TempHex.B32 += bai_n * ((BCDopt[ucA] >> 4 ) * 10 + (BCDopt[ucA] & 0x0F));
        //bai_n *= 100;
    }
    for (ucA=0; ucA<Len; ucA++)
    { 
        HEXopt[ucA] = TempHex.B08[ucA];
    }
}

/*********************************************************
��������Hex2Bcd_4                 
��  ������4�ֽ�HEX��ת��ΪBCD
����ֵ��Ҫת����HEX
���ֵ: BCD
����ֵ����                                        
*********************************************************/
void Hex2Bcd_4(uint8_t *HEXopt, uint8_t *BCDopt)
{
    Hex2Bcd( HEXopt, BCDopt, 4 );
}

/*********************************************************
��������Bcd2Hex_4                       
��  ������4�ֽ�BCD��ת��ΪHEX                  
����ֵ��Ҫת����BCD��                                         
���ֵ: HEX
����ֵ����                                        
*********************************************************/
void Bcd2Hex_4(uint8_t *BCDopt, uint8_t *HEXopt)
{
    Bcd2Hex( BCDopt, HEXopt, 4 );  
}

/*
*********************************************************************************************************
*	�� �� ��: CheckOddEven
*	����˵��: �ж�������ż��
*	��    ��:  ���ж�����
*	�� �� ֵ: ��żλ
*********************************************************************************************************
*/
uint8_t CheckOddEven ( uint8_t Data )
{
    uint8_t i, j;
    j = 0;
    for ( i = 0; i < 8; i++ )
    {
        if ( Data & 0x01 )
        {
            j++;
        }
        Data = Data >> 1;
    }
    return ( j );
}
/*
*********************************************************************************************************
*	�� �� ��: CheckOddEven
*	����˵��: ��ʱ1ms����
*	��    ��:  ��ʱʱ�䡣��λms��
*	�� �� ֵ: 
*********************************************************************************************************
*/
void DelayMs(uint16_t m)
{
	uint16_t i;
	
	while (m--)
	{
		for (i=0; i<1124; i++);
	}
} 
/*
*********************************************************************************************************
*	�� �� ��: SumCheck
*	����˵��: У���
*	��    ��:  data ��У������ָ�� num ��У������ݸ���
*	�� �� ֵ: У���
*********************************************************************************************************
*/
uint16_t SumCheck(uint8_t* data, uint8_t num)
{
	uint16_t check = 0;
	uint8_t	i;
	
	for (i=0; i<num; i++)
	{
		if (i%2)
			check += ((uint16_t)data[i] << 8);
		else
			check += data[i];
	}
	return check;
}

#define BREAKER_CRC_POLY (0x01)
uint8_t Breaker_CRC8(uint8_t *ptr, uint8_t len)
{
    uint8_t i = 0; 
    uint8_t crc=0x00; /* ����ĳ�ʼcrcֵ */ 

    while(len--)
    {
        crc ^= *ptr++;  /* ÿ��������Ҫ������������,������ָ����һ���� */  
        for (i=8; i>0; --i)   /* ������μ�����������һ���ֽ�crcһ�� */  
        { 
            if (crc & 0x80)
                crc = (crc << 1) ^ BREAKER_CRC_POLY;
            else
                crc = (crc << 1);
        }
    }

    return (crc); 
}
uint8_t Breaker_FrameProc(uint8_t *pInbuf, uint8_t len)
{
    if(Breaker_CRC8(pInbuf,pInbuf[1]) == 0)
    {
        uint32_t id = *(pInbuf+6);
        if(pInbuf[2] == 0xA0 && Breaker_NeedSetId())
        {
            if(gCurrentUsedID.B16[0] == id)
            {
                Breaker_WriteId(id);
            }
            else if(id > gCurrentUsedID.B16[1])
            {
                gCurrentUsedID.B16[1] = id;
            }
        }
        if(gId == id)
        {
            uint8_t cmd = pInbuf[2];
            switch(cmd)
            {
                case 0xA0:
                {
                    uint8_t Txbuf[BREAKERFRAMELEN] = {0x5A,0x0F,0xA1,0,0,0,0, 0,0,0,0,0,0,0,0};
                    Txbuf[6] = gId;
                    Txbuf[BREAKERFRAMELEN-1] = Breaker_CRC8(Txbuf,Txbuf[1]-1);
                    //RS485_Send_DataToBuf(Txbuf,sizeof(Txbuf));
                }
                break;
                case 0xA2://�򿪶�·��
                {
                    uint8_t Txbuf[BREAKERFRAMELEN] = {0x5A,0x0F,0xA3,0,0,0,0, 0,0,0,0,0,0,0,0};
                    RELAY_On();
                    
                    Txbuf[6] = gId;
                    Txbuf[BREAKERFRAMELEN-1] = Breaker_CRC8(Txbuf,Txbuf[1]-1);
                    RS485_Send_DataToBuf(Txbuf,sizeof(Txbuf));
                    memset(g_EP_Data.energy.B08,0,sizeof(g_EP_Data));
                }
                break;
                case 0xA4://��ѯ״̬
                {
                    uint8_t Txbuf[BREAKERFRAMELEN] = {0x5A,0x0F,0xA5,0,0,0,0, 0,0,0,0,0,0,0,0};
                    
                    Txbuf[6] = gId;
                    //g_Emu_Data.U.B32 = 2349;
                    Txbuf[7] = g_Emu_Data.U.B32>>8;//��ѹ��λ0.1V
                    Txbuf[8] = g_Emu_Data.U.B32;
                    
                    //g_Emu_Data.I.B32 = 0x2349;
                    Txbuf[9] = g_Emu_Data.I.B32>>8;
                    Txbuf[10] = g_Emu_Data.I.B32;
                    
                    //g_Emu_Data.P.B32 = 2349000;
                    Txbuf[11] = g_Emu_Data.P.B32/1000>>8;
                    Txbuf[12] = g_Emu_Data.P.B32/1000;
                    
                    //*(uint16_t *)(p16+9) = g_Emu_Data.I.B32; //������λmA
                    //*(uint16_t *)(p16+11) = g_Emu_Data.P.B32/1000;//���ʵ�λ0.1W
                    //*(uint8_t*)(Txbuf+13) = g_EP_Data.energy.B32/10;//0.1KWh
                    
                    Txbuf[BREAKERFRAMELEN-1] = Breaker_CRC8(Txbuf,Txbuf[1]-1);
                    RS485_Send_DataToBuf(Txbuf,sizeof(Txbuf));
                }
                break;
                case 0xA6://�رն�·��
                {
                    uint8_t Txbuf[BREAKERFRAMELEN] = {0x5A,0x0F,0xA7,0,0,0,0, 0,0,0,0,0,0,0,0};
                    
                    RELAY_Off();
                    
                    Txbuf[6] = gId;
                    Txbuf[BREAKERFRAMELEN-1] = Breaker_CRC8(Txbuf,Txbuf[1]-1);
                    RS485_Send_DataToBuf(Txbuf,sizeof(Txbuf));
                }
                break;
                case 0xAA://У׼��·��
                {
                }
                break;
            }
        }
    }
    return 0;
}

/****************************RELAY ****************************/
void RELAY_On(void ) 
{
    //GPIO->DATABCR.DATABCR_2 = 1;
    //GPIO->DATABSR.DATABSR_3 = 1;

    GPIO->DATABSR.DATABSR_8 = 1;
}
void RELAY_Off(void )
{
    //GPIO->DATABCR.DATABCR_3 = 1;
    //GPIO->DATABCR.DATABCR_2 = 1;
    
    GPIO->DATABCR.DATABCR_8 = 1;
}


void Breaker_InitDeviceID(void)
{
    IAP_ErasePage(EMU_ID_PA);
    IAP_ReadId( &gId);
    gCurrentUsedID.B32=0;
}
void Breaker_ReportId(uint32_t id)
{
    uint8_t Txbuf[BREAKERFRAMELEN] = {0x5A,0x0F,0xA1,0,0,0,0, 0,0,0,0,0,0,0,0};
    Txbuf[6] = id;
    Txbuf[BREAKERFRAMELEN-1] = Breaker_CRC8(Txbuf,Txbuf[1]-1);
    RS485_Send_DataToBuf(Txbuf,sizeof(Txbuf));
}
void Breaker_WriteId(uint32_t id)
{
    IAP_WriteId(id);
    IAP_ReadId(&gId);
}


