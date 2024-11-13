// 拿二维数组举例，彻底搞懂a,&a,&a[0],&a[0][0],a+1....的区别
#include <iostream>

/*
    1 2 3 4
    5 6 7 8         = A
    9 10 11 12
*/

int main(int argc, const char** argv)
{
    int a[3][4] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    /*C++中，实际上是当成 int a[3]来存的，{{1,2,3,4},{5,6,7,8},{9,10,11,12}}
    a[3]的每个元素是一个长度为4的一维数组。
    因此，C++的二维数组一定是行优先

    */
    std::cout << "a:" << a << std::endl;
    std::cout << "*(*(a+1)+2):" << *(*(a + 1) + 2) << std::endl;
    /* 
    a+1得到的是指向一个一维数组[4]的指针。
    *(a+1)得到这个一维数组首元素地址
    */

    std::cout << " *(a[1]+2)" << *(a[1]+2) << std::endl; //a[1]直接得到一个一维数组名，a[1]+2，得到1行2列元素的地址。

    std::cout << "sizeof(a):" << sizeof(a) << std::endl;
    std::cout << "sizeof(int):" << sizeof(int) << std::endl;
    std::cout << "&a:" << &a << std::endl; //得到指向整个数组的指针 int *p [12]
    std::cout << "&a + 1:" << &a + 1 << std::endl;// 地址前进12个int
    

    return 0;
}