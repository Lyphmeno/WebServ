#pragma once

#include <stdexcept>
#include <vector>
<<<<<<< HEAD
#include <iostream>
#include <errno.h>

#include "Socket.hpp"
#include "epSocket.hpp"
#include "Server.hpp"

#define BUFFSIZE 1024
=======
#include <sys/epoll.h>
#include "Server.hpp"
#include "SocketManager.hpp"
>>>>>>> main

namespace ft {

class Webserv
{
public:
	Webserv();
	~Webserv();

<<<<<<< HEAD
	void	run();

private:
	bool	isSock(const int &fd);

private:
	epSocket				ep;
	std::vector<ft::Socket>	sockets;
	std::vector<ft::Socket>	clients;
	std::vector<ft::Server>	servers;
=======
private:
	Webserv(const Webserv &x);
	Webserv	&operator=(const Webserv &x);

public:
	SocketManager		manager;
	std::vector<Server>	servers;
>>>>>>> main
};

}