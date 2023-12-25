#include "Socket_Server.h"
#include <arpa/inet.h>
#include <cstring>
#include <netinet/in.h>

Socket_Server::Socket_Server()
{
    this->commun_fd = 0;
    this->listen_fd = 0;
    memset(&(this->client_addr), 0, sizeof(this->client_addr));
    memset(&(this->server_addr), 0, sizeof(this->server_addr));
}

Socket_Server::~Socket_Server()
{
}

int Socket_Server::server_soc_create(int domain, int type, int protocol)
{
    this->listen_fd = socket(domain, type, protocol);
    if (this->listen_fd < 0) {
        perror("server_soc_create");
        return -1;
    }
    return 0;
}

int Socket_Server::server_soc_bind(int domain, const std::string ip_address, int port)
{
    this->server_addr.sin_family = domain;
    this->server_addr.sin_port = htons(port);
    inet_pton(domain, ip_address.c_str(), &(this->server_addr.sin_addr.s_addr));
    sockaddr* addr = reinterpret_cast<sockaddr*>(&this->server_addr);
    int ret = bind(this->listen_fd, addr, sizeof(this->server_addr));
    if (ret < 0) {
        perror("server_soc_bind");
        return -1;
    }
    return 0;
}

int Socket_Server::server_soc_bind(int domain, int port)
{
    this->server_addr.sin_family = domain;
    this->server_addr.sin_port = htons(port);
    this->server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    sockaddr* addr = reinterpret_cast<sockaddr*>(&this->server_addr);
    int ret = bind(this->listen_fd, addr, sizeof(this->server_addr));
    if (ret < 0) {
        perror("server_soc_bind");
        return -1;
    }
    return 0;
}

int Socket_Server::server_soc_listen(int link_number)
{
    int ret = listen(this->listen_fd, link_number);
    if (ret < 0) {
        perror("server_soc_listen");
        return -1;
    }
    return 0;
}

int Socket_Server::client_accept()
{
    socklen_t length = sizeof(this->client_addr);
    sockaddr* addr = reinterpret_cast<sockaddr*>(&(this->client_addr));
    this->commun_fd = accept(this->listen_fd, addr, &length);
    if (this->commun_fd < 0) {
        perror("client_accept failed");
        return -1;
    }
    return 0;
}

int Socket_Server::server_soc_all(int domain, int type, int protocol, const std::string ip_address, int port, int link_number)
{
    using namespace std;
    int ret = server_soc_create(domain, type, protocol);
    if (ret < 0) {
        cout << "in server_soc_all: server_soc_create-->failed" << endl;
        return -1;
    }
    ret = server_soc_bind(domain, ip_address, port);
    if (ret < 0) {
        cout << "in server_soc_all: server_soc_bind-->failed" << endl;
        return -1;
    }
    ret = server_soc_listen(link_number);
    if (ret < 0) {
        cout << "in server_soc_all: server_soc_listen-->failed" << endl;
        return -1;
    }
    ret = client_accept();
    if (ret < 0) {
        cout << "in server_soc_all: client_accept-->failed" << endl;
        return -1;
    }
    return 0;
}

int Socket_Server::server_soc_all(int domain, int type, int protocol, int port, int link_number)
{
    using namespace std;
    int ret = server_soc_create(domain, type, protocol);
    if (ret < 0) {
        cout << "in server_soc_all: server_soc_create-->failed" << endl;
        return -1;
    }
    ret = server_soc_bind(domain, port);
    if (ret < 0) {
        cout << "in server_soc_all: server_soc_bind-->failed" << endl;
        return -1;
    }
    ret = server_soc_listen(link_number);
    if (ret < 0) {
        cout << "in server_soc_all: server_soc_listen-->failed" << endl;
        return -1;
    }
    ret = client_accept();
    if (ret < 0) {
        cout << "in server_soc_all: client_accept-->failed" << endl;
        return -1;
    }
    return 0;
}

void Socket_Server::print_client_info(int domain)
{
    char sIP[16];
    inet_ntop(domain, &(this->client_addr.sin_addr.s_addr), sIP, sizeof(sIP));
    std::cout << "client--> ip_address == " << sIP << std::endl;
    std::cout << "client--> port == " << ntohs(client_addr.sin_port) << std::endl;
}
