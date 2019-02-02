#ifndef WIRINGLEEZ_H_
#define WIRINGLEEZ_H_

#ifdef __cplusplus
extern "C" {
#endif
#define GPIO_FILENAME_DEFINE(pin,field) char fileName[255] = {0}; \
        sprintf(fileName, "/sys/class/gpio/gpio%d/%s", pin, field);

#define HIGH 0x1
#define LOW  0x0

#define INPUT 0x0
#define OUTPUT 0x1


	extern int convert_gpio_pin(const char *pin_str);
	extern int export_gpio_pin(int pin);
	extern int unexport_gpio_pin(int pin);
	extern int set_gpio_value(int pin, int value);
	extern int get_gpio_value(int pin);
	extern int set_gpio_direction(int pin, int direction);
	extern int get_gpio_direction(int pin);
	extern int pinMode(const char *pin_str, int direction);
	extern int digitalWrite(const char *pin_str, int value);
	extern int digitalRead(const char *pin_str);
#ifdef __cplusplus
}
#endif


#endif