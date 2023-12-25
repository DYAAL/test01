#include "socket_client.h"
#include <cstring>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    Socket_Client client;
    int ret = client.socket_in_one(AF_INET, SOCK_STREAM, 0, "192.168.248.135", 4567);
    if (ret < 0) {
        std::cout << "in main_client, something is wrong!" << std::endl;
    }
    char buffer[128];

    while (1) {
        memset(buffer, 0, sizeof(buffer));
        ssize_t word_num = read(STDIN_FILENO, buffer, sizeof(buffer));
        if (word_num == -1) {
            perror("read error");
        }
        ssize_t write_result = write(client.communication_fd, buffer, word_num);
        if (write_result == -1) {
            perror("write error");
            // 处理错误情况，可能需要退出循环或进行其他处理
        }
        memset(buffer, 0, sizeof(buffer));
        ssize_t read_result = read(client.communication_fd, buffer, sizeof(buffer));
        if (read_result == -1) {
            perror("read error");
            // 处理错误情况，可能需要退出循环或进行其他处理
        }
        std::cout << "[" << buffer << "]" << std::endl;
    }
    close(client.communication_fd);
    return 0;
}