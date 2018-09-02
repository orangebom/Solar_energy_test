#include "key.h"


//mode:0,不支持连续按;1,支持连续按;
//注意此函数有响应优先级,KEY3>KEY2
uint8_t KEY_Scan(uint8_t mode)
{
    static uint8_t key_up=1;     //按键松开标志
    if(mode==1)key_up=1;    //支持连按
    if(key_up&&(KEY2==1||KEY3==0))
    {
        HAL_Delay(10);
        key_up=0;
        if(KEY2==0)       return KEY2_PRES;
        else if(KEY3==1)  return KEY3_PRES;        
    }else if(KEY2==0&&KEY3==1)key_up=1;
    return 0;   //无按键按下
}

