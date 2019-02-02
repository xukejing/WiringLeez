#include "wiringleez.h"
int main()
{
	pinMode(GPIO4_30, OUTPUT);//设置为输出
	digitalWrite(GPIO4_30, HIGH);//设置为高
	sleep(1);
	digitalWrite(GPIO4_30, LOW);//设置为低
	sleep(1);
	digitalWrite(GPIO4_30, HIGH);//设置为输入
	pinMode(GPIO4_30, INPUT); 
	int pin4_30 = digitalRead(GPIO4_30);//读取IO电平高低
	return 0;
}
