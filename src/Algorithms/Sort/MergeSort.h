#ifndef HEADER_MERGE_SORT_H
#define HEADER_MERGE_SORT_H
#include <functional>
#include <iterator>

template <typename RandomIt, typename Predicate = std::less<>>
void Merge(RandomIt begin, size_t mid, size_t high, Predicate cmp = std::less<>{})
{
    size_t i{mid + 1};
    size_t low = 0;
    std::vector<typename std::iterator_traits<RandomIt>::value_type> vec;
    vec.resize(high + 1);
    size_t k{0};
    while (low <= mid && i <= high) {
        if (cmp(*(begin + low), *(begin + i))) {
            vec[k] = *(begin + low);
            low++;
        }
        else {
            vec[k] = *(begin + i);
            i++;
        }
        k++;
    }
    if (low <= mid) {
        std::copy(begin + low, begin + mid + 1, vec.begin() + k);
        k += (mid + 1 - low);
    }
    std::copy(vec.begin(), vec.begin() + k, begin);
}

template <typename RandomIt, typename Predicate = std::less<>>
void MergeSort(RandomIt begin, RandomIt end, Predicate cmp = std::less{})
{
    if (begin >= (end - 1)) {
        return;
    }
    size_t mid = (end - 1 - begin) / 2;
    MergeSort(begin, begin + mid + 1, cmp);
    MergeSort(begin + mid + 1, end, cmp);
    Merge(begin, mid, end - 1 - begin, cmp);
}
#endif