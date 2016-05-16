#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_exti.h"
#include "delay.h"
#include "motor.h"
#include "pid.h"
#include "communication.h"
#include "avoid_block.h"
#include "tcs3200.h"
#include "core_cm3.h"
#include "misc.h"
#include <stdio.h>


#define BIT(x)	(1 << (x))

int setup()
{
	USART_Config();
    Delay_Init(72);
    Motor_Init();
//	tcs3200_init();
//	avoid_block_Init();
}


int main()
{
	setup();
	while(1)
	{
		// Motor1_Speed(0);
		// Motor2_Speed(150);
		// Motor3_Speed(20);
		// Motor4_Speed(50);
		// Motor5_Speed(-50);
		// Motor6_Speed(50);
		//USART_printf(com1,"com1:hello world!");	
		//USART_printf(wifi,"wifi:hello world!");	
		//USART_printf(com2,"com2:hello world!");	
		
	}
	
}

int abs(int a);
int map(int low, int high, int new_low, int new_high, int value);

void USART_printf(USART_TypeDef* USARTx, uint8_t *Data,...);    //USART3/UART4/UART5
extern uint8_t info_com1[Buffer_Size];   //USART3-user1
extern uint8_t info_wifi[Buffer_Size];   //USART4-WiFi
extern uint8_t info_com2[Buffer_Size];   //USART5-user2

/*
 *typedef struct RGB
 *{
 *    int R;
 *	  int G;
 *	  int B;
 *};
 */
 RGB Get_RGB1();

void Motor1_Speed(int speed); 
void Motor2_Speed(int speed); 
void Motor3_Speed(int speed); 
void Motor4_Speed(int speed); 
void Motor5_Speed(int speed); 
void Motor6_Speed(int speed); 

//FIXME query for accurate exti interrupts.
void EXTI3_IRQHandler(void) {EXTI_ClearITPendingBit(EXTI_Line3);}
void EXTI4_IRQHandler(void) {EXTI_ClearITPendingBit(EXTI_Line4);}
void EXTI9_5_IRQHandler(void) {EXTI_ClearITPendingBit(EXTI_Line5);}  //for EXTI5
void EXTI15_10_IRQHandler(void) {EXTI_ClearITPendingBit(EXTI_Line15);}  //for EXTI13,14,15

