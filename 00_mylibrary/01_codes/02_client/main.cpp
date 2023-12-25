#include "Socket_Client.h"
#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main()
{
    Socket_Client client;
    int ret = client.client_soc_all(AF_INET, SOCK_STREAM, 0, "192.168.3.5", 2345);
    if (ret < 0) {
        std::cout << "in main_client, something is wrong!" << std::endl;
    }
    char buffer[128];
    while (true) {
        memset(buffer, 0, sizeof(buffer));
        ssize_t word_num = read(STDIN_FILENO, buffer, sizeof(buffer));
        if (word_num == -1) {
            perror("read error");
        }
        ssize_t write_result = write(client.commun_fd, buffer, word_num);
        if (write_result == -1) {
            perror("write error");
            // 处理错误情况，可能需要退出循环或进行其他处理
        }
        memset(buffer, 0, sizeof(buffer));
        ssize_t read_result = read(client.commun_fd, buffer, sizeof(buffer));
        if (read_result == -1) {
            perror("read error");
            // 处理错误情况，可能需要退出循环或进行其他处理
        }
        std::cout << "[" << buffer << "]" << std::endl;
    }
    close(client.commun_fd);
    return 0;
}

