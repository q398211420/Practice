#include "mytool.h"

template <typename T>
concept C1 = requires(T&& a) { std::cout << *std::begin(a); };

void fun(C1 auto&& a)
{
    for (const auto& e : a) {
        std::cout << e << " ";
    }
    std::cout << std::endl;
}

template <typename T, typename U>
auto fun2(T&& a, U&& b) 
requires requires
{
    a + b;
}
{
    return a + b;
}

int main(int argc, char* argv[])
{
    int                   a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<float>    v{1, 2, 3, 4};
    std::array<double, 5> r{-1, -2, -3, -4, -5};
    fun(a);
    fun(v);
    fun(r);

    //fun2(2, v); 编译错误
    fun2(2, 3.5);

    return 0;
}