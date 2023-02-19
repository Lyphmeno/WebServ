#pragma once

#include <sys/socket.h>
#include <netinet/in.h>

namespace ft {

struct Socket
{
<<<<<<< HEAD
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
=======
	int			fd;
	sockaddr_in	addr;
>>>>>>> main
};

}