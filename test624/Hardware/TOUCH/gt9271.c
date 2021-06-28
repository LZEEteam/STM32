#include <tftlcd.h>
#include "gt9271.h"
#include "touch.h"
#include "ctiic.h"
#include "usart.h"
#include "delay.h" 
#include "string.h" 
#include "stdio.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//10.1����ݴ�����-GT9271 ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2017/6/7
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 


//GT9271���ò�����
//��һ���ֽ�Ϊ�汾��(0X41),���뱣֤�µİ汾�Ŵ��ڵ���GT9271�ڲ�
//flashԭ�а汾��,�Ż��������.
//�ֱ���1280*800
const u8 GT9271_CFG_TBL[]=
{ 
	0x41,0x00,0x05,0x20,0x03,0x0A,0x3D,0x20,0x01,0x0A,
	0x28,0x0F,0x6E,0x5A,0x03,0x05,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x18,0x1A,0x1E,0x14,0x8F,0x2F,0xAA,
	0x26,0x24,0x0C,0x08,0x00,0x00,0x00,0x81,0x03,0x2D,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x1A,0x3C,0x94,0xC5,0x02,0x07,0x00,0x00,0x04,
	0x9E,0x1C,0x00,0x89,0x21,0x00,0x77,0x27,0x00,0x68,
	0x2E,0x00,0x5B,0x37,0x00,0x5B,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x19,0x18,0x17,0x16,0x15,0x14,0x11,0x10,
	0x0F,0x0E,0x0D,0x0C,0x09,0x08,0x07,0x06,0x05,0x04,
	0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x02,0x04,0x06,0x07,0x08,0x0A,0x0C,
	0x0D,0x0F,0x10,0x11,0x12,0x13,0x14,0x19,0x1B,0x1C,
	0x1E,0x1F,0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,
	0x28,0x29,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x5D,0x01
};   

//����GT9147���ò���
//mode:0,���������浽flash
//     1,�������浽flash
u8 GT9271_Send_Cfg(u8 mode)
{
	u8 buf[2];
	u8 i=0;
	buf[0]=0;
	buf[1]=mode;	//�Ƿ�д�뵽GT9271 FLASH?  ���Ƿ���籣��
	for(i=0;i<(sizeof(GT9271_CFG_TBL)-2);i++)buf[0]+=GT9271_CFG_TBL[i];		//����У���
	buf[0]=(~buf[0])+1;
	GT9271_WR_Reg(GT9271_CFGS_REG,(u8*)GT9271_CFG_TBL,sizeof(GT9271_CFG_TBL));	//���ͼĴ�������
	GT9271_WR_Reg(GT9271_CHECK_REG,buf,2);    //д��У���,�����ø��±��
	return 0;
} 


