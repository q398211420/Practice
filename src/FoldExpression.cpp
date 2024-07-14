#include<iostream>
template<typename... Args>
auto Fun1(Args... args)
{
    return (... - args);
}

template<typename... Args>
auto Fun2(Args... args)
{
    return (args - ...);
}

template<typename... Args>
auto Fun3(Args... args)
{
    return (2 - ... - args);
}

template <typename... Args>
auto Fun4(Args... args)
{
    return (args - ... - 2);
}

int main(int argc, const char** argv)
{
    std::cout << Fun1(1, 2, 3, 4, 5) << std::endl;//-13
    std::cout << Fun2(1, 2, 3, 4, 5) << std::endl;//3
    std::cout << Fun3(1, 2, 3, 4, 5) << std::endl;//-13
    std::cout << Fun4(1, 2, 3, 4, 5) << std::endl;//1
    return 0;
}