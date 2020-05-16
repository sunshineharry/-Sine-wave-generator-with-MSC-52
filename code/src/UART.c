#include "8051.h"
#include "interrupt_func.h"
uchar UARTReceiveData = 0;

// ��ʼ������
void UART_init()
{
    TIM_1_init();       // ����������
    SM0 = 0;
    SM1 = 1;
    ES = 1;             // �������ж�
    REN = 0;            // �����������н���
    EA = 1;             // �������ж�
}
    
    
// ���ڷ�������
void UART_send_data(unsigned char data_to_send)
{
    SBUF = data_to_send;        // �����ݷ��뻺����
    while (!TI);                // ����ing
    TI = 0;                     // ��ձ�־λ
}

// ���ڽ�������
void UART_receive_data() interrupt (UART0_VECTOR)
{
    if(RI)
        UARTReceiveData = SBUF;
    RI = 0;
}

