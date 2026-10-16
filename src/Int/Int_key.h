#ifndef __INT_KEY_H__
#define __INT_KEY_H__

#include <STC89C5xRC.H>

#define SW1 P42
#define SW2 P43
#define SW3 P32
#define SW4 P33

bit Int_Key_CheckSW1Pressed();
bit Int_Key_CheckSW2Pressed();
bit Int_Key_CheckSW3Pressed();
bit Int_Key_CheckSW4Pressed();


#endif /* __INT_KEY_H__ */