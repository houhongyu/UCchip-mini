
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
		Delay_us(100000);	                    //��ʱ100ms   
		//Led_ON(); 	   
		Trig_H
		Delay_us(1000);	                        //��ʱ1ms
		Trig_L	  	 
		while(Echo==0);  
		count=0;		 					
		while(Echo==1);					//�ж�ECHO��ߣ�����ʼ��ʱ��ʱ
		distance=((count*68)/1000);		      //���ݼ���Ķ�ʱʱ�����������ϰ���ľ���
		if(distance>400) 
			distance=2;   
    return distance;
}

void csb_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;		   			 //Trig
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;			 //ͨ���������ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			 //���ģʽ����ٶ�50MHz
  GPIO_Init(GPIOC, &GPIO_InitStructure); 

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;		               //Echo
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;			 //ͨ���������ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			 //���ģʽ����ٶ�50MHz
  GPIO_Init(GPIOC, &GPIO_InitStructure); 
}

/*void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				     //״̬LED1
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;			 //ͨ���������ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			 //���ģʽ����ٶ�50MHz
  GPIO_Init(GPIOB, &GPIO_InitStructure); 
}*/

/****************************************************************************
* ��    �ƣ�void timer_ini(void)
* ��    �ܣ���ʱ����ʼ������
* ��ڲ�������
* ���ڲ�������
* ˵    ����
* ���÷������� 
****************************************************************************/ 
void timer_ini(void)
{
   TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
   //����TIM2��ʱ��
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
   //���½�Timer����Ϊȱʡֵ
   TIM_DeInit(TIM2);
   //�����ڲ�ʱ�Ӹ�TIM2�ṩʱ��Դ
   TIM_InternalClockConfig(TIM2);
   //Ԥ��Ƶϵ��Ϊ36000-1������������ʱ��Ϊ72MHz/144 = 500KHz   
   TIM_TimeBaseStructure.TIM_Prescaler = 144 - 1;
   //����ʱ�ӷָ�
   TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
   //���ü�����ģʽΪ���ϼ���ģʽ
   TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
   //���ü��������С��ÿ��2�����Ͳ���һ�������¼�
   TIM_TimeBaseStructure.TIM_Period = 2-1;
   //������Ӧ�õ�TIM2��
   TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);
   //�������жϱ�־
   TIM_ClearFlag(TIM2, TIM_FLAG_Update);
   //��ֹARRԤװ�ػ�����
   TIM_ARRPreloadConfig(TIM2, DISABLE);
   //����TIM2���ж�
   TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
   TIM_Cmd(TIM2,ENABLE);
}
