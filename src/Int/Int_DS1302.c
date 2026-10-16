#include "Int_DS1302.h"
#include <STC89C5xRC.H>

#define SCLK P37
#define IO P40
#define CE P41

#define SECOND 0x80
#define MINUTE 0x82
#define HOUR 0x84
#define DAY_OF_MONTH 0x86
#define MONTH 0x88
#define DAY_OF_WEEK 0x8A
#define YEAR 0x8C

void Int_DS1302_Init() {
    SCLK = 0;
    IO = 0;
    CE = 0;
}

/**
 * @brief 写字节，低位开始
 *
 * @param byte
 */
void Int_DS1302_WriteByte(u8 byte) {
    u8 i;
    for (i = 0; i < 8; i++) {
        IO = byte & 0x01;
        byte >>= 1;
        // 上升沿写入
        SCLK = 0;
        SCLK = 1;
    }
}

/**
 * @brief 读取字节
 *
 * @return u8
 */
u8 Int_DS1302_ReadByte() {
    u8 byte = 0, i;
    for (i = 0; i < 8; i++) {
        // 再下降沿写入数据，从高位开始
        if (i > 0) {
            SCLK = 1;
        }
        SCLK = 0;
        byte >>= 1;
        if (IO) {
            byte |= 0x80;
        }
    }
    return byte;
}

/**
 * @brief 写入寄存器
 *
 * @param cmd_byte 控制字节
 * @param data_byte 数据字节
 */
void Int_DS1302_WriteReg(u8 cmd_byte, u8 data_byte) {
    Int_DS1302_Init();
    CE = 1;

    Int_DS1302_WriteByte(cmd_byte);
    Int_DS1302_WriteByte(data_byte);

    CE = 0;
}

/**
 * @brief 读取寄存器中数据
 *
 * @param cmd_byte 控制字节
 * @return 数据字节
 */
u8 Int_DS1302_ReadReg(u8 cmd_byte) {
    u8 data_byte;
    Int_DS1302_Init();
    CE = 1;

    Int_DS1302_WriteByte(cmd_byte);
    data_byte = Int_DS1302_ReadByte();

    CE = 0;

    return data_byte;
}

/**
 * @brief 设置起始时间
 *
 */
void Int_DS1302_SetDateTime(DateTime_Struct *dts) {
    // 分别对应 秒、分、时、天、月、年、周
    u8 date_byte = ((dts->second / 10) << 4) | (dts->second % 10);
    Int_DS1302_WriteReg(SECOND, date_byte);

    date_byte = ((dts->minute / 10) << 4) | (dts->minute % 10);
    Int_DS1302_WriteReg(MINUTE, date_byte);

    date_byte = ((dts->hour / 10) << 4) | (dts->hour % 10);
    Int_DS1302_WriteReg(HOUR, date_byte);

    date_byte = ((dts->day_of_month / 10) >> 4) | (dts->day_of_month % 10);
    Int_DS1302_WriteReg(DAY_OF_MONTH, date_byte);

    date_byte = ((dts->month / 10) << 4) | (dts->month % 10);
    Int_DS1302_WriteReg(MONTH, date_byte);

    date_byte = ((dts->year / 10) << 4) | (dts->year % 10);
    Int_DS1302_WriteReg(YEAR, date_byte);

    date_byte = dts->day_of_week;
    Int_DS1302_WriteReg(DAY_OF_WEEK, date_byte);
}

/**
 * @brief 获取时间
 *
 */
void Int_DS1302_GetDateTime(DateTime_Struct *dts) {
    // 分别对应 秒、分、时、天、月、年、周
    u8 date_byte = Int_DS1302_ReadReg(SECOND + 1);
    dts->second = ((date_byte >> 4) * 10) + (date_byte & 0x0F);

    date_byte = Int_DS1302_ReadReg(MINUTE + 1);
    dts->minute = ((date_byte >> 4) * 10) + (date_byte & 0x0F);

    date_byte = Int_DS1302_ReadReg(HOUR + 1);
    dts->hour = ((date_byte >> 4) * 10) + (date_byte & 0x0F);

    date_byte = Int_DS1302_ReadReg(DAY_OF_MONTH + 1);
    dts->day_of_month = ((date_byte >> 4) * 10) + (date_byte & 0x0F);

    date_byte = Int_DS1302_ReadReg(MONTH + 1);
    dts->month = ((date_byte >> 4) * 10) + (date_byte & 0x0F);

    date_byte = Int_DS1302_ReadReg(YEAR + 1);
    dts->year = ((date_byte >> 4) * 10) + (date_byte & 0x0F);

    date_byte = Int_DS1302_ReadReg(DAY_OF_WEEK + 1);
    dts->day_of_week = date_byte;
}