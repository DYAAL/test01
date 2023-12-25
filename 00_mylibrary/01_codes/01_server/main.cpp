#include "Socket_Server.h"
#include <iostream>
#include <string.h>
#include <unistd.h>

int main()
{
while (1) {
        Socket_Server server;
        int ret = server.server_soc_all(AF_INET, SOCK_STREAM, 0, "192.168.3.5", 2345, 128);
        server.print_client_info(AF_INET);
        if (ret < 0) {
            std::cout << "in main_server, something is wrong!" << std::endl;
        }
        char buffer[1024];
        while (1) {
            memset(buffer, 0X00, sizeof(buffer));
            int word_num = read(server.commun_fd, buffer, sizeof(buffer));
            if (word_num == 0) {
                // 客户端已关闭连接
                std::cout << "Client disconnected." << std::endl;
                break; // 退出循环或采取其他适当的处理
            }
            std::cout << "[" << buffer << "]" << std::endl;
            for (int i = 0; i < word_num; i++) {
                buffer[i] = toupper(buffer[i]);
            }
            write(server.commun_fd, buffer, word_num);
            
        }
        close(server.commun_fd);
        close(server.listen_fd);
    }
    return 0;
}
