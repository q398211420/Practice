#include <iostream>
#include <type_traits>

// 为什么存在第二种形式
/*
Overload 2 is for the case labeled "B. Should forward an rvalue as an rvalue"
in N2951. In a nutshell this case enables:std::forward<T>(u.get());where you are
unsure if u.get() returns an lvalue or rvalue,but either way if T is not an
lvalue reference type,you want to move the returned value.But you don't use
std::move because if T is an lvalue reference type, you don' t wantto move from
the return.
*/
// 可能有这种矫揉造作的情景
// 没有第二种重载形式的话，就没法forward<T>(std::move(t))
// 虽然挺多余，但是确保了右值应该被转发为右值

void Fun1(int&& t)
{
    t = 1;
    std::cout << "right value:" << t << std::endl;
}
void Fun1(int& t)
{
    t = 7;
    std::cout << "left value:" << t << std::endl;
}

template <typename T>
void Fun(T&& t)
{
    Fun1(std::forward<T>(t));
}

template <typename _Tp>
constexpr _Tp&&
Myforward(typename std::remove_reference<_Tp>::type& __t) noexcept
{
    return static_cast<_Tp&&>(__t);
}

template <typename _Tp>
constexpr _Tp&&
Myforward(typename std::remove_reference<_Tp>::type&& __t) noexcept
{
    static_assert(!std::is_lvalue_reference<_Tp>::value,
                  "template argument"
                  " substituting _Tp is an lvalue reference type");
    return static_cast<_Tp&&>(__t);
}

int main(int argc, char* argv[])
{
    int a = 5;
    Fun(std::move(a));
    std::cout << "a:" << a << std::endl;  // 通过右值引用 ，修改了a的值

    int&& b = 3;
    int&  c = b;
    c       = 99;
    std::cout << "b:" << b << std::endl;
    std::cout << "b address:" << &b
              << std::endl;  // 右值引用本身是左值，可取地址
    return 0;
}
