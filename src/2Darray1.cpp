/*
以下针对二维数组
a;   // 代表数组首行地址，一般用a[0][0]的地址表示
&a;  // 代表整个数组的地址，一般用a[0][0]地址表示
a[i];代表了第i行起始元素的地址
&a[i];代表了第i行的地址，一般用a[i][0] 的地址表示 

(a[i][j] 可看成{{j个元素},{j个元素},{j个元素}}) 每个{j个元素}，都是一个正规的数组，这样来理解a[i]，和&a[i])

a[i] +j;  //代表了第i行第j个元素地址,a[i]就是j==0的情况 
a[i][j];          //代表了第i行第j个元素
&a[i][j];        // 代表了第i行第j个元素的地址 
*a; //代表数组a首元素地址也就是a[0]或者&a[0][0]
*(a + i);         // 代表了第i行首元素的地址,*a是i=0的情况
*(a + i) + j;     // 代表了第i行j个元素的地址
**a;              // 代表a的首元素的值也就是a[0][0]
*(*(a + i) + j);  // 代表了第i行第j个元素

a + i == &a[i] == a[i] == &a[i][0] ==*(a +i)
虽然它们的值相等，但他们的意义不全相等.
a+i和&a[i]意义相同都表示行地址，
a[i],&a[i][0],*(a+i)意思相同，都表示该行起始元素地址。
*/

#include <stdio.h>

using namespace std;

int main(int argc, char* argv[])
{
    int a[3][4] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    printf("%d\n", a);
    printf("a + 1 \t &a + 1 \t a[0] + 1 \t &a[0] + 1\n");
    printf("%d \t %d \t %d \t %d", a + 1, &a + 1, a[0] + 1, &a[0] + 1);
    printf("\n");
    // (1)第一行输出,表示数组的起始地址
    // (2)由于a表示的数组首行地址，因此a+1中的1其实代表了数组中的一行元素的大小，也就是4*4个字节(一行4个int元素，每个int占4个字节)，等于16
    // (3)由于&a表示的是一个数组，因此&a+1中的1其实代表了整个数组的大小，也就是3*4*4个字节3*4为元素个数最后的4是int表示的4个字节大小)，等于48
    // (4)由于a[0]代表了第0行第0个元素的地址，因此a[0]+1中的1其实代表了一个元素的大小，也就是1*4，等于4
    // (5)由于&a[0]代表了第0行的地址，因此&a[0]+1中的1其实代表了一行元素的大小，也就是4*4个字节(同(2))，等于16

    printf("%d\n", *(*(a+1)+5));//10

    return 0;
}
