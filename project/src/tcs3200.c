#include "stm32f10x.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_rcc.h"
#include "tcs3200.h"

u8 Rgena = 0,Ggena = 0,Bgena = 0;
u16 Ramount = 0,Gamount = 0,Bamount = 0;
u16 tcs3200_amount = 0;

void tcs3200_init()
{
	GPIO_InitTypeDef GPIO_InitStructure;    
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);    

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_SetBits(GPIOB,GPIO_Pin_12);  //S0
	GPIO_SetBits(GPIOB,GPIO_Pin_13);  //S1
	GPIO_SetBits(GPIOB,GPIO_Pin_14);  //S2
	GPIO_SetBits(GPIOB,GPIO_Pin_15);  //S3

	EXTI12_OUT1_Init();

	// RCC->APB2ENR|=1<<2;    //使能PORTA时钟	   
	// GPIOA->CRL&=0xfff00000;
	// GPIOA->CRL|=0x00003333;//PA0.PA1.PA2.PA3推挽输出。
	// GPIOA->CRL|=0x00080000;//PA4输入
	// GPIOA->ODR|=9;		   //全部口上拉。
	// S0=s0;
	// S1=s1;
}

void EXTI12_OUT1_Init()
{
	GPIO_InitTypeDef  GPIO_InitStructure;  
    EXTI_InitTypeDef  exti;  
    NVIC_InitTypeDef  NVIC_exti;  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);                                                
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA,&GPIO_InitStructure);  
               
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource12);  
      
    exti.EXTI_Line = EXTI_Line12;  
    exti.EXTI_Mode = EXTI_Mode_Interrupt;
    exti.EXTI_Trigger = EXTI_Trigger_Falling;    
    exti.EXTI_LineCmd = ENABLE;  
    EXTI_Init(&exti);  
      
    //NVIC中断控制配置  
    NVIC_exti.NVIC_IRQChannel = EXTI15_10_IRQn;  
    NVIC_exti.NVIC_IRQChannelPreemptionPriority = 0x00;
    NVIC_exti.NVIC_IRQChannelSubPriority = 0x00;
    NVIC_exti.NVIC_IRQChannelCmd = ENABLE;  
    NVIC_Init(&NVIC_exti);        
}

void EXTI12_IRQHandler(void) 
{
	tcs3200_amount++;
	EXTI_ClearITPendingBit(EXTI_Line12);
}

/*
 * TCS3200 OUT2 has conflict with light_switch6.(EXTI_15)
 */
// void EXTI15_OUT1_Init()
// {
// 	GPIO_InitTypeDef  GPIO_InitStructure;  
//     EXTI_InitTypeDef  exti;  
//     NVIC_InitTypeDef  NVIC_exti;  
//     RCC_APB2PeriphCBockCmd(RCC_APB2Periph_GPIOA,ENABLE);
//     RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);                                                
    
//     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;  
//     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
//     GPIO_Init(GPIOA,&GPIO_InitStructure);  
               
//     GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource15);  
      
//     exti.EXTI_Line = EXTI_Line15;  
//     exti.EXTI_Mode = EXTI_Mode_Interrupt;
//     exti.EXTI_Trigger = EXTI_Trigger_Falling;    
//     exti.EXTI_LineCmd = ENABLE;  
//     EXTI_Init(&exti);  
      
//     //NVIC中断控制配置  
//     NVIC_exti.NVIC_IRQChannel = EXTI15_IRQn;  
//     NVIC_exti.NVIC_IRQChannelPreemptionPriority = 0x00;
//     NVIC_exti.NVIC_IRQChannelSubPriority = 0x00;
//     NVIC_exti.NVIC_IRQChannelCmd = ENABLE;  
//     NVIC_Init(&NVIC_exti);        
// }

// void EXTI15_IRQHandler(void) 
// {
// 	tcs3200_amount++;
// 	EXTI_ClearITPendingBit(EXTI_Line15);
// }

RGB Get_RGB1()
{
	RGB output;
	whitebalance();
	output.R = tcs3200_RED();
	output.G = tcs3200_GREEN();
	output.B = tcs3200_BLUE();
	return output;
}

RGB Get_RGB2()
{
	// RGB output;
	// whitebalance();
	// output.R = tcs3200_RED();
	// output.G = tcs3200_GREEN();
	// output.B = tcs3200_BLUE();
	// return output;
}



