#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <string>

namespace ft {

struct Socket
{
	int			fd;
	sockaddr_in	addr;

	bool		header;
	size_t		hlen;
	size_t		blen;
	std::string	request;
	std::string	response;
};
}
