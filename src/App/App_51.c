#include "App_51.h"

#include "Dir_INT0.h"
#include "Int_Buzzer.h"
#include "Int_DigitalTube.h"
#include "Int_Key.h"
#include "Int_LED.h"
#include "Int_MatrixKey.h"

u8 index = 0;

void App_51_start() {
    Dir_INT0_Init();
    Dri_INt0_RegisterCallBack(Fun_Int_DigitalTube);
    Dri_INt0_RegisterCallBack(Fun_Int_Key);
    Dri_INt0_RegisterCallBack(Fun_Int_Key_DigitalTube);
    Dri_INt0_RegisterCallBack(Fun_Int_MatrixKey);
    while (1) {
        Com_Util_Delay1MS(5000);
    }
}

/**
 * @brief 数码管测试
 *
 */
void Fun_Int_DigitalTube() {

    Int_DigitalTube_Init();
    // 动态显示数字1234
    //  Int_DigitalTube_DisplayNum(1234);
    //  while (1) {
    //      Int_DigitalTube_Refresh();
    //  }

    // 显示数字
    Int_DigitalTube_DisplayNum1(-12345.6789);
    // Int_DigitalTube_DisplayNum(123456789);
    while (1) {
        Int_DigitalTube_Refresh();
        if (!SW3)
            break;
    }
}

/**
 * @brief 独立按键，控制LED灯点亮熄灭
 *
 */
void Fun_Int_Key() {
    while (1) {
        if (Int_Key_CheckSW1Pressed())
            Int_LED_IsSwitchLED(LED1);
        if (Int_Key_CheckSW2Pressed())
            Int_LED_IsSwitchLED(LED2);
        if (Int_Key_CheckSW3Pressed())
            Int_LED_IsSwitchLED(LED3);
        if (Int_Key_CheckSW4Pressed())
            Int_LED_IsSwitchLED(LED4);
        if (!SW3)
            break;
    }
}

/**
 * @brief 独立按键，控制数码管显示1234
 *
 */
void Fun_Int_Key_DigitalTube() {
    // Int_DigitalTube_Init();
    // while (1) {
    //     if (Int_Key_CheckSW1Pressed()) {
    //         Int_DigitalTube_DisplayNum(1);
    //     }
    //     if (Int_Key_CheckSW2Pressed()) {
    //         Int_DigitalTube_DisplayNum(2);
    //     }
    //     if (Int_Key_CheckSW3Pressed()) {
    //         Int_DigitalTube_DisplayNum(3);
    //     }
    //     if (Int_Key_CheckSW4Pressed()) {
    //         Int_DigitalTube_DisplayNum(4);
    //     }
    //     Int_DigitalTube_Refresh();
    //     if (test_toggle)
    //         break;
    // }
}

/**
 * @brief 矩阵按键，控制数码管显示数字, 关闭LED灯
 *
 */
void Fun_Int_MatrixKey() {
    u8 key_num = 0;
    u8 is_init = 0;
    Int_DigitalTube_Init();
    while (1) {
        key_num = Int_MatrixKey_IsSWPressed();
        if (key_num) {
            Int_DigitalTube_DisplayNum(key_num);
            // 蜂鸣器
            Int_Buzzer_Buzz();
        }
        Int_DigitalTube_Refresh();
        if (!SW3)
            break;
    }
}
