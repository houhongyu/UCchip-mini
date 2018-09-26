						  
#include "demo.h"


void timer_ini(void);
extern unsigned char fd1[];
extern unsigned char fd2[];
extern unsigned char fd3[];
extern unsigned char fd4[];
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
   
   //定时器是为了产生250K的更新频率， 也就是4us的定时  用于超声波的控制
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

/******************* (C) COPYRIGHT STM32 *****END OF FILE****/

