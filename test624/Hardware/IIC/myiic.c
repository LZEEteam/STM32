#include "myiic.h"
#include "tim.h"
#include "delay.h"

void IIC_Start(void)
{
	SDA_OUT();     //sda�����
	IIC_SDA(1);	  	  
	IIC_SCL(1);
	delay_us(4);
 	IIC_SDA(0);//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL(0);//ǯסI2C���ߣ�׼�����ͻ��������
}	  
//����IICֹͣ�ź�
void IIC_Stop(void)
{
	SDA_OUT();//sda�����
	IIC_SCL(0);
	IIC_SDA(0);//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL(1); 
	delay_us(4);			
	IIC_SDA(1);//����I2C���߽����ź�
}

uint8_t IIC_Wait_Ack(void)
{
	uint8_t ucErrTime=0;
	SDA_IN();      //SDA����Ϊ����
	IIC_SDA(1);delay_us(1);	   
	IIC_SCL(1);delay_us(1);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL(0);//ʱ�����0
	return 0;  
} 
//����ACKӦ��
void IIC_Ack(void)
{
	IIC_SCL(0);
	SDA_OUT();
	IIC_SDA(0);
	delay_us(2);
	IIC_SCL(1);
	delay_us(2);
	IIC_SCL(0);
}

void IIC_NAck(void)
{
	IIC_SCL(0);
	SDA_OUT();
	IIC_SDA(1);
	delay_us(2);
	IIC_SCL(1);
	delay_us(2);
	IIC_SCL(0);
}					 				     

void IIC_Send_Byte(uint8_t txd)
{                        
    uint8_t t;
	SDA_OUT(); 	    
    IIC_SCL(0);//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        IIC_SDA((txd&0x80)>>7);
        txd<<=1; 	  
		delay_us(2);   //��TEA5767��������ʱ���Ǳ����
		IIC_SCL(1);
		delay_us(2); 
		IIC_SCL(0);	
		delay_us(2);
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK
uint8_t IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
        IIC_SCL(0); 
        delay_us(2);
		IIC_SCL(1);
        receive<<=1;
        if(READ_SDA)receive++;   
		delay_us(1); 
    }					 
    if (!ack)
        IIC_NAck();//����nACK
    else
        IIC_Ack(); //����ACK
    return receive;
}



void MYIIC_Write_REG(uint8_t SlaveAddress, uint8_t REG_Address,uint8_t REG_data)
{
    IIC_Start();
    IIC_Send_Byte(SlaveAddress);
    IIC_Wait_Ack();
    IIC_Send_Byte(REG_Address);
    IIC_Wait_Ack();
    IIC_Send_Byte(REG_data);
    IIC_Wait_Ack();
    IIC_Stop();
}


uint8_t MYIIC_Read_REG(uint8_t SlaveAddress,uint8_t REG_Address)
{
    uint8_t data;
    IIC_Start();
    IIC_Send_Byte(SlaveAddress);
    IIC_Wait_Ack();
    IIC_Send_Byte(REG_Address);
    IIC_Wait_Ack();
    IIC_Start();
    IIC_Send_Byte(SlaveAddress + 1);
    IIC_Wait_Ack();
    data = IIC_Read_Byte(0);
    IIC_NAck();
    IIC_Stop();
    return data;
}


u8 MYIIC_CheckDevice(uint8_t SlaveAddress)
{
    IIC_Start();
    IIC_Send_Byte(SlaveAddress);
    IIC_Wait_Ack();
    {
	IIC_Stop();
	return 0;
    }
    IIC_Stop();
    return 1;
}

