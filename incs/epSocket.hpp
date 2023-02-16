#pragma once


#include <sys/epoll.h>
#include <unistd.h>
#include <stdexcept>

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

	public:
		int			fd;
		epoll_event	ev;
};

}