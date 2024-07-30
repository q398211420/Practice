#include <concepts>
#include <iostream>
#include<vector>
#include <array>

template <typename T>
concept Printable = requires(const T& a) {
    std::cout << *std::begin(a);
    requires std::ranges::forward_range<T>;
};

void MyPrint(const Printable auto& a)
{
    for (auto e : a) {
        std::cout << e << " ";
    }
    std::cout << std::endl;
}
