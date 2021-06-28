#include <tftlcd.h>
#include "usmart.h"
#include "usmart_str.h"
#include "pcf8574.h"
#include "24cxx.h"
#include "ap3216c.h"
#include "myiic.h"
#include "adc_test.h"
#include "dac_test.h"
struct _m_usmart_nametab usmart_nametab[]=
{
#if USMART_USE_WRFUNS==1
	(void*)read_addr,"u32 read_addr(u32 addr)",
	(void*)write_addr,"void write_addr(u32 addr,u32 val)",	 
#endif
	/*
	(void*)delay_ms,"void delay_ms(u16 nms)",
 	(void*)delay_us,"void delay_us(u32 nus)",
 	*/
	(void*)LCD_Clear,"void LCD_Clear(u16 Color)",
	(void*)LCD_Fill,"void LCD_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color)",
	(void*)LCD_DrawLine,"void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2)",
	(void*)LCD_DrawRectangle,"void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2)",
	(void*)LCD_Draw_Circle,"void Draw_Circle(u16 x0,u16 y0,u8 r)",
	(void*)LCD_ShowNum,"void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size)",
	(void*)LCD_ShowString,"void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p)",
	(void*)LCD_Fast_DrawPoint,"void LCD_Fast_DrawPoint(u16 x,u16 y,u16 color)",
	(void*)LCD_ReadPoint,"u16 LCD_ReadPoint(u16 x,u16 y)",
	(void*)LCD_Display_Dir,"void LCD_Display_Dir(u8 dir)",
	(void*)LCD_ShowxNum,"void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode)",
	(u8*)PCF8574_ReadOneByte,"u8 PCF8574_ReadOneByte(void)",
	(void*)PCF8574_WriteOneByte,"void PCF8574_WriteOneByte(u8 DataToWrite)",
	(void*)PCF8574_WriteBit,"void PCF8574_WriteBit(u8 bit,u8 sta)",
	(u8*)PCF8574_ReadBit,"u8 PCF8574_ReadBit(u8 bit)",
	(uint8_t*)AT24CXX_ReadOneByte,"uint8_t AT24CXX_ReadOneByte(uint16_t ReadAddr)",
	(void*)AT24CXX_WriteOneByte,"void AT24CXX_WriteOneByte(uint16_t WriteAddr,uint8_t DataToWrite)",
	(void*)AT24CXX_WriteLenByte,"void AT24CXX_WriteLenByte(uint16_t WriteAddr,uint32_t DataToWrite,uint8_t Len)",
	(uint32_t*)AT24CXX_ReadLenByte,"uint32_t AT24CXX_ReadLenByte(uint16_t ReadAddr,uint8_t Len)",
	(u8*)AP3216C_WriteOneByte,"u8 AP3216C_WriteOneByte(u8 reg,u8 data)",
	(u8*)AP3216C_ReadOneByte,"u8 AP3216C_ReadOneByte(u8 reg)",
	(void*)AP3216C_ReadData,"void AP3216C_ReadData(u16* ir,u16* ps,u16* als)",
	(void*)MYIIC_Write_REG,"void MYIIC_Write_REG(uint8_t SlaveAddress, uint8_t REG_Address,uint8_t REG_data)",
	(uint8_t*)MYIIC_Read_REG,"uint8_t MYIIC_Read_REG(uint8_t SlaveAddress,uint8_t REG_Address)",
	(uint16_t*)Get_Adc,"u16  Get_Adc(u32 ch)",
	(uint16_t*)Get_Adc_Average,"u16 Get_Adc_Average(u32 ch,u8 times)",
	(void*)DAC1_Set_Vol,"void DAC1_Set_Vol(u16 vol)",

};						  

struct _m_usmart_dev usmart_dev=
{
	usmart_nametab,
	usmart_init,
	usmart_cmd_rec,
	usmart_exe,
	usmart_scan,
	sizeof(usmart_nametab)/sizeof(struct _m_usmart_nametab),
	0,
	0,
	1,
	0,
	0,
	0,
};   



















