#include "pcf8574.h"


//��ʼ��PCF8574
u8 PCF8574_Init(void)
{
    u8 temp=0;
    /*
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOB_CLK_ENABLE();           //ʹ��GPIOBʱ��
	
    GPIO_Initure.Pin=GPIO_PIN_12;           //PB12
    GPIO_Initure.Mode=GPIO_MODE_INPUT;      //����
    GPIO_Initure.Pull=GPIO_PULLUP;          //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);     //��ʼ��
    */
   // IIC_Init();					            //IIC��ʼ��
	//���PCF8574�Ƿ���λ
    IIC_Start();    	 	   
	IIC_Send_Byte(PCF8574_ADDR);            //д��ַ
	temp=IIC_Wait_Ack();		            //�ȴ�Ӧ��,ͨ���ж��Ƿ���ACKӦ��,���ж�PCF8574��״̬
    IIC_Stop();					            //����һ��ֹͣ����
    PCF8574_WriteOneByte(0XFF);	            //Ĭ�����������IO����ߵ�ƽ
	return temp;
}

//��ȡPCF8574��8λIOֵ
//����ֵ:����������
u8 PCF8574_ReadOneByte(void)
{				  
	u8 temp=0;		  	    																 
    IIC_Start();    	 	   
	IIC_Send_Byte(PCF8574_ADDR|0X01);   //�������ģʽ
	IIC_Wait_Ack();	 
    temp=IIC_Read_Byte(0);		   
    IIC_Stop();							//����һ��ֹͣ����
	return temp;
}
//��PCF8574д��8λIOֵ
//DataToWrite:Ҫд�������
void PCF8574_WriteOneByte(u8 DataToWrite)
{				   	  	    																 
    IIC_Start();  
    IIC_Send_Byte(PCF8574_ADDR|0X00);   //����������ַ0X40,д����
	IIC_Wait_Ack();	    										  		   
	IIC_Send_Byte(DataToWrite);    	 	//�����ֽ�
	IIC_Wait_Ack();      
    IIC_Stop();							//����һ��ֹͣ����
	delay_ms(10);	 
}

//����PCF8574ĳ��IO�ĸߵ͵�ƽ
//bit:Ҫ���õ�IO���,0~7
//sta:IO��״̬;0��1
void PCF8574_WriteBit(u8 bit,u8 sta)
{
    u8 data;
    data=PCF8574_ReadOneByte(); //�ȶ���ԭ��������
    if(sta==0)data&=~(1<<bit);     
    else data|=1<<bit;
    PCF8574_WriteOneByte(data); //д���µ�����
}

//��ȡPCF8574��ĳ��IO��ֵ
//bit��Ҫ��ȡ��IO���,0~7
//����ֵ:��IO��ֵ,0��1
u8 PCF8574_ReadBit(u8 bit)
{
    u8 data;
    data=PCF8574_ReadOneByte(); //�ȶ�ȡ���8λIO��ֵ
    if(data&(1<<bit))return 1;
    else return 0;   
}  
    
