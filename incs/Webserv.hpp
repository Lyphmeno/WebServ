#pragma once

#include <stdexcept>
#include <vector>
#include <iostream>

#include "Socket.hpp"
#include "epSocket.hpp"
#include "Server.hpp"

namespace ft {

class Webserv
{

public:
	Webserv();
	Webserv(const Webserv &x);
	Webserv	&operator=(const Webserv &x);
	~Webserv();

private:
	void	run();
	bool	isSock(const int &fd);

private:
	epSocket				ep;
	std::vector<ft::Socket>	sockets;
	std::vector<ft::Socket>	clients;
	std::vector<ft::Server>	servers;
};

}