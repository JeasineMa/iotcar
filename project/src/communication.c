#include "communication.h"
#include "motor.h"
#include "stm32f10x.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_dma.h"
#include "core_cm3.h"
#include <stdarg.h>

/*
 * USART3 -> user
 * USART4 -> Wi-Fi Node
 * USART5 -> user 
 */

uint8_t info_com1[Buffer_Size] = "#000-000*";   //USART3-user1
uint8_t info_wifi[Buffer_Size] = "#000-000*";   //USART4-WiFi
uint8_t info_com2[Buffer_Size] = "#000-000*";   //USART5-user2

uint8_t Buff_USART3[30];
uint8_t Buff_USART4[20];    
uint8_t Buff_USART5[20];

int Order_USART3 = 0;
int Order_USART4 = 0;
int Order_USART5 = 0;

/*
  Recommand Command format:
  #089-C*
  C-Clockwise
  A-AntiClockwise
  N- Noturn
*/

void USART3_IRQHandler(void)
{
	if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) {
		USART_SendData(USART3, USART_ReceiveData(USART3)); 

		//put your code here

	}
	USART_ClearITPendingBit(USART3,USART_IT_RXNE);

	// uint8_t tmp;
	// if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) //接收中断
	// {
	// 	tmp = USART_ReceiveData(USART3);
	// 	if(tmp == '#')
	// 	{
	// 		Order_USART3 = 0;
	// 	}
	// 	Buff_USART3[Order_USART3] = tmp;
	// 	Order_USART3++;
	// 	if(tmp == '*')
	// 	{
	// 		memcpy(info_com1, Buff_USART3, Buffer_Size);
	// 		Order_USART3 = 0;
	// 	}
	// 	// if(tmp == '$')    //增加软复位 trick
	// 	// {
	// 	// 	 NVIC_SystemReset();
	// 	// }
	// }
	// USART_ClearITPendingBit(USART3,USART_IT_RXNE);
}

void UART4_IRQHandler(void)
{
	if (USART_GetITStatus(UART4, USART_IT_RXNE) != RESET) {
		USART_SendData(UART4, USART_ReceiveData(UART4)); 

		//put your code here

	}
	USART_ClearITPendingBit(UART4,USART_IT_RXNE);
	
	// uint8_t tmp;
	// if (USART_GetITStatus(UART4, USART_IT_RXNE) != RESET) //接收中断
	// {
	// 	tmp = USART_ReceiveData(UART4);
	// 	if(tmp == '#')
	// 	{
	// 		Order_USART4 = 0;
	// 	}
	// 	Buff_USART4[Order_USART4] = tmp;
	// 	Order_USART4++;
	// 	if(tmp == '*')
	// 	{
	// 		memcpy(info_wifi, Buff_USART4, Buffer_Size);
	// 		Order_USART4 = 0;
	// 	}
	// 	// if(tmp == '$')    //增加软复位 trick
	// 	// {
	// 	// 	 NVIC_SystemReset();
	// 	// }
	// }
	// USART_ClearITPendingBit(UART4,USART_IT_RXNE);
}

void UART5_IRQHandler(void)
{
	if (USART_GetITStatus(UART5, USART_IT_RXNE) != RESET) {
		USART_SendData(UART5, USART_ReceiveData(UART5)); 

		//put your code here

	}
	USART_ClearITPendingBit(UART5,USART_IT_RXNE);

	// uint8_t tmp;
	// if (USART_GetITStatus(UART5, USART_IT_RXNE) != RESET) //接收中断
	// {
	// 	tmp = USART_ReceiveData(UART5);
	// 	if(tmp == '#')
	// 	{
	// 		Order_USART5 = 0;
	// 	}
	// 	Buff_USART5[Order_USART5] = tmp;
	// 	Order_USART5++;
	// 	if(tmp == '*')
	// 	{
	// 		memcpy(info_com2, Buff_USART5, Buffer_Size);
	// 		Order_USART5 = 0;
	// 	}
	// 	// if(tmp == '$')    //增加软复位 trick
	// 	// {
	// 	// 	 NVIC_SystemReset();
	// 	// }
	// }
	// USART_ClearITPendingBit(UART5,USART_IT_RXNE);
}

void USART_Config()
{
	USART3_Config();
	USART4_Config();
	USART5_Config();
}

void USART3_Config()
{
	GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    USART_InitTypeDef USART_InitStructure; 
   
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE); 
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;    
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);    
    
    USART_InitStructure.USART_BaudRate = 115200;        
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    
    USART_Init(USART3, &USART_InitStructure);
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
    USART_Cmd(USART3, ENABLE);	
}

