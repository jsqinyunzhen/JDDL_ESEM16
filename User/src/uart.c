#include "includes.h"
#include <stdlib.h> 
#include <stdio.h>

//DL645_TypeDef 			g_dl645 = {0};

uint8_t g_Outbuf[UART_BUF_LEN] = {0};		//待发送数据缓存
uint8_t g_OutbufLen = 0;
uint8_t g_SendedCnt = 0;

uint8_t g_Inbuf[UART_BUF_LEN] = {0};		//待发送数据缓存
uint8_t g_InbufLen = 0;		//接收数据个数
uint8_t g_RxDelayTimer = 0;

//uint8_t g_Data_C;			//控制码
//uint8_t g_Data_L;			//数据域长度
//uint8_t g_K_Outbuf = 0;		//返回帧数据域长度
//B32_B08 gu_Data_DI;			//帧数据标识



void RS485_Send_DataToBuf(uint8_t *buf ,uint8_t len)
{
    if(g_SendedCnt < g_OutbufLen)
    {
        return;
    }
    g_SendedCnt = 0;
    g_OutbufLen = len;
    memcpy(g_Outbuf,buf,len);
    FlagSet(g_Tasks_Flag, TASK_FLAG_UART_TX);			//产生事件标志，给主函数处理
    RS485_Send_On();
    UART_RX_DISABLE;					//接收中断禁止
    UART_TX_ENABLE;						//发送中断使能(发送一个数据中断)	
}


