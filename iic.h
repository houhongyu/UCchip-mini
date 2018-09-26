#ifndef __IIC__H_
#define __IIC__H_
#include "stm32f10x.h"	   
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_tim.h"	 
#include "stm32f10x_spi.h"
#include "stm32f10x_i2c.h"
#include "misc.h"

#include  <stdarg.h>
#define IIC_SCL_Pin  GPIO_Pin_6
#define IIC_SDA_Pin  GPIO_Pin_7
#define GPIO_IIC     GPIOB
#define RCC_APB2Periph_GPIOIIC  RCC_APB2Periph_GPIOB

#define IIC_SDA_OUT()  {GPIOB->CRL&=0XFF0FFFFF;GPIOB->CRL|=0x00300000;}//输入模式上拉下拉输入模式
#define IIC_SDA_IN()   {GPIOB->CRL&=0XFF0FFFFF;GPIOB->CRL|=0x00800000;}//通用推挽输出50MZ

#define SDA_PIN_OUT       PCout(7)
#define SCL_PIN_OUT       PCout(6)
#define SDA_PIN_IN        PCin(7)

void iic_init(void);
void iic_start(void);
void iic_stop(void);
u8 iic_wait_ack(void);
void iic_byte_write(u8 buf);
u8 iic_byte_read(unsigned char ask);
void iic_page_write(u8 device_address,u8 word_address,u8 byte_num,u8 *send_buff);
void iic_nbyte_read(u8 device_address,u8 word_address,u8 byte_num ,u8 *receive_buff);

void AT24_onebyte_write(u8 device_address,u8 word_address,u8 send_buff);
u8  AT24_onebyte_read(u8 device_address,u8 word_address);
void AT24_nbyte_read(u8 device_address,u8 word_address,u8 num,u8 *receive_buf);
#endif
