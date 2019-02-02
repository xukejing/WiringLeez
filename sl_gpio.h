#ifndef SL_GPIO_H_
#define SL_GPIO_H_

#ifdef __cplusplus
extern "C" {
#endif
#define GPIO_FILENAME_DEFINE(pin,field) char fileName[255] = {0}; \
        sprintf(fileName, "/sys/class/gpio/gpio%d/%s", pin, field);

#define	GPIO_OUT	(1)
#define GPIO_IN		(2)

#define GPIO_LOW    (0)
#define GPIO_HIGH   (1)


extern int convert_gpio_pin(const char *pin_str);
extern int export_gpio_pin(int pin);
extern int unexport_gpio_pin(int pin);
extern int set_gpio_value(int pin, unsigned char value);
extern int get_gpio_value(int pin);
extern int set_gpio_direction(int pin, int direction);
extern int get_gpio_direction(int pin);
#ifdef __cplusplus
}
#endif


#endif
