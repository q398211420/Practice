/*
多重背包问题
问题描述
有容积为 V VV 的背包，给定一些物品，每种物品包含体积 w、价值 v、和数量 k，求用该背包能装下的最大价值总量。

算法分析
01 背包问题与完全背包问题实际上是两种极端，而多重背包问题则正是介于这两者之间的一种情况。基于此，我们可以将多重背包问题转化为 01 背包或完全背包问题来进行求解。

可以把某种物品中的 k 个视为 k 种不同物品，此时再对所有物品按照01背包问题来进行处理。
这样的转化当然是成立的，但是仅在数据范围较小时才适用，一旦每种物品的数量稍大一点，在时间上必然有超时的风险。
此时，对于某种物品（假设有 k 个），若我们采用一种更精炼的划分方案，就会使得该物品分类下来的组数大大减少。
比如可以采用二进制的拆分将原来的 k kk个物品分为： { 1 , 2 , 4 , ..., 剩余部分 }这些组，
以替代最初的分类：{ 1 , 1 , 1 , … , 1 } 这些组，这是一个 log2(n)级别的数量优化。

若存在某个物品，其数量 k kk 乘以其单位体积大于背包总容量（即 k ∗ w [i] > V），那么此时对于该物品而言，它与背包之间是完全背包问题。
上述两点分别从 01 背包和完全背包的角度对多重背包问题进行了转化，而多重背包正好也是介于 01 背包和完全背包之间的问题。
正是这两点，使得我们能设计出一个可以与 “单调队列优化” 分庭抗衡的算法。下面还是用一个实际例题来练手，以巩固理解。


输入格式
输入的第一行有两个整数 n （ 1 ≤ n ≤ 100000 ） n（1 ≤ n ≤ 100000）n（1≤n≤100000）和 m （ 1 ≤ m ≤ 10000 ） m（1 ≤ m ≤ 10000）m（1≤m≤10000），用一个空格隔开，
n 表示推车所能程受的最大重量，m 代表超市中的商品种类数。
接下来有 m行，每行包括 3 个在 1 到 1000 之间（包括 1 和 1000）的整数，分别表示当前某个商品的重量、价格以及库存数量。

输出格式
输出一行，这一行只包含一个整数，表示辰辰所能取到的最大价值。

样例输入
50 4
10 200 4
15 250 3
20 350 2
25 500 1

样例输出
950
*/

#include <iostream>
using namespace std;

const int N = 100005;
const int M = 10005;
int n, m;
int dp[N], w[M], v[M], num[M];

void ZeroOnePack(int weight, int value)  //01背包模型
{
    for (int i = n; i >= weight; i--)
        dp[i] = max(dp[i], dp[i - weight] + value);
}
void CompletePack(int weight, int value)  //完全背包模型
{
    for (int i = weight; i <= n; i++)
        dp[i] = max(dp[i], dp[i - weight] + value);
}
void MultiplePack(int weight, int value, int number)  //多重背包模型
{
    if (number * weight > n) {  //如果总容量比这个物品的容量要小，那就退化为完全背包
        CompletePack(weight, value);
        return;
    }
    else {  //否则就将其转化为01背包（并利用二进制的拆分来优化）
        int k = 1;
        while (k <= number) {
            ZeroOnePack(k * weight, k * value);
            number -= k;
            k << 1;
        }
        if (number != 0)
            ZeroOnePack(number * weight, number * value);
    }
}

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
        cin >> w[i] >> v[i] >> num[i];
    for (int i = 1; i <= m; i++)
        MultiplePack(w[i], v[i], num[i]);
    cout << dp[n] << endl;
    return 0;
}
