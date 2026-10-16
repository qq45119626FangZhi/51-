#include "Int_key.h"
#include "Com_Util.h"

/**
 * @brief 判断按键1是否按下
 * 
 * @return bit 1表示按下，0标识没有按下
 */
bit Int_Key_CheckSW1Pressed() { 
    //先判断按键状态，0标识按下，按位取反为1，条件成立
    if(!SW1){
        //解决物理按键抖动问题
        Com_Util_Delay1MS(10);
        //再次判断按键状态，0标识按下，按位取反为1，条件成立
        if(!SW1){
            //如果按键一直是按下状态，等待
           while (!SW1);
           //while循环执行完毕表示，按键已经抬起，在按键抬起的时间触发按键点击事件
           return 1;
        }
    }
    return 0; 
}

/**
 * @brief 判断按键2是否按下
 * 
 * @return bit 1表示按下，0标识没有按下
 */
bit Int_Key_CheckSW2Pressed() { 
    if(!SW2){
        Com_Util_Delay1MS(10);
        if(!SW2){
           while (!SW2);
           return 1;
        }
    }
    return 0; 
}

/**
 * @brief 判断按键3是否按下
 * 
 * @return bit 1表示按下，0标识没有按下
 */
bit Int_Key_CheckSW3Pressed() { 
    if(~SW3){
        Com_Util_Delay1MS(10);
        if(~SW3){
           while (~SW3);
           return 1;
        }
    }
    return 0; 
}

/**
 * @brief 判断按键4是否按下
 * 
 * @return bit 1表示按下，0标识没有按下
 */
bit Int_Key_CheckSW4Pressed() { 
    if(~SW4){
        Com_Util_Delay1MS(10);
        if(~SW4){
           while (~SW4);
           return 1;
        }
    }
    return 0; 
}