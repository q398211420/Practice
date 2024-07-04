// 华为typeinfer对复数和实数的随机矩阵特殊处理引发的联想练习
// 实现一份代码，对三类对象统一处理(normal,A,B)
#include <algorithm>
#include <iostream>
#include <iterator>
// #define S
#define B
#ifdef S
struct Normal
{
    std::string name;
};

struct Other
{
    std::string Aname;
};

struct Derive : public Normal
{
};

template <typename T>
struct ObjType
{
    using type = T;
};

template <>
struct ObjType<Other>
{
    using type = Other*;
};
// 适用场景1
// 对Normal类取类型，得到的是类本身，对Other类取类型，得到的是Other类指针。
#endif

#ifdef B
struct Normal
{
    std::string name{"name"};
};

struct Other
{
    std::string Oname{"Oname"};
};

template <typename T>
struct TypeInfer
{
};

template <>
struct TypeInfer<int>
{
    using obj = Normal;
};

template <>
struct TypeInfer<float>
{
    using obj = Other;
};

template <typename T>
void Fun()
{
    typename TypeInfer<T>::obj x;
    std::cout << typeid(x).name() << std::endl;
}

// 适用场景2 推断模板类型参数
#endif

int main(int argc, char* argv[])
{
#ifdef S
    ObjType<Normal>::type a;
    ObjType<Other>::type  b;

    std::cout << typeid(a).name() << std::endl;
    std::cout << typeid(b).name() << std::endl;
#endif

#ifdef B
    Normal a;
    Other b;
    Fun<int>();
    Fun<float>();
#endif

    // int                        n[5] = {1, 2, 3, 4, 5};
    // std::ostream_iterator<int> o(std::cout, ",");
    // std::transform(std::begin(n), std::end(n), o, [](int x) { return ++x; });

    //
    // Derive d;
    // Normal *dd = &d;
    // Normal &ddd = d;
    // std::cout << typeid(d).name() << std::endl;
    // std::cout << typeid(dd).name() << std::endl;
    // std::cout << typeid(ddd).name() << std::endl;
};