
#define GLOBALS
/* Includes ------------------------------------------------------------------*/
		
#include "demo.h"
#include  <stdarg.h>

int Echo_distance(void); 
//void NVIC_Configuration(void);
void csb_Configuration(void);
//void Usart1_Init(void);
void timer_ini(void);
//void GPIO_Configuration(void);
//char *itoa(int value, char *string, int radix);
//void timer_ini(void);
extern void Delay_us(__IO uint32_t nTime);
unsigned int distance;
volatile unsigned int count;

int Echo_distance(void)
{	
		Delay_us(100000);	                    //延时100ms   
		//Led_ON(); 	   
		Trig_H
		Delay_us(1000);	                        //延时1ms
		Trig_L	  	 
		while(Echo==0);  
		count=0;		 					
		while(Echo==1);					//判断ECHO变高，并开始定时计时
		distance=((count*68)/1000);		      //根据计算的定时时间计算出距离障碍物的距离
		if(distance>400) 
			distance=2;   
    return distance;
}

void csb_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;		   			 //Trig
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;			 //通用推挽输出模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			 //输出模式最大速度50MHz
  GPIO_Init(GPIOC, &GPIO_InitStructure); 

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;		               //Echo
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;			 //通用推挽输出模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			 //输出模式最大速度50MHz
  GPIO_Init(GPIOC, &GPIO_InitStructure); 
}

/*void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				     //状态LED1
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;			 //通用推挽输出模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			 //输出模式最大速度50MHz
  GPIO_Init(GPIOB, &GPIO_InitStructure); 
}*/

/****************************************************************************
* 名    称：void timer_ini(void)
* 功    能：定时器初始化函数
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/ 
void timer_ini(void)
{
   TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
   //允许TIM2的时钟
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
   //重新将Timer设置为缺省值
   TIM_DeInit(TIM2);
   //采用内部时钟给TIM2提供时钟源
   TIM_InternalClockConfig(TIM2);
   //预分频系数为36000-1，这样计数器时钟为72MHz/144 = 500KHz   
   TIM_TimeBaseStructure.TIM_Prescaler = 144 - 1;
   //设置时钟分割
   TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
   //设置计数器模式为向上计数模式
   TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
   //设置计数溢出大小，每计2个数就产生一个更新事件
   TIM_TimeBaseStructure.TIM_Period = 2-1;
   //将配置应用到TIM2中
   TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);
   //清除溢出中断标志
   TIM_ClearFlag(TIM2, TIM_FLAG_Update);
   //禁止ARR预装载缓冲器
   TIM_ARRPreloadConfig(TIM2, DISABLE);
   //开启TIM2的中断
   TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
   TIM_Cmd(TIM2,ENABLE);
}
