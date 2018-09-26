#define GLOBALS
/* Includes ------------------------------------------------------------------*/
#include "iic.h"
#include "sys.h"

#define BHAddWrite     0x46      //�ӻ���ַ+���д����λ
#define BHAddRead      0x47      //�ӻ���ַ+��������λ
#define BHPowDown      0x00      //�ر�ģ��
#define BHPowOn        0x01      //��ģ��ȴ�����ָ��
#define BHReset        0x07      //�������ݼĴ���ֵ��PowerOnģʽ����Ч
#define BHModeH1       0x10      //�߷ֱ��� ��λ1lx ����ʱ��120ms
#define BHModeH2       0x11      //�߷ֱ���ģʽ2 ��λ0.5lx ����ʱ��120ms
#define BHModeL        0x13      //�ͷֱ��� ��λ4lx ����ʱ��16ms
#define BHSigModeH     0x20      //һ�θ߷ֱ��� ���� ������ģ��ת�� PowerDownģʽ
#define BHSigModeH2    0x21      //ͬ������
#define BHSigModeL     0x23      // ������


float light(void);
void bh_data_send(u8 command);
u16 bh_data_read(void);
extern void Delay_us(__IO uint32_t nTime);
float datalx=0;

float light(void)
{                 
	bh_data_send(BHPowOn);    //??????
	bh_data_send(BHReset);    //???????
	bh_data_send(BHModeH2);   //????????2
	Delay_us(180000);            //???????????,??????180ms??
	datalx =bh_data_read()/1.2; //???????????1.2??????lx????????
	return datalx;
}


u16 bh_data_read(void)
{
	u16 buf;
	iic_start();                       
	iic_byte_write(BHAddRead);         
	iic_wait_ack();                    
	buf=iic_byte_read(1);              
	buf=buf<<8;                        
	buf+=0x00ff&iic_byte_read(0);      //??????????
	iic_stop();                        //?????? 
	return buf; 
}
void bh_data_send(u8 command)
{
    do
		{
			iic_start();                      
			iic_byte_write(BHAddWrite);       
    } while(iic_wait_ack());          
    iic_byte_write(command);         
    iic_wait_ack();                   
    iic_stop();                       
}

/*********************************************************************************
��������iic_init
��  �ܣ�����SDA ��SCL�˿�
��  ������
����ֵ����
***********************************************/
void iic_init(void)
{
	/*****����GPIO��**************************************/
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOIIC, ENABLE);
   
		GPIO_InitStructure.GPIO_Pin=IIC_SCL_Pin|IIC_SDA_Pin;
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	
		GPIO_Init(GPIO_IIC, &GPIO_InitStructure);	
	
	/********��IIC�� SCL SDA �����ͷ�����******************/
		SDA_PIN_OUT=1;
		SCL_PIN_OUT=1;
}
/***********************************************************
��������iic_start
��  �ܣ�����iic��������ʽ����SCL�ߵ�ƽ�ڼ佫SDA�ɸ��õ�
��  ������
����ֵ����
**********************************************************/
void iic_start(void)
{
	IIC_SDA_OUT();
	SDA_PIN_OUT=1;
	SCL_PIN_OUT=1;
	Delay_us(1);
	SDA_PIN_OUT=0;
	Delay_us(1);
	SCL_PIN_OUT=0;
}
/*************************************************************
��������iic_stop
��  �ܣ�ֹͣ�������ݣ�ʵ�ַ�ʽ��SCL�ߵ�ƽ�ڼ佫SDA�ɵ��ø�
��  ������
����ֵ����
*************************************************************/
void iic_stop(void)
{
	
    SCL_PIN_OUT=0;
		IIC_SDA_OUT();	
		SDA_PIN_OUT=0;
		Delay_us(1);
		SCL_PIN_OUT=1;
		SDA_PIN_OUT=1;
		Delay_us(1);
}
/*************************************************************
��������iic_ack
��  �ܣ����մӻ�Ӧ���źţ��ͷŵ����߶�ȡSDA�ÿ��Ƿ��и�����,
        ��һ��ʱ����Ӧ��Ĭ�Ͻ������
��  ������
����ֵ����
***************************************************************/
u8 iic_wait_ack(void)
{
	u8 i=0;
	IIC_SDA_IN();
	SDA_PIN_OUT=1;Delay_us(1);
	SCL_PIN_OUT=1;Delay_us(1);
	while(SDA_PIN_IN)
	{
		i++;
		if(i>250) 
		{		
      iic_stop();			//���i>255�������Ӧ���źţ�iicֹͣ
			return 1;
		}
		
	}
	SCL_PIN_OUT=0;//ʱ�����0 
	return 0;
}
/*************************************************************
��������iic_nask
��  �ܣ�������Ӧ���ź�
��  ������
��  �أ���
*************************************************************/
void iic_nack(void)
{
	SCL_PIN_OUT=0;
	IIC_SDA_OUT();
	SDA_PIN_OUT=1;
	Delay_us(1);
	SCL_PIN_OUT=1;
	Delay_us(1);
	SCL_PIN_OUT=0;
}	
/*************************************************************
��������iic_ask
��  �ܣ�����askӦ��
��  ������
��  �أ���
**************************************************************/
void iic_ack(void)
{
	SCL_PIN_OUT=0;
	IIC_SDA_OUT();
	SDA_PIN_OUT=0;
	Delay_us(1);
	SCL_PIN_OUT=1;
	Delay_us(1);
	SCL_PIN_OUT=0;
}
/*************************************************************
��������iic_bit_write
��  �ܣ�����һ���ֽ�
��  ����u8
����ֵ����
*************************************************************/
void iic_byte_write(u8 buf)
{
	 u8 i;
	 IIC_SDA_OUT();
	 SCL_PIN_OUT=0;
	 for(i=1;i<=8;i++)
	 {
		 SDA_PIN_OUT=(buf>>(8-i))&0x01;
		 Delay_us(1);
		 SCL_PIN_OUT=1;
		 Delay_us(1);
		 SCL_PIN_OUT=0;
		 Delay_us(1);		
	}
}
/*************************************************************
��������iic_bit_read
��  �ܣ�������ȡһ���ֽ�
��  ����ask
����ֵ��
*************************************************************/
u8 iic_byte_read(unsigned char ask)
{
	unsigned char  i,buf=0;
	IIC_SDA_IN();
	for(i=0;i<8;i++)
	{
	   SCL_PIN_OUT=0;
	   Delay_us(1);
	   SCL_PIN_OUT=1;
	   buf <<=1;
	   if(SDA_PIN_IN)
		   buf++;
	    Delay_us(1);
	}
	if(!ask)
		iic_nack();
	else
		iic_ack();
	return buf;
}
