/*
网上看到一段神奇的代码，不一对。

*/
#include <atomic>
#include <condition_variable>

std::mutex m;
std::atomic<bool> ok(false);
std::condition_variable cv;

void Wait()
{
    std::unique_lock<std::mutex> l(m);
    cv.wait(l, [&] { return ok.load(); });
    ok = false;
}
void Notify()
{
    if (ok.exchange(true) == false) {
        m.lock();    // (1)
        m.unlock();  // (2)  (1),(2)起到同步屏障的作用: 使得这个时刻没有其他人已经处于加锁中，即要么在加锁前，要么在解锁后。
        // 或许可以 std::lock_guard<std::mutex>{m}; // 匿名变量即生即死，从而完成自动加锁，又马上解锁
        cv.notify_all();
    }
}

// 更通常的写法是

bool is_ready = false;
std::condition_variable cvv;
std::mutex mm;

void thread_1()
{
    std::unique_lock<std::mutex> lock(mm);
    while (!is_ready)
        cvv.wait(lock);
    // ....
}

void thread_2()
{
    {
        std::lock_guard<std::mutex> lock(mm);
        is_ready = true;
    }
    cvv.notify_one();
}
/*
条件变量为什么要搭配锁使用，结合上述例子：
    这里，首先我们在 while (not is_ready) 前就加锁，接着把锁传给 wait 操作，wait 内部实现在将 thread_1挂到 cv的等待线程列表后就解锁，让其他线程可以操作共享状态 is_ready，
    然后在 thread_1 被唤醒时再加上锁。这样一来就保证了「 while (not is_ready)到挂载当前线程到等待列表」 这一整个过程的原子性，保证了 wait 执行的时候，notify_one必然没有执行， 
    也就不会出现「漏掉通知」这一现象。

    所以本质上可以说这个 mutex 主要目的仍然是保护共享状态 is_ready，并不是条件变量本身，故而条件变量被设计为和锁搭配使用。
*/
int main(int argc, const char** argv)
{
    return 0;
}