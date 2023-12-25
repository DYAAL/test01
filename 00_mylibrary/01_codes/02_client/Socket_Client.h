#ifndef SOCKET_CLIENT_H
#define SOCKET_CLIENT_H

#include <iostream>
#include <netinet/in.h>
#pragma once

class Socket_Client {
public:
    Socket_Client();
    ~Socket_Client();
    int client_soc_create(int domain, int type, int protocol);
    int client_soc_connect(int domain, int port);
    int client_soc_connect(int domain, std::string ip_address, int port);
    int client_soc_all(int domain, int type, int protocol, const std::string ip_address, int port);
    int client_soc_all(int domain, int type, int protocol, int port);
    sockaddr_in client_addr;
    int commun_fd;

private:
};

#endif