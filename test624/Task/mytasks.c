#include "mytasks.h"
#include "usart.h"
#include "stdio.h"
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "sys.h"
#include "gpio.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"
#include "usmart.h"
#include "key.h"
#include "touch.h"


void UASRT_RE(void const * argument)
{
	u8 len;
	while(1){
		if(USART_RX_STA&0x8000)
		{
			len=USART_RX_STA&0x3fff;
			printf("%s\r\n",USART_RX_BUF);
			usmart_exe_usb(USART_RX_BUF,len);
			USART_RX_STA=0;
		}
		osDelay(100);
	}
}

void Key_Scan(void const * argument)
{
	u8 key;
	while(1){
		key=KEY_Scan(0); 		    //得到键值
			   	if(key)
				{
					switch(key)
					{
						case WKUP_PRES:
							printf("WKUP_PRES\r\n");
							break;
						case KEY2_PRES:
							printf("KEY2_PRES\r\n");
							break;
						case KEY1_PRES:
							printf("KEY1_PRES\r\n");
							break;
						case KEY0_PRES:
							printf("KEY0_PRES\r\n");
							break;
					}
				}
			   	osDelay(100);
	}
}

void TP_test(void const * argument){
	while(1){

		if(tp_dev.touchtype&0X80){
			printf("ctp_test\r\n");
			ctp_test();//电容屏测试

		}
			else
				{
				printf("rtp_test\r\n");
				rtp_test(); 					//电阻屏测试
				}
			osDelay(100);
		}
}
