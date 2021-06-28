#ifndef _KEY_H
#define _KEY_H
#include "gpio.h"


#define KEY0        HAL_GPIO_ReadPin(GPIOH,GPIO_PIN_3)  //KEY0_PH3
#define KEY1        HAL_GPIO_ReadPin(GPIOH,GPIO_PIN_2)  //KEY1_PH2
#define KEY2        HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_13) //KEY2_PC13
#define WK_UP       HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)  //WKUP_PA0

#define KEY0_PRES 	1  	//KEY0
#define KEY1_PRES	2	//KEY1
#define KEY2_PRES	3	//KEY2
#define WKUP_PRES   4	//WKUP


uint8_t KEY_Scan(uint8_t mode);
#endif
