#ifndef __DELAY_H
#define __DELAY_H

#include "stm32f10x.h"

/*.h.c�����ڲ�ͬ���ļ�*/
/*�����ĺô��ǣ��������ļ����ø��ļ��еı���ʱֱ��#include���ɣ����ص���extern*/
extern uint16_t fac_ms;//ȫ�ֱ���
extern uint8_t fac_us;//ȫ�ֱ���

void Delay_Ms(uint16_t nms);
void Delay_Us(uint32_t nus);
void Delay_Init(uint8_t SYSCLK);
void Delay(uint8_t s);

#endif

