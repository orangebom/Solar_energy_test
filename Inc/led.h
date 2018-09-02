#ifndef __LED_H
#define __LED_H

#define LED1_OFF HAL_GPIO_WritePin(GPIOE,GPIO_PIN_5,GPIO_PIN_SET);   	//LED1对应引脚PE5拉高
#define LED1_ON HAL_GPIO_WritePin(GPIOE,GPIO_PIN_5,GPIO_PIN_RESET);   	//LED1对应引脚PE5拉低

#define LED0_OFF HAL_GPIO_WritePin(GPIOE,GPIO_PIN_6,GPIO_PIN_SET);   	//LED0对应引脚PE6拉高
#define LED0_ON HAL_GPIO_WritePin(GPIOE,GPIO_PIN_6,GPIO_PIN_RESET);   	//LED0对应引脚PE6拉低

void LED_Init(void);


#endif