// 数据结构P274
#include <iostream>
#include <random>
class Item {
public:
    int key;
};

class SqList {
public:
    static constexpr size_t length{
        101};  // 使用constexpr修饰的静态变量必须在类内初始化
    Item r[length];
};

class imp {
public:
    static void QuickSort(SqList& L);

private:
    static int  Partition(SqList& L, int low, int high);
    static void QSort(SqList& L, int low, int high);
};

int imp::Partition(SqList& L, int low, int high)
{
    L.r[0]       = L.r[low];
    int pivotkey = L.r[low].key;
    while (low < high) {
        while (low < high && L.r[high].key >= pivotkey)
            high--;
        L.r[low] = L.r[high];
        while (low < high && L.r[low].key <= pivotkey)
            low++;
        L.r[high] = L.r[low];
    }
    L.r[low] = L.r[0];
    return low;
}

void imp::QSort(SqList& L, int low, int high)
{
    if (low >= high)
        return;
    int pivotloc = Partition(L, low, high);
    QSort(L, low, pivotloc - 1);
    QSort(L, pivotloc + 1, high);
}

void imp::QuickSort(SqList& L)
{
    QSort(L, 1, L.length);
}

int main(int argc, char* argv[])
{
    SqList                     L;
    std::default_random_engine r;
    r.seed(time(nullptr));
    std::cout << "before quicksort:" << std::endl;
    for (size_t i = 0; i < L.length; i++) {
        L.r[i].key = r() % 1000;
        std::cout << L.r[i].key << " ";
    }
    std::cout  << std::endl;
    std::cout << "after quicksort:" << std::endl;
    imp::QuickSort(L);
    for (auto e : L.r) {
        std::cout << e.key << " ";
    }
    std::cout << std::endl;
    return 0;
}