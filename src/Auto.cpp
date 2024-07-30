#include<iostream>

auto fun1(int &a)
{
    return a;
}

decltype(auto) fun2(int& a) //C++14写法 和fun3一样
{
    return a;
}

decltype(auto) fun3(int& a)  //C++14写法 和fun3一样
{
    return a;
}

int main(int argc, const char** argv) {
    int a = 5;
    int b = fun1(a);

    int& c = fun2(a);
    c = 7;
    std::cout << "a:" <<a<< std::endl;
    int& d = fun3(a);
    d = 10;
    std::cout << "a:" << a << std::endl;

    return 0;
}