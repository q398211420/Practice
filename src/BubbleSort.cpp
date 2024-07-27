#include <iostream>
#include "mytool.h"
void BubbleSort(int a[], size_t len)
{
    for (size_t i = len - 1; i > 1; i--) {
        for (size_t j = 0; j < i; j++) {
            if (a[j] > a[j+1]) {
                std::swap(a[j+1], a[j]);
            }
        }
    }
}

int main(int argc, char* argv[])
{
    srand(time(nullptr));
    int a[10];
    for (size_t i = 0; i < 10; i++) {
        int num = rand() % 100;
        a[i]    = num;
    }
    std::cout << "before:";
    MyPrint(a);
    BubbleSort(a, 10);
    std::cout << " after:";
    MyPrint(a);
   
    return 0;
}