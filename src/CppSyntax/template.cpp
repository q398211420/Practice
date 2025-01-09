// 华为typeinfer引发的联想练习
// 利用模板实现对复数类和其他类的不同处理
#include <algorithm>
#include <iostream>
#include <iterator>
#include <type_traits>
#include <complex>

struct MyComplex
{
    void Print()
    {
        std::cout << "I'm Complex" << std::endl;
    }
};

struct MyOthers
{
    void Print()
    {
        std::cout << "I'm Others" << std::endl;
    }
};

// 方法一，定义一个TypeInfer
// 缺点，需要手动写不同复数类型的代码

template <typename T>
struct TypeInfer
{
    using type = MyOthers;
};

template <>
struct TypeInfer<std::complex<int>>
{
    using type = MyComplex;
};

template <>
struct TypeInfer<std::complex<float>>
{
    using type = MyComplex;
};

template <typename T>
void Fun1()
{
    typename TypeInfer<T>::type x;
    x.Print();
}

// 方法2，利用type_traits

// 1
template <typename T>
struct IsComplex : public std::false_type
{
};

// 2
template <typename T>
struct IsComplex<std::complex<T>> : public std::true_type
{
};
// 这是两个不同的类，基类都不一样，不要错误理解成2是1的特化

template <typename T>
void Fun2(std::enable_if_t<IsComplex<T>::value>* = nullptr)
{
    MyComplex x;
    x.Print();
}

template <typename T>
void Fun2(std::enable_if_t<!IsComplex<T>::value>* = nullptr)
{
    MyOthers x;
    x.Print();
}

int main(int argc, char* argv[])
{
    Fun1<int>();
    Fun1<std::complex<int>>();
    Fun2<int>();
    Fun2<std::complex<int>>();
    return 0;
};