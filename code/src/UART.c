#include "8051.h"
#include "interrupt_func.h"
uchar UARTReceiveData = 0;

// 初始化串口
void UART_init()
{
    TIM_1_init();       // 产生波特率
    SM0 = 0;
    SM1 = 1;
    ES = 1;             // 允许串口中断
    REN = 0;            // 不允许串口运行接收
    EA = 1;             // 允许总中断
}
    
    
// 串口发送数据
void UART_send_data(unsigned char data_to_send)
{
    SBUF = data_to_send;        // 将数据放入缓冲区
    while (!TI);                // 发送ing
    TI = 0;                     // 清空标志位
}

// 串口接收数据
void UART_receive_data() interrupt (UART0_VECTOR)
{
    if(RI)
        UARTReceiveData = SBUF;
    RI = 0;
}

