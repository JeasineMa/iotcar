#include "motor.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"
#include "delay.h"
#include "pid.h"

#define Max_Speed 100

int abs(int a)
{
	if (a >= 0)
		return a;
	else
		return -a;
}

int map(int low, int high, int new_low, int new_high, int value)
{
	return (((new_high - new_low)/(high - low))*(value-low) + new_low);
}

void Motor1_Speed(int speed)
{
	if(abs(speed) > Max_Speed) {
		speed = (speed > 0?100:-100);
	}
	if (speed == 0) {
		GPIO_ResetBits(GPIOC, GPIO_Pin_0);
		TIM_SetCompare1(TIM1, 0);
		TIM_SetCompare2(TIM1, 0);
	} else {
		GPIO_SetBits(GPIOC, GPIO_Pin_0);
		if (speed > 0) {
			TIM_SetCompare1(TIM1, speed);
			TIM_SetCompare2(TIM1, 0);
		} else {
			TIM_SetCompare1(TIM1, 0);
			TIM_SetCompare2(TIM1, -speed);
		}
	}
}

void Motor2_Speed(int speed)
{
	if(abs(speed) > Max_Speed) {
		speed = (speed > 0?100:-100);
	}
	if (speed == 0) {
		GPIO_ResetBits(GPIOC, GPIO_Pin_1);
		TIM_SetCompare3(TIM1, 0);
		TIM_SetCompare4(TIM1, 0);
	} else {
		GPIO_SetBits(GPIOC, GPIO_Pin_1);
		if (speed > 0) {
			TIM_SetCompare3(TIM1, speed);
			TIM_SetCompare4(TIM1, 0);
		} else {
			TIM_SetCompare3(TIM1, 0);
			TIM_SetCompare4(TIM1, -speed);
		}
	}
}

void Motor3_Speed(int speed)
{
	if(abs(speed) > Max_Speed) {
		speed = (speed > 0?100:-100);
	}
	if (speed == 0) {
		GPIO_ResetBits(GPIOC, GPIO_Pin_2);
		TIM_SetCompare1(TIM5, 0);
		TIM_SetCompare2(TIM5, 0);
	} else {
		GPIO_SetBits(GPIOC, GPIO_Pin_2);
		if (speed > 0) {
			TIM_SetCompare1(TIM5, speed);
			TIM_SetCompare2(TIM5, 0);
		} else {
			TIM_SetCompare1(TIM5, 0);
			TIM_SetCompare2(TIM5, -speed);
		}
	}
}

void Motor4_Speed(int speed)
{
	if(abs(speed) > Max_Speed) {
		speed = (speed > 0?100:-100);
	}
	if (speed == 0) {
		GPIO_ResetBits(GPIOC, GPIO_Pin_3);
		TIM_SetCompare3(TIM5, 0);
		TIM_SetCompare4(TIM5, 0);
	} else {
		GPIO_SetBits(GPIOC, GPIO_Pin_3);
		if (speed > 0) {
			TIM_SetCompare3(TIM5, speed);
			TIM_SetCompare4(TIM5, 0);
		} else {
			TIM_SetCompare3(TIM5, 0);
			TIM_SetCompare4(TIM5, -speed);
		}
	}
}

void Motor5_Speed(int speed)
{
	if(abs(speed) > Max_Speed) {
		speed = (speed > 0?100:-100);
	}
	if (speed == 0) {
		GPIO_ResetBits(GPIOC, GPIO_Pin_4);
		TIM_SetCompare1(TIM8, 0);
		TIM_SetCompare2(TIM8, 0);
	} else {
		GPIO_SetBits(GPIOC, GPIO_Pin_4);
		if (speed > 0) {
			TIM_SetCompare1(TIM8, speed);
			TIM_SetCompare2(TIM8, 0);
		} else {
			TIM_SetCompare1(TIM8, 0);
			TIM_SetCompare2(TIM8, -speed);
		}
	}
}

