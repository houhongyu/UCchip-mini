						  
#include "demo.h"


void timer_ini(void);
extern unsigned char fd1[];
extern unsigned char fd2[];
extern unsigned char fd3[];
extern unsigned char fd4[];
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
   
   //��ʱ����Ϊ�˲���250K�ĸ���Ƶ�ʣ� Ҳ����4us�Ķ�ʱ  ���ڳ������Ŀ���
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

/******************* (C) COPYRIGHT 2011 �ܶ�STM32 *****END OF FILE****/

