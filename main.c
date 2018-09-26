/****************************************************************************
* 文件历史:
* 版本号  日期       作者    说明
* v0.1    2014-12-19 sun68  创建该文件
*
*/

#define GLOBALS
/* Includes ------------------------------------------------------------------*/
		
#include "demo.h"
#include  <stdarg.h>
	 

static __IO uint32_t TimingDelay;
void Delay_us(__IO uint32_t nTime);
void RCC_Configuration(void);  
//void LED_Config(void);
void SysTick_Init(void);
extern void Read_RT(void);
extern float light(void);
extern void iic_init(void);
extern void timer_ini(void);
extern void csb_Configuration(void);
extern int Echo_distance(void);

extern unsigned char succ;
extern float datalx;
//extern unsigned char wd[];
//extern unsigned char sd[];
//extern unsigned char du[];

/****************************************************************************
* 名    称：int main(void)
* 功    能：主函数
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：
****************************************************************************/ 

int main(void)
{	
  RCC_Configuration();	             //设置内部时钟及外设时钟使能	 
	SysTick_Init();                //时钟节拍中断时1ms一次  用于定时 
  iic_init();                 //光照强度IIC
	csb_Configuration();				 //超声波控制脚初始化 
	timer_ini();                 //测距所用定时器2初始化
  while(1)
  { 
	  Read_RT();                   //读取温度值
		light();                     //读取光照度
		Echo_distance();             //读取液位值
		
  }
}

/****************************************************************************
* 名    称：void RCC_Configuration(void)
* 功    能：系统时钟配置为72MHZ， 外设时钟配置
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/ 
void RCC_Configuration(void){

   SystemInit();  
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC , ENABLE);
  					
}
/****************************************************************************
* 名    称：void Delay(__IO uint32_t nTime)
* 功    能：定时延时程序 1us为单位
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/  
void Delay_us(__IO uint32_t nTime)
{ 
  TimingDelay = nTime;

  while(TimingDelay != 0);
}
/****************************************************************************
* 名    称：void TimingDelay_Decrement(void)
* 功    能：获取节拍程序
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/  
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}

/******时钟节拍中断时1ms一次  用于定时 ******/
void SysTick_Init(void)
{
	if (SysTick_Config(72000))		    //时钟节拍中断时1ms一次  用于定时 
  { 
    /* Capture error */ 
     while (1);
  }
}
/****************************************************************************
* 名    称：void LED_Config(void)
* 功    能：LED 控制初始化函数
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/ 
/*void LED_Config(void){
  GPIO_InitTypeDef GPIO_InitStructure;	  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				     //LED1  V1	  配置为通用推挽输出  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			 //口线翻转速度为50MHz
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				     //PA6配置为通用推挽输出  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			 //口线翻转速度为50MHz
  GPIO_Init(GPIOA, &GPIO_InitStructure);	
  
  GPIO_SetBits(GPIOA, GPIO_Pin_8);	
  
  Delay_us(100000);
  
  GPIO_ResetBits(GPIOB, GPIO_Pin_5);	                      //LED1灭		
} */                                      


/****************************************************************************/
