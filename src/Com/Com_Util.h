#ifndef __COM_UTIL_H__
#define __COM_UTIL_H__

#include <INTRINS.H>

typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long int u32;

void Com_Util_Delay1MS(u16 count);

void Com_Util_Delay480us(void); //@11.0592MHz

void Com_Util_Delay60us(void); //@11.0592MHz

void Com_Util_Delay420us(void); //@11.0592MHz

void Com_Util_Delay50us(void); //@11.0592MHz

void Com_Util_Delay10us(void); //@11.0592MHz

#endif /* __COM_UTIL_H__ */