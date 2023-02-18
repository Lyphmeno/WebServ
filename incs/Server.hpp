#pragma once

#include <sys/socket.h>
#include <netinet/in.h>

namespace ft {

struct Server
{
	sockaddr_in	addr;
};

}