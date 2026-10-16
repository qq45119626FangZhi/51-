#include "Int_EEPROM.h"
#include "Dri_IIC.h"

#define EEPROM_ADDR_WRITE 0xA0
#define EEPROM_ADDR_READ 0xA1
#define PAGE_SIZE 16

/**
 * @brief 往某个页写数据
 *
 * @param addr  开始写入的地址
 * @param bytes 写入的字节数据
 * @param len   写入的字节数
 */
void Int_EEPROM_WritePage(u8 addr, u8 *bytes, u8 len) {
    u8 i;
    Dri_IIC_Start();
    Dri_IIC_SendByte(EEPROM_ADDR_WRITE);
    Dri_IIC_ReceiveAck();
    Dri_IIC_SendByte(addr);
    Dri_IIC_ReceiveAck();

    for (i = 0; i < len; i++) {
        Dri_IIC_SendByte(bytes[i]);
        Dri_IIC_ReceiveAck();
    }

    Dri_IIC_Stop();
    Com_Util_Delay1MS(3);
}

/**
 * @brief 往EEPROM中写入多个字节
 *
 * @param addr  开始写入的地址
 * @param bytes 写入的字节数据
 * @param len   写入的字节数
 */

void Int_EEPROM_WriteBytes(u8 addr, u8 *bytes, u8 len) {
    u8 page_remain = PAGE_SIZE - (addr & 0x0F);
    if (page_remain >= len) {
        Int_EEPROM_WritePage(addr, bytes, len);
    } else {
        Int_EEPROM_WritePage(addr, bytes, page_remain);
        addr += page_remain;
        bytes += page_remain;
        len -= page_remain;
        // 递归调用
        Int_EEPROM_WriteBytes(addr, bytes, len);
    }
}

/**
 * @brief 从EEPROM中读取多个字节
 *
 * @param addr  开始读取的地址
 * @param bytes 存储读取到的字节数据
 * @param len   读取的字节数
 */
void Int_EEPROM_ReadBytes(u8 addr, u8 *bytes, u8 len) {
    u8 i;
    Dri_IIC_Start();
    Dri_IIC_SendByte(EEPROM_ADDR_WRITE);
    Dri_IIC_ReceiveAck();
    Dri_IIC_SendByte(addr);
    Dri_IIC_ReceiveAck();

    Dri_IIC_Start();
    Dri_IIC_SendByte(EEPROM_ADDR_READ);
    Dri_IIC_ReceiveAck();

    for (i = 0; i < len; i++) {
        bytes[i] = Dri_IIC_ReceiveByte();
        Dri_IIC_SendAck(i == len - 1);
    }

    Dri_IIC_Stop();
}
