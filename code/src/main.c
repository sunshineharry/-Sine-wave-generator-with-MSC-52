#include "8051.h"
#include "interrupt_func.h"
#include "UART_func.h"
#include "LED_func.h"

unsigned int time = 0;              // 延时常数


// 初始化函数
void init()
{
    UART_init();
    TIM_0_init();
    EX0_init();
    EX1_init();
}


void main()
{
    unsigned char tmp = 200;            // time = 2*tmp
    unsigned int T = 0;                 // 正弦波的周期
                                        // 换算关系：T = 2.5 * time
    init();
    while(1)
    {
        // 更新数据
        if((IE0==1)&&(IE1==0))
        {
            tmp +=10;
            IE0 = 0;
        }
        if((IE0==0)&&(IE1==1))
        {
            tmp -=10;
            IE1 = 0;
        }
        if((IE0==1)&&(IE1==1))
        {
            tmp = tmp - 1;
            IE0 = 0;
            IE1 = 0;
        }

        time = tmp*2;
        T = (unsigned int)(5*tmp);        // 更新周期T

        // 串口发送
        UART_send_data((unsigned char)(T>>8));          // 串口发送高八位
        UART_send_data((unsigned char)(T&0x00ff));      // 串口发送低八位
        
        // LED发送
        if (time==400)                                  // 周期T=1s
        {
            LED_show(1,1);
            LED_show(1,1);                              // 第一位LED显示字符'1'   
        }
        else
        {
            LED_show(1,10);                             // 第一位LED显示字符'0.'
            LED_show(2,(T/100));
            LED_show(3,((T%100)/10));
            LED_show(4,(T%10));
        }
        LED_show(6,11);                             // 第一位LED显示字符'S'
        

    }
}
