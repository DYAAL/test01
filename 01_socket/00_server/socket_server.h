
#ifndef CREATE_Socket_Server_H
#define CREATE_Socket_Server_H
#include <iostream>
#include <netinet/in.h>
#pragma once


class Socket_Server {
public:
    Socket_Server();
    ~Socket_Server();
    int socket_create(int domain, int type, int protocol);
    int socket_bind(std::string ip_address, int port);
    int socket_bind(int port);
    void socket_accept();
    int socket_in_one(int domain, int type, int protocol, std::string ip_address, int port);
    int socket_in_one(int domain, int type, int protocol, int port);
    int print_client_addr();
    int listen_fd;
    int communication_fd;
    sockaddr_in serv_sockaddr;
    sockaddr_in client_sockaddr;

private:
};

#endif