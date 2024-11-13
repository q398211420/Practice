#include "mytool.h"
#include <type_traits>

// 模板的非类型模板参数(nontype template parameters),
// 可以使用整型类型(integral type),
// 指针(pointer)
// 引用(reference);

// 绑定非类型整数形参的实参必须是常量表达式(constant expression, constexpr);

// 不能把普通的局部对象或者动态对象 绑定
// 指针或引用的非类型形参,可以使用全局类型进行绑定;

template <typename T>
T addT(T value,
       typename std::enable_if<std::is_integral<T>::value, T>::type* = nullptr)
{
    return value + 10;
}

template <typename T>
T addT(T value,
       typename std::enable_if<std::is_floating_point<T>::value, T>::type* =
           nullptr)
{
    return value + 5;
}

int main()
{
    int    d = 10;
    double f = 20;
    d        = addT(d);
    f        = addT(f);
    std::cout << d << std::endl;
    std::cout << f << std::endl;
    return 0;
}
