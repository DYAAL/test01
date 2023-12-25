#include "Socket_Client.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

Socket_Client::Socket_Client()
{
}

Socket_Client::~Socket_Client()
{
}

int Socket_Client::client_soc_create(int domain, int type, int protocol)
{
    this->commun_fd = socket(domain, type, protocol);
    if (this->commun_fd < 0) {
        perror("client_soc_create");
        return -1;
    }
    return 0;
}

int Socket_Client::client_soc_connect(int domain, int port)
{
    this->client_addr.sin_family = domain;
    this->client_addr.sin_port = htons(port);
    this->client_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    sockaddr* addr = reinterpret_cast<sockaddr*>(&this->client_addr);
    int ret = connect(this->commun_fd, addr, sizeof(*addr));
    if (ret < 0) {
        perror("client_soc_connect");
        return -1;
    }
    return 0;
}

int Socket_Client::client_soc_connect(int domain, std::string ip_address, int port)
{
    this->client_addr.sin_family = domain;
    this->client_addr.sin_port = htons(port);
    inet_pton(domain, ip_address.c_str(), &(this->client_addr.sin_addr.s_addr));
    sockaddr* addr = reinterpret_cast<sockaddr*>(&this->client_addr);
    int ret = connect(this->commun_fd, addr, sizeof(*addr));
    if (ret < 0) {
        perror("client_soc_connect_ip");
        return -1;
    }
    return 0;
}

int Socket_Client::client_soc_all(int domain, int type, int protocol, const std::string ip_address, int port)
{
    using namespace std;
    int ret = client_soc_create(domain, type, protocol);
    if (ret < 0) {
        cout << "in client_soc_all: client_soc_create-->failed" << endl;
        return -1;
    }
    ret = client_soc_connect(domain, ip_address, port);
    if (ret < 0) {
        cout << "in client_soc_all_ip: client_soc_connect-->failed" << endl;
        return -1;
    }
    return 0;
}

int Socket_Client::client_soc_all(int domain, int type, int protocol, int port)
{
    using namespace std;
    int ret = client_soc_create(domain, type, protocol);
    if (ret < 0) {
        cout << "in client_soc_all: client_soc_create-->failed" << endl;
        return -1;
    }
    ret = client_soc_connect(domain, port);
    if (ret < 0) {
        cout << "in client_soc_all: client_soc_connect-->failed" << endl;
        return -1;
    }
    return 0;
}