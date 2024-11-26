#ifndef HEADER_SHELL_SORT_H
#define HEADER_SHELL_SORT_H
#include <functional>
#include <array>
template <typename RandomIt, typename Predicate = std::less<>>
void ShellInsert(RandomIt begin, int endPos, int dk, Predicate cmp = std::less<>{})
{
    for (int i = dk; i <= endPos; i++) {
        if (cmp(*(begin + i - dk), *(begin + i))) {
            continue;
        }
        auto value = *(begin + i);
        int j = i - dk;
   
        for (j; j >= 0 && cmp(value, *(begin + j)); j -= dk) {
            *(begin + j + dk) = *(begin + j);
        }
        *(begin + j + dk) = value;
    }
}

template <typename RandomIt, typename Predicate = std::less<>>
void ShellSort(RandomIt begin, RandomIt end, Predicate cmp = std::less<>{})
{
    std::array<int, 4> dk{41, 19, 5, 1};
    for (auto var : dk) {
        if (var <= end - 1 - begin)
            ShellInsert(begin, end - 1 - begin, var, cmp);
    }
}
#endif