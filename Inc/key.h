#ifndef __KEY_H
#define __KEY_H
#include "stm32f1xx.h"
#include <stdint.h>

#define KEY3        HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_4)  //KEY0按键PE4
#define KEY2        HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)  //KEY1按键PE3

#define KEY3_PRES 	1
#define KEY2_PRES	2

uint8_t KEY_Scan(uint8_t mode);

#endif