#include <iostream>

auto IsPalindrome(int x) -> bool
{
    // 负数或以 0 结尾的非零数不是回文数
    if (x < 0 || (x % 10 == 0 && x != 0)) {
        return false;
    }

    int reversedHalf = 0;
    while (x > reversedHalf) {
        // 将数字的后半部分逐位反转
        reversedHalf = reversedHalf * 10 + x % 10;
        x /= 10;
    }

    // x == reversedHalf: 偶数长度回文
    // x == reversedHalf / 10: 奇数长度回文
    return x == reversedHalf || x == reversedHalf / 10;
}
int main(int argc, const char** argv)
{
    if (IsPalindrome(6)) {
        std::cout << "/* message */" << std::endl;
    }
    return 0;
}