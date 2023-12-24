#include "socket_server.h"
#include <arpa/inet.h>
#include <memory>
#include <netinet/in.h>
#include <strings.h>
#include <sys/socket.h>

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

int Socket_Server::socket_bind(std::string ip_address, int port)
{
    this->serv_sockaddr.sin_family = AF_INET;
    this->serv_sockaddr.sin_port = htons(port);
    inet_pton(AF_INET, ip_address.c_str(), &serv_sockaddr.sin_addr.s_addr);
    sockaddr* addr = reinterpret_cast<sockaddr*>(&this->serv_sockaddr);
    int ret = bind(communication_fd, addr, sizeof(*addr));
    if (ret < 0) {
        perror("binding failed");
        return -1;
    }
    return 0;
}

int Socket_Server::socket_bind(int port)
{
    this->serv_sockaddr.sin_family = AF_INET;
    this->serv_sockaddr.sin_port = htons(port);
    this->serv_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    sockaddr* addr = reinterpret_cast<sockaddr*>(&(this->serv_sockaddr));
    int ret = bind(listen_fd, addr, sizeof(*addr));
    if (ret < 0) {
        perror("binding failed");
        return -1;
    }
    return 0;
}

void Socket_Server::socket_accept()
{   
    socklen_t length = sizeof(this->client_sockaddr);
    sockaddr* addr = reinterpret_cast<sockaddr*>(&this->client_sockaddr);
    this->communication_fd = accept(this->listen_fd, addr, &length);
}

int Socket_Server::socket_in_one(int domain, int type, int protocol, std::string ip_address, int port)
{
    int ret = socket_create(domain, type, protocol);
    if (ret < 0) {
        return -1;
    }
    ret = socket_bind(ip_address, port);
    if (ret < 0) {
        return -1;
    }
    listen(this->listen_fd, 128);
    socket_accept();
    return 0;
}

int Socket_Server::socket_in_one(int domain, int type, int protocol, int port)
{
    int ret = socket_create(domain, type, protocol);
    if (ret < 0) {
        return -1;
    }
    ret = socket_bind(port);
    if (ret < 0) {
        return -1;
    }
    listen(this->listen_fd, 128);
    socket_accept();
    return 0;
}
int Socket_Server::print_client_addr()
{
    char sIP[16];
    inet_ntop(AF_INET, &client_sockaddr.sin_addr.s_addr, sIP, sizeof(sIP));
    std::cout<<"client--> ip_address == "<<sIP<<std::endl;
    std::cout<<"client--> port == "<<ntohs(client_sockaddr.sin_port)<<std::endl;
}

Socket_Server::~Socket_Server()
{
}
