#include<iostream>

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

template<typename T>
void Fun(T&& t)
{
    Fun1(std::forward<T>(t));
}

int main(int argc, char* argv[])
{
    int a = 5;
    Fun(std::move(a));
    std::cout << "a:" << a << std::endl; //通过右值引用 ，修改了a的值

    int&& b = 3;
    int&  c = b;
    c       = 99;
    std::cout << "b:" << b<<std::endl;
    std::cout << "b address:" << &b << std::endl; //右值引用本身是左值，可取地址
    return 0;
}