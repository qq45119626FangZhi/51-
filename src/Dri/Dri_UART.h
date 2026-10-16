#ifndef __DRI_UART_H__
#define __DRI_UART_H__
#include "Com_Util.h"

void Dri_UART_Init();
void Dri_UART_SendChar(u8 ch);
void Dri_UART_SendString(u8 *str);
bit Dri_UART_IsReceiveString(u8 *str);
void Dri_UART_Timer0CallBack();

#endif /* __DRI_UART_H__ */