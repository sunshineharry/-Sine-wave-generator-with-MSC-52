#include "LED.h"

// 延时，提供LED显示间隔
void delayus(void)
{  
    unsigned char a;
    for(a=5;a>0;a--);
}


void LED_show(uchar LED_number,uchar num)
{
    uchar tmp = 0;
    tmp = LED_number<<5;
    P2 = tmp | 0x0f;
    P1 = num_encode[num];
    delayus();
}