//��GT9271д��һ������
//reg:��ʼ�Ĵ�����ַ
//buf:���ݻ�������
//len:д���ݳ���
//����ֵ:0,�ɹ�;1,ʧ��.
u8 GT9271_WR_Reg(u16 reg,u8 *buf,u8 len)
{
	u8 i;
	u8 ret=0;
	CT_IIC_Start();	
 	CT_IIC_Send_Byte(GT9271_CMD_WR);   	//����д���� 	 
	CT_IIC_Wait_Ack();
	CT_IIC_Send_Byte(reg>>8);   	//���͸�8λ��ַ
	CT_IIC_Wait_Ack(); 	 										  		   
	CT_IIC_Send_Byte(reg&0XFF);   	//���͵�8λ��ַ
	CT_IIC_Wait_Ack();  
	for(i=0;i<len;i++)
	{	   
    	CT_IIC_Send_Byte(buf[i]);  	//������
		ret=CT_IIC_Wait_Ack();
		if(ret)break;  
	}
    CT_IIC_Stop();					//����һ��ֹͣ����	    
	return ret; 
}
//��GT9271����һ������
//reg:��ʼ�Ĵ�����ַ
//buf:���ݻ�������
//len:�����ݳ���			  
void GT9271_RD_Reg(u16 reg,u8 *buf,u8 len)
{
	u8 i; 
	CT_IIC_Start();	
	CT_IIC_Send_Byte(GT9271_CMD_WR);   //����д���� 	 
	CT_IIC_Wait_Ack();
	CT_IIC_Send_Byte(reg>>8);   	//���͸�8λ��ַ
	CT_IIC_Wait_Ack(); 	 										  		   
	CT_IIC_Send_Byte(reg&0XFF);   	//���͵�8λ��ַ
	CT_IIC_Wait_Ack();  
	CT_IIC_Start();  	 	   
	CT_IIC_Send_Byte(GT9271_CMD_RD);   //���Ͷ�����		   
	CT_IIC_Wait_Ack();	   
	for(i=0;i<len;i++)
	{	   
		buf[i]=CT_IIC_Read_Byte(i==(len-1)?0:1); //������	  
	} 
	CT_IIC_Stop();					//����һ��ֹͣ����    
} 
//��ʼ��GT9271������
//����ֵ:0,��ʼ���ɹ�;1,��ʼ��ʧ�� 
u8 GT9271_Init(void)
{
	u8 temp[5]; 
    GPIO_InitTypeDef GPIO_Initure;
	__HAL_RCC_GPIOH_CLK_ENABLE();			//����GPIOHʱ��
    __HAL_RCC_GPIOI_CLK_ENABLE();			//����GPIOIʱ��             
    //PH7
    GPIO_Initure.Pin=GPIO_PIN_7;            //PH7
    GPIO_Initure.Mode=GPIO_MODE_INPUT;      //����
    GPIO_Initure.Pull=GPIO_PULLUP;          //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
    HAL_GPIO_Init(GPIOH,&GPIO_Initure);     //��ʼ��
            
    //PI8
    GPIO_Initure.Pin=GPIO_PIN_8;            //PI8
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //�������
    HAL_GPIO_Init(GPIOI,&GPIO_Initure);     //��ʼ��
	
	CT_IIC_Init();      	//��ʼ����������I2C����  
	GT9271_RST(0);			//��λ
	delay_ms(10);
 	GT9271_RST(1);			//�ͷŸ�λ		    
	delay_ms(10); 
	
    GPIO_Initure.Pin=GPIO_PIN_7;            //PH7
    GPIO_Initure.Mode=GPIO_MODE_INPUT;      //����
    GPIO_Initure.Pull=GPIO_NOPULL;          //��������������������
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
    HAL_GPIO_Init(GPIOH,&GPIO_Initure);     //��ʼ��
	
	delay_ms(100);   
	GT9271_RD_Reg(GT9271_PID_REG,temp,4);		//��ȡ��ƷID
	temp[4]=0;
	printf("CTP ID:%s\r\n\r\n",temp);			//��ӡID 
	if(strcmp((char*)temp,"9271")==0)			//ID==9147
	{
		temp[0]=0X02;			
		GT9147_WR_Reg(GT9271_CTRL_REG,temp,1);	//��λGT9271
		GT9147_RD_Reg(GT9271_CFGS_REG,temp,1);	//��ȡGT9271_CFGS_REG�Ĵ���
		if(temp[0]<0X41)						//Ĭ�ϰ汾�Ƚϵ�,��Ҫ����flash����
		{
			printf("Default Ver:%d\r\n",temp[0]);
			GT9271_Send_Cfg(1);					//���²���������
		}
		delay_ms(10);
		temp[0]=0X00;	 
		GT9147_WR_Reg(GT9271_CTRL_REG,temp,1);	//������λ   
		return 0;
	} 
	return 1;  
}