/*
*********************************************************************************************************
*	函 数 名: Uart_Rx
*	功能说明: Uart中断接收处理
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void Uart_Rx(uint8_t rcv_data)
{
    if(g_InbufLen >= UART_BUF_LEN)
    { 
        memset(g_Inbuf,0,sizeof(g_Inbuf));
        g_InbufLen = 0;
    }
    g_Inbuf[g_InbufLen++] = rcv_data;
    g_RxDelayTimer = 2;
	#if 0
	result = SUCCEED;
	g_dl645.Overtimr_Timer = RX_TIMEOUT_MAX;
	switch(g_dl645.Step)
	{
		case ST_START:				//接收前导符
			if(rcv_data == 0XFE)  	//如果接收到前导符,准备接受第一个前导符
			{
				g_dl645.DataLen = 0;
				g_dl645.Len = 0;
				g_dl645.Step = ST_WAIT_H1;
			}
			else                 	//等待接收状态第一个收到的不是前导符，仍然维持等待接受状态
			{				
				result = FAILED;								
			}
			break;			
		case ST_WAIT_H1:			//接收第一个68
			if (rcv_data == 0XFE)	//如果接收到前导符保持状态不变
			{
			
			}
			else if (rcv_data == 0X68) //接收第一个68
			{
				g_dl645.data_buf[0] = 0x68;
				g_dl645.DataLen = 0;
				g_dl645.Len = 0;
				g_dl645.Step = ST_WAIT_ADDR;				
			}
			else
			{
				result = FAILED;
			}
			break;
		case ST_WAIT_ADDR:				//接收地址	
			g_dl645.Len++;		
			g_dl645.data_buf[g_dl645.Len] = rcv_data;
			if (g_dl645.Len >= 6)
			{
				for (i=0; i<6; i++)     //查看地址是否为0xAA
				{
//                    if ( ( g_dl645.data_buf[1 + i] != g_DeviceInfo.Dev_ID[i] )
//                            && ( g_dl645.data_buf[1 + i] != 0XAA ) )
					if (g_dl645.data_buf[1 + i] != 0XAA )
						break;
				}
				if ( i != 6)
                {
                    result = FAILED;
                }
                else
                {
                    g_dl645.Step = ST_WAIT_H2;
                }				
			}
			break;
		case ST_WAIT_H2:				//接收第二个68
            g_dl645.Len++;
            if (rcv_data == 0x68)
            {
                g_dl645.data_buf[g_dl645.Len] = 0x68;
                g_dl645.Step = ST_WAIT_CTRL;
                g_dl645.DataLen = 0;
            }
            else
            {
                result = FAILED;
            }
			break;
		case ST_WAIT_CTRL:              //控制码
            g_dl645.Len++;
            g_dl645.data_buf[g_dl645.Len] = rcv_data;
            g_dl645.Step = ST_WAIT_LEN;
            g_dl645.DataLen = 0;            
			break;
		case ST_WAIT_LEN:               //接收数据长度
            g_dl645.Len++;
            g_dl645.data_buf[g_dl645.Len] = rcv_data;
            if (rcv_data == 0)
            {
                g_dl645.Step = ST_WAIT_CS;
                g_dl645.DataLen = 0;     
            }
            else if (rcv_data <= 200)
            {
                g_dl645.Step = ST_WAIT_DATA;
                g_dl645.DataLen = 0;             
            }
            else
            {
                result = FAILED;
            }            
			break;
		case ST_WAIT_DATA:              //接收数据域
            g_dl645.Len++;
            g_dl645.data_buf[g_dl645.Len] = rcv_data;
            g_dl645.DataLen++;   
            if (g_dl645.DataLen >= g_dl645.data_buf[9])
            {
                g_dl645.Step = ST_WAIT_CS;
            }            
			break;
		case ST_WAIT_CS:
            cs = 0;
            for (i=0; i<= g_dl645.Len; i++)
            {
                cs = cs + g_dl645.data_buf[i];
            }
            if (cs == rcv_data)
            {
 				g_dl645.Len++;
				g_dl645.data_buf[g_dl645.Len] = rcv_data;
				g_dl645.Step = ST_WAIT_END;               
            }
            else
            {
                result = FAILED;
            }
			break;
		case ST_WAIT_END:
            if (rcv_data == 0x16)
            {
                g_dl645.Len++;
                g_dl645.data_buf[g_dl645.Len] = 0x16;
                g_dl645.Step = ST_START;  
                g_dl645.Overtimr_Timer = RESPONSETIME_MAX;
				FlagSet(g_Tasks_Flag, TASK_FLAG_UART);			//产生事件标志，给主函数处理
                UART_TX_DISABLE;								//发送中断禁止
				UART_RX_DISABLE;								//接收中断禁止
            }
            else
            {
                result = FAILED;
            }           
			break;
		default:
            result = FAILED;
			break;		
	}
    if (result != SUCCEED)
    {
        g_dl645.Overtimr_Timer = 1;     		//重新进入等待接收状态
        g_dl645.Step = ST_START;  
    }
    #endif
}
/*
*********************************************************************************************************
*	函 数 名: Uart_Proc
*	功能说明: Uart处理
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
uint32_t bswap_32(uint32_t x)
{
    return (((uint32_t)(x) & 0xff000000) >> 24) |  (((uint32_t)(x) & 0x00ff0000) >> 8) | \
        (((uint32_t)(x) & 0x0000ff00) << 8) | (((uint32_t)(x) & 0x000000ff) << 24);
}

void Uart_Proc(void)
{
    if(g_InbufLen > 0 && g_Inbuf[0] != 0)
    {
        char *buf08;
        uint8_t Len = 0;	
        uint8_t Rxbuf[UART_BUF_LEN] = {0};
        
        Len = g_InbufLen;
        memcpy(Rxbuf,g_Inbuf,Len);
        
        g_InbufLen = 0;
        memset(g_Inbuf,0,sizeof(g_Inbuf));
        
        buf08 = (char*)Rxbuf + 3;

        if(Rxbuf[0] == 0x5A && Rxbuf[1] == 0x0F)
        {
            Breaker_FrameProc(Rxbuf,Len);
        }
        else if(strncmp((char*)Rxbuf,"ID:",3) ==0)
        {
            uint32_t id = atoi((char*)buf08);
            uint8_t buf[UART_BUF_LEN] = {0};
            
            if(id >= 1)
            {
                gId = id;
                Breaker_WriteId(gId);
            }
            sprintf((char*)buf,"\r\nID=%d\r\n",gId);
            RS485_Send_DataToBuf(buf,strlen((char*)buf));
        }
        else if(strncmp((char*)Rxbuf,"AUG",3) ==0)
        {
            B32_B08 adj,data;
            data.B32 = atoi((char*)buf08)*10;
            Hex2Bcd_4(data.B08,adj.B08);adj.B32 = bswap_32(adj.B32);
            UGAIN_Adjust(adj.B08);
        }
        else if(strncmp((char*)Rxbuf,"AIA",3) ==0)
        {
            B32_B08 adj,data;
            data.B32 = atoi((char*)buf08);
            Hex2Bcd_4(data.B08,adj.B08);adj.B32 = bswap_32(adj.B32);
            IAGAIN_Adjust(adj.B08);
        }
        else if(strncmp((char*)Rxbuf,"APA",3) ==0)
        {
            B32_B08 adj,data;
            data.B32 = atoi((char*)buf08)*10000;
            Hex2Bcd_4(data.B08,adj.B08);adj.B32 = bswap_32(adj.B32);
            PAGAIN_Adjust(adj.B08);
        }
        else if(strncmp((char*)Rxbuf,"AAP",3) ==0)
        {
            B32_B08 adj,data;
            data.B32 = atoi((char*)buf08)*10000;
            Hex2Bcd_4(data.B08,adj.B08);adj.B32 = bswap_32(adj.B32);
            APHCAL_Adjust(adj.B08);
        }
        else if(strncmp((char*)Rxbuf,"APO",3) ==0)
        {
            B32_B08 adj,data;
            data.B32 = atoi((char*)buf08)*10000;
            Hex2Bcd_4(data.B08,adj.B08);adj.B32 = bswap_32(adj.B32);
            PAOFF_Adjust(adj.B08);
        }
        else if(strncmp((char*)Rxbuf,"AD:",3) ==0)
        {
            B32_B08 u,i,p,ap,po;
            B32_B08 adj = {0};
            
            buf08 = strstr(buf08,"ID");
            if(buf08 != 0)
            {
                buf08 += 2;
                gId = atoi((char*)buf08);
            }
            buf08 = (char*)strstr((char*)buf08,"U");
            if(buf08 != 0)
            {
                buf08 += 1;
                u.B32 = atoi((char*)buf08)*10;
            }
            buf08 = (char*)strstr((char*)buf08,"I");
            if(buf08 != 0)
            {
                buf08 += 1;
                i.B32 = atoi((char*)buf08);
            }
            buf08 = (char*)strstr((char*)buf08,"P");
            if(buf08 != 0)
            {
                buf08 += 1;
                p.B32 = atoi((char*)buf08)*10000;
            }
            buf08 = (char*)strstr((char*)buf08,"AP");
            if(buf08 != 0)
            {
                buf08 += 2;
                ap.B32 = atoi((char*)buf08)*10000;
            }
            buf08 = (char*)strstr((char*)buf08,"PO");
            if(buf08 != 0)
            {
                buf08 += 2;
                po.B32 = atoi((char*)buf08)*10000;
            }
            //if(Get_Factor() >= 900)
            {
                Hex2Bcd_4(p.B08,adj.B08);adj.B32 = bswap_32(adj.B32);
                PAGAIN_Adjust(adj.B08);
            }
            //else
            
            //DelayMs(1000);
            {
                Hex2Bcd_4(ap.B08,adj.B08);adj.B32 = bswap_32(adj.B32);
                APHCAL_Adjust(adj.B08);
            }

           // DelayMs(1000);

            Hex2Bcd_4(u.B08,adj.B08);adj.B32 = bswap_32(adj.B32);
            UGAIN_Adjust(adj.B08);
            
          //  DelayMs(1000);
            Hex2Bcd_4(i.B08,adj.B08);adj.B32 = bswap_32(adj.B32);
            IAGAIN_Adjust(adj.B08);
            

            Hex2Bcd_4(po.B08,adj.B08);adj.B32 = bswap_32(adj.B32);
            PAOFF_Adjust(adj.B08);
            
        }
        else if(strncmp((char*)Rxbuf,"OPEN",4) ==0)
        {
            RELAY_On();
        }
        else if(strncmp((char*)Rxbuf,"CLOSE",5) ==0)
        {
            RELAY_Off();
        }
        else if(strncmp((char*)Rxbuf,"RESET",5) ==0)
        {
            Energy_Reset();
            IAP_ErasePage(EMU_DATA_PA);
            DelayMs(10); 
            NVIC_SystemReset();
        }
        else if(strncmp((char*)Rxbuf,"REBOOT",6) ==0)
        {
            NVIC_SystemReset();
        }
        else if(strncmp((char*)Rxbuf,"SETPO",5) ==0)
        {
            buf08 = (char*)Rxbuf + 5;
            g_EM_GainPara.Paoff_Gain.B16 = atoi((char*)buf08);
            Emu_Adjust_Save();
        }
        else if(strncmp((char*)Rxbuf,"SETUA",5) ==0)
        {
            buf08 = (char*)Rxbuf + 5;
            g_EM_GainPara.U_Gain.B16 = atoi((char*)buf08);
            Emu_Adjust_Save();
        }
        else if(strncmp((char*)Rxbuf,"SETIA",5) ==0)
        {
            buf08 = (char*)Rxbuf + 5;
            g_EM_GainPara.I_Gain.B16 = atoi((char*)buf08);
            Emu_Adjust_Save();
        }
        else if(strncmp((char*)Rxbuf,"SETPA",5) ==0)
        {
            buf08 = (char*)Rxbuf + 5;
            g_EM_GainPara.P_Gain.B16 = atoi((char*)buf08);
            Emu_Adjust_Save();
        }
        else if(strncmp((char*)Rxbuf,"SETPH",5) ==0)
        {
            buf08 = (char*)Rxbuf + 5;
            g_EM_GainPara.Phase_Gain.B16 = atoi((char*)buf08);
            Emu_Adjust_Save();
        }
        else if(strncmp((char*)Rxbuf,"VERSION",5) ==0)
        {
            if(gId > 0 && gId <= 20)
            {
                DelayMs(100*(gId-1)); 
            }
#if RELAY_DEFUALT_STATUS
            //RS485_Send_DataToBuf("\r\nV1.0_ON_191127\r\n",strlen("\r\nV1.0_ON_191127\r\n"));
            RS485_Send_DataToBuf("\r\nV1.0_CLOSE_191206\r\n",strlen("\r\nV1.0_CLOSE_191206\r\n"));
#else
            //RS485_Send_DataToBuf("\r\nV1.0_OFF_191127\r\n",strlen("\r\nV1.0_OFF_191127\r\n"));
            RS485_Send_DataToBuf("\r\nV1.0_OPEN_191206\r\n",strlen("\r\nV1.0_OPEN_191206\r\n"));
#endif
        }
        else if(strncmp((char*)Rxbuf,"PRINTON",7) ==0)
        {
            if(Len > 7)
            {
                uint8_t id = 0;
                char *pbuf = (char*)Rxbuf + 7;
                id = atoi((char*)pbuf);
                if(gId == id)
                {
                    gEMUprint = 1;
                    gGainPrint = 1;
                }
            }
            else
            {
                gEMUprint = 1;
                gGainPrint = 1;
            }
            //RS485_Send_DataToBuf(gEMUprint?"On \r\n":"Off\r\n",5);
        }
        else if(strncmp((char*)Rxbuf,"PRINTOFF",8) ==0)
        {
            gEMUprint = 0;
            //RS485_Send_DataToBuf(gEMUprint?"On \r\n":"Off\r\n",5);
        }
        else if(strncmp((char*)Rxbuf,SETALLID,strlen(SETALLID)) ==0)
        {
            Breaker_InitDeviceID();
        }
        else if(strncmp((char*)Rxbuf,"GETID",strlen("GETID")) ==0)
        {
            uint8_t buf[UART_BUF_LEN] = {0};
            if(gId > 0 && gId <= 20)
            {
                DelayMs(100*(gId-1)); 
            }
            sprintf((char*)buf,"\r\nid=%d,T=%d:%d:%d",gId,gSecond/3600,gSecond/60%60,gSecond%60);
            RS485_Send_DataToBuf(buf,strlen((char*)buf));
        }
    }


	#if 0
	g_Data_C = g_dl645.data_buf[8];
	g_Data_L = g_dl645.data_buf[9];
	
	//余3码处理
	for (i=0; i<g_Data_L; i++)
	{
        g_dl645.data_buf[10 + i] -= 0x33;    
	}
	switch (g_Data_C)
	{
		case 0x11:		//读数据
		case 0x1F:		//扩展命令，校表
			gu_Data_DI.B08[0] = g_dl645.data_buf[10];			
			gu_Data_DI.B08[1] = g_dl645.data_buf[11];	
			gu_Data_DI.B08[2] = g_dl645.data_buf[12];	
			gu_Data_DI.B08[3] = g_dl645.data_buf[13];	
			break;
		default:
			break;
	}
	Judge_645_C(g_Data_C);
	g_Data_C |= 0x80 ;
	/*******发送数据处理*********/
	g_dl645.data_buf[0] = 0xFE;
	g_dl645.data_buf[1] = 0xFE;
	g_dl645.data_buf[2] = 0xFE;
	g_dl645.data_buf[3] = 0x68;