void USART4_Config()
{
	GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    USART_InitTypeDef USART_InitStructure; 
   
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE); 
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;    
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    
    NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);    
    
    USART_InitStructure.USART_BaudRate = 115200;        
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    
    USART_Init(UART4, &USART_InitStructure);
    USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
    USART_Cmd(UART4, ENABLE);	
}

void USART5_Config()
{
	GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    USART_InitTypeDef USART_InitStructure; 
   
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD , ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE); 
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;    
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    
    NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);    
    
    USART_InitStructure.USART_BaudRate = 115200;        
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    
    USART_Init(UART5, &USART_InitStructure);
    USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);
    USART_Cmd(UART5, ENABLE);	
}



/*
 * 函数名：fputc
 * 描述  ：重定向c库函数printf到USART1
 * 输入  ：无
 * 输出  ：无
 * 调用  ：由printf调用
 */
int fputc(int ch, FILE *f)
{
	/* 将Printf内容发往串口 */
	USART_SendData(USART1, (unsigned char) ch);
//	while (!(USART1->SR & USART_FLAG_TXE));
	while (USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET);	
	return (ch);
}

/*
 * 函数名：itoa
 * 描述  ：将整形数据转换成字符串
 * 输入  ：-radix =10 表示10进制，其他结果为0
 *         -value 要转换的整形数
 *         -buf 转换后的字符串
 *         -radix = 10
 * 输出  ：无
 * 返回  ：无
 * 调用  ：被USART1_printf()调用
 */
static char *itoa(int value, char *string, int radix)
{
	int     i, d;
	int     flag = 0;
	char    *ptr = string;
	
	/* This implementation only works for decimal numbers. */
	if (radix != 10)
	{
	    *ptr = 0;
	    return string;
	}
	
	if (!value)
	{
	    *ptr++ = 0x30;
	    *ptr = 0;
	    return string;
	}
	
	/* if this is a negative value insert the minus sign. */
	if (value < 0)
	{
	    *ptr++ = '-';
	
	    /* Make the value positive. */
	    value *= -1;
	}
	
	for (i = 10000; i > 0; i /= 10)
	{
	    d = value / i;
	
	    if (d || flag)
	    {
	        *ptr++ = (char)(d + 0x30);
	        value -= (d * i);
	        flag = 1;
	    }
	}
	
	/* Null terminate the string. */
	*ptr = 0;
	
	return string;

} /* NCL_Itoa */

/*
 * 函数名：USART1_printf
 * 描述  ：格式化输出，类似于C库中的printf，但这里没有用到C库
 * 输入  ：-USARTx 串口通道，这里只用到了串口1，即USART1
 *		     -Data   要发送到串口的内容的指针
 *			   -...    其他参数
 * 输出  ：无
 * 返回  ：无 
 * 调用  ：外部调用
 *         典型应用USART1_printf( USART1, "\r\n this is a demo \r\n" );
 *            		 USART1_printf( USART1, "\r\n %d \r\n", i );
 *            		 USART1_printf( USART1, "\r\n %s \r\n", j );
 */
void USART_printf(USART_TypeDef* USARTx, uint8_t *Data,...)
{
	const char *s;
	int d;   
	char buf[16];
	
	va_list ap;
	va_start(ap, Data);
	
	while ( *Data != 0)     // 判断是否到达字符串结束符
	{				                          
		if ( *Data == 0x5c )  //'\'
	{									  
	switch ( *++Data )
	{
		case 'r':							          //回车符
			USART_SendData(USARTx, 0x0d);
			Data ++;
		break;
		
		case 'n':							          //换行符
			USART_SendData(USARTx, 0x0a);	
			Data ++;
		break;
		
		default:
			Data ++;
		break;
	}			 
	}
	else if ( *Data == '%')
	{									  //
	switch ( *++Data )
	{				
		case 's':										  //字符串
			s = va_arg(ap, const char *);
	for ( ; *s; s++) 
	{
		USART_SendData(USARTx,*s);
		while( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET );
	}
		Data++;
		break;
	
	case 'd':										//十进制
	d = va_arg(ap, int);
	itoa(d, buf, 10);
	for (s = buf; *s; s++) 
	{
		USART_SendData(USARTx,*s);
		while( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET );
	}
	Data++;
	break;
		 default:
				Data++;
		    break;
	}		 
	} /* end of else if */
	else USART_SendData(USARTx, *Data++);
	while( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET );
	}
}
