/*
通过一道面试题掌握优先级队列用法
某公司组织一场公开招聘活动，假设由于人数和场地的限制，每人每次面试的时长不等，并已经安排给定，用(S1,E1)、 (S2,E2)、 (Sj,Ej)…(Si < Ei，均为非负整数)表示每场面试的开始和结束时间。

面试采用一对一的方式，即一名面试官同时只能面试一名应试者，一名面试官完成一次面试后可以立即进行下一场面试，且每个面试官的面试人次不超过 m。

为了支撑招聘活动高效顺利进行，请你计算至少需要多少名面试官。

输入描述

输入的第一行为面试官的最多面试人次 m，第二行为当天总的面试场次 n，

接下来的 n 行为每场面试的起始时间和结束时间，起始时间和结束时间用空格分隔。

其中， 1 <= n, m <= 500

输出描述

输出一个整数，表示至少需要的面试官数量。

示例 1   输入输出示例仅供调试，后台判题数据一般不包含示例

输入

2

5

1 2

2 3

3 4

4 5

5 6

输出

3

说明

总共有 5 场面试，且面试时间都不重叠，但每个面试官最多只能面试 2 人次，所以需要 3 名面试官。

示例2
输入
3
3
1 2
2 3
3 4
输出
1
说明
总共有3场面试，面试时间都不重叠，每个面试官最多能面试3人次，所以只需要1名面试官。


示例3
输入
3
3
8 35
5 10
1 3
输出
2
说明
总共有3场面试，[5,10]和[8,35]有重叠，所以至少需要2名面试官。
*/

#include <iostream>
#include <queue>

struct Interviewer
{
    int person{0};
    int end{0};
};

auto main(int argc, const char** argv) -> int
{
    int m, n;
    std::cin >> m >> n;
    std::vector<std::pair<int, int>> interview;
    for (int i = 0; i < n; i++) {
        int start, end;
        std::cin >> start >> end;
        interview.emplace_back(start, end);
    }
    std::sort(interview.begin(), interview.end(), [](std::pair<int, int> a, std::pair<int, int> b) {
        return a.second < b.second;
    });
    auto cmp = [](Interviewer a, Interviewer b) { return a.end > b.end; };
    std::priority_queue<Interviewer, std::vector<Interviewer>, decltype(cmp)> pq;
    if (!interview.empty()) {
        int count = 0;
        Interviewer in{1, interview.begin()->second};
        pq.push(in);
        for (int i = 1; i < interview.size(); i++) {
            bool flag = true;
            int start = interview[i].first;
            while (!pq.empty() && start >= pq.top().end) {
                if (pq.top().person == m) {
                    pq.pop();
                    count++;
                    continue;
                }
                int person = pq.top().person + 1;
                int end = interview[i].second;
                pq.pop();
                pq.emplace(person, end);
                flag = false;
                break;
            }
            if (flag) {
                pq.emplace(1, interview[i].second);
            }
        }
        std::cout << pq.size() + count << std::endl;
    }
    else {
        std::cout << "0" << std::endl;
    }

    return 0;
}
