#include "Int_DigitalTube.h"

#include <MATH.H>
#include <STC89C5xRC.H>

// 需要显示的数字，对应8位数码管
static u8 display_buffer[8];

// 数码管中0-9对应的十六进制数
static u8 num_codes[] = {
    0x3F,  // 对应二进制 0011 1111  对应数码管 0
    0x06,  // 对应二进制 0000 0110  对应数码管 1
    0x5B,  // 对应二进制 0101 1011  对应数码管 2
    0x4F,  // 对应二进制 0100 1111  对应数码管 3
    0x66,  // 对应二进制 0110 0110  对应数码管 4
    0x6D,  // 对应二进制 0110 1101  对应数码管 5
    0x7D,  // 对应二进制 0111 1101  对应数码管 6
    0x07,  // 对应二进制 0000 0111  对应数码管 7
    0x7F,  // 对应二进制 0111 1111  对应数码管 8
    0x6F   // 对应二进制 0110 1111  对应数码管 9
};

/**
 * @brief 数组整体左移一位
 *
 */
void arrow_left1() {
  u8 j;
  for (j = 7; j > 0; j--) {
    display_buffer[j] = display_buffer[j - 1];
  }
}

/**
 * @brief 初始化数码管
 *
 */
void Int_DigitalTube_Init() { P36 = 0; }

/**
 * @brief 显示一个数字到数码管中
 *
 * @param position 显示的位置，位选
 * @param num_code 显示的数字， 段选
 */
void Int_DigitalTube_DisplaySingleNum(u8 position, u8 num_code) {
  // 段选置空
  P0 = 0;
  // P17-P10，置空 P15-P3
  P1 &= 0xc7;  // 11000111
  // 位选的数，向左移动3为，然后与P1做与运算
  position <<= 3;  // 000xxx00
  P1 |= position;  // 110xxx00

  // while (i > 0) {
    P0 = num_code;
  //   i--;
  // }
}

void Int_DigitalTube_DisplayNum(u32 num) {
  u8 i;
  // 清空buffer缓存数据
  for (i = 0; i < 8; i++) {
    display_buffer[i] = 0;
  }

  // 如果数字是0，数组最后一位置为0
  if (!num) {
    display_buffer[7] = num_codes[0];
    return;
  }

  i = 7;
  // 组装任意8位数，按位拆分给数组中每一位赋值
  while (num > 0) {
    display_buffer[i--] = num_codes[num % 10];
    num /= 10;
  }
}

/**
 * @brief  提取小数部分并转为整数（自动适配1~6位小数）
 * @param  num  输入小数（支持大于1的数，仅取小数部分处理）
 * @return unsigned long  小数位对应的整数
 */
u32 float_to_int_decimal(float num) {
  u32 temp_num;
  // 提取纯小数部分（兼容输入大于1的情况，比如1.125也只处理0.125）
  float dec_part = num - (u32)num;
  // 放大6位小数 + 0.5做四舍五入，抵消float精度误差
  temp_num = (u32)(dec_part * 1000000.0 + 0.5);
  // 自动去掉末尾的0，适配不同小数位数
  while (temp_num != 0 && (temp_num % 10) == 0) {
    temp_num /= 10;
  }
  return temp_num;
}

void Int_DigitalTube_DisplayNum1(float num) {
  // 遍历数组角标， 小数的key
  u8 i, temp_i, f_key = 1;
  // 整数部位值
  u32 int_num, temp_int_num;
  // 小数部位值
  float f_num;
  // 清空buffer缓存数据
  for (i = 0; i < 8; i++) {
    display_buffer[i] = 0;
  }

  // 如果数字是0，数组最后一位置为0
  if (!num) {
    display_buffer[7] = num_codes[0];
    return;
  }

  i = 7;
  // 获取整数
  int_num = (u32)(abs(num));
  // 获取小数，并转为正的小数
  if (num < 0) {
    f_num = -(num + int_num);
  } else {
    f_num = num - int_num;
  }

  // 组装小数，最大支持6位小数，并写入buffer中
  if (f_num > 0) {
    u32 int_num1 = float_to_int_decimal(f_num);
    while (int_num1 != 0) {
      display_buffer[i--] = num_codes[int_num1 % 10];
      int_num1 /= 10;
    }
  }
  // 记录加载小数后，i的值
  temp_i = i;
  ;
  // 记录整数值
  temp_int_num = int_num;
  while (int_num != 0) {
    // 此处i--正常是小于0，但是是无符号，i= 255；
    // 如果整数位+小数位大于8，数组整体左移x-8次
    if (i > 8) {
      arrow_left1();
      temp_i++;  // 记录整数值的角标
    }
    int_num /= 10;
    i--;
  }

  i = temp_i;
  int_num = temp_int_num;
  // 组装整数，按位拆分给数组中每一位赋值
  while (int_num != 0) {
    display_buffer[i] = num_codes[int_num % 10];
    // 如果是小数，最后一位加上小数点，对应二进制10000000
    if (f_key && f_num > 0) {
      f_key = 0;
      display_buffer[i] += 128;
    }
    int_num /= 10;
    i--;
  }

  // 负数添加负号
  if (num < 0) {
    // i是无符号，不会存在负数，会变成255
    if (i > 8) {
      i = 0;
      arrow_left1();
    }
    display_buffer[i] = 0x40;  // 01000000
  }
}

void Int_DigitalTube_Refresh() {
  u8 i;
  for (i = 0; i < 8; i++) {
    Int_DigitalTube_DisplaySingleNum(i, display_buffer[i]);
    Com_Util_Delay1MS(1);
  }
}
