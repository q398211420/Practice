/*
信号量和锁的关系:
虽然锁和信号量都是同步机制，但它们在功能和应用场景上有所不同。

相同点：
线程同步工具：它们都用于解决并发环境中线程之间的同步问题，防止多个线程同时访问共享资源时发生数据竞争。
阻塞线程：当资源不可用时，都会阻塞试图访问该资源的线程，直到资源可用为止。
互斥操作：在特定情况下，二元信号量可以实现类似互斥锁的功能，即确保同一时刻只能有一个线程访问资源。
不同点：
控制粒度：

锁：专门用于互斥访问，确保只有一个线程能进入临界区，不能控制资源的访问数量。
信号量：可以控制多个线程同时访问资源，它不仅用于互斥，还可以用于协调多个线程对资源的并发访问。
复杂性：

锁：实现简单，通常只有一个计数器，用于管理资源的占用情况。
信号量：相对复杂一些，特别是计数信号量，它允许多个线程同时访问资源，需要更复杂的计数器管理。
资源计数：

锁：没有计数功能，只能用于单线程互斥。
信号量：通过计数器表示资源的数量，可以允许多个线程同时访问有限数量的资源。
用途：

锁：用于保护临界区，防止多个线程同时访问导致数据不一致。
信号量：不仅可以实现互斥访问，还可以用于实现复杂的线程协调，限制多个线程对资源的并发访问。
*/

#include <atomic>

/// @brief C++原子类型实现自旋锁
class SpinLock {
public:
    void Lock()
    {
        while (flag.exchange(true, std::memory_order_acquire))  // (1)
            ;
    }
    void UnLock()
    {
        flag.store(false, std::memory_order_release);  // (2)
    }

private:
    std::atomic<bool> flag{false};
};

SpinLock mu;
void thread1()
{
    // some operations
    mu.Lock();  // (3)
}

void thread2()
{
    mu.Lock();  // (4)
}
int main(int argc, const char** argv) {
    return 0;
}
/*
(1) 处加锁用到的 exchange 是一种 read - modify- write 操作，它将目标值(第一个参数)
写入原子变量，并返回写入前的值。在这个实现中，锁被占用时flag 为 true。如果锁被占用，(1) 处的 exchange 操作会一直返回true，线程阻塞在循环中，直到锁被释放。
flag 为 false，exchange 操作将 flag重新置为true 以抢占锁，并且返回其原来的值 false，循环退出，加锁成功。解锁则很简单,
将 flag 置为 false 即可。由于解锁操作使用 memory_order_release 且加锁操作使用memory_order_acquire，所以能保证加锁成功时与上一次解锁操作构成 “synchronizes- with” 的关系。
(3) 和(4) 之间没有任何同步关系。假设先执行操作(3)后执行操作(4)，那么 thread1 中(3) 之前的操作结果不一定对 thread2
可见。但只会有一个线程得到锁，这是由原子变量的修改顺序(modification order) 所保证的。要么 thread1 先将 flag 置为
true，要么 thread2 先将 flag 置为 true，这个顺序是全局一致的。
*/