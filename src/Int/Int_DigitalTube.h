#ifndef __INT_DIGITALTUBE_H__
#define __INT_DIGITALTUBE_H__

#include "Com_Util.h"

void Int_DigitalTube_Init();
void Int_DigitalTube_DisplaySingleNum(u8 position, u8 num_code);
void Int_DigitalTube_DisplayNum(u32 num);
void Int_DigitalTube_DisplayNum1(float num);
void Int_DigitalTube_Refresh();

#endif /* __INT_DIGITALTUBE_H__ */