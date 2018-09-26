
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
* ��    �ƣ�unsigned char Read_DAT(void)
* ��    �ܣ�DHT11������
* ��ڲ�������
* ���ڲ���������8λ������
* ˵    ����
* ���÷������� 
****************************************************************************/ 
unsigned char Read_DAT(void)
{
   unsigned char i=0,temp=0;
   while(i<8)
	 {
			ncount=0;
			while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==0&&ncount<254);	      //1bit ��ʼ
			ncount=0;
			temp=temp<<1;
			while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==1&&ncount<254);		  //��ȡ��Ч��1bit
			if(ncount<30) temp=temp&0xfe;							              //26-28us �����ȡλΪ0
			else temp=temp|0x01;									              //70us �����ȡλΪ1 
			i++;
   }	  
   return(temp);	
}
/****************************************************************************
* ��    �ƣ�void Read_RT(void)
* ��    �ܣ���ʪ�ȺͶ��¶�
* ��ڲ�������
* ���ڲ�������
* ˵    ����
* ���÷������� 
****************************************************************************/ 
void Read_RT(void)
{
   unsigned char tp=0;			
   GPIO_InitTypeDef GPIO_InitStructure;	  
   Delay_us(100);	
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				     //PA8����Ϊͨ���������  
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			 //���߷�ת�ٶ�Ϊ50MHz
   GPIO_Init(GPIOA, &GPIO_InitStructure);	
   GPIO_SetBits(GPIOA, GPIO_Pin_8);	
   Delay_us(1000000);												//��ʱ1��
   GPIO_ResetBits(GPIOA, GPIO_Pin_8);		
   Delay_us(20000);												 //��ʱ20ms
   GPIO_SetBits(GPIOA, GPIO_Pin_8);	
   Delay_us(25);	  												 //��ʱ25us
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				     //PA8����Ϊ��������  
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			 //���߷�ת�ٶ�Ϊ50MHz
   GPIO_Init(GPIOA, &GPIO_InitStructure);
   Delay_us(30);
   if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==0)
	 {				 //�ж��Ƿ���ֵ�80us��Ӧ
      ncount=0;
   	  while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==0&&ncount<254);   //��80uc��Ӧ
			ncount=0;
			while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==1&&ncount<254);	  //��80us��Ӧ
			RH_H=Read_DAT();											 //��ʪ����������
			RH_L=Read_DAT();											 //��ʪ��С������
			T_H=Read_DAT();											 //���¶���������
			T_L=Read_DAT();											 //���¶�С������
			Sumcheck=Read_DAT();										 //��У���
			tp=RH_H+RH_L+T_H+T_L; 									 //����У���
			if(tp==Sumcheck) succ=1;									 //��ȡ�ɹ�
			else succ=0;												 //��ȡʧ��
			ncount=0;
   }
   else succ=0;	   												 //��ȡʧ��
   //if(succ==1) GPIO_SetBits(GPIOB, GPIO_Pin_5);	                 //LED1 �� 
   //else GPIO_ResetBits(GPIOB, GPIO_Pin_5);	                     //LED1��
}
/****************************************************************************/
