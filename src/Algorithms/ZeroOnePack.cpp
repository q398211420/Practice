/*
问题描述
辰辰是个天资聪颖的孩子，他的梦想是成为世界上最伟大的医师。为此，他想拜附近最有威望的医师为师。医师为了判断他的资质，给他出了一个难题。医师把他带到一个到处都是草药的山洞里对他说：“孩子，这个山洞里有一些不同的草药，采每一株都需要一些时间，每一株也有它自身的价值。我会给你一段时间，在这段时间里，你可以采到一些草药。如果你是一个聪明的孩子，你应该可以让采到的草药的总价值最大。”
如果你是辰辰，你能完成这个任务吗？

输入格式
第一行有 2 个整数 T ( 1 ≤ T ≤ 1000 ) 和 M ( 1 ≤ M ≤ 100 ) T(1≤T≤1000)和M(1≤M≤100)T(1≤T≤1000)和M(1≤M≤100)，用一个空格隔开，T TT 代表总共能够用来采药的时间，M MM 代表山洞里的草药的数目。

接下来的 M MM 行每行包括两个在 1 到 100 之间（包括 1 和 100）的整数，分别表示采摘某株草药的时间和这株草药的价值。

输出格式
1 个整数，表示在规定的时间内可以采到的草药的最大总价值。

样例输入
70 3
71 100
69 1
1 2

样例输出
3
*/
#include <iostream>
#include <gtest/gtest.h>
using namespace std;

// 方便理解的二维表格形式，行代表物品种类，列代表重量
void Unoptimized()
{
    const int N = 1005;
    const int M = 105;
    int n, m;
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

由于大容量的背包在存放物品时可能不仅能存放前面已经存放的，或许还会因为大容量而使得其能拿更多的物品，从而出现反复拿小体积物品的情况。
因此在自左向右更新的过程中，由于取 max ( d p [ j ] , d p [ j − w [ i ] ] + v [ i ] ) \text{max}(dp[j] , dp[j - w[i]] + v[i])max(dp[j],dp[j−w[i]]+v[i]) 
而使得后面的数组在更新时不断利用前面已经保留好的结果来进行状态转转移，进而不断出错（即对某件物品反复拿取）。

虽然如此，但这个递推公式本身是正确的，只是在使用过程中由于更新方向而出现了一些错误。
从右向左对数组进行更新就好了

PS: 注意：这里的 “错误” 做法，洽洽又是后面完全背包问题的正确处理办法

*/
void Optimized()
{
    const int N = 1005;
    const int M = 105;
    int n, m;
    int dp[N] = {0}, t[M] = {0}, v[M] = {0};
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
        cin >> t[i] >> v[i];
    for (int i = 1; i <= m; i++)
        for (int j = n; j >= t[i]; j--)  // 在 j < t[i] 的这部分（dp[j]），dp[] 数组将延续之前的状态，因此不用更新
            dp[j] = std::max(dp[j], dp[j - t[i]] + v[i]);
    cout << dp[n] << endl;
}

TEST(Algorithms, ZeroOnePack){}
