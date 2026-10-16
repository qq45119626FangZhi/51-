#ifndef __INT_OLED_H__
#define __INT_OLED_H__

#include "Com_Util.h"

void Int_OLED_Init();

void Int_OLED_ClearScreen();

void Int_OLED_WriteData(u8 *bytes, u8 len);

void Int_OLED_WriteCmd(u8 *bytes, u8 len);

void Int_OLED_ShowStr(u8 x, u8 y, char *str);

void Int_OLED_ShowNum(u8 x, u8 y, long int num);

#endif /* __INT_OLED_H__ */