#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include "../incs/SocketData.hpp"

namespace ft {

struct Socket
{
public:
	Socket(const Server &config);
	Socket(const Socket &x);
	Socket	&operator=(const Socket &x);
	~Socket();
private:
	Socket();

public:
	int			fd;
	sockaddr_in	addr;
	SocketData	data;
};

}