const u16 GT9271_TPX_TBL[10]=
{GT9271_TP1_REG,GT9271_TP2_REG,GT9271_TP3_REG,GT9271_TP4_REG,GT9271_TP5_REG,
GT9271_TP6_REG,GT9271_TP7_REG,GT9271_TP8_REG,GT9271_TP9_REG,GT9271_TP10_REG,};
//ɨ�败����(���ò�ѯ��ʽ)
//mode:0,����ɨ��.
//����ֵ:��ǰ����״̬.
//0,�����޴���;1,�����д���
u8 GT9271_Scan(u8 mode)
{
	u8 buf[4];
	vu8 i=0;
	u8 res=0;
	u16 temp;
	u16 tempsta;
 	static u8 t=0;//���Ʋ�ѯ���,�Ӷ�����CPUռ����   
	t++;
	if((t%10)==0||t<10)//����ʱ,ÿ����10��CTP_Scan�����ż��1��,�Ӷ���ʡCPUʹ����
	{
		GT9271_RD_Reg(GT9271_GSTID_REG,&mode,1);	//��ȡ�������״̬  
 		if(mode&0X80&&((mode&0XF)<11))
		{
			i=0;
			GT9271_WR_Reg(GT9271_GSTID_REG,(u8*)&i,1);	//���־ 		
		}		
		if((mode&0XF)&&((mode&0XF)<11))
		{
			temp=0XFFFF<<(mode&0XF);	//����ĸ���ת��Ϊ1��λ��,ƥ��tp_dev.sta���� 
			tempsta=tp_dev.sta;			//���浱ǰ��tp_dev.staֵ
			tp_dev.sta=(~temp)|TP_PRES_DOWN|TP_CATH_PRES; 
			tp_dev.x[9]=tp_dev.x[0];	//���津��0������
			tp_dev.y[9]=tp_dev.y[0];
			for(i=0;i<10;i++)
			{
				if(tp_dev.sta&(1<<i))	//������Ч?
				{
					GT9271_RD_Reg(GT9271_TPX_TBL[i],buf,6);	//��ȡXY����ֵ
					if(tp_dev.touchtype&0X01)//����
					{
						tp_dev.y[i]=((u16)buf[3]<<8)+buf[2];
						tp_dev.x[i]=((u16)buf[1]<<8)+buf[0];
						 
					}else
					{
						tp_dev.x[i]=800-(((u16)buf[3]<<8)+buf[2]);
						tp_dev.y[i]=((u16)buf[1]<<8)+buf[0];
					}  
					//printf("x[%d]:%d,y[%d]:%d\r\n",i,tp_dev.x[i],i,tp_dev.y[i]); 
				}			
			} 
			res=1;
			if(tp_dev.x[0]>lcddev.width||tp_dev.y[0]>lcddev.height)//�Ƿ�����(���곬����)
			{ 
				if((mode&0XF)>1)		//��������������,�򸴵ڶ�����������ݵ���һ������.
				{
					tp_dev.x[0]=tp_dev.x[1];
					tp_dev.y[0]=tp_dev.y[1];
					t=0;				//����һ��,��������������10��,�Ӷ����������
				}else					//�Ƿ�����,����Դ˴�����(��ԭԭ����)  
				{
					tp_dev.x[0]=tp_dev.x[9];
					tp_dev.y[0]=tp_dev.y[9];
					mode=0X80;		
					tp_dev.sta=tempsta;	//�ָ�tp_dev.sta
				}
			}else t=0;					//����һ��,��������������10��,�Ӷ����������
		}
	}
	if((mode&0X8F)==0X80)//�޴����㰴��
	{ 
		if(tp_dev.sta&TP_PRES_DOWN)		//֮ǰ�Ǳ����µ�
		{
			tp_dev.sta&=~TP_PRES_DOWN;	//��ǰ����ɿ�
		}else							//֮ǰ��û�б�����
		{ 
			tp_dev.x[0]=0xffff;
			tp_dev.y[0]=0xffff;
			tp_dev.sta&=0XE000;			//�������Ч���	
		}	 
	} 	
	if(t>240)t=10;//���´�10��ʼ����
	return res;
}
 



























