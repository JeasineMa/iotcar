#include "avoid_block.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_rcc.h"
#include "misc.h"
#include "core_cm3.h"

void avoid_block_Init()
{
	EXTI3_Init();
	EXTI4_Init();
	EXTI5_Init();
	EXTI13_Init();
	EXTI14_Init();
	EXTI15_Init();
}

void EXTI3_Init()
{
	GPIO_InitTypeDef  GPIO_InitStructure;  
    EXTI_InitTypeDef  exti;  
    NVIC_InitTypeDef  NVIC_exti;  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);                                                
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB,&GPIO_InitStructure);  
               
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource3);  
      
    exti.EXTI_Line = EXTI_Line3;  
    exti.EXTI_Mode = EXTI_Mode_Interrupt;
    exti.EXTI_Trigger = EXTI_Trigger_Rising_Falling;    //FIXME 
    exti.EXTI_LineCmd = ENABLE;  
    EXTI_Init(&exti);  
      
    //NVIC中断控制配置  
    NVIC_exti.NVIC_IRQChannel = EXTI3_IRQn;  
    NVIC_exti.NVIC_IRQChannelPreemptionPriority = 0x01;
    NVIC_exti.NVIC_IRQChannelSubPriority = 0x01;
    NVIC_exti.NVIC_IRQChannelCmd = ENABLE;  
    NVIC_Init(&NVIC_exti);        
}

void EXTI4_Init()
{
	GPIO_InitTypeDef  GPIO_InitStructure;  
    EXTI_InitTypeDef  exti;  
    NVIC_InitTypeDef  NVIC_exti;  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);                                                
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB,&GPIO_InitStructure);  
               
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource4);  
      
    exti.EXTI_Line = EXTI_Line4;  
    exti.EXTI_Mode = EXTI_Mode_Interrupt;
    exti.EXTI_Trigger = EXTI_Trigger_Rising_Falling;    //FIXME 
    exti.EXTI_LineCmd = ENABLE;  
    EXTI_Init(&exti);  
      
    //NVIC中断控制配置  
    NVIC_exti.NVIC_IRQChannel = EXTI4_IRQn;  
    NVIC_exti.NVIC_IRQChannelPreemptionPriority = 0x01;
    NVIC_exti.NVIC_IRQChannelSubPriority = 0x01;
    NVIC_exti.NVIC_IRQChannelCmd = ENABLE;  
    NVIC_Init(&NVIC_exti);        
}

void EXTI5_Init()
{
	GPIO_InitTypeDef  GPIO_InitStructure;  
    EXTI_InitTypeDef  exti;  
    NVIC_InitTypeDef  NVIC_exti;  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);                                                
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB,&GPIO_InitStructure);  
               
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource5);  
      
    exti.EXTI_Line = EXTI_Line5;  
    exti.EXTI_Mode = EXTI_Mode_Interrupt;
    exti.EXTI_Trigger = EXTI_Trigger_Rising_Falling;    //FIXME 
    exti.EXTI_LineCmd = ENABLE;  
    EXTI_Init(&exti);  
      
    //NVIC中断控制配置  
    NVIC_exti.NVIC_IRQChannel = EXTI9_5_IRQn ;  
    NVIC_exti.NVIC_IRQChannelPreemptionPriority = 0x01;
    NVIC_exti.NVIC_IRQChannelSubPriority = 0x01;
    NVIC_exti.NVIC_IRQChannelCmd = ENABLE;  
    NVIC_Init(&NVIC_exti);        
}

void EXTI13_Init()
{
	GPIO_InitTypeDef  GPIO_InitStructure;  
    EXTI_InitTypeDef  exti;  
    NVIC_InitTypeDef  NVIC_exti;  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);                                                
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOC,&GPIO_InitStructure);  
               
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource13);  
      
    exti.EXTI_Line = EXTI_Line13;  
    exti.EXTI_Mode = EXTI_Mode_Interrupt;
    exti.EXTI_Trigger = EXTI_Trigger_Rising_Falling;    //FIXME 
    exti.EXTI_LineCmd = ENABLE;  
    EXTI_Init(&exti);  
      
    //NVIC中断控制配置  
    NVIC_exti.NVIC_IRQChannel = EXTI15_10_IRQn ;  
    NVIC_exti.NVIC_IRQChannelPreemptionPriority = 0x01;
    NVIC_exti.NVIC_IRQChannelSubPriority = 0x01;
    NVIC_exti.NVIC_IRQChannelCmd = ENABLE;  
    NVIC_Init(&NVIC_exti);        
}

void EXTI14_Init()
{
	GPIO_InitTypeDef  GPIO_InitStructure;  
    EXTI_InitTypeDef  exti;  
    NVIC_InitTypeDef  NVIC_exti;  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);                                                
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOC,&GPIO_InitStructure);  
               
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource14);  
      
    exti.EXTI_Line = EXTI_Line14;  
    exti.EXTI_Mode = EXTI_Mode_Interrupt;
    exti.EXTI_Trigger = EXTI_Trigger_Rising_Falling;    //FIXME 
    exti.EXTI_LineCmd = ENABLE;  
    EXTI_Init(&exti);  
      
    //NVIC中断控制配置  
    NVIC_exti.NVIC_IRQChannel = EXTI15_10_IRQn ;  
    NVIC_exti.NVIC_IRQChannelPreemptionPriority = 0x01;
    NVIC_exti.NVIC_IRQChannelSubPriority = 0x01;
    NVIC_exti.NVIC_IRQChannelCmd = ENABLE;  
    NVIC_Init(&NVIC_exti);        
}

void EXTI15_Init()
{
	GPIO_InitTypeDef  GPIO_InitStructure;  
    EXTI_InitTypeDef  exti;  
    NVIC_InitTypeDef  NVIC_exti;  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);                                                
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOC,&GPIO_InitStructure);  
               
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource15);  
      
    exti.EXTI_Line = EXTI_Line15;  
    exti.EXTI_Mode = EXTI_Mode_Interrupt;
    exti.EXTI_Trigger = EXTI_Trigger_Rising_Falling;    //FIXME 
    exti.EXTI_LineCmd = ENABLE;  
    EXTI_Init(&exti);  
      
    //NVIC中断控制配置  
    NVIC_exti.NVIC_IRQChannel = EXTI15_10_IRQn;  
    NVIC_exti.NVIC_IRQChannelPreemptionPriority = 0x01;
    NVIC_exti.NVIC_IRQChannelSubPriority = 0x01;
    NVIC_exti.NVIC_IRQChannelCmd = ENABLE;  
    NVIC_Init(&NVIC_exti);        
}