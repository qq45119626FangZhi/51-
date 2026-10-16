#ifndef __INT_DS1302_H__
#define __INT_DS1302_H__

#include "Com_Util.h"

typedef struct {
    u8 second;
    u8 minute;
    u8 hour;
    u8 day_of_month;
    u8 month;
    u8 year;
    u8 day_of_week;

} DateTime_Struct;

void Int_DS1302_Init();
void Int_DS1302_WriteByte(u8 byte);
u8 Int_DS1302_ReadByte();
void Int_DS1302_WriteReg(u8 cmd_byte, u8 data_byte);
u8 Int_DS1302_ReadReg(u8 cmd_byte);
void Int_DS1302_SetDateTime(DateTime_Struct *dts);
void Int_DS1302_GetDateTime(DateTime_Struct *dts);

#endif /* __INT_DS1302_H__ */