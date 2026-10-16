#ifndef __INT_MATRIXKEY_H__
#define __INT_MATRIXKEY_H__

#include "Com_Util.h"

/**
 * @brief 按键按下检测（消抖+松手有效），支持传入任意sbit引脚
 * @param sw  输入：按键对应的sbit变量（按下为低电平）
 * @param res 输出：检测结果（bit类型），1=按下并松手，0=未按下
 */
#define Int_Key_CheckSWPressed(sw, res) do { \
    res = 0; \
    if(!(sw)) { \
        Com_Util_Delay1MS(10); \
        if(!(sw)) { \
            while(!(sw)); \
            res = 1; \
        } \
    } \
} while(0)


/**
 * @brief 按键检测（低电平触发、10ms消抖、松手有效，和原sbit版逻辑完全一致）
 * @param port  端口寄存器（直接填P1/P2/P3，不要传地址）
 * @param bit_n 按键对应位号（0~7，P24就填4）
 * @param res   输出结果变量，1=按下并松手，0=未按下
 */
#define Int_Key_CheckByBit(port, bit_n, res) do { \
    res = 0; \
    if( !((port) & (1 << (bit_n))) ) {  /* 第一次检测低电平 */ \
        Com_Util_Delay1MS(10); \
        if( !((port) & (1 << (bit_n))) ) {  /* 消抖后二次确认 */ \
            while( !((port) & (1 << (bit_n))) );  /* 等待松手（电平变高） */ \
            res = 1; \
        } \
    } \
} while(0)


u8 Int_MatrixKey_IsSWPressed();


#endif /* __INT_MATRIXKEY_H__ */