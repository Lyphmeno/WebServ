#pragma once

#include <vector>

#include "Socket.hpp"

#define MAXEV 100

namespace ft {

class Webserv
{

public:
	Webserv();
	Webserv(const Webserv &x);
	Webserv	&operator=(const Webserv &x);
	~Webserv();

public:
	epSocket				ep;
	std::vector<ft::Socket>	sockets;
	std::vector<ft::Server>	servers;
};

}