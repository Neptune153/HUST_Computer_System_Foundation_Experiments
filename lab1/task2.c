
#include <stdio.h>
#include <stdlib.h>

/* 1. 返回 x 的绝对值 */
int absVal(int x) {
    int mask = x >> 31;
    return (x ^ mask) + (~mask + 1);    
}
/* 标准函数  */
int absVal_standard(int x) {
    return (x < 0) ? -x : x;
}

/* 2. 实现 -x */
int negate(int x) {  
    return ~x + 1;
}
/* 标准函数 */
int negate_standard(int x) {
    return -x;
}

/* 3. 实现 & */     
int bitAnd(int x, int y) {  
    return ~(~x | ~y);
}
/* 标准函数 */
int bitAnd_standard(int x, int y) {
    return x & y;
}
/* 4. 实现 | */
int bitOr(int x, int y) {
    return ~((~x) & (~y));
}
/* 标准函数 */
int bitOr_standard(int x, int y) {
    return x | y;
}
/* 5. 实现 ^ */
int bitXor(int x, int y) {
    return ~(~(x & ~y) & ~(~x & y));
}
/* 标准函数 */
int bitXor_standard(int x, int y) {
    return x ^ y;
}

/* 6. 判断x是否为最大的正整数（7FFFFFFF） */
int isTmax(int x) {
    int y = x + 1;         
    return !(y ^ ~x) & !!y;         
}
/* 标准函数 */
int isTmax_standard(int x) {
    return x == 0x7FFFFFFF;
}
/* 7. 统计x的二进制表示中 1 的个数 */
int bitCount(int x) {
    int count = 0;
    while(x){
        count += x & 1;
        x >>= 1;
    }
    return count;
}

/* 标准函数 */
int bitCount_standard(int x) {
    int count = 0;
    for(int i=1;i<=32;++i){
        count += x & 1;
        x >>= 1;
    }
    return count;
}

/* 8. 产生从lowbit 到 highbit 全为1，其他位为0的数00001 11000 */
int bitMask(int highbit, int lowbit) {  
    return (~(~0 << (highbit - lowbit + 1))) << lowbit;
}
/* 标准函数 */
int bitMask_standard(int highbit, int lowbit) {
    return (1 << (highbit + 1)) - (1 << lowbit);
}
/* 9. 当x+y 会产生溢出时返回1，否则返回 0 */
int addOK(int x, int y) {
    int sum = x + y;
    return (((x^sum)&(y^sum))>>31)& 1;    

}
/* 标准函数 */
int addOK_standard(int x, int y) {
    int sum = x + y;
    return (x > 0 && y > 0 && sum <= 0) || (x < 0 && y < 0 && sum >= 0);
}

/* 10. 将x的第n个字节与第m个字节交换，返回交换后的结果 */
int byteSwap(int x, int n, int m) {
    int mask = 0xFF; // 字节掩码
    int byte_n = (x >> (n << 3)) & mask; 
    int byte_m = (x >> (m << 3)) & mask; 
    x &= ~(mask << (n << 3));
    x |= (byte_m << (n << 3)); 
    x &= ~(mask << (m << 3)); 
    x |= (byte_n << (m << 3)); 
    return x;
}
/* 标准函数 */
int byteSwap_standard(int x, int n, int m) {
    int mask = 0xFF; // 字节掩码
    int byte_n = (x >> (n << 3)) & mask; 
    int byte_m = (x >> (m << 3)) & mask; 
    x &= ~(mask << (n << 3));
    x |= (byte_m << (n << 3)); 
    x &= ~(mask << (m << 3)); 
    x |= (byte_n << (m << 3)); 
    return x;
}
/*11. 当 x =0 时，返回 1; 其他情况返回 0。实现逻辑非(!)  */  
int bang(int x) {
    return ((x | (~x + 1)) >> 31) + 1;
}
/* 标准函数 */
int bang_standard(int x) {
    return !x;
}
/*12 int 当 x有奇数个二进制位0，返回1；否则返回0*/
int bitParity(int x) {
    x = ~x; 
    x ^= x >> 16;
    x ^= x >> 8;
    x ^= x >> 4;
    x ^= x >> 2;
    x ^= x >> 1;
    return x & 1; 
}
/* 标准函数 */
int bitParity_standard(int x) {
    int count = 0;
    while(x){
        count++;
        x &= x - 1;
    }
    return count & 1;
}

int main() {
    printf("1. absVal(-1) = %d, \n   absVal_standard(-1) = %d\n", absVal(-1), absVal_standard(-1));
    printf("2. negate(2) = %d, \n   negate_standard(2) = %d\n", negate(2), negate_standard(2));
    printf("3. bitAnd(12, 6) = %d, \n   bitAnd_standard(12, 6) = %d\n", bitAnd(12, 6), bitAnd_standard(12, 6));
    printf("4. bitOr(5, 3) = %d, \n   bitOr_standard(5, 3) = %d\n", bitOr(5, 3), bitOr_standard(5, 3));
    printf("5. bitXor(5, 3) = %d, \n   bitXor_standard(5, 3) = %d\n", bitXor(5, 3), bitXor_standard(5, 3));
    printf("6. isTmax(0x7FFFFFFF) = %d, \n   isTmax_standard(0x7FFFFFFF) = %d\n", isTmax(0x7FFFFFFF), isTmax_standard(0x7FFFFFFF));
    printf("7. bitCount(15) = %d, \n   bitCount_standard(15) = %d\n", bitCount(15), bitCount_standard(15));
    printf("8. bitMask(5, 3) = %X, \n   bitMask_standard(5, 3) = %X\n", bitMask(5, 3), bitMask_standard(5, 3));
    printf("9. addOK(0x7FFFFFFF, 1) = %d, \n   addOK_standard(0x7FFFFFFF, 1) = %d\n", addOK(0x7FFFFFFF, 1), addOK_standard(0x7FFFFFFF, 1));
    printf("10. byteSwap(0x12345678, 1, 3) = %X, \n    byteSwap(0xDEADBEEF, 0, 2) = %X\n", byteSwap(0x12345678, 1, 3), byteSwap(0xDEADBEEF, 0, 2));
    printf("11. bang(0) = %d,\n    bang(-1) = %d, \n    bang(2) = %d\n", bang(0), bang(-1), bang(2));
    printf("12. bitParity(5) = %d,  \n    bitParity(7) = %d\n", bitParity(5), bitParity(7));
    return 0;
}


