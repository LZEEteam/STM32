#include "delay.h"
#include "sys.h"
#include "tim.h"

void delay_us(uint32_t us)
{
	  (&htim3)->Instance->CNT = (0x0000efff -us);//  __HAL_TIM_SET_COUNTER(&htim3,differ);

	//  HAL_TIM_Base_Start(&htim3);
	  SET_BIT(TIM3->CR1, TIM_CR1_CEN);

	//__HAL_TIM_GET_COUNTER(&htim3);
	  while(((&htim3)->Instance->CNT) < 0x0000effe)	//  READ_REG(TIM3->CNT)
	  {
	  }
	//  HAL_TIM_Base_Stop(&htim3);
	  CLEAR_BIT(TIM3->CR1, TIM_CR1_CEN);

}

void delay_ms(uint32_t ms)
{
	HAL_Delay(ms);
}

































