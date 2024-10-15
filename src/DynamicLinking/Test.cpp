#include <iostream>
#include <dlfcn.h>
using Hello = void (*)();
int main(int argc, const char** argv) {
    // 使用RTLD_NOW会报错 ./libHello.so: undefined symbol: _Z3Funv
    // RTLD_LAZY:在dlopen返回前，对于动态库中存在的未定义的变量(如外部变量extern，也可以是函数)不执行解析，就是不解析这个变量的地址。
    // RTLD_NOW：与上面不同，他需要在dlopen返回前，解析出每个未定义变量的地址，如果解析不出来，在dlopen会返回NULL，错误为：
    void* handle = dlopen("./libHello.so", RTLD_LAZY);
    if(!handle){
        std::cout << dlerror() << std::endl;
        return 1;
    }

    //获取函数指针
    Hello hello = (Hello)dlsym(handle, "_Z5Hellov");
    if(!hello){
        std::cout << dlerror() << std::endl;
        dlclose(handle);
        return 1;
    }

    hello();
    dlclose(handle);

    return 0;
}

// RTLD_LAZY：延迟解析库的外部符号，首次调用时再绑定，提升加载性能。
// RTLD_NOW：立即解析库的外部符号，确保加载时所有符号都可用。
// RTLD_BINDING_MASK：用于屏蔽绑定模式，提取绑定时间的值。
// RTLD_NOLOAD：不加载库，只检查是否已加载。
// RTLD_DEEPBIND：通常，动态链接器会优先使用先加载的库中的符号，但 RTLD_DEEPBIND 会改变这种行为，让当前库优先解析自己的符号。先解析库自己的符号，避免与其他库符号冲突。
// RTLD_GLOBAL：当使用 RTLD_GLOBAL 标志时，加载库中的符号不仅对该库可见，还会对随后加载的库可见。使库中的符号全局可见，供后续加载的库使用。