#pragma once

#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdexcept>

namespace ft {

class Socket
{
	public:
		Socket();
		Socket(const Socket &x);
		Socket	&operator=(const Socket &x);
		~Socket();

		void	open();
		void	close();
		void	set(const Server &addr);
	
	public:
		int					fd;
		sockaddr_in			addr;
};

}
