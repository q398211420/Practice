// 生成一个序列的所有子序列
#include <iostream>
#include <vector>
#include <gtest/gtest.h>

void DFS(const std::vector<int>& vec, int cur, std::vector<int>& out)
{
    if (cur == vec.size()) {
        if(out.size()==0){
            return;
        }
        if (out.size() == 1) {
            std::cout << *out.begin() << std::endl;
        }
        else {
            for (auto i = out.begin(); i < out.end() - 1; i++) {
                std::cout << *i << ",";
            }

            std::cout << *(out.end() - 1);
            std::cout << std::endl;
        }
        return;
    }
    out.push_back(vec[cur]);
    DFS(vec, cur + 1, out);
    out.pop_back();

    DFS(vec, cur + 1, out);
}

TEST(Algorithms, DFS_Combination)
{
    std::vector<int> vec{1, 2, 3};
    std::vector<int> out;
    DFS(vec, 0, out);
}
