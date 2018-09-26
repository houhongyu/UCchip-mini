
#define GLOBALS
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"	   
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_tim.h"	 
#include "stm32f10x_spi.h"
#include "stm32f10x_i2c.h"
#include "misc.h"	
#include  <stdarg.h>

extern void Delay_us(__IO uint32_t nTime);
void Read_RT(void);
unsigned char Read_DAT(void);
unsigned char RH_H,RH_L,T_H,T_L,Sumcheck=0,TEMP,succ=0,ncount=0;

//extern unsigned char wd[];
//extern unsigned char sd[];
//extern unsigned char du[];

/****************************************************************************
* 名    称：unsigned char Read_DAT(void)
* 功    能：DHT11读数据
* 入口参数：无
* 出口参数：返回8位的数据
* 说    明：
* 调用方法：无 
****************************************************************************/ 
unsigned char Read_DAT(void)
{
   unsigned char i=0,temp=0;
   while(i<8)
	 {
			ncount=0;
			while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==0&&ncount<254);	      //1bit 开始
			ncount=0;
			temp=temp<<1;
			while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==1&&ncount<254);		  //读取有效的1bit
			if(ncount<30) temp=temp&0xfe;					 //26-28us 代表读取位为0
			else temp=temp|0x01;					//70us 代表读取位为1 
			i++;
   }	  
   return(temp);	
}
/****************************************************************************
* 名    称：void Read_RT(void)
* 功    能：读湿度和读温度
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/ 
void Read_RT(void)
{
   unsigned char tp=0;			
   GPIO_InitTypeDef GPIO_InitStructure;	  
   Delay_us(100);	
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				     //PA8配置为通用推挽输出  
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			 //口线翻转速度为50MHz
   GPIO_Init(GPIOA, &GPIO_InitStructure);	
   GPIO_SetBits(GPIOA, GPIO_Pin_8);	
   Delay_us(1000000);						//延时1秒
   GPIO_ResetBits(GPIOA, GPIO_Pin_8);		
   Delay_us(20000);						 //延时20ms
   GPIO_SetBits(GPIOA, GPIO_Pin_8);	
   Delay_us(25);	  					 //延时25us
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				 //PA8配置为浮空输入  
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//口线翻转速度为50MHz
   GPIO_Init(GPIOA, &GPIO_InitStructure);
   Delay_us(30);
   if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==0)
	 {				 //判断是否出现低80us响应
      ncount=0;
   	  while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==0&&ncount<254);   //低80uc响应
			ncount=0;
			while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==1&&ncount<254);	  //高80us响应
			RH_H=Read_DAT();					//读湿度整数部分
			RH_L=Read_DAT();					//读湿度小数部分
			T_H=Read_DAT();						 //读温度整数部分
			T_L=Read_DAT();						 //读温度小数部分
			Sumcheck=Read_DAT();					//读校验和
			tp=RH_H+RH_L+T_H+T_L; 					 //计算校验和
			if(tp==Sumcheck) succ=1;			//读取成功
			else succ=0;					 //读取失败
			ncount=0;
   }
   else succ=0;	   							 //读取失败
   //if(succ==1) GPIO_SetBits(GPIOB, GPIO_Pin_5);	                 //LED1 亮 
   //else GPIO_ResetBits(GPIOB, GPIO_Pin_5);	                     //LED1灭
}
/****************************************************************************/
