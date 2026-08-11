#include <queue>
#include <condition_variable>

template <typename T>
class BlockingQueue {
public:
    BlockingQueue(bool nonblock = false);

private:
    // 当消费者线程为空时，交换生产者和消费者队列
    int SwapQueue()
    {
        std::unique_lock<std::mutex> lock(m_producerMutex);
        m_notEmpty.wait(lock, [this] { return !m_producerQueue.empty() || m_nonblock; });
        return{};
    }
    bool m_nonblock;
    std::queue<T> m_producerQueue;
    std::queue<T> m_consumerQueue;
    std::mutex m_producerMutex;
    std::mutex m_consumerMutex;
    std::condition_variable m_notEmpty;
};
int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
