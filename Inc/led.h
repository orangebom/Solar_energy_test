#ifndef __LED_H
#define __LED_H

#define LED1_OFF HAL_GPIO_WritePin(GPIOE,GPIO_PIN_5,GPIO_PIN_SET);   	//LED1��Ӧ����PE5����
#define LED1_ON HAL_GPIO_WritePin(GPIOE,GPIO_PIN_5,GPIO_PIN_RESET);   	//LED1��Ӧ����PE5����

#define LED0_OFF HAL_GPIO_WritePin(GPIOE,GPIO_PIN_6,GPIO_PIN_SET);   	//LED0��Ӧ����PE6����
#define LED0_ON HAL_GPIO_WritePin(GPIOE,GPIO_PIN_6,GPIO_PIN_RESET);   	//LED0��Ӧ����PE6����

void LED_Init(void);


#endif