#include "Int_Buzzer.h"
#include "STC89C5xRC.H"

void Int_Buzzer_Buzz() {
    u8 count = 100;
    while (count--) {
        BUZZER = ~BUZZER;
        Com_Util_Delay1MS(1);
    }
}
