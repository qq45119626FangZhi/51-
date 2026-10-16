#include "Dri_Timer0.h"
#include "Com_Util.h"
#include <STC89C5xRC.H>
#include <STDIO.H>

Timer0_CallBack_Type callbacks[CALLBACK_LENGTH];

/**
 * @brief 初始化Timer0中断
 *
 */
void Dri_Timer0_Init() {
    // 打开开关
    EA = 1;
    ET0 = 1;

    // TMOD寄存器后四位置空
    TMOD &= 0xF0;

    // TMOD寄存器配置模式，统一设置后三位
    // 001， 第一个0是选择系统时钟计算模式，后面01表示表示0-16位定时计时器
    TMOD |= 0x01;

    // 设置初始值，已毫秒位单位，1ms
    TL0 = 64614;      // 有8位，低位只有8位，只能存下后8位，存入低8位
    TH0 = 64614 >> 8; // 整体右移8位，变成高8位，存入高8位

    // 启动
    TMOD &= ~(1 << 3);
    TR0 = 1;
}

void Dri_Timer0_RegisterCallBack(Timer0_CallBack_Type callback) {
    u8 i;
    // 先判断是否存在
    for (i = 0; i < CALLBACK_LENGTH; i++)
        if (callbacks[i] == callback)
            return;

    // 存入数组
    for (i = 0; i < CALLBACK_LENGTH; i++) {
        if (callbacks[i] == NULL) {
            callbacks[i] = callback;
            break;
        }
    }
}

void Dri_Timer0_UnRegisterCallBack(Timer0_CallBack_Type callback) {
    u8 i;
    // 移除数据
    for (i = 0; i < CALLBACK_LENGTH; i++) {
        if (callbacks[i] == callback) {
            callbacks[i] = NULL;
            break;
        }
    }
}

void Dri_Timer0_Handler() interrupt 1 {
    // 每1ms触发一个计时器，需要重新设置初始值
    u8 i;
    TL0 = 64614;      // 有8位，低位只有8位，只能存下后8位，存入低8位
    TH0 = 64614 >> 8; // 整体右移8位，变成高8位，存入高8位
    for (i = 0; i < CALLBACK_LENGTH; i++)
        if (callbacks[i] != NULL)
            callbacks[i](); // 函数指针调用函数
}
