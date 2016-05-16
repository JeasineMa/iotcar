#ifndef __TCS3200_H
#define __TCS3200_H

typedef unsigned char u8;
typedef unsigned short u16;

extern u16 tcs3200_amount;

extern u8 Rgena,Ggena,Bgena;
extern u16 Ramount,Gamount,Bamount;


// #define S0 PAout(0)
// #define S1 PAout(1)
// #define S2 PAout(2)
// #define S3 PAout(3)
// #define OUT PAin(4)

typedef struct
{
	int R;
	int G;
	int B;
}RGB;

RGB Get_RGB1();
RGB Get_RGB2();

void tcs3200_init();

void whitebalance(void);
u16 tcs3200_RED(void);
u16 tcs3200_GREEN(void);
u16 tcs3200_BLUE(void);

#endif

