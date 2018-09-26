#include "stm32f10x.h"	   
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_tim.h"	 
#include "stm32f10x_spi.h"
#include "stm32f10x_i2c.h"
#include "misc.h"

#ifdef GLOBALS 
#define EXT
#else
#define EXT extern 
#endif
//#define Led_ON()   GPIO_SetBits(GPIOB, GPIO_Pin_5)  	      //LED1ÁÁ
//#define Led_OFF()  GPIO_ResetBits(GPIOB, GPIO_Pin_5) 	      //LED2Ãð

#define Trig_H  GPIO_SetBits(GPIOC, GPIO_Pin_8);			//³¬Éù²¨¿ØÖÆTrig 	
#define Trig_L  GPIO_ResetBits(GPIOC, GPIO_Pin_8);			
#define Echo   GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_9)	 	//³¬Éù²¨»ØÉùEcho	

