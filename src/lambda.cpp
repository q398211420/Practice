#include <iostream>
#include <memory>
#include <vector>
class L1 {
public:
    void Print() const noexcept
    {
        std::cout << a << std::endl;
    }
    L1(int aa)
    {
        a = aa;
    };
    L1()
    {
        a = 20;
    };
    void Test() noexcept
    {
        auto g = [this]() {
            a = 88;
        };  //值捕获this指针，由于没有修改this指针，不需要加mutable
        auto f = [*this]() mutable {
            a = 99;
        };  // 值捕获*this，拷贝整个*this对象。修改对象需要加mutable。由于是值捕获，所以不会影响原对象
        g();
        f();
    }
    // 在使用 capture 子句时，建议你记住以下几点（尤其是使用采取多线程的 Lambda 时）：

    // 引用捕获可用于修改外部变量，而值捕获却不能实现此操作。 （mutable 允许修改副本，而不能修改原始项。）

    // 引用捕获会反映外部变量的更新，而值捕获不会。

    // 引用捕获引入生存期依赖项，而值捕获却没有生存期依赖项。 当 Lambda 以异步方式运行时，这一点尤其重要。

    // 如果在异步 Lambda 中通过引用捕获局部变量，该局部变量将很容易在 Lambda 运行时消失。 代码可能会导致在运行时发生访问冲突。

private:
    int a{10};
};

//C++14lambda特性，初始化捕获和泛型参数
void C14()
{
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    // 泛型 Lambda 表达式，用于打印容器中的元素
    auto printElement = [](const auto& elem) { std::cout << elem << " "; };
    printElement(v[2]);
    std::cout << std::endl;

    //初始化捕获最大的应用是下面的移动捕获，确保资源在lambda生命周期内是独占的
    //创建一个指向vector<int>的unique_ptr，并将其所有权传递给lambda表达式。
    auto pNums = std::make_unique<std::vector<int>>(10);
    std::cout << pNums.get() << std::endl;
    auto a = [ptr = move(pNums)]() {};
    std::cout << pNums.get() << std::endl;
}

void Closure()
{
    //重复理解lambda函数的闭包，当函数 值捕获 到了外部变量，函数就和变量绑定到了一起。
    int  x = 1;
    int  y = 1;
    auto f = [=]() mutable throw()->int
    {
        int n = x + y; //刚开的x和y是捕获外部的，后面每次调用，都是内部绑定的x和y
        x     = y;
        y     = n;
        return n;
    };
    f();
    f();
    int n = f();
    std::cout << "*******************" << std::endl;
    std::cout << "n:" << n << std::endl;//5
}
int main(int argc, const char** argv)
{
    L1 a;
    a.Test();
    a.Print();

    std::cout << "*******************" << std::endl;
    C14();

    std::cout << "*******************" << std::endl;
    int m = 0;
    int n = 0;
    // [m, &n](int a) mutable { m = ++n + a; }(4);值捕获的需要加mutable
    [&m, &n](int a) { m = ++n + a; }(4);  //不用加mutable
    std::cout << m << std::endl << n << std::endl;
    // Lambda 表达式只能捕获具有自动存储持续时间的变量。
    // 但是,可以在 Lambda 表达式体中使用具有静态持续存储时间的变量

    return 0;
}