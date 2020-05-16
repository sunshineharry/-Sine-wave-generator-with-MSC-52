#include "8051.H"


void TIM_0_init(void)
{
    TMOD = TMOD | 0x02;     // 定时器0选择方式2工作
    TH0 = 0xD2;             // 25us 的自动重装定时器
    TL0 = 0xD2;            
    ET0 = 1;                // 打开 T0 中断
    PT0 = 1;                // 设置高优先级
    TR0 = 1;                // T0启动
    EA = 1;                 // 打开总中断
}

void TIM_1_init()
{
    TMOD = TMOD | 0x20;     // 定时器1选择方式2工作
    TH1 = 0xFD;             // 波特率产生
    TL1 = 0xFD;            
    TR1 = 1;                // T0启动
}

void EX0_init()
{
    IT0 = 1;    // 下降沿触发
    PX0 = 0;    // 高优先级
    EX0 = 1;    // 单个中断允许
    EA = 1;     // 总中断运行
}

void EX1_init()
{
    IT1 = 1;    // 下降沿触发
    PX1 = 0;    // 高优先级
    EX1 = 1;    // 单个中断允许
    EA = 1;     // 总中断运行
}