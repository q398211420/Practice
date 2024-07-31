/*  1.递归展开获取参数包 */
// #include<iostream>
// template <typename T>
// void ShowList(T value)
// {
//     std::cout << value <<std::endl;

// }

// void ShowList()
// {
//     std::cout << std::endl;
// }

// template<typename T, typename... Args>
// void ShowList(T value, Args... args)
// {
//     std::cout << value << " ";
//     ShowList(args...);
// }

// int main(int argc, const char** argv)
// {
//     ShowList();
//     ShowList('x');
//     ShowList('x', 'y');
//     ShowList('x', 1);

//     return 0;
// }

/* 2. 利用初始化列表展开参数包和使用逗号表达式返回一致的类型(C++11即可) */
// #include <iostream>

// template <class... Args> void ShowList(Args... args)
// {
//     int dummy[] = {(std::cout << args << " ", 0)...};
//     std::cout << "|dummy: ";
//     for(auto e : dummy){
//         std::cout << e << " ";
//     }
//     std::cout << std::endl;
// }

// int main()
// {
//     ShowList(1);
//     ShowList(1, 'a');
//     ShowList(1, 'a', "Hello");
//     ShowList(1, 'a', "Hello", 3.14);
//     return 0;
// }
// 在上述代码中，我们使用逗号表达式在展开过程中依次执行(
// std::cout << args << " ",0)。
// 这里使用了一个技巧，将逗号表达式作为初始化列表的一部分，并将它们赋值给一个名为
// dummy 的整型数组。因为逗号表达式返回最后一个表达式的结果，这里我们使用了
// 0 作为最后一个表达式，来确保整型数组中的元素都是 0。
// 通过这种方式，逗号表达式会依次执行参数包中的每个表达式，并输出到标准输出流中。

// 3.C++17的折叠表达式

// 4. Lambda捕获
//  Lambda 捕获
int main(int argc, const char** argv) {
    return 0;
}
