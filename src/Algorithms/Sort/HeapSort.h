#ifndef HEADER_HEAP_SORT_H
#define HEADER_HEAP_SORT_H
#include <functional>

template <typename RandomIt, typename Predicate = std::less<>>
void HeapAdjust(int pos, RandomIt begin, RandomIt end, Predicate cmp = std::less<>{})
{
    int parent = pos;
    auto value = *(begin+pos-1);
    for (int i = 2 * pos; (begin + i - 1) <= end; i *= 2) {
        int offset = i - 1;
        if ((begin + offset + 1 <= end) && cmp(*(begin + offset), *(begin + offset + 1))) {
            i++;
            offset++;
        }

        if (cmp(*(begin + offset), value)) {
            break;
        }

        *(begin + parent - 1) = *(begin + offset);
        parent = i;
    }

    *(begin + parent - 1) = value;
}

template <typename RandomIt, typename Predicate = std::less<>>
void HeapSort(RandomIt begin, RandomIt end, Predicate cmp = std::less<>{})
{
    int pos = (end - begin) / 2;
    int posOffset = pos - 1;
    for (int i = posOffset; i >= 0; i--) {
        HeapAdjust(i+1, begin, end - 1, cmp);
    }
    for (auto it = end - 1; it > begin; it--) {
        std::swap(*begin, *(it));
        HeapAdjust(1, begin, it-1, cmp);
     
    }
}
#endif