// 	memcpy( (g_dl645.data_buf+4),g_DeviceInfo.Dev_ID , 6); //copy
	g_dl645.data_buf[4] = 0;		//地址未用
	g_dl645.data_buf[5] = 0;
	g_dl645.data_buf[6] = 0;
	g_dl645.data_buf[7] = 0;
	g_dl645.data_buf[8] = 0;
	g_dl645.data_buf[9] = 0;
	g_dl645.data_buf[10] = 0x68;
	g_dl645.data_buf[11] = g_Data_C;
	switch (g_Data_C)
	{
		case 0x91:
			g_dl645.data_buf[12] = g_K_Outbuf + 4;			//增加4位数据标识
			memcpy ((g_dl645.data_buf+13),gu_Data_DI.B08, 4);
			memcpy ((g_dl645.data_buf+17),g_Outbuf, g_K_Outbuf);
			break;
		case 0x9F:
			g_dl645.data_buf[12] = g_K_Outbuf;
			memcpy ((g_dl645.data_buf+3),g_Outbuf, g_K_Outbuf);
			break;
		default:
			break;
	}	
    //余3码处理
    for (i=0; i<g_dl645.data_buf[12]; i++)
    {
        g_dl645.data_buf[13+i] += 0x33;
    }
    //校验和
   	buf08 = 0;
	for (i=3; i<13+g_dl645.data_buf[12]; i++)
	{
		buf08 = buf08 + g_dl645.data_buf[i];
	}
	g_dl645.data_buf[13+g_dl645.data_buf[12]] = buf08;		//cs
	g_dl645.data_buf[14+g_dl645.data_buf[12]] = 0x16;
	g_dl645.Len = 15+g_dl645.data_buf[12];					//发送数据长度

	g_dl645.TxDelay_Timer = TX_START_DELAY_MIN;				//30ms后发送第一个前导码
	g_dl645.Overtimr_Timer = TX_START_DELAY_MIN*2;			//如果长时间没有进入发送状态，则强制进入接收态
	#endif
}
/*
*********************************************************************************************************
*	函 数 名: Judge_645_C
*	功能说明: 
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void Judge_645_C ( uint8_t  Data_C )
{
    switch ( Data_C ) //判断控制码
    {
        case 0X11:    //读数据
            Uart_Proc_11();
            break;
            /************************************************/
        case 0X1F:    //校表
            Uart_Proc_1F(); 
            break;
            /************************************************/
        default:      //无请求数据
            break;
            /************************************************/
    }
}
/*
*********************************************************************************************************
*	函 数 名: Uart_Proc_11
*	功能说明: 645-11命令， 读数据处理
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void Uart_Proc_11 ( void )
{
#if 0
	B32_B08 temp;

	switch (gu_Data_DI.B32)
	{
        case 0x02010100 :  // 读取A相电压值
            g_Outbuf[0] = g_Emu_Data.U.B08[0];
            g_Outbuf[1] = g_Emu_Data.U.B08[1];
            g_K_Outbuf = 2 ;
            break ;
        case 0x02020100 :  // 读取A相电流值
            g_Outbuf[0] = g_Emu_Data.I1.B08[0];
            g_Outbuf[1] = g_Emu_Data.I1.B08[1];
            g_Outbuf[2] = g_Emu_Data.I1.B08[2];
            g_K_Outbuf = 3 ;
            break ;
        case 0x02030000 :  //瞬时总有功功率
            temp.B32 = g_Emu_Data.P1.B32;
            temp.B32 = temp.B32 >> 12;//转换数据格式
            g_Outbuf[0] = temp.B08[0] ;
            g_Outbuf[1] = temp.B08[1] ;
            g_Outbuf[2] = temp.B08[2] ;
            g_K_Outbuf = 3 ;
            break ;
        case 0x02060000 :  //总功率因数
            g_Outbuf[0] = g_Emu_Data.Cosa.B08[0];
            g_Outbuf[1] = g_Emu_Data.Cosa.B08[1];
            g_K_Outbuf = 2 ;
            break ;
        case 0x02800001 :  //N线电流
            g_Outbuf[0] = 0 ; //g_Emu_Data.I2.B08[0];
            g_Outbuf[1] = 0 ; //g_Emu_Data.I2.B08[1];
            g_Outbuf[2] = 0 ; //g_Emu_Data.I2.B08[2];
            g_K_Outbuf = 3 ;
            break ;
        case 0x02800002 :  //电网频率
            g_Outbuf[0] = g_Emu_Data.Freq.B08[0];
            g_Outbuf[1] = g_Emu_Data.Freq.B08[1];
            g_K_Outbuf = 2 ;
            break ;
        default:
            g_K_Outbuf = 1 ;
            g_Outbuf[0] = 2 ; // 错误信息字
            break ;
	}
	#endif
}
/*
*********************************************************************************************************
*	函 数 名: Uart_Proc_1F
*	功能说明: 645-1F命令， 校表处理
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void  Uart_Proc_1F ( void )
{
#if 0
    B32_B08 data;

    data.B08[0] = g_dl645.data_buf[14] ;
    data.B08[1] = g_dl645.data_buf[15] ;
    data.B08[2] = g_dl645.data_buf[16] ;
    data.B08[3] = g_dl645.data_buf[17] ;
    switch ( gu_Data_DI.B32 )
    {
        case 0x01000000 :  			//清除校准寄存器命令,初始化
            if ( data.B32 == 0 )
            {
				memcpy(g_EM_GainPara.U_Gain.B08, ADJ_DEFAULT, EE_PARAM_SUM);
#ifdef EEP_SAVE_EP
				EEP_WriteStr(EE_ADJ_BASEADDR, (uint8_t *)ADJ_DEFAULT[0].B08 ,EE_PARAM_SUM*2);	
				EEP_WriteStr(EE_ADJ_BASEADDR+EE_BACKUPS_OFFSET, (uint8_t *)ADJ_DEFAULT[0].B08 ,EE_PARAM_SUM*2);	  
#endif
                Emu_Adjust_Check();
				g_K_Outbuf = 0 ;
            }
            else
            {
                g_Outbuf[0] = 5 ;
                g_K_Outbuf = 1 ;
            }
            break ;
        case 0x01000001 :           //校UGAIN
			UGAIN_Adjust( &data.B08[0] ) ;	
			g_K_Outbuf = 0 ;
            break ;
        case 0x01000002 :           //校IAGAIN
			IAGAIN_Adjust ( &data.B08[0] ) ;
			g_K_Outbuf = 0;
            break ;
        case 0x01000003 :   		//校PAGAIN
			PAGAIN_Adjust ( &data.B08[0] ) ;
			g_K_Outbuf = 0;
            break ;
        case 0x01000004 :  			//校APHCAL
			APHCAL_Adjust ( &data.B08[0] ) ;
			g_K_Outbuf = 0;
            break ;
        case 0x01000005 :  			//校PAOFF
			PAOFF_Adjust ( &data.B08[0] ) ;
			g_K_Outbuf = 0;
            break ;
        case 0x01000006 :  			//ESEM16没有B线电流校准         
			g_Outbuf[0] = 5 ;	
			g_K_Outbuf = 1 ;
            break ;
        case 0x010000FF :  			//清除电量
            if ( data.B32 == 0 )
            {
                // add clear power		
				Energy_Reset();				
                g_K_Outbuf = 0 ;				
            }
            else
            {
                g_Outbuf[0] = 5 ;
                g_K_Outbuf = 1 ;
            }
            break ;
        default:
            g_K_Outbuf = 1 ;
            g_Outbuf[0] = 6 ;
            break ;
    }
    #endif
}
/*
*********************************************************************************************************
*	函 数 名: Uart_Tx
*	功能说明: uart 发送处理
*	形    参：无
*	返 回 值: 0:发送完成 1：发送未完成
*********************************************************************************************************
*/
uint8_t Uart_Tx(void)
{
	uint8_t senddata = 0 ;

	#if 1
	if (g_SendedCnt >= g_OutbufLen)
	{
        UART_RX_ENABLE;
        UART_TX_DISABLE;
        RS485_Send_Off();
        g_SendedCnt = 0;
        g_OutbufLen = 0;
		return 0;
	}
	else
	{
		senddata = g_Outbuf[g_SendedCnt++];
		UART0->TXBUF0.TXBUF0 = senddata;
		return 1;
	}
    #else
	if (g_dl645.Cnt >= g_dl645.Len)
	{
        UART_RX_ENABLE;
        UART_TX_DISABLE;
        RS485_Send_Off();
        g_dl645.DataLen = 0;
        g_dl645.Len = 0;
        g_dl645.Cnt = 0;
        g_dl645.Step = ST_START;			//接收状态
		return 0;
	}
	else
	{
		g_dl645.Overtimr_Timer = TX_TIMEOUT_MAX;
		senddata = g_dl645.data_buf[g_dl645.Cnt++];
		UART0->TXBUF0.TXBUF0 = senddata;
		return 1;
	}
    #endif
}
