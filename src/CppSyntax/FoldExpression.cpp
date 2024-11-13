/*
1、一元左折叠(unary left fold)(... op pack)一元左折叠(... op E) 展开之后变为((E1 op E2)op...) op EN
2、一元右折叠(unary right fold)(pack op...)一元右折叠(E op...) 展开之后变为 E1op(... op(EN - 1 op EN)) 
3、二元左折叠(binary left fold)(init op... op pack)二元左折叠(I op... op E)展开之后变为(((I op E1)op E2)op...) op EN
4、二元右折叠(binary right fold)(pack op... op init)二元右折叠(E op... op I)展开之后变为 E1 op(... op(EN−1 op(EN op I))) 

op代表运算符，在二元折叠中，两个运算符必须相同。
pack代表参数包
init代表初始值
省略号在包的左边就是左折叠 省略号在包的右边就是右折叠
*/
#include <iostream>
    template <typename... Args>
    auto Fun1(Args... args)
{
    return (... - args);
}

template <typename... Args>
auto Fun2(Args... args)
{
    return (args - ...);
}

template <typename... Args>
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
    std::cout << Fun1(1, 2, 3, 4, 5) << std::endl;  //-13
    std::cout << Fun2(1, 2, 3, 4, 5) << std::endl;  // 3
    std::cout << Fun3(1, 2, 3, 4, 5) << std::endl;  //-13
    std::cout << Fun4(1, 2, 3, 4, 5) << std::endl;  // 1
    return 0;
}

