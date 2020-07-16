
// Explanation of the script: https://medium.com/@tuztheultimatezed/rgbctf-writeup-advanced-reversing-mechanics-2-37a7d4d15534

#include<stdio.h>
#include<string.h>  // for strcpy

typedef unsigned char byte;
typedef unsigned int uint;
void encryptFlag(byte *param_1)
{
    byte *array;
  byte *next_ptr;
  uint uVar1;
  byte next_value;
  uint uVar2;
  uint uVar3;

  next_value = *param_1;
  array = param_1;
  if (next_value == 0) {
    return;
  }
  while( 1 ) {
    uVar2 = (uint)next_value;
    uVar1 = uVar2 - 10 & 0xff;
    uVar3 = uVar2;
    if ((next_value < 0x50) && (uVar3 = uVar1, 0x50 < uVar1)) {
      uVar3 = uVar2 + 0x46 & 0xff;
    }
    uVar3 = (uVar3 - 7 ^ 0x43) & 0xff;
    next_ptr = array + 1;
    *array = (byte)(uVar3 << 6) | (byte)(uVar3 >> 2);
    next_value = *next_ptr;
    if (next_value == 0) break;
    uVar3 = (int)(next_ptr + -(int)param_1) % 5;
    next_value = next_value << (-uVar3 & 7) | next_value >> (uVar3 & 0xff);
    if (uVar3 == 2) {
      next_value = next_value - 1;
    }
    *next_ptr = next_value;
    next_value = *next_ptr;
    array = next_ptr;
  }
  return;
}


int main(){
    byte flag[36] = {'r', 'g', 'b', 'C', 'T', 'F', '{',0};
    byte expected[35] = {10, 251, 244, 136, 221, 157, 125, 95, 158, 163, 198, 186, 245, 149, 93, 136, 59, 225, 49, 80, 199, 250, 245, 129, 153, 201, 124, 35, 161, 145, 135, 181, 177, 149, 228};
    for (int i = 7; i < sizeof(expected); i ++){
        for (int cur = 32; cur < 128; cur++){
            byte test_flag[60] = {0};
            strcpy(test_flag, flag);    // create an array = flag

            test_flag[i] = (char)cur;   // assign the next character in the array to be cur
            encryptFlag(test_flag);
            if (test_flag[i] == expected[i]){ // if the encrypted character matches the corresponding
                                              // element in expected then append it to our flag
                flag[i] = (char)cur;
                printf("flag: %s\n", flag);
                break;
            }
        }

    }
	return 0;
}










