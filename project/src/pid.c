#include "pid.h"
#define MAX_INTEGRATION_ERROR                2500
#define MAX_PID_OUTPUT                       4000


/*������
1.�����λ����4000��
2.��δ�������ձ�����������ڶ����ǽǶ�
3.180�ȴ��ĳ�������
*/

PID Motor_Run={0,0,0,0,0,0,0,0}, Motor_Turn={1,0,400,0,450,0,0,0};  //����ʱע��Ӧ��ȡ��ַ
void calcPID(PID *pid, int input)
{
	int output,error;
	error=pid->targetValue-input;	
	if (pid->Ki != 0)
	{
	    pid->integrationError += error;
	    pid->integrationError *= 0.95;
	    // Limit the maximum integration error
	    if (pid->integrationError > MAX_INTEGRATION_ERROR)
	    {
	        pid->integrationError = MAX_INTEGRATION_ERROR;
	    }
	    else if (pid->integrationError < -MAX_INTEGRATION_ERROR)
	    {
	        pid->integrationError = -MAX_INTEGRATION_ERROR;
	    }
	 }

	output = pid->Kp * error + pid->Ki * pid->integrationError + pid->Kd * (error - pid->lastError);

	// Limit the maximum output
	if (output > MAX_PID_OUTPUT)
	{
	    output = MAX_PID_OUTPUT;
	}
	else if (output < -MAX_PID_OUTPUT)
	{
	    output = -MAX_PID_OUTPUT;
	}

	pid->lastError = error;
	pid->PWM = output;
}
