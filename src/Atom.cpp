/*
几个在原子类型里会用到的概念：

1.修改顺序
对一个原子变量的所有修改操作总是存在一定的先后顺序，且所有线程都认可这个顺序，即使这些修改操作是在不同的线程中执行的。这个所有线程一致同意的顺序就称为修改顺序(modification order)，
这意味着：
    (1)两个修改操作不可能同时进行，一定存在一个先后顺序。这很容易理解，因为这是原子操作必须保证的，否则就有数据竞争的问题。
    (2)即使每次运行的修改顺序可能都不同，但所有线程看到的修改顺序总是一致的。如果线程
    a 看到原子变量 x 由 1 变成 2，那么线程 b 就不可能看到 x 由 2 变成
    1。 
    (3)无论使用哪种内存顺序，原子变量的操作总能满足修改顺序一致性，即使是最松散的
    memory_order_relaxed。

2.顺序一致性：由memory_order_seq_cst实现

3.为什么非原子类型不存在顺序一致性概念？
    因为非原子类型不需要线程间同步。

    非原子类型的内存操作没有同步机制：非原子类型的读写操作不是并发安全的，这意味着多个线程对同一非原子变量的访问可能会导致数据竞争。
    一旦发生数据竞争，程序的行为就变得不确定，编译器和硬件可能会进行各种优化和重排，导致无法保证操作的执行顺序。
    因此，顺序一致性概念不适用于非原子类型，因为没有保证这些操作在多线程环境中会按照编写顺序执行。

4.happens - before和synchronizes - with语义
    happens -before :
        如果两个操作之间存在依赖关系，并且一个操作一定比另一个操作先发生，那么者两个操作就存在happens - before关系;

    synchronizes -with :
    synchronizes - with关系指原子类型之间的操作，如果原子操作A在像变量X写入一个之后，接着在同一线程或其它线程原子操作B又读取该值或重新写入一个值.
    那么A和B之间就存在synchronizes - with关系;

    注意这两种语义只是一种关系，并不是一种同步约束，也就是需要我们编程去保证，而不是它本身就存在。


5. 指令乱序
    这块需要注意的是：编译器只需要保证在单线程环境下，执行的结果最终一致就可以了，所以，指令乱序在单线程环境下完全是允许的。
    对于编译器来说，它只知道：在当前线程中，数据的读写以及数据之间的依赖关系。
    但是，编译器并不知道哪些数据是在线程间共享，而且是有可能会被修改的。而这些是需要开发人员去保证的。

6.memory_order_relaxed
memory_order_relaxed不能保证执行顺序，典型使用场景是统计计数的需求场景，比如shared_ptr增加引用计数

7.Acquire - Release模型的控制力度介于Relax模型和Sequential consistency模型之间。其定义如下：

    • Acquire：如果一个操作X带有acquire语义，那么在操作X后的所有读写指令都不会被重排序到操作X之前  
    （通俗的理解为，发布，发布出来是为了给其他线程用，所以得确保发布时前面的读写指令不会重排到X之后，这样发布之前的操作才对其他线程可见）

    • Relase：如果一个操作X带有release语义，那么在操作X前的所有读写指令操作都不会被重排序到操作X之后 
    （通俗的理解为，获取，获取出来是为了给该线程之后的指令用，所以得确保获取之后的指令不会重排到获取之前）


8.CPU缓存

    同步缓存过程当中造成的数据变更顺序，在各个核心看起来可能不同。
    比如核心1更新了x，核心2更新了y，在核心3看来到底是x先更新，还是y先更新，在核心4看来又如何，等等一系列问题。
    原子类型一定能保证同意一量的修改顺序一致性。memory_order_cst_seq模型才能保证不同变量的顺序一致性，即在一个总的顺序中。


9.Release sequences：
    针对一个原子变量 M 的 release 操作 A 完成后，接下来 M 上可能还会有一连串的其他操作，如果这一连串操作是任意线程上的 read-modify-write 操作。
    则称这一连串的操作为以 release 操作 A 为首的 release sequence。这里的写操作和 read-modify-write 操作可以使用任意内存顺序。
    如果一个 acquire 操作在同一个原子变量上读到了一个 release 操作写入的值，或者读到了以这个 release 操作为首的 release sequence 写入的值，
    那么这个 release 操作 “synchronizes-with” 这个 acquire 操作。

10.个人对acquire-release模型的理解：
    memory_order_acquire和memory_order_release并不保证执行先后顺序，不是说一定先执行ac再执行rel，而是保证如果执行了ac，且rel也执行了，
那么在rel执行之前的所有内容，对此ac可见。所以通常用while循环来确保acquire能load到

参考资料
1.https://mp.weixin.qq.com/s/t5_Up2YZEZt1NLbvgYz9FQ
2.https://www.zhihu.com/question/408308390/answer/2532410246
*/

#include <thread>
#include <atomic>
#include <cassert>
#include <vector>
#include <iostream>

std::atomic<bool> x{false}, y{false};

void thread1()
{
    x.store(true, std::memory_order_release);  // (1)
}

void thread2()
{
    y.store(true, std::memory_order_release);  // (2)
}

std::atomic<int> z{0};

void read_x_then_y()
{
    while (!x.load(std::memory_order_acquire))
        ;  // (3)
    if (y.load(std::memory_order_acquire))
        ++z;  // (4)
}

void read_y_then_x()
{
    while (!y.load(std::memory_order_acquire))
        ;  // (5)
    if (x.load(std::memory_order_acquire))
        ++z;  // (6)
}

int main()
{
    std::thread a(thread1), b(thread2), c(read_x_then_y), d(read_y_then_x);
    a.join(), b.join(), c.join(), d.join();
    assert(z.load() != 0);  // (7)
    std::cout << z.load() << std::endl;
}
