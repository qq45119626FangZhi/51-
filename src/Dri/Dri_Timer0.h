#ifndef __DRI_TIMER0_H__
#define __DRI_TIMER0_H__

// 定义数组长度
#define CALLBACK_LENGTH 5
// 定义函数指针别名
typedef void (*Timer0_CallBack_Type)();

void Dri_Timer0_Init();
void Dri_Timer0_RegisterCallBack(Timer0_CallBack_Type callback);
void Dri_Timer0_UnRegisterCallBack(Timer0_CallBack_Type callback);

#endif /* __DRI_TIMER0_H__ */