#include "Dir_INT0.h"
#include "Com_Util.h"
#include "Int_LED.h"
#include "Int_key.h"
#include <STC89C5xRC.H>
#include <STDIO.H>

#define INt0_CALLBACK_LENGTH 5

INt0_CallBack_Type int0_callbacks[INt0_CALLBACK_LENGTH];
u8 fun_index = 0;

/**
 * @brief 初始化外部中断0
 *
 */
void Dir_INT0_Init() {
    // 打开开关
    EA = 1;  // 中断总开关，1开，0关
    EX0 = 1; // 外部中断0的开关,1开，0关

    IT0 = 1; // 使用下降沿电平触发

    // 设置优先级位10，有四种11，10，01，00
    IPH |= 0x01; // 不可位寻址，只能通过与运算控制位的值
    PX0 = 0;
}

void Dri_INt0_RegisterCallBack(INt0_CallBack_Type callback) {
    u8 i;
    // 先判断是否存在
    for (i = 0; i < INt0_CALLBACK_LENGTH; i++)
        if (int0_callbacks[i] == callback)
            return;

    // 存入数组
    for (i = 0; i < INt0_CALLBACK_LENGTH; i++) {
        if (int0_callbacks[i] == NULL) {
            int0_callbacks[i] = callback;
            break;
        }
    }
}

/**
 * @brief 外部中断0，CPU自动调用，interrupt关键字，0表示中断器的号码，0-7
 * 0外部中断0
 * 1计时器中断0
 * 4串口中断
 *
 */
void Dir_INT0_Handler() interrupt 0 {
    Com_Util_Delay1MS(10);
    if (!SW3) {
        if (fun_index >= INt0_CALLBACK_LENGTH) {
            fun_index = 0;
        }
        int0_callbacks[fun_index]();
    }
}