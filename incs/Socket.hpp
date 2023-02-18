#pragma once

#include <sys/socket.h>
#include <netinet/in.h>

namespace ft {

struct Socket
{
	int			fd;
	sockaddr_in	addr;
};

}