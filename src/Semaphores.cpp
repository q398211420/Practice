/*
    信号量实验
    自己实现：
    1.最简单的整型信号量（自旋锁）
    2.记录型信号量
    3.AND型信号量

    PS:
    1.条件变量的虚假唤醒：线程在没有满足条件的情况下被误唤醒,比如notify_one，本该唤醒一个，却唤醒了多个线程.
    2.互斥锁用于互斥访问，条件变量用于同步(确保按一定顺序)
    3.信号量和互斥锁区别：
        信号量，主要用于线程同步，其核心思想是控制对共享资源的访问许可，当资源可用时，允许线程继续操作；当资源被占用时，线程则阻塞直到资源变得可用。
        互斥锁，主要用于线程互斥，确保同一时刻只有一个线程能访问特定的资源，防止资源被多个线程同时访问。
        互斥锁是一种特殊的信号量。（S只能为0或1）
    4.多线程内存模型
    5.CPU的缓存一致性 （注意理解程序的执行从RAM->Cache->CPU，执行完后CPU->Cache->RAM，同一个变量在多线程下，可能在多个CPU缓存里都有副本）

*/
#include <iostream>
#include <thread>
#include <atomic>
#include <condition_variable>
std::atomic<int> s(3);
std::condition_variable cvs;

//整形信号量
namespace Int {
    void Wait(std::atomic<int>& s)
    {
        while (s <= 0) {};
        s--;
    }

    void Signal(std::atomic<int>& s)
    {
        s++;
    }

    void Runner(int i)
    {
        Wait(s);
        std::cout << "Thread " << i << " is running" << std::endl;
        sleep(i + 2);
        std::cout << "Thread " << i << " unlock" << std::endl;
        Signal(s);
    }
    void Test()
    {
        std::thread t1{Runner, 1};
        std::thread t2{Runner, 2};
        std::thread t3{Runner, 3};
        std::thread t4{Runner, 4};
        std::thread t5{Runner, 5};
        std::thread t6{Runner, 6};
        std::thread t7{Runner, 7};
        t1.join();
        t2.join();
        t3.join();
        t4.join();
        t5.join();
        t6.join();
        t7.join();
    }

}  // namespace Int

//记录型信号量(C++11条件变量+互斥信号量)
namespace Record {
    void Wait(std::atomic<int>& s)
    {
        s--;
    }
}  // namespace Record
int main(int argc, const char** argv)
{
    Int::Test();
    return 0;
}
