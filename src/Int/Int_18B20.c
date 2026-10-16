#include "Int_18B20.h"
#include "Dri_1Wire.h"

u8 Int_18B20_GetTemperature() {
    u8 ls_byte, ms_byte;
    // 初始化
    Dri_1Wire_Init();
    // 发送ROM命令 跳过ROM命令[0xCC]
    Dri_1Wire_WriteByte(0xCC);
    // 发送功能命令，温度转换[44h]
    // 注意: 完成上述操作后，18B20会自动恢复到低功耗状态
    Dri_1Wire_WriteByte(0x44);

    // 初始化
    Dri_1Wire_Init();
    // 发送ROM命令 跳过ROM命令[0xCC]
    Dri_1Wire_WriteByte(0xCC);

    // 发送功能命令，读取暂存寄存器 [BEh]
    Dri_1Wire_WriteByte(0xBE);

    // 接收前2个字节即可
    ls_byte = Dri_1Wire_ReadByte();
    ms_byte = Dri_1Wire_ReadByte();

    return (ls_byte >> 4) | (ms_byte << 4);
}