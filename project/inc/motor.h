#ifndef _MOTOR_H_
#define _MOTOR_H_

void Motor_Init(void);

void Motor1_Speed(int speed); 
void Motor2_Speed(int speed); 
void Motor3_Speed(int speed); 
void Motor4_Speed(int speed); 
void Motor5_Speed(int speed); 
void Motor6_Speed(int speed); 

int abs(int a);
int map(int low, int high, int new_low, int new_high, int value);

#endif


