/*
    信号量实验
    自己实现：
    1.整型信号量（自旋）
    2.记录型信号量(这里采用条件变量 + 互斥锁实现)
        记录型信号量是由于它采用了记录型的数据结构而得名的，除了需要一个用于代表资源数目的整型变量value外，还应增加一个进程链表指针list
        伪代码可描述如下：
        typedef struct {
            int value;
            struct process_control_block *list;
        }semaphore;
    3.AND型信号量（以后再实现）

    PS:
    1.条件变量的虚假唤醒：线程在没有满足条件的情况下被误唤醒,比如notify_one，本该唤醒一个，却唤醒了多个线程.
    2.互斥锁用于互斥访问，条件变量用于同步(确保按一定顺序)
    3.信号量和互斥锁区别：
        信号量，主要用于线程同步，其核心思想是控制对共享资源的访问许可，当资源可用时，允许线程继续操作；当资源被占用时，线程则阻塞直到资源变得可用。
        互斥锁，主要用于线程互斥，确保同一时刻只有一个线程能访问特定的资源，防止资源被多个线程同时访问。
        互斥锁是一种特殊的信号量。（S只能为0或1）
    4.多线程内存模型
    5.CPU的缓存一致性 （注意理解程序的执行从RAM->Cache->CPU，执行完后CPU->Cache->RAM，同一个变量在多线程下，可能在多个CPU缓存里都有副本）

条件变量参考资料:
1.https://zhuanlan.zhihu.com/p/599172163
2.https://blog.csdn.net/weixin_42445065/article/details/136657401
3.https://www.zhihu.com/question/541037047  
4.https://www.zhihu.com/question/541037047
*/
#include <iostream>
#include <thread>
#include <atomic>
#include <condition_variable>

//以下实现均未验证正确性
//整形信号量（自旋）
class Semaphore {
public:
    virtual void Wait() = 0;
    virtual void Signal() = 0;
};

class IntSemaphore : public Semaphore {
public:
    IntSemaphore(int count) : m_count(count) {}
    void Wait()
    {
        while (m_count.load(std::memory_order_acquire) <= 0)
            ;
        m_count.fetch_sub(1, std::memory_order_acquire);
    }
    void Signal()
    {
        m_count.fetch_add(1, std::memory_order_release);
    }

private:
    std::atomic<int> m_count;
};

class RecordSemaphore : public Semaphore {
public:
    RecordSemaphore(int count = 0) : m_count(count) {}
    void Wait()
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_condition.wait(lock, [this]() { return !!m_count; });
        m_count--;
    }
    void Signal()
    {
        {
            std::lock_guard lock(m_mutex);
            m_count++;
        }
        m_condition.notify_one();
    }

private:
    int m_count;
    std::condition_variable m_condition;
    std::mutex m_mutex;
};
