#include "Int_LED.h"
#include "Com_Util.h"
#include "Int_Key.h"

void Int_LED_Init(bit b) { P34 = b; }

/**
 * @brief 往返流水灯
 *
 */
void Int_Running_Light() {
    u8 temp = 0x01;
    u8 arrow = 1;
    Int_LED_Init(1);

    while (1) {
        P0 = ~temp;
        if (arrow) {
            temp <<= 1;
            if (temp == 0x80)
                arrow = 0;
        } else {
            temp >>= 1;
            if (temp == 0x01)
                arrow = 1;
        }
        Com_Util_Delay1MS(100);
    }
}