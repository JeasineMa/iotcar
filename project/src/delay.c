#include "delay.h"
#include "stm32f10x.h"
#include "core_cm3.h"

#define BIT(x)	(1 << (x))

uint16_t fac_ms;//ȫ�ֱ���
uint8_t fac_us;//ȫ�ֱ���

/****************************************************
�������ܣ�ms����ʱ
���������nms : ����
�����������
��    ע�����ô˺���ǰ����Ҫ��ʼ��Delay_Init()����
*****************************************************/							    
void Delay_Ms(uint16_t nms)
{
   	  SysTick->LOAD = (u32)fac_ms*nms-1;//����ʱ��ֵ
	  SysTick->VAL = 1;//���д��ֵ��������ؼĴ�����ֵ
	  SysTick->CTRL |= BIT(0);//SysTickʹ��
	  while(!(SysTick->CTRL&(1<<16)));//�ж��Ƿ����0
	  SysTick->CTRL &=~BIT(0);//�ر�SysTick
}

/****************************************************
�������ܣ���ʱ��ʼ��
���������SYSCLK : ϵͳʱ��(72)MHZ
�����������
��    ע����
*****************************************************/
void Delay_Init(uint8_t SYSCLK)
{
	 SysTick->CTRL &=~BIT(2);//ѡ���ⲿʱ��
	 SysTick->CTRL &=~BIT(1);//�رն�ʱ������0����ж�����
	 fac_us = SYSCLK/8;//�����SysTick����ֵ
	 fac_ms = (uint16_t)fac_us*1000;	 
}

/****************************************************
�������ܣ�us����ʱ
���������nus : ΢��
�����������
��    ע�����ô˺���ǰ����Ҫ��ʼ��Delay_Init()����
*****************************************************/		    								   
void Delay_Us(u32 nus)
{		
	  SysTick->LOAD = (u32)fac_us*nus-1;//����ʱ��ֵ
	  SysTick->VAL = 1;//���д��ֵ��������ؼĴ�����ֵ
	  SysTick->CTRL |= BIT(0);//SysTickʹ��
	  while(!(SysTick->CTRL&(1<<16)));//�ж��Ƿ����0
	  SysTick->CTRL &=~BIT(0);//�ر�SysTick
}

void Delay(uint8_t s)
{
	for (uint8_t i = s ; i > 1 ; i--) {}
}


void SysTick_Init(uint8_t SYSCLK)
{
	// SysTick->CTRL &=~BIT(2);//ѡ���ⲿʱ��
	// SysTick->CTRL |=BIT(1);//�򿪶�ʱ������0����ж�����
	// fac_us = SYSCLK/8;//�����SysTick����ֵ

	// SysTick->LOAD = (u32)fac_us*1000 - 1;//����ʱ��ֵ   1msһ��
	// SysTick->VAL = 1;//���д��ֵ��������ؼĴ�����ֵ
	// SysTick->CTRL |= BIT(0);//SysTickʹ��
	// NVIC_SetPriority(SysTick_IRQn, 0x0);
}


void SysTick_Handler()
{
	// stop_protect++;
	// if (stop_protect > stop_protect_val && speed != 0) {
	// 	memcpy(Cmd_Ble, stop_protect_buff, 20);
	// }
	// //Speed_Query();
	// Angle_Query();

	
 //    //�˶�����Բ��ô�ͳ���Ʒ�ʽ
	// //calcPID(&Motor_Run, Car_Speed);
	// calcPID(&Motor_Turn, Car_Angle);
	// //Car_Run_Speed(Motor_Run.PWM);
	// Car_Turn_Speed(Motor_Turn.PWM);   

	// //SysTick->VAL = SysTick->LOAD;   //���VAL����ʼ��Systick����п���
}


