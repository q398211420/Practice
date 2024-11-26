#ifndef HEADER_SELECT_SORT_H
#define HEADER_SELECT_SORT_H
#include <functional>
#include <algorithm>

template <typename RandomIt, typename Predicate = std::less<>>
void SelectSort(RandomIt begin, RandomIt end, Predicate cmp = std::less<>{})
{
    for (auto it = begin; it != end - 1; it++) {
        auto min = std::min_element(it, end, cmp);
        if (min != it)
            std::swap(*it, *min);
    }
}
#endif