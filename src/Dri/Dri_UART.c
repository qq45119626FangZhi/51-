#include "Dri_UART.h"
#include "Int_LED.h"
#include <STC89C5xRC.H>

#define END_TIME 10

// 是否正在发送
static bit s_is_sending = 0;
// 是否接收完成
static u8 s_receive_complete = 0;
// 缓存接收数据的指令
static u8 s_receive_buffer[10];
// 缓存数据的角标
static u8 s_receive_index = 0;
// 判断AURT总线是否空闲
static u8 s_idle_count = 0;

/**
 * @brief UART串口初始化
 *
 */
void Dri_UART_Init() {
    // UART中断启用
    EA = 1; // 中断总开关
    ES = 1; // 串口中断开关

    // 串口的工作模式，01表示模式1，8位UART，比特率可变
    SM0 = 0;
    SM1 = 1;
    PCON &= 0x7F; // 设置波特率9600，SMOD位，最高位为0
    REN = 1;      // 设置接收使能
    SM2 = 0;      // 不检测结束位

    // 设置定时器1来协助处理串口功能
    // // ET1 = 1;不处理定时器1的串口服务，不需要
    TMOD &= 0x0F; // 高4位置空
    // 给高4位同时赋值，0010，
    // 第一个0
    // Game启动定时器，第二个0，C/T系统定时，10表示8位自动重装载工作模式，对应M1和M0位
    TMOD |= 0x20;
    TL1 = 253; // 脉冲计数器初始值
    TH1 = 253; // 脉冲计数器初始值
    TR1 = 1;   // 启动定时器

    // 串口接收中断标志复位
    TI = 0;
    RI = 0;
}

/**
 * @brief 发送单个字符
 *
 * @param ch 一个字符
 */
void Dri_UART_SendChar(u8 ch) {
    while (s_is_sending);
    s_is_sending = 1;
    SBUF = ch;
}

/**
 * @brief 发送字符串
 *
 * @param str 字符 指针
 */
void Dri_UART_SendString(u8 *str) {
    while (*str != '\0') {
        Dri_UART_SendChar(*str);
        str++;
    }
}

/**
 * @brief 判断字符串指令，
 *
 * @param str 字符指针
 * @return 1是，0否
 */
bit Dri_UART_IsReceiveString(u8 *str) {
    u8 i;
    if (s_receive_complete) {
        // 如果接收完成，将指令数据赋值给指针
        for (i = 0; i < s_receive_index; i++) {
            str[i] = s_receive_buffer[i];
        }
        str[i] = '\0';          // 每个字符串指令添加结束标志
        s_receive_index = 0;    // 重置数组角标
        s_receive_complete = 0; // 重置接收完成的状态
        return 1;
    }
    return 0;
}

/**
 * @brief 判断字符串指令，使用总线空闲方案
 *
 */
void Dri_UART_Timer0Callback() {
    // 如果时间大于10毫秒，且有接受过数据，表示接收完成
    s_idle_count++;
    if (s_idle_count > END_TIME && s_receive_index > 0) {
        s_receive_complete = 1;
    }
}

/**
 * @brief 串口UART的中断服务
 *
 */
void Dri_UATR_Handler() interrupt 4 {
    // 发送数据完成
    if (TI == 1) {
        s_is_sending = 0; // 发送状态
        TI = 0;           // 重置发送中断标志
    }

    // 接收数据完成。
    if (RI == 1) {
        // 缓存命令数据
        s_receive_buffer[s_receive_index++] = SBUF;
        s_idle_count = 0; // 接收到数据，重置时间计数器

        RI = 0; // 重置接收中断标志
    }
}
