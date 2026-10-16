#include "Dri_1Wire.h"
#include <STC89C5xRC.H>

#define DQ P44

bit Dri_1Wire_Init() {
    bit result;
    DQ = 0; // 主设备将DQ拉低保持480us
    Com_Util_Delay480us();
    DQ = 1; // 主设备释放dq

    // 从设备会等待15-60us,将DQ拉低，回应主设备
    Com_Util_Delay60us();

    // 读取DQ
    // DQ = 0 , 表示回复了存在脉冲
    // DQ = 1 , 表示没有回复存在脉冲
    result = ~DQ;

    // 等待420us，满足最小时长要求
    Com_Util_Delay420us();

    return result;
}

/**
 * @brief 写入字节，低位优先
 *
 */
void Dri_1Wire_WriteByte(u8 byte) {
    u8 i;
    for (i = 0; i < 8; i++) {
        DQ = 0; // 主设备拉低

        // 设备按照当前要发送的是0 还是1 ，将DQ进行拉低或者拉高
        DQ = byte & 0x01;
        byte >>= 1;

        // 主设备保持60us , 从设备会在15- 60us期间读取DQ
        Com_Util_Delay60us();

        DQ = 1; // 主设备释放
    }
}

/**
 * @brief 读取一个字节
 *
 * @return u8
 */
u8 Dri_1Wire_ReadByte() {
    u8 byte = 0;
    u8 i;
    for (i = 0; i < 8; i++) {
        // 主设备先拉低，再释放
        DQ = 0;
        DQ = 1;

        // 从设备会按照要发送的0 还是1 ， 会将DQ 进行拉低或者拉高，并保持15us
        // 主设备选择在第10us，对DQ进行读取
        Com_Util_Delay10us();
        byte >>= 1;
        if (DQ) {
            byte |= 0x80;
        }

        // 主设备再等50us，满足最短时长要求
        Com_Util_Delay50us();
    }

    return byte;
}
