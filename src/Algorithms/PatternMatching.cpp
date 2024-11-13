#include <cassert>
#include <cstring>
#include <iostream>
#include <gtest/gtest.h>


static constexpr int SUBMAXSIZE = 100;
static constexpr int  MAXSIZE    = 1000;

int FindStr(const std::string& str1, const std::string& str2)
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
            j = 0;
            i = i - j + 1;
        }
    }
    if (j = s2Len) {
        std::cout << "s2 position in s1 is : " << i - s2Len << std::endl;
        return i - s2Len;
    }

    else
        return -1;
}

int KMP(const std::string& str1, const std::string& str2, int next[])  //
{
    int i = 0, j = 0;
    int len1 = str1.length();
    int len2 = str2.length();
    int pos  = -1;
    while (i < len1 && j < len2) {
        if (j == -1 || str1[i] == str2[j]) {
            ++i;
            ++j;
        }
        else{
            j = next[j];
        }
    }
    if(j = len2){
        pos = i - j;
    }
    return pos;
}
void PrintNext(int next[], int len)
{
    for (int i = 0; i < len; ++i) {
        std::cout << i << ": " << next[i] << std::endl;
    }
}

// next数组存放子串匹配失败时，下一次子串开始匹配的位置，为-1则主串指针向后移动
void Next(std::string str, int next[])
{
    size_t len = str.length();
    int    i = 0, j = -1;
    next[i] = -1;
    while (i < len - 1) {
        if (j == -1 || str[j] == str[i]) {
            ++i;
            ++j;
            next[i] = j;
        }
        else {
            j = next[j];
        }
    }
}

// 对求next数组的修正算法，如果next[i] = T[i]，则next[i] = next[next[i]]
void NextVal(std::string str, int nextval[])
{
    size_t len = str.length();
    int    i = 0, j = -1;
    nextval[i] = -1;
    while (i < len - 1) {
        if (j == -1 || str[j] == str[i]) {
            ++i;
            ++j;
            if (str[j] == str[i]) {
                nextval[i] = nextval[j];
            }
            else {
                nextval[i] = j;
            }
        }
        else {
            j = nextval[j];
        }
    }
}


TEST(PatternMatch, KMP)
{
    std::string s1, s2;
    // std::getline(std::cin, s1);
    // std::getline(std::cin, s2);
    s1 = "ABABABAABABAAABABAA";
    s2 = "ABABAAABABAA";
    /*
        i: 0A  1B  2A  3B  4A  5A  6A  7B  8A  9B  10A  11A
     next: -1   0   0   1   2   3   1   1   2   3    4    5
     nextV:-1   0   -1  0   -1   3  1   0   -1  0    -1   3
    */
    assert(s1.length() < MAXSIZE && s2.length() < SUBMAXSIZE);
    int len = s2.length();
    int next[SUBMAXSIZE];
    Next(s2, next);
    // PrintNext(next, len);

    int nextVal[SUBMAXSIZE];
    NextVal(s2, nextVal);
    // PrintNext(nextVal, len);
    auto pos1 = KMP(s1, s2, next);
    auto pos2 = KMP(s1, s2, nextVal);
    auto pos3 = s1.find(s2);
    std::cout << pos1 << pos2 << pos3 << std::endl;
    EXPECT_EQ(pos1, pos2);
    EXPECT_EQ(pos1, pos3);
}