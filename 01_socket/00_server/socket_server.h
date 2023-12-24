
#ifndef CREATE_Socket_Server_H
#define CREATE_Socket_Server_H


#pragma once


#include <netinet/in.h>


class Socket_Server
{
public:

Socket_Server();
~Socket_Server();
int socket_create(int domain, int type, int protocol);
int socket_bind(int listen_fd, int addr_0for_auto, int port);
void socket_accept(int listen_fd);
int socket_in_one(int domain, int type, int protocol, int addr_0for_auto, int port);
int listen_fd;
int communication_fd;
sockaddr_in serv_sockaddr;

private:

};

#endif