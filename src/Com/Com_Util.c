#include "Com_Util.h"

/**
 * @brief 程序延迟函数，毫秒
 *
 * @param count 毫秒单位
 */
void Com_Util_Delay1MS(u16 count) {
    unsigned char data i, j;
    while (count > 0) {
        _nop_();
        i = 2;
        j = 199;
        do {
            while (--j);
        } while (--i);
        count--;
    }
}

void Com_Util_Delay480us(void) {
    unsigned char data i;

    _nop_();
    i = 218;
    while (--i);
}

void Com_Util_Delay60us(void) {
    unsigned char data i;

    i = 25;
    while (--i);
}

void Com_Util_Delay420us(void) {
    unsigned char data i;

    i = 191;
    while (--i);
}

void Com_Util_Delay50us(void) {
    unsigned char data i;

    _nop_();
    i = 20;
    while (--i);
}

void Com_Util_Delay10us(void) {
    unsigned char data i;

    i = 2;
    while (--i);
}
