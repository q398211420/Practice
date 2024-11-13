// meyer单例
#include <iostream>

class Singleton {
  public:
    static Singleton& GetInstance()
    {
        static Singleton ins;
        return ins;
    }
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    ~Singleton()
    {
        std::cout << "destructor called" << std::endl;
    }
    void use() const
    {
        std::cout << "func is using" << std::endl;
    }

  private:
    Singleton()
    {
        std::cout << "constructor called" << std::endl;
    }
};

int main(int argc, char* argv[])
{
    Singleton& s1 = Singleton::GetInstance();
    Singleton& s2 = Singleton::GetInstance();
    s1.use();

    return 0;
}