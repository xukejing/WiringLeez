/*
*********************************************************************************************************
*
*	�ļ��� : wiringleez.c
*	�޸��� : sl_gpio.c
*   ˵    �� : ���澸��Sourcelink��gpio��Ļ����ϣ��ĳ���arduino���ݵ�����IO����
*
*
*********************************************************************************************************
*/
#include "wiringpi.h"
#include "so_lib.h"

DEBUG_SET_LEVEL(DEBUG_LEVEL_ERR);


/*
�ѱ�׼�ַ���io��עת����gpioϵͳ�е�io���
����gpio��gpio�Ķ˿ڶ���0��ʼ����imx6ulgpio�Ǵ�1��ʼ
Ҫ�Զ���ǰ��һλ��ԭ��ͼ�ϱ�עGPIO5_01, ʵ���ڳ�����Ҫ��дGPIO4_01
����ṹ����Ҫ�޸�
*/
EXPORT int convert_gpio_pin(const char *pin_str)
{
	const char *ppin = pin_str;
	unsigned char port = 0;
	unsigned char pin = 0;
	char pin_buf[5] = { 0 };
	if (strlen(ppin) != 8) {
		ERR("please use GPIOx_xx\n");
		return -1;
	}
	int ret = -1;
	if (strncmp(ppin, "GPIO", 4) != 0) {
		ret = -1;
	}
	else {
		ppin += 4;
		port = *ppin;
		if (port >= 'A' && port <= 'G') {
			port -= 'A';
		}
		else if (port >= '0' && port <= '6') {
			port -= '0';
		}
		else {
			return -1;
		}
		ppin++;
		if (*ppin == '_') {
			ppin++;
			strncat(pin_buf, ppin, 2);
			pin = atoi(pin_buf);
		}
		ret = port * 32 + pin;
	}
	return ret;
}


EXPORT int export_gpio_pin(int pin)
{
	int ret = write_intvalue_to_file("/sys/class/gpio/export", pin);
	if (ret > 0)
		return 0;
	else
		return -1;
}


EXPORT int unexport_gpio_pin(int pin)
{
	int ret = write_intvalue_to_file("/sys/class/gpio/unexport", pin);
	if (ret > 0)
		return 0;
	else
		return -1;
}

/*
��λ�ɹ�����0,���򷵻�-1
*/
EXPORT int set_gpio_value(int pin, int value)
{
	int ret = -1;
	GPIO_FILENAME_DEFINE(pin, "value");
	ret = write_intvalue_to_file(fileName, value);
	if (ret > 0)
		return 0;
	else
		return -1;
}


EXPORT int get_gpio_value(int pin)
{
	GPIO_FILENAME_DEFINE(pin, "value");
	return read_intvalue_from_file(fileName);
}


EXPORT int set_gpio_direction(int pin, int direction)
{
	char direction_str[10];
	int ret = -1;
	GPIO_FILENAME_DEFINE(pin, "direction");
	switch (direction) {
	case OUTPUT:
		strcpy(direction_str, "out");
		break;
	case INPUT:
		strcpy(direction_str, "in");
		break;
	default:
		ERR("%s error\n", __func__);
		break;
	}
	ret = write_value_to_file(fileName, direction_str);
	if (ret > 0)
		return 0;
	else
		return -1;
}


EXPORT int get_gpio_direction(int pin)
{
	char buff[50];
	int ret = 0;
	GPIO_FILENAME_DEFINE(pin, "direction");

	ret = read_value_from_file(fileName, buff, sizeof(buff) - 1);
	if (ret > 0) {
		/* �����ִ�Сд�Ƚ� */
		if (strncasecmp(buff, "out", 3)) {
			ret = OUTPUT;
		}
		else if (strncasecmp(buff, "in", 2)) {
			ret = INPUT;
		}
		else {
			ERR("direction wrong, must be in or out,  but %s", buff);
			return -1;
		}
	}
	return ret;
}

/*
pinMode������GPIO��ʼ��
����pinMode(GPIO4_30,OUTPUT)
*/
EXPORT int pinMode(const char *pin_str, int direction)
{
	int pin;
	pin = convert_gpio_pin(*pin_str);
	export_gpio_pin(pin);
	int ret=set_gpio_direction( pin, direction);
	return ret;
}


/*
digitalWrite��������GPIO�ߵ͵�ƽ
����digitalWrite(GPIO4_30,HIGH)
*/
EXPORT int digitalWrite(const char *pin_str, int value)
{
	int pin;
	pin = convert_gpio_pin(*pin_str);
	int ret=set_gpio_value(pin, value);
	return ret;
}

/*
digitalRead������ȡGPIO�ߵ͵�ƽ
����int pin4_30=digitalRead(GPIO4_30)
*/
EXPORT int digitalRead(const char *pin_str)
{
	int pin;
	pin = convert_gpio_pin(*pin_str);
	int	value=get_gpio_value(pin);
	return value;
}