#ifndef __COMMON__H__
#define __COMMON__H__

#include "stm32f10x.h"
#include "pin.h"
#include <stdint.h>
#include <stdio.h>

#ifndef NULL
#define NULL ((void*)0)
#endif
#ifndef bool
#define bool uint8_t
#define true 1
#define TRUE true
#define false 0
#define FALSE false
#endif

#define DBG_MSG(format, ...) printf("[Debug]%s: " format "\r\n", __func__, ##__VA_ARGS__)
#define ERR_MSG(format, ...) printf("[Error]%s: " format "\r\n", __func__, ##__VA_ARGS__)
 
void RCC_GPIOClockCmd(GPIO_TypeDef* GPIOx, FunctionalState state);
void RCC_USARTClockCmd(USART_TypeDef* USARTx, FunctionalState state);
void Timer_16bit_Calc(int freq, uint16_t *period, uint16_t *prescaler);

#endif /* __COMMON__H__ */