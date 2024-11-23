#include <iostream>
#include <deque>
#include <vector>
#include <gtest/gtest.h>

std::vector<int> maxSlidingWindow(const std::vector<int>& nums, int k)
{
    std::deque<int> dq;       // 双端队列，存储下标
    std::vector<int> result;  // 存储结果

    for (int i = 0; i < nums.size(); i++) {
        // 移出队列中不在窗口范围内的元素
        if (!dq.empty() && dq.front() <= i - k) {
            dq.pop_front();
        }

        // 从队尾移除所有比当前元素小的元素
        while (!dq.empty() && nums[dq.back()] < nums[i]) {
            dq.pop_back();
        }

        // 将当前元素的下标加入队列
        dq.push_back(i);

        // 当窗口达到大小 k 时，记录当前窗口的最大值
        if (i >= k - 1) {
            result.push_back(nums[dq.front()]);
        }
    }
    return result;
}

TEST(Algorithms, MonotonicQueue)
{
    std::vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
    int k = 3;
    std::vector<int> result = maxSlidingWindow(nums, k);

    for (int max_val : result) {
        std::cout << max_val << " ";
    }
    std::cout  << std::endl;
}

/*
单调队列的定义
单调队列是一种数据结构，确保队列中的元素值按某种单调关系排列（例如递增或递减）。在不同情况下，选择适当的单调关系可以帮助我们在 
O(1) 时间内获取队列中最值。

常用的两种单调队列：

单调递增队列：从队头到队尾元素递增，适用于求解最小值。
单调递减队列：从队头到队尾元素递减，适用于求解最大值。
单调队列的实现思路
假设我们要求一个长度为 𝑘
k 的滑动窗口的最大值：

维护一个双端队列：队列中存储的是下标，不是值。这样可以通过下标判断队头元素是否已经滑出窗口。
保持队列单调递减：
当插入一个新的元素时，将双端队列中小于该元素的元素全部弹出，因为它们不可能再成为最大值。
插入后，如果队头元素对应的值超出了窗口范围，则将其从队头弹出。
取最大值：每次窗口滑动时，队头元素就是当前窗口的最大值。
*/