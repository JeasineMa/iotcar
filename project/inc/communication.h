#ifndef __COMMUNICATION_H
#define	__COMMUNICATION_H

#include <stdio.h>
#include "stm32f10x_usart.h"

#define Buffer_Size 20

#define com1 USART3
#define com2 UART5
#define wifi UART4

extern uint8_t info_com1[Buffer_Size];   //USART3-user1
extern uint8_t info_wifi[Buffer_Size];   //USART4-WiFi
extern uint8_t info_com2[Buffer_Size];   //USART5-user2

void USART_printf(USART_TypeDef* USARTx, uint8_t *Data,...);

void USART_Config();

int fputc(int ch, FILE *f);


#endif 
