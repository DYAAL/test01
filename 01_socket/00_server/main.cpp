#include "socket_server.h"
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <memory>


int main()
{
    Socket_Server server;
    int ret = server.socket_in_one(AF_INET, SOCK_STREAM, 0, 0, 4567);
    if(ret < 0 ){
        std::cout<<"in main, something is wrong!"<<std::endl;
    }

    char buffer[1024];
    while(1){
        memset(buffer, 0X00, sizeof(buffer));
        int word_num = read(server.communication_fd, buffer, sizeof(buffer));
        std::cout<<"["<<buffer<<"]"<<std::endl;
        for (int i=0 ; word_num; i++) {
            buffer[i] = toupper(buffer[i]);
        }
        write(server.communication_fd, buffer, word_num);
    }
    close(server.communication_fd);
    close(server.listen_fd);
    return 0;
}
