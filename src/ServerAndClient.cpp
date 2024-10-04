#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER
#ifdef SERVER
int main(int argc, const char** argv)
{
    int server_fd;
    struct sockaddr_in address;
    int reuse = 1;
    int addrlen = sizeof(address);

    // 创建套接字 (AF_INET = IPv4, SOCK_STREAM = TCP)
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // 允许套接字地址重用
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &reuse,
                   sizeof(reuse)) < 0) {
        perror("setsockopt failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // 设置地址和端口
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;  // 绑定到所有本地IP地址
    address.sin_port =
        htons(8080);  // 端口设置为8080，使用htons转换为网络字节序

    // 绑定套接字到指定的IP和端口
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // 开始监听，最大等待队列长度为3
    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    std::cout << "Server is listening on port 8080..." << std::endl;
    pid_t pid = getpid();

    while (1) {
        int new_socket;

        // struct sockaddr_in client_addr;
        // socklen_t client_len = sizeof(client_addr);
        // 这里是重用的之前的sockaddr_in变量，没有新定义

        if ((new_socket = accept(server_fd, (struct sockaddr*)&address,
                                 (socklen_t*)&addrlen)) < 0) {
            perror("accept failed");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        // 打印连接信息和进程ID
        printf("New connection accepted from %s:%d, PID: %d\n",
               inet_ntoa(address.sin_addr), 
               
               (address.sin_port), pid);

        // 处理连接
        // 在这里可以执行与客户端通信的代码

        // 关闭连接
        close(new_socket);
    }

    // 关闭套接字
    close(server_fd);

    return 0;
}
#endif

#ifdef CLIENT
int main(int argc, const char** argv)


    return 0;
}
#endif