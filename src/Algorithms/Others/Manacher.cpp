/*
马拉车求最长回文子串长度算法
有几点需要注意理解
1. radius 代表回文半径，比如1234321 回文半径为4
2. 添加诸如'#'这类特殊字符，使得所有回文串必为奇数串，可以把原回文串的奇偶串统一处理
3. arr存储了每个以当前下标为中心的回文串的回文半径。最后结果最长回文子串的长度等于arr[target] -1(可自行证明)
4.  从左往右依次计算对应下标的回文半径，如果当前下标j被包含在某个i的回文半径(只需和当前所求到的所有回文半径里，最靠右的那个比较)之内，
    则当前下标j的回文半径至少是关于i的镜像那个下标的回文半径(前提是j+j的回文半径也在i的半径之内)。
    比如 1 2 3 2 5 2 3 2 1 ，右边的3位于5的半径之内，所以右边的3的半径可依据左边的3的半径来算
*/
#include <string>
#include <vector>
#include <gtest/gtest.h>

auto Manacher(std::string str) -> int
{
    std::string newStr;
    newStr += "$#";  //$为哨兵
    for (auto e : str) {
        newStr += e;
        newStr += "#";
    }
    int maxRadius{1};
    int rBorder{1};  //当前已求所有回文子串中最右边界的下一个位置
    int rIndex{0};
    std::vector<int> arr(newStr.length(), 1);
    for (int i = 2; i < newStr.length() - 1; i++) {
        int radius{1};
        // i - rIndex = rIndex - j;
        // j = 2*rIndex-i;
        radius = i < rBorder ? std::min(arr[2 * rIndex - i], rBorder - i) : 1;

        while(newStr[i+radius] == newStr[i-radius]){
            radius++;
        }
  

        arr[i] = radius;
        maxRadius = std::max(radius, maxRadius);
        if (i + radius > rBorder) {
            rBorder = i + radius;
            rIndex = i;
        }
    }

    return maxRadius - 1;
}
TEST(Others, Manacher)
{
    EXPECT_EQ(Manacher("a"), 1);
    EXPECT_EQ(Manacher("ababc"), 3);
    EXPECT_EQ(Manacher("abacabaabacaba"), 14);
    
}