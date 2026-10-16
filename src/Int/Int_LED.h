#ifndef __INT_LED_H__
#define __INT_LED_H__

#include <STC89C5xRC.H>

//LED 总开关
#define LED P34

//1-4的灯
#define LED1 P00
#define LED2 P01
#define LED3 P02
#define LED4 P03
#define Int_LED_IsSwitchLED(led) (led = !led)

void Int_LED_Init(bit b);
void Int_Running_Light();


#endif /* __INT_LED_H__ */