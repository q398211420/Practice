//数字字符串互相转换
#include "mytool.h"
#include <sstream>

int main(int argc, const char**argv)
{
    
    int a = 12345;
    std::ostringstream o1;
    o1 << a;
    std::string s1 = o1.str();
    std::cout << s1 << std::endl;

    std::string s2 = "54321";
    std::istringstream i1(s2);
    int                b;
    i1 >> b;
    std::cout << b << std::endl;

    char format[64];
    sprintf(format, "%d", 12345);
    std::cout << format << std::endl;

    b = std::stoi("1234");
    std::cout << b << std::endl;


    return 0;
}