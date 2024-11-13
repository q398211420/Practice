#include<iostream>
#include<fstream>

int main(int argc, char* argv[])
{
/*
    所以存在这么一种情况，当 vim 以 UTF - 8 编码保存，然后在编译的时候加入 -finput - charset =GBK，则 GCC 会将                                
    UTF -8 编码值当成 GBK 来看待，然后将 GBK 编码值转换成 UTF -8 （可执行代码的编码格式，可通过 - fexec - charset =
    选项指定）。

    通过上面的测试代码做一个举例，编译：gcc - finput - charset = GBK - E 1.c -o 1.s

    1.s 文件如上所示，方框中的数据转换过程如下：

    1.“你好” 的 UTF -
    编码的八进制为：\344\275\240 （你）\345\245\275 （好），十六进制依次为0xE4、0xBD、0xA0、0xE5、0xA5、0xBD。

    2.GBK 编码为 2 个字节，将 UTF -
    当成 GBK 看待，所以依次为 0xE4BD、0xA0E5、0xA5BD。

    3.GBK 编码值 0xE4BD 的字符为 “浣”，这个字符所对应的 UTF -
    编码值为 0xE6B5A3（\346\265\243），这就是转换完成的结果，其余字符依次按这样的方式转换。
*/
    char w1[] = "中";
    std::cout << w1 << std::endl;

    /* 个人理解:
        只要编译器正确识别了字符（观感上为在vscode指定的编码下，正确的显示了想要的字符），那么不管源文件中的字符采取什么编码方式，在编译后生成的二进制文件中，字符的编码都不会变。
        此时在内存中的编码，只与GCC-fexec-charset选项设置的内码有关。

        比如汉字“中”，不管在源文件是采取utf-8编码下的“中”（三字节），还是GBK编码下的“中”（两字节），
        编译以后在内存里都是“中”（三字节 因为-fexec-charset默认为utf-8）。

    */

    return 0;
}   