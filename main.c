/****************************************************************************
* �ļ���ʷ:
* �汾��  ����       ����    ˵��
* v0.1    2014-12-19 sun68  �������ļ�
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
* ��    �ƣ�int main(void)
* ��    �ܣ�������
* ��ڲ�������
* ���ڲ�������
* ˵    ����
* ���÷�����
****************************************************************************/ 

int main(void)
{	
  RCC_Configuration();	             //�����ڲ�ʱ�Ӽ�����ʱ��ʹ��	 
	SysTick_Init();                //ʱ�ӽ����ж�ʱ1msһ��  ���ڶ�ʱ 
  iic_init();                 //����ǿ��IIC
	csb_Configuration();				 //���������ƽų�ʼ�� 
	timer_ini();                 //������ö�ʱ��2��ʼ��
  while(1)
  { 
	  Read_RT();                   //��ȡ�¶�ֵ
		light();                     //��ȡ���ն�
		Echo_distance();             //��ȡҺλֵ
		
  }
}

/****************************************************************************
* ��    �ƣ�void RCC_Configuration(void)
* ��    �ܣ�ϵͳʱ������Ϊ72MHZ�� ����ʱ������
* ��ڲ�������
* ���ڲ�������
* ˵    ����
* ���÷������� 
****************************************************************************/ 
void RCC_Configuration(void){

   SystemInit();  
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC , ENABLE);
  					
}
/****************************************************************************
* ��    �ƣ�void Delay(__IO uint32_t nTime)
* ��    �ܣ���ʱ��ʱ���� 1usΪ��λ
* ��ڲ�������
* ���ڲ�������
* ˵    ����
* ���÷������� 
****************************************************************************/  
void Delay_us(__IO uint32_t nTime)
{ 
  TimingDelay = nTime;

  while(TimingDelay != 0);
}
/****************************************************************************
* ��    �ƣ�void TimingDelay_Decrement(void)
* ��    �ܣ���ȡ���ĳ���
* ��ڲ�������
* ���ڲ�������
* ˵    ����
* ���÷������� 
****************************************************************************/  
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}

/******ʱ�ӽ����ж�ʱ1msһ��  ���ڶ�ʱ ******/
void SysTick_Init(void)
{
	if (SysTick_Config(72000))		    //ʱ�ӽ����ж�ʱ1msһ��  ���ڶ�ʱ 
  { 
    /* Capture error */ 
     while (1);
  }
}
/****************************************************************************
* ��    �ƣ�void LED_Config(void)
* ��    �ܣ�LED ���Ƴ�ʼ������
* ��ڲ�������
* ���ڲ�������
* ˵    ����
* ���÷������� 
****************************************************************************/ 
/*void LED_Config(void){
  GPIO_InitTypeDef GPIO_InitStructure;	  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				     //LED1  V1	  ����Ϊͨ���������  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			 //���߷�ת�ٶ�Ϊ50MHz
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				     //PA6����Ϊͨ���������  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			 //���߷�ת�ٶ�Ϊ50MHz
  GPIO_Init(GPIOA, &GPIO_InitStructure);	
  
  GPIO_SetBits(GPIOA, GPIO_Pin_8);	
  
  Delay_us(100000);
  
  GPIO_ResetBits(GPIOB, GPIO_Pin_5);	                      //LED1��		
} */                                      


/****************************************************************************/
