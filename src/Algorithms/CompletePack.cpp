/*
问题描述
辰辰是个天资聪颖的孩子，他的梦想是成为世界上最伟大的医师。为此，他想拜附近最有威望的医师为师。医师为了判断他的资质，给他出了一个难题。医师把他带到一个到处都是草药的山洞里对他说：“孩子，这个山洞里有一些不同种类的草药，采每一种都需要一些时间，每一种也有它自身的价值。我会给你一段时间，在这段时间里，你可以采到一些草药。如果你是一个聪明的孩子，你应该可以让采到的草药的总价值最大。”
如果你是辰辰，你能完成这个任务吗？
此题和原题（P1048 采药）的不同点：

每种草药可以无限制地疯狂采摘。
药的种类眼花缭乱，采药时间好长好长啊！（暗示数据范围更大）
输入格式
输入第一行有两个整数 T （ 1 ≤ T ≤ 100000 ） T（1 ≤ T ≤ 100000）T（1≤T≤100000） 和 M （ 1 ≤ M ≤ 10000 ） M（1 ≤ M ≤ 10000）M（1≤M≤10000），用一个空格隔开，T TT 代表总共能够用来采药的时间，M MM 代表山洞里的草药的数目。接下来的M行每行包括两个在 1 到 10000之间（包括 1 和 10000）的整数，分别表示采摘某种草药的时间和这种草药的价值。

输出格式
输出一行，这一行只包含一个整数，表示在规定的时间内，可以采到的草药的最大总价值。

样例输入
70 3
71 100
69 1
1 2

样例输出
140
*/

// 方便理解的二维表格形式，行代表物品种类，列代表重量
#include <iostream>
#include <gtest/gtest.h>
using namespace std;
void CPUnoptimized()
{
    const int N = 1005;
    const int M = 105;
    int n, m, maxValue, temp;
    int dp[M][N] = {0}, t[M] = {0}, v[M] = {0};

    cin >> n >> m;
    for (int i = 1; i <= m; i++)
        cin >> t[i] >> v[i];
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            if (j >= t[i])
                dp[i][j] = std::max(dp[i - 1][j], dp[i - 1][j - t[i]] + v[i]);
            else
                dp[i][j] = dp[i - 1][j];
    cout << dp[m][n] << endl;
}

/* 
采用滚动数组降维
在前面 01 背包问题中我们讨论降维时，出现了一个有趣的现象——如果更新dp[]数组时采用自左向右的方向，那么在后面进行更新时，其执行逻辑是“可重复拿取某件物品”！
巧了，现在我们所作的假设就是所有物品都有无数件（即可重复拿），这不正好就可以拿来用了么？
换言之，现在我们不再需要用最里面的那层 k kk 循环来确定某个网格到底拿多少物品才能使得背包总价值最大，而是通过采取和 01 背包问题中相反的更新p[] 
数组方向来实现。这样一来，我们还顺带解决了时间复杂度过高的问题！
*/
void CPOptimized()
{
    const int N = 100005;
    const int M = 10005;
    int n, m;
    int dp[N] = {0}, t[M] = {0}, v[M] = {0};

    cin >> n >> m;
    for (int i = 1; i <= m; i++)
        cin >> t[i] >> v[i];
    for (int i = 1; i <= m; i++)
        for (int j = t[i]; j <= n; j++)
            dp[j] = max(dp[j], dp[j - t[i]] + v[i]);
    cout << dp[n] << endl;
}

TEST(Algorithms, CompletePack){}