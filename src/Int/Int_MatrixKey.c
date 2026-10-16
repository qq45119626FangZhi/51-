#include "Int_MatrixKey.h"

#include "STC89C5xRC.H"

// P2对应的数
// static u8 matrixKey_Codes[] = {0xFE, 0xFD, 0xFB, 0xF7};

// // 返回值
// static u8 matrixKey_nums[] = {5, 9, 13, 17};
// /*
//   0xA0          1            2           3           4
//   10100000   00000001   00000010     00000011     00000100
//  ^
//              10100001   10100010     10100011     10100100
//           11111110
// 1 << 4 =  00010000
// &         00010000
// */
// static u8 p2_addrs[] = {0xA4, 0xA5, 0xA6, 0xA7};

/**
 * @brief 控制矩阵按键
 *
 * @return u8 返回数字
 */
u8 Int_MatrixKey_IsSWPressed() {
  // P2组 GIOP
  u8 i = 0, j = 0;
  for (i = 0; i < 4; i++) {
    P2 = ~(1 << i);
    for (j = 0; j < 4; j++) {
      if (!(P2 & (16 << j))) {
        Com_Util_Delay1MS(10);
        if (!(P2 & (16 << j))) {
          while (!(P2 & (16 << j)));
          return 5 + j + 4 * i;
        }
      }
    }
  }
  return 0;
}