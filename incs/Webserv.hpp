#pragma once

#include <vector>
#include <sys/epoll.h>
#include "Server.hpp"
#include "SocketManager.hpp"

namespace ft {

class Webserv
{
	public:
		Webserv();
		Webserv(const Webserv &x);
		Webserv	&operator=(const Webserv &x);
		~Webserv();

	public:
		SocketManager		manager;
		std::vector<Server>	servers;
};

}