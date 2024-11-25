#ifndef HEADER_BINSERT_SORT_H
#define HEADER_BINSERT_SORT_H

#include <functional>

template <typename RandomIt, typename Predicate = std::less<>>
void BInsertSort(RandomIt begin, RandomIt end, Predicate cmp = Predicate{})
{
    for (auto it = begin + 1; it < end; it++) {
        if (cmp(*(it - 1), *it)) {
            continue;
        }
        auto value = *it;
        int low = 0;
        int high = it - begin - 1;
        while (low <= high) {
            auto mid = (low + high) / 2;
            if(cmp(*(begin+mid),value)){
                low = mid+1;
            }
            else
            {
                high = mid - 1;
            }
        }
        for (auto iit = it - 1; iit >= (begin + high + 1);iit--){
            *(iit + 1) = *(iit);
        }
        *(begin + high + 1) = value;
    }
}

#endif