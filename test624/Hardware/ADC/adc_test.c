#include <adc_test.h>
#include "delay.h"
#include "adc.h"
#include "stdio.h"
#include "usart.h"

u16 Get_Adc(u32 ch)   
{
    ADC_ChannelConfTypeDef ADC1_ChanConf;
    ch = ADC_CHANNEL_5;
    ADC1_ChanConf.Channel=ch;
    ADC1_ChanConf.Rank=1;
    ADC1_ChanConf.SamplingTime=ADC_SAMPLETIME_480CYCLES;
    ADC1_ChanConf.Offset=0;                 
    HAL_ADC_ConfigChannel(&hadc1,&ADC1_ChanConf);
	
    HAL_ADC_Start(&hadc1);
	
    HAL_ADC_PollForConversion(&hadc1,10);
   
	return (u16)HAL_ADC_GetValue(&hadc1);
}

u16 Get_Adc_Average(u32 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
	float adcx = 0;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc(ch);
		delay_ms(5);
	}

	adcx = ((float)(temp_val/times)*(3.3/4096));
	printf("\r\n V=%f2\r\n",adcx);

	return temp_val/times;
} 
