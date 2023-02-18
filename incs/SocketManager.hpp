#pragma once

#include <vector>
#include <stdexcept>
#include <sys/epoll.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include "Socket.hpp"

#define MAXEVENTS 10
#define MAXQUEU 10

namespace ft {

class SocketManager
{
	public:
		SocketManager();
		SocketManager(const SocketManager &x);
		SocketManager	&operator=(const SocketManager &x);
		~SocketManager();

		void	addServer(const sockaddr_in &addr);
		void	setNoBlock(const int &fd);
		void	addEp(const int &fd);
		void	close();

	public:
		int					epfd;
		epoll_event			epev[MAXEVENTS];
		std::vector<Socket>	servers;
		std::vector<Socket>	clients;
};

}