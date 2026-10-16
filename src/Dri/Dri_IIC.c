#include "Dri_IIC.h"

/**
 * @brief 发送起始信号
 *
 */
void Dri_IIC_Start() {
    SCL = 1;
    SDA = 1;
    SDA = 0;
    SCL = 0;
}

/**
 * @brief 发送结束信号
 *
 */
void Dri_IIC_Stop() {
    SDA = 0;
    SCL = 1;
    SDA = 1;
}

/**
 * @brief 发送一个字节
 *
 * @param byte
 */

void Dri_IIC_SendByte(u8 byte) {
    u8 i;
    u8 temp = 0x80;
    for (i = 0; i < 8; i++) {
        SDA = (byte & temp) == 0 ? 0 : 1;
        temp >>= 1;
        SCL = 1;
        SCL = 0;
    }
}

/**
 * @brief 读取一个字节
 *
 * @return u8
 */
u8 Dri_IIC_ReceiveByte() {
    u8 byte = 0;
    u8 i;
    SDA = 1;
    for (i = 0; i < 8; i++) {
        SCL = 1;
        byte = (byte << 1) | SDA;
        SCL = 0;
    }
    return byte;
}

/**
 * @brief 发送ACK
 *
 * @param ack
 */
void Dri_IIC_SendAck(bit ack) {
    SDA = ack;
    SCL = 1;
    SCL = 0;
}

/**
 * @brief 接收ACK
 *
 * @return bit
 */

bit Dri_IIC_ReceiveAck() {
    bit ack;
    SDA = 1;
    SCL = 1;
    ack = SDA;
    SCL = 0;
    return ack;
}
