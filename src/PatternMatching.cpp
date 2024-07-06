#include <cassert>
#include <cstring>
#include <iostream>

#define SUBMAXSIZE 100
#define MAXSIZE 1000
int FindStr(const std::string& str1, const std::string& str2)  // 暴力匹配
{
    int s1Len = str1.length();
    int s2Len = str2.length();
    int i = 0, j = 0;
    while (i < s1Len && j < s2Len) {
        if (str1[i] == str2[j]) {
            ++i;
            ++j;
        }
        else {
            j = 1;
            i = i - j + 2;
        }
    }
    if (j = s2Len)
        return i - s2Len;

    else
        return -1;
}

int KMP(const std::string& str1, const std::string& str2)  //
{
    return 0;
}

// next数组存放子串匹配失败时，下一次子串开始匹配的位置，为-1则主串指针向后移动
void Next(std::string str, int next[])
{
    size_t len = str.length();
    int    i   = 0;
    next[0]    = -1;
    int j =
        -1;  // j表示当前循环中要比较的next[j]值，对于每个i，首轮比较一定是str[i]和
             // str[next[i]];
    while (i < len - 1) {
        if (j == -1 || str[i] == str[j]) {
            ++i;
            ++j;
            next[i] = j;
        }
        else
            j = next[j];
    }
}

void NextVal(std::string str, int a[])  // 对求next数组的修正算法，如果next[i] =
                                        // T[i]，则next[i] = next[next[i]]
{
}

int main(int argc, char* argv[])
{
    std::string s1, s2;
    // std::getline(std::cin, s1);
    // std::getline(std::cin, s2);
    s1 = "iamaboyanasdeLOVElym";
    s2 = "LOVE";
    assert(s1.length() < MAXSIZE && s2.length() < SUBMAXSIZE);
    int pos = FindStr(s1, s2);
    std::cout << "s2 position in s1 is : " << pos << std::endl;

    return 0;
}