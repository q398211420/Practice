#ifndef HEADER_QUICK_SORT_H
#define HEADER_QUICK_SORT_H

#include <functional>

template <typename RandomIt, typename Predicate = std::less<>>
auto Partition(RandomIt begin, RandomIt end, Predicate cmp = std::less<>{}) -> int
{
    auto pivot = *begin;
    int low = 0;
    int high = end - begin;
    while (low < high) {
        while (!cmp(*(begin + high), pivot) && low < high) {
            high--;
        }
        *(begin + low) = *(begin + high);
        while (!cmp(pivot, *(begin + low)) && low < high) {
            low++;
        }
        *(begin + high) = *(begin + low);
    }

    *(begin + low) = pivot;

    return low;
}

template <typename RandomIt, typename Predicate = std::less<>>
void QuickSortImp(RandomIt begin, RandomIt end, Predicate cmp = std::less<>{})
{
    if (begin >= end) {
        return;
    }
    int pivot = Partition(begin, end, cmp);
    QuickSortImp(begin, begin + pivot - 1, cmp);
    QuickSortImp(begin + pivot + 1, end, cmp);
}

template <typename RandomIt, typename Predicate = std::less<>>
void QuickSort(RandomIt begin, RandomIt end, Predicate cmp = std::less<>{})
{
    QuickSortImp(begin, end - 1, cmp);
}

#endif
