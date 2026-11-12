// meyer单例
#include <iostream>
#include <gtest/gtest.h>

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

TEST(DesignPatterns, Singleton)
{
    Singleton& s1 = Singleton::GetInstance();
    Singleton& s2 = Singleton::GetInstance();
    s1.use();
}
