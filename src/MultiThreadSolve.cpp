/*
    死锁产生的必要条件：
        1.互斥条件
        2.请求和保持条件
        3.不可抢占条件
        4.循环等待条件
    几个经典的进程同步问题
    1.The producer-consumer problem
    2.The Dinning Philosophers Problem
        该问题是描述五个哲学家公用一张圆桌，分别坐在周围的五张椅子上，在圆桌上有五个碗和五只筷子，他们的生活方式
        是交替地进行思考和进餐。平时，一个哲学家进行思考，饥饿时便试图取用其左右最靠近他的筷子，只有在他拿到两只
        筷子时才能进餐。进餐毕，放下筷子继续思考。
        经分析可知，放在桌子上的筷子是临界资源，在一段时间内只允许一位哲学家使用。
        为了实现对筷子的互斥使用，可以用一个信号量表示一只筷子，由这五个信号量构成信号量数组，其描述如下：
            semaphore chopstick[5] = {1, 1, 1, 1, 1};
        所有信号量均被初始化为1，第i位哲学家的活动课描述为：
        do {
            wait(chopstick[i]);
            wait(chopstick[(i+1)%5]);
            ...
            // eat
            ...
            signal(chopstick[i]);
            signal(chopstick[(i+1)%5]);
            ...
            // think
            ...
        }while(TRUE);
    在以上描述中，当哲学家饥饿时，总是先去拿他左手边的筷子，即执行wait(chopstick[i]);
    成功后，又去拿他右边的筷子，即执行wait(chopstick[(i+1)%5]);又成功后便可进餐。进餐毕，
    又先放下他左边的筷子，然后再放下他右边的筷子。虽然，上述解法可保证不会有两个相邻的哲学家
    同时进餐，但却有可能引起死锁。假如五位哲学家同时饥饿而各自拿起左边的筷子时，就会使五个信号量
    chopstick均为0;当他们再试图去拿右边的筷子时，都将因无筷子可拿而无限期的等待。对于这样的死锁问题，
    可采取以下几种解决办法：
    （1） 至多只允许有四位哲学家同时去拿左边的筷子，最终能保证至少有一位哲学家能够进餐，并在用毕时能
    释放出他用过的两只筷子，从而使更多的哲学家能够进餐。
    （2）仅当哲学家的左、右两只筷子均可用时，才允许他拿起筷子进餐。
    （3）规定奇数号哲学家先拿他左边的筷子，然后再去拿他右边的筷子；而偶数号哲学家则相反。按此规定，将是1、2号哲学家
    竞争1号筷子；3、4号哲学家竞争3号筷子。即五位哲学家都先竞争奇数号筷子，获得后，再去竞争偶数号筷子，最后总会有一位
    哲学家能获得两只筷子而进餐。

    3.Reader-Writer Problem
        允许多个进程同时读一个共享对象，但不允许一个写进程和其他读进程或者写进程同时访问共享对象
*/
#include "Semaphores.h"
#include <random>
#include <thread>

constexpr int MAX_COUNT = 5;
std::mutex m;
RecordSemaphore empty{MAX_COUNT};
RecordSemaphore full{0};
char buffer[5] = {'$', '$', '$', '$', '$'};
int in{0}, out{0};
//   1.The producer-consumer problem
void Producer(int i)
{
    double s = static_cast<double>(std::rand()) / RAND_MAX;
    do {
        empty.Wait();
        m.lock();
        buffer[in] = 65 + (in % MAX_COUNT);  //写入 A,B,C....
        //std::cout << "produce product " << buffer[in]<< std::endl;
        in = (in + 1) % MAX_COUNT;
        m.unlock();
        full.Signal();

    } while (true);
}
void Consumer()
{
    double s = static_cast<double>(std::rand()) / RAND_MAX;

    do {
        full.Wait();
        m.lock();
        char product = buffer[out];
        buffer[out] = 36;  // ASCII 36,代表$，即产品被消耗
        out = (out + 1) % MAX_COUNT;
        std::cout << "consume product " << product << std::endl;
        sleep(s);
        m.unlock();
        empty.Signal();

    } while (true);
}
//   1.The producer-consumer problem

//   2.The producer-consumer problem
std::mutex chopstick[5];
std::mutex mm;
void Philosopher(int i)
{
    if (i < 0 || i > 4)
        return;
    do {
        mm.lock();
        chopstick[i].lock();
        chopstick[(i + 1) % 5].lock();
        mm.unlock();
        std::cout << "Philosopher NO." << i << "is dinning" << std::endl;
        chopstick[i].unlock();
        chopstick[(i + 1) % 5].unlock();
    } while (1);
}
void TestPhilosopher()
{
    std::thread threads[5];
    for (size_t i = 0; i < 5; i++) {
        threads[i] = std::thread(Philosopher, i);
    }
    for (auto& th : threads) {
        if (th.joinable()) {
            th.join();
        }
    }
}
//   2.The producer-consumer problem

//   3.Reader-Writer Problem
/*
    为实现读与写进程在读写时的互斥而设置了一个互斥信号量wmutex。另外，再设置一个整形变量readcount表示正在读的进程数目。由于只要有一个
    读进程在读，便不允许写进程区写。因此，仅当人readcount=0，表示无度进场正在读时，读进程才需要执行wait(wmutex)操作。若wait(wmutex)
    操作成功，读进程便可去读，相应地，做readcount+1操作。同理，仅当读进程在执行了readcount-1操作后值为0时，才需执行signal(wmutex)操作
    ，以便让写进程写操作。又因为readcount是一个可被多个读进程访问的临界资源，因此，也应该为它设置一个互斥信号量rmutex。
*/
// V1版本读进程优先
// V2版本读写公平法(写进程优先级比V1稍微高)
// V3写进程优先 (待实现)
std::mutex wmutex;
std::mutex rmutex;
int readCount{0};
void ReaderV1(int i)
{
    do {
        rmutex.lock();
        if (readCount == 0) {
            wmutex.lock();
        }
        readCount++;
        rmutex.unlock();

        std::cout << "Reader NO." << i << " is reading..." << std::endl;

        rmutex.lock();
        if (--readCount == 0) {
            wmutex.unlock();
        }

        rmutex.unlock();
    } while (1);
}
void WriterV1(int i)
{
    do {
        wmutex.lock();
        std::cout << "Writer NO." << i << " is writing..." << std::endl;
        wmutex.unlock();

    } while (1);
}
void TestReaderWriterV1()
{
    std::thread Writers[200], Readers[100];
    for (size_t i = 0; i < 200; i++) {
        Writers[i] = std::thread(WriterV1, i);
    }
    for (size_t i = 0; i < 100; i++) {
        Readers[i] = std::thread(ReaderV1, i);
    }

    for (auto& th : Writers) {
        if (th.joinable()) {
            th.join();
        }
    }
    for (auto& th : Readers) {
        if (th.joinable()) {
            th.join();
        }
    }
}
//   3.Reader-Writer Problem

int main(int argc, const char** argv)
{
    srand(time(0));

    return 0;
}