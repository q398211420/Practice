#include <iostream>
using namespace std;
struct A
{
    char  a;
    int   b;
    short c;
};

struct B
{
    short c;
    char  a;
    int   b;
};
int main()
{
    cout << sizeof(A) << endl;
    cout << sizeof(B) << endl;
    return 0;
}

// 以上面结构体A为例，第一个成员a是char类型，占用1个字节空间，偏移量为0，第二个成员b是int类型，占用4个字节空间，按照规则1，b的偏移量必须是int类型的整数倍，所以编译器会在a变量后面插入3字节缓冲区，保证此时b的偏移量(
//     4字节)
//         是b类型的整数倍(
//             当前恰好是1倍)，第3个成员c为short类型，此时c的偏移量正好是4
//     + 4 =
//     8个字节，已经是short类型的整数倍，故b与c之间不用填充缓冲字节。但这时，结构体A的大小为8 +
//     2 = 10个字节，按照规则2，结构体A大小必须是其最大成员类型int的整数倍，所以在10个字节的基础上再填充2个字节，保证最后结构体大小为12，以符合规则2.