void Motor6_Speed(int speed)
{
	if(abs(speed) > Max_Speed) {
		speed = (speed > 0?100:-100);
	}
	if (speed == 0) {
		GPIO_ResetBits(GPIOC, GPIO_Pin_5);
		TIM_SetCompare3(TIM8, 0);
		TIM_SetCompare4(TIM8, 0);
	} else {
		GPIO_SetBits(GPIOC, GPIO_Pin_5);
		if (speed > 0) {
			TIM_SetCompare3(TIM8, speed);
			TIM_SetCompare4(TIM8, 0);
		} else {
			TIM_SetCompare3(TIM8, 0);
			TIM_SetCompare4(TIM8, -speed);
		}
	}
}

void Motor_Init(void)
{
	GPIO_Motor_Init();
	TIM1_Init();  //motor1/2
	TIM5_Init();  //motor3/4
	TIM8_Init();  //motor5/6
}

void GPIO_Motor_Init(void)
{
	// motor:output&enable pins

	GPIO_InitTypeDef GPIO_InitStructure;  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE);      

	// motor1/2
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;      
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;           
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;          
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// motor3/4
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;      
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;           
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;          
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// motor5/6
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;      
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;           
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;          
	GPIO_Init(GPIOC, &GPIO_InitStructure);	  

	// motor1-6 enable
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void TIM1_Init(void)
{
	// motor 1/2
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure; 
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);   	   
	TIM_DeInit(TIM1);
	TIM_TimeBaseStructure.TIM_Prescaler = 0xFF;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = Max_Speed;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;

	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);

	TIM_OCStructInit(&TIM_OCInitStructure);         
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 

	/*Motor 1*/
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;           
	TIM_OCInitStructure.TIM_Pulse = 0;  
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OC1Init(TIM1,&TIM_OCInitStructure);	 
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);

	/*Motor 1R*/
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;	
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable); 

	/*Motor 2*/
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;	
	TIM_OC3Init(TIM1, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable); 

	/*Motor 2R*/
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;	
	TIM_OC4Init(TIM1, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable); 

	TIM_ARRPreloadConfig(TIM1, ENABLE);

	TIM1->BDTR |= 1<<15;  

	TIM_Cmd(TIM1,ENABLE);
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
}

void TIM5_Init()
{
	// motor 3/4
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure; 
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);   	   
	TIM_DeInit(TIM5);
	TIM_TimeBaseStructure.TIM_Prescaler = 0xFF;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = Max_Speed;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;

	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStructure);

	TIM_OCStructInit(&TIM_OCInitStructure);         
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 

	/*Motor 3*/
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;           
	TIM_OCInitStructure.TIM_Pulse = 0;  
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OC1Init(TIM5,&TIM_OCInitStructure);	 
	TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);

	/*Motor 3R*/
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;	
	TIM_OC2Init(TIM5, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable); 

	/*Motor 4*/
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;	
	TIM_OC3Init(TIM5, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM5, TIM_OCPreload_Enable); 

	/*Motor 4R*/
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;	
	TIM_OC4Init(TIM5, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM5, TIM_OCPreload_Enable); 

	TIM_ARRPreloadConfig(TIM5, ENABLE);

	TIM5->BDTR |= 1<<15;  

	TIM_Cmd(TIM5,ENABLE);
	TIM_CtrlPWMOutputs(TIM5, ENABLE);
} 

void TIM8_Init()
{
	// motor 5/6
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure; 
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);   	   
	TIM_DeInit(TIM8);
	TIM_TimeBaseStructure.TIM_Prescaler = 0xFF;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = Max_Speed;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;

	TIM_TimeBaseInit(TIM8,&TIM_TimeBaseStructure);

	TIM_OCStructInit(&TIM_OCInitStructure);         
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 

	/*Motor 5*/
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;           
	TIM_OCInitStructure.TIM_Pulse = 0;  
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OC1Init(TIM8,&TIM_OCInitStructure);	 
	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);

	/*Motor 5R*/
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;	
	TIM_OC2Init(TIM8, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable); 

	/*Motor 6*/
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;	
	TIM_OC3Init(TIM8, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable); 

	/*Motor 6R*/
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;	
	TIM_OC4Init(TIM8, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable); 

	TIM_ARRPreloadConfig(TIM8, ENABLE);

	TIM8->BDTR |= 1<<15;  

	TIM_Cmd(TIM8,ENABLE);
	TIM_CtrlPWMOutputs(TIM8, ENABLE);
}

