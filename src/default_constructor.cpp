#include <iostream>
class MyClass {
public:
    MyClass();
    MyClass(int i)
    {
        this->i = i;
    }
    int i;
};

int main(int argc, const char** argv)
{
    MyClass t1(1);
    MyClass t2(t1);
    std::cout << "t2 i: " << t2.i<<std::endl;
    return 0;
}