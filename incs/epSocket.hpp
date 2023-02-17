#pragma once


#include <sys/epoll.h>
#include <unistd.h>
#include <stdexcept>

#define MAXEV 100

namespace ft {

class epSocket
{
	public:
		epSocket();
		epSocket(const epSocket &x);
		epSocket	&operator=(const epSocket &x);
		~epSocket();

		void	open();
		void	close();
		void	add(const int &fd);

	public:
		int			fd;
		epoll_event	ev[MAXEV];
};

}
