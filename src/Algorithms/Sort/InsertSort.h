#ifndef HEADER_INSERT_SORT_H
#define HEADER_INSERT_SORT_H


#include <functional>
template <typename RandomIt, typename Predicate = std::less<>>
void InsertSort(RandomIt begin, RandomIt end, Predicate cmp = Predicate{})
{
    for (auto it = begin + 1; it < end; it++) {
        auto value = *it;
        auto iit = it - 1;
        if(!cmp(value,*iit)) continue;
        *it = *iit;
        iit--;
        while ((iit >= begin) && cmp(value, *iit)) {
            *(iit + 1) = *(iit);
            iit--;
        }
        *(iit + 1) = value;
    }
}
#endif