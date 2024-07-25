#include <cstring>
#include <iostream>

// 考察除法和取模
void fun1()
{
    signed int a = -4;
    signed int b = -3;
    int        c = 2;
    std::cout << a / c + a % b << std::endl;
    std::cout << c / a + b % c << std::endl;
}
//////////////////////////////////////////////////////////////////////////////////////////

// 考察指针
void fun2()
{
    int  arr[] = {1, 2, 3, 4, 5};
    int* p     = &arr[3];
    int* q     = arr;
    *(p--) += 2;
    *(q++) = *(q++) - 1;

    std::cout << *p << std::endl;
    std::cout << *(q - 1) << std::endl;
}
//////////////////////////////////////////////////////////////////////////////////////////

// 移位
void fun3()
{
    int x = 137, n = 3;
    std::cout << (x << n) << std::endl;
}
//////////////////////////////////////////////////////////////////////////////////////////

/*逻辑运算
与1相与 : 保持位值不变
与0相与 : 将位值清零
与1相或 : 将位值设为1
与0相或: 保持位值不变
*/
void fun4()
{
    int b;
    for (int i = 0; i < 20; i++) {
        if ((i & 0xf) < 3) {
            b = i;
            std::cout << ++b << " ";
        }
    }
    std::cout << std::endl;
}
//////////////////////////////////////////////////////////////////////////////////////////

void fun5()
{
    // 若int input[3][2]={{1,2},{4,5},{7,8}};
    // 且sum函数调用为int total = sum(input, 3)
    // 则sum函数的原型为
    // 1.int sum(int *a[],  int len)
    // 2.int sum(int (*a)[],  int len)
    // 3.int sum(int *a[2],  int len)
    // 4.int sum(int (*a)[2],  int len)
}
//////////////////////////////////////////////////////////////////////////////////////////

// 下面函数返回值为
int fun6()
{
    int  a    = 0;
    char s1[] = "hello,Mary.";
    char s2[] = "hello,Nancy.";
    a         = std::strcmp(s1, s2);
    return a;
}

// C++ 中运算符的运算规则是，优先级高的运算符先执行，优先级低的运算符后执行，
// 同一优先级的运算符按照从左到右的顺序进行。
// C++中大部分运算符都是从左向右执行的，只有单目运算符、赋值运算符它们是从右向左执行的。
//////////////////////////////////////////////////////////////////////////////////////////

// 在32位系统中的结果为:
void fun8()
{
    int  a[3]   = {1, 2, 3};
    int* p      = a;
    char s1[]   = "hello,world!";
    char s2[20] = "hello,world!";
    std::cout << sizeof(p) << sizeof(s1) << sizeof(s2) << std::endl;
}
//////////////////////////////////////////////////////////////////////////////////////////

// fun9()
namespace {
    class A {
    public:
        A()
        {
            std::cout << "A";
        }
        ~A()
        {
            std::cout << "~A";
        }
    };

    class B {
    public:
        B()
        {
            std::cout << "B";
        }
        ~B()
        {
            std::cout << "~B";
        }
    };

    class C : public A, public B {
    public:
        C()
        {
            std::cout << "C";
        }
        ~C()
        {
            std::cout << "~C";
        }
    };

    // void main()
    // {
    //     C x;
    // }
    // 此时程序的输出是？
}  // namespace
void fun9()
{
    C x;
}
//////////////////////////////////////////////////////////////////////////////////////////

void fun10()
{
    int A[2][3] = {1, 2, 3, 4, 5, 6};
    std::cout << *((*A + 1) + 1) << std::endl;
    std::cout << *(*(A + 1) + 1) << std::endl;
}
//////////////////////////////////////////////////////////////////////////////////////////

void fun11()
{
    int              b[3] = {1, 3, 5};
    const int*       a1   = b;
    int const*       a2   = b;
    int* const       a3   = b;
    const int* const a4   = b;
}
//////////////////////////////////////////////////////////////////////////////////////////

void fun12()
{
#define CALCULATE(x, y, z) x + y* z
    int                           a;
    a = CALCULATE(2, 3, 4) * CALCULATE(2, 3, 4);
    std::cout << a << std::endl;
}
//////////////////////////////////////////////////////////////////////////////////////////

// fun13()
namespace {
    class Base {
    public:
        virtual int fcn()
        {
            return 0;
        }
    };
    class D1 : public Base {
    public:
        int fcn(int x = 1)
        {
            return x;
        }
        virtual void f2() {}
    };
    class D2 : private D1 {
    public:
        int fcn(int) {}
        int fcn()
        {
            return 2;
        }
        void f2() {}
    };

}  // namespace
void fun13()
{
    Base  b, d2;
    D1    d1;
    Base *bptr = &b, *d1ptr = &d1;
    D2*   d2ptr = (D2*)&d2;
    std::cout << bptr->fcn() << " " << d1ptr->fcn() << " " << d2ptr->fcn()
              << std::endl;
}
//////////////////////////////////////////////////////////////////////////////////////////

namespace {
    class AA {
    public:
        virtual int fcn(int)
        {
            return 0;
        }
    };
    class BB : public AA {
    public:
        int fcn(int x = 1)
        {
            return x;
        }
        virtual void f2() {}
    };
    class CC : public BB {
    public:
        int fcn(int x = 9)
        {
            return x;
        }
        virtual void f2() {}
    };
}  // namespace
void fun14()
{
    BB  b;
    AA* pa = &b;
    CC  c;
    BB* pb = &c;
    std::cout << pa->fcn(5) << std::endl;  // 输出5，调用的BB

    // std::cout<< pa->fcn()<< std::endl;
    // 编译错误。编译时是按照实际指针类型（AA*）去查找的函数，此时AA类必须传一个参数。函数运行的时候，才是动态绑定的方法。

    std::cout << pb->fcn() << std::endl;
    // 输出1，调用的CC中的函数，但是默认形参值是静态绑定的，来自于BB*
}
//////////////////////////////////////////////////////////////////////////////////////////

static int y = 0;
int        m = 0, n = 0, k = 0;
int        fun15(int* pt, int& qt, int tt)
{
    static int a   = 0;
    int        sum = 0;
    while (tt > 0) {
        sum = sum + *pt + qt + a;
        (*pt)++;
        qt++;
        a++;
        y++;
        tt--;
    }
    return sum;
}
// int main(int argc, const char** argv)
// {
//     extern int m, n;
//     int        k   = 2;
//     int        sum = fun15(&m, n, k);
//     std::cout << sum << " " << n << " " << y << std::endl;
//     return 0;
// }
//////////////////////////////////////////////////////////////////////////////////////////

void fun16()
{
    int x = 5;
    int y = ~x;
    int z = -6;
    int q = 0xfffffffa;
    printf("%d, %x,%x,%x,%d", y, y, x, z, q);
}
/////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, const char** argv)
{
    return 0;
}
