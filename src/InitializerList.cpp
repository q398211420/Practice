#include <initializer_list>
#include <cassert>
#include "mytool.h"
#include <array>
struct A
{
    A() = default;

    explicit A(std::initializer_list<int> lst);

    // const std::initializer_list<int>& 也行，因为{，，，} 是一个右值。
    // 但是没必要，因为initializer_list只保存数据起始指针和末尾指针，
    // 发生拷贝也只拷贝这两个指针，所有副本共享一个对象.
    A(A&&)                 = default;
    A(const A&)            = default;
    A& operator=(A&&)      = default;
    A& operator=(const A&) = default;
    ~A();
    std::array<int, 10> nums;
};

A::A(std::initializer_list<int> lst)
{
    assert(lst.size() < nums.size());
    int i = 0;
    for (auto e : lst) {
        nums[i] = e;
        i++;
    }
}

A::~A() {}
int main(int argc, const char** argv)
{
    //A a = {1, 2, 3, 5, 6, 7, 8, 9, 10}; explicit不允许隐式转换
    A a{1, 2, 3, 4, 5, 6};
    MyPrint(a.nums);

    return 0;
}