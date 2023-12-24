#include "socket_server.h"
#include <cstdio>
#include <iostream>
#include <memory>
#include <netinet/in.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>

Socket_Server::Socket_Server()
{
    bzero(&(this->serv_sockaddr), sizeof(serv_sockaddr));
}

int Socket_Server::socket_create(int domain, int type, int protocol)
{
    this->listen_fd = socket(domain, type, protocol);
    if (this->listen_fd < 0) {
        perror("socket creating error");
        return -1;
    }
    return 0;
}

int Socket_Server::socket_bind(int listen_fd, int addr_0for_auto, int port)
{
    this->serv_sockaddr.sin_family = AF_INET;
    this->serv_sockaddr.sin_port = htons(port);
    if (addr_0for_auto == 0) {
        this->serv_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    }
    sockaddr* addr = reinterpret_cast<sockaddr*>(&this->serv_sockaddr);
    int ret = bind(listen_fd, addr, sizeof(*addr));
    if (ret < 0) {
        perror("binding failed");
        return -1;
    }
    return 0;
}


void Socket_Server::socket_accept(int listen_fd)
{
    this->communication_fd = accept(this->listen_fd, nullptr, nullptr);
}

int Socket_Server::socket_in_one(int domain, int type, int protocol, int addr_0for_auto, int port)
{
    int ret = socket_create(domain, type, protocol);
}

Socket_Server::~Socket_Server()
{
}
