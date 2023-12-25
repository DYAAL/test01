#ifndef SOCKET_SERVER_H
#define SOCKET_SERVER_H

#include <iostream>
#include <netinet/in.h>
#pragma once

class Socket_Server {
public:
    Socket_Server();
    ~Socket_Server();
    int server_soc_create(int domain, int type, int protocol);
    int server_soc_bind(int domain, const std::string ip_address, int port);
    int server_soc_bind(int domain, int port);
    int server_soc_listen(int link_number);
    int client_accept();
    int server_soc_all(int domain, int type, int protocol, const std::string ip_address, int port, int link_number);
    int server_soc_all(int domain, int type, int protocol, int port, int link_number);
    void print_client_info(int domain);
    sockaddr_in server_addr;
    sockaddr_in client_addr;
    int listen_fd;
    int commun_fd;

private:
};

#endif