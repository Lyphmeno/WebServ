#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <string>

namespace ft {

struct Socket
{
	int			fd;
	sockaddr_in	addr;

	int			hlen;
	int			blen;
	std::string	request;
	std::string	response;
};
}
