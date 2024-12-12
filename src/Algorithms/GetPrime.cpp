/*筛法求素数 优化版*/
#include <gtest/gtest.h>
#include <vector>

// 求小于等于n的所有素数个数
// 筛出m的倍数时，只需要从第m倍开始，因为m的1,2,3,...m-1倍，已经在之前被筛出过了。
auto GetPrime(int n) -> int
{
    int cnt{0};
    std::vector<bool> isPrime(n, true);
    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) {
            cnt++;
            for (int j = i * i; j <= n; j += i) {
                isPrime[j] = false;
            }
        }
    }
    return cnt;
}

TEST(Algorithms, GetPrime)
{
    EXPECT_EQ(GetPrime(100), 25);
    EXPECT_EQ(GetPrime(200), 46);
    EXPECT_EQ(GetPrime(300), 62);
    EXPECT_EQ(GetPrime(400), 78);
    EXPECT_EQ(GetPrime(500), 95);
    EXPECT_EQ(GetPrime(600), 109);
    EXPECT_EQ(GetPrime(1000), 168);
}