/*******************************************
*
*		  白平衡
*
*******************************************/
void whitebalance(void)
{	
	GPIO_ResetBits(GPIOB, GPIO_Pin_14);
	GPIO_ResetBits(GPIOB, GPIO_Pin_15); //红色通道
	tcs3200_amount = 0;			        //开始计数
	Delay_Ms(10);
	Rgena = tcs3200_amount;   //求出红色因子      
	tcs3200_amount = 0;
//----------------------------------
	GPIO_SetBits(GPIOB, GPIO_Pin_14);
	GPIO_SetBits(GPIOB, GPIO_Pin_15); //绿色通道
	tcs3200_amount = 0;			        //开始计数
	Delay_Ms(10);
	Ggena = tcs3200_amount;   //求出绿色因子      
	tcs3200_amount = 0;
//----------------------------------
	GPIO_ResetBits(GPIOB, GPIO_Pin_14);
	GPIO_SetBits(GPIOB, GPIO_Pin_15); //蓝色通道
	tcs3200_amount = 0;			        //开始计数
	Delay_Ms(10);
	Bgena = tcs3200_amount;   //求出蓝色因子      
	tcs3200_amount = 0;
	
	GPIO_SetBits(GPIOB, GPIO_Pin_14);
	GPIO_ResetBits(GPIOB, GPIO_Pin_15); //关闭通道  	  
}


// void whitebalance(void)
// {
// 	EXTIX_Init();		 //外部中断初始化
// 	S2=0;S3=0;//红色通道
// 	amount=0;			 //开始计数
// 	delay_ms(10);
// 	Rgena = amount;   //求出红色因子      
// 	amount=0;
// //----------------------------------
// 	S2=1;S3=1;//绿色通道
// 	amount=0;
// 	delay_ms(10);
// 	Ggena = amount;	 //求出绿色因子
// 	amount=0;
// //----------------------------------
// 	S2=0;S3=1;//蓝色通道
// 	amount=0;
// 	delay_ms(10);
// 	Bgena = amount;	  //求出蓝色因子
// 	amount=0;
// 	S2=1;S3=0;//关闭通道  	  
// }

u16 tcs3200_RED(void)
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_14);
	GPIO_ResetBits(GPIOB, GPIO_Pin_15); //红色通道
	tcs3200_amount = 0;
	Delay_Ms(10);
	Ramount= (u32) tcs3200_amount*255/Rgena;	 //取R值
	if(Ramount>255) Ramount = 255;
	return Ramount;
	tcs3200_amount = 0;
}

u16 tcs3200_GREEN(void)
{
	GPIO_SetBits(GPIOB, GPIO_Pin_14);
	GPIO_SetBits(GPIOB, GPIO_Pin_15); //红色通道
	tcs3200_amount = 0;
	Delay_Ms(10);
	Gamount= (u32) tcs3200_amount*255/Ggena;	 //取R值
	if(Gamount>255) Gamount = 255;
	return Gamount;
	tcs3200_amount = 0;
}

u16 tcs3200_BLUE(void)
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_14);
	GPIO_SetBits(GPIOB, GPIO_Pin_15); //红色通道
	tcs3200_amount = 0;
	Delay_Ms(10);
	Bamount= (u32) tcs3200_amount*255/Bgena;	 //取R值
	if(Bamount>255) Bamount = 255;
	return Bamount;
	tcs3200_amount = 0;
} 



// u16 tcs3200_RED(void)
// {
// 	S2=0;S3=0;
// 	amount=0;
// 	delay_ms(10);
// 	Ramount=(u32) amount*255/Rgena;	 //取R值
// 	if(Ramount>255) Ramount = 255;
// 	return Ramount;
// //	amount=0;
// }

// u16 tcs3200_GREEN(void)
// {
// 	S2=1;S3=1;
// 	amount=0;
// 	delay_ms(10);
// 	Gamount=(u32) amount*255/Ggena;	//取G值
// 	if(Gamount>255) Gamount = 255;
// 	return Gamount;
// //	amount=0;
// }

// u16 tcs3200_BLUE(void)
// {
// 	S2=0;S3=1;
// 	amount=0;
// 	delay_ms(10);
// 	Bamount=(u32) amount*255/Bgena;//去B值
// 	if(Bamount>255) Bamount = 255;
// 	return Bamount;
// //	amount=0;
// } 

