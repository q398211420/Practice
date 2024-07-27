#include <concepts>
#include <iostream>

template <typename T>
concept C1 = requires(const T& a) {
    std::cout << *std::begin(a);
    requires std::ranges::forward_range<T>;
};

void MyPrint(const C1 auto& a)
{
    for (auto e : a) {
        std::cout << e << " ";
    }
    std::cout << std::endl;
}

