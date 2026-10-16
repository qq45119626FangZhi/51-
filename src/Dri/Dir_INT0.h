#ifndef __DIR_INT0_H__
#define __DIR_INT0_H__
typedef void (*INt0_CallBack_Type)();

void Dir_INT0_Init();
void Dri_INt0_RegisterCallBack(INt0_CallBack_Type callback);

#endif /* __DIR_INT0_H__ */