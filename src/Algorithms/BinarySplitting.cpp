/*
    一个拆分正整数的小技巧，可以证明 任意十进制整数N，可以被拆分成
    1 + 2 + 4 + 8 + ... + 一个剩余值的形式，且这些部分之间互相组合
    可以组合出1~N之间的任意数。
    比如 6 = 1 + 2 + 3
    1 和 2 和 3 可以组合出 1 -6 之间的任意数
    1:1
    2:2
    3:3
    4:1+3
    5:3+2
    6:6
*/
#include <iostream>
#include <gtest/gtest.h>
TEST(Algorithms, BinarySplitting)
{
    int number;
    while (std::cin >> number) {
        int part = 1;
        while (part <= number) {
            std::cout << part << " ";
            number -= part;
            part <<= 1;
        }
        if (number)
            std::cout << number << std::endl;
    }
 
}