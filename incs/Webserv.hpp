#pragma once

#include <stdexcept>
#include <vector>
#include <iostream>
#include <errno.h>

#include "Socket.hpp"
#include "epSocket.hpp"
#include "Server.hpp"

#define BUFFSIZE 1024

namespace ft {

class Webserv
{

public:
	Webserv();
	Webserv(const Webserv &x);
	Webserv	&operator=(const Webserv &x);
	~Webserv();

	void	run();

private:
	bool	isSock(const int &fd);

private:
	epSocket				ep;
	std::vector<ft::Socket>	sockets;
	std::vector<ft::Socket>	clients;
	std::vector<ft::Server>	servers;
};

}