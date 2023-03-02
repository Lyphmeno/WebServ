#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <string>

namespace ft {

struct Socket
{
public:
	Socket();
	Socket(const Socket &x);
	Socket	&operator=(const Socket &x);
	~Socket();

public:
	int					fd;
	sockaddr_in			addr;
	unsigned long int	hlen;
	unsigned long int	blen;
	std::string			request;
	std::string			response;
};

}
