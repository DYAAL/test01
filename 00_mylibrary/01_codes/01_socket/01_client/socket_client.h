#ifndef Socket_Client_H
#define Socket_Client_H
#include <iostream>
#include <netinet/in.h>
#pragma once

class Socket_Client {
public:
    Socket_Client();
    ~Socket_Client();
    int socket_create(int domain, int type, int protocol);
    int socket_connect(int port);
    int socket_connect(std::string ip_address, int port);
    int socket_in_one(int domain, int type, int protocol, std::string ip_address, int port);
    int socket_in_one(int domain, int type, int protocol, int port);

    int communication_fd;
    sockaddr_in client_sockaddr;

private:
};

#endif