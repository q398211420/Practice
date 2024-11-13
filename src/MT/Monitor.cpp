/*
    《计算机操作系统》P62管程代码C++实现
*/
#include <condition_variable>
#include <iostream>
#include <thread>
#include <vector>
#include "mytool.h"
constexpr int N = 5;
class MonitorPC {
public:
    MonitorPC()
    {
        for (auto& e : m_buffer) {
            e = '$';
        }
    }
    void put(char x)
    {
        std::unique_lock lock(m_mutex);
        m_notFull.wait(lock, [this]() { return m_count < N; });
        m_buffer[m_in] = x;
        std::cout << "produce product" << std::endl;
        m_in = (m_in + 1) % N;
        m_count++;
        lock.unlock();
        m_notEmpty.notify_one();
    }
    void get(char& x)
    {
        std::unique_lock lock(m_mutex);
        m_notEmpty.wait(lock, [this]() { return m_count > 0; });
        x = m_buffer[m_out];
        m_buffer[m_out] = '$';
        std::cout << "consume product" << std::endl;
        m_out = (m_out + 1) % N;
        m_count--;
        lock.unlock();
        m_notFull.notify_one();
    }

private:
    char m_buffer[N];
    int m_in{0}, m_out{0};
    std::condition_variable m_notFull, m_notEmpty;
    int m_count{0};
    std::mutex m_mutex;
};
/*
注：
    以上只是伪代码(可能实现都有BUG），实际还应该确保
    "任一时刻管程中只能有一个活跃进程，这一特性使得管程能有效地完成互斥。
    管程是编程语言的组成部分，
    编译器知道其特殊性，进入管程时的互斥由编译器负责，通常做法是使用互斥量或二元信号量。
    这样就不需要程序员安排互斥，出错的可能性就小很多"
*/
MonitorPC PC;
void producer(char x)
{
    PC.put(x);
}
std::mutex vecMutex;
void consumer(std::vector<char>& vec)
{
    char x;
    PC.get(x);
    std::lock_guard<std::mutex> lock(vecMutex);
    vec.push_back(x);  // 在消费者中填充 vec
}
int main(int argc, const char** argv)
{
    std::thread threads[52];
    std::vector<char> vec;
    int j = 0;
    for (int i = 0; i < 26; i++) {
        threads[i] = std::thread(producer, 'A' + j);
        ++j;
        j %= 26;
    }
    for (int i = 26; i < 52; i++) {
        threads[i] = std::thread(consumer, std::ref(vec));  // 传递 vec
    }
    for (int i = 0; i < 52; i++) {
        threads[i].join();
    }
    MyPrint(vec);
    std::sort(vec.begin(),vec.end());
    MyPrint(vec);

    return 0;
}
