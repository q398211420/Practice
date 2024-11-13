#include <thread>
#include <utility>
#include <cassert>

void f() {}
void g() {}

int main(int argc, const char** argv)
{
    std::thread a{f};
    std::thread b = std::move(a);
    assert(!a.joinable());
    assert(b.joinable());
    a = std::thread{g};
    assert(a.joinable());
    assert(b.joinable());
    // a = std::move(b);  // 错误，不能转移所有权到 joinable 的线程
    a.join();
    a = std::move(b);
    assert(a.joinable());
    assert(!b.joinable());
    a.join();
    return 0;
}