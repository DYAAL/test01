#include "socket_client.h"
#include <arpa/inet.h>
#include <iostream>
#include <stdio.h>
#include <sys/socket.h>

Socket_Client::Socket_Client()
{
}

Socket_Client::~Socket_Client()
{
}

int Socket_Client::socket_create(int domain, int type, int protocol)
{
    this->communication_fd = socket(domain, type, protocol);
    if (this->communication_fd < 0) {
        perror("socket creating error");
        return -1;
    }
    return 0;
}

int Socket_Client::socket_connect(int port)
{
    this->client_sockaddr.sin_family = AF_INET;
    this->client_sockaddr.sin_port = htons(port);
    this->client_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    sockaddr* addr = reinterpret_cast<sockaddr*>(&this->client_sockaddr);
    int ret = bind(communication_fd, addr, sizeof(*addr));
    if (ret < 0) {
        perror("binding failed");
        return -1;
    }
    return 0;
}

int Socket_Client::socket_connect(std::string ip_address, int port)
{
    this->client_sockaddr.sin_family = AF_INET;
    this->client_sockaddr.sin_port = htons(port);
    inet_pton(AF_INET, ip_address.c_str(), &client_sockaddr.sin_addr.s_addr);
    sockaddr* addr = reinterpret_cast<sockaddr*>(&this->client_sockaddr);
    int ret = connect(communication_fd, addr, sizeof(*addr));
    if (ret < 0) {
        perror("connect failed");
        return -1;
    }
    return 0;
}

int Socket_Client::socket_in_one(int domain, int type, int protocol, std::string ip_address, int port)
{
    int ret = socket_create(domain, type, protocol);
    if (ret < 0) {
        return -1;
    }
    ret = socket_connect(ip_address, port);
    if (ret < 0) {
        return -1;
    }
    return 0;
}

int Socket_Client::socket_in_one(int domain, int type, int protocol, int port)
{
    int ret = socket_create(domain, type, protocol);
    if (ret < 0) {
        return -1;
    }
    ret = socket_connect(port);
    if (ret < 0) {
        return -1;
    }
    return 0;
}


