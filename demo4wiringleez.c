#include "wiringpi.h"
int main()
{
	pinMode(GPIO4_30, OUTPUT);//����Ϊ���
	digitalWrite(GPIO4_30, HIGH);//����Ϊ��
	sleep(1);
	digitalWrite(GPIO4_30, LOW);//����Ϊ��
	sleep(1);
	digitalWrite(GPIO4_30, HIGH);//����Ϊ����
	pinMode(GPIO4_30, INPUT); 
	int pin4_30 = digitalRead(GPIO4_30);//��ȡIO��ƽ�ߵ�
	return 0;
}