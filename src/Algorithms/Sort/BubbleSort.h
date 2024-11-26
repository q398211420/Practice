#ifndef HEADER_BUBBLE_SORT_H
#define HEADER_BUBBLE_SORT_H
#include <functional>

template <typename RandomIt, typename Predicate = std::less<>>
void BubbleSort(RandomIt begin, RandomIt end, Predicate cmp = std::less<>{})
{
    for (auto it = end - 2; it >= begin; it--) {
        for (auto iit = begin; iit <= it; iit++) {
            if (cmp(*(iit + 1), *iit)) {
                std::swap(*(iit + 1), *iit);
            }
        }
    }
}

#endif