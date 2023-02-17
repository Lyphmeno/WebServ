#include "../incs/Socket.hpp"

namespace ft {

////////////////////////////////////////////////////////////////////////////////
//                                constructor                                 //
////////////////////////////////////////////////////////////////////////////////

Socket::Socket() : fd(-1)
{
}

Socket::Socket(const Socket &x) : fd(x.fd), addr(x.addr)
{
}

Socket	&Socket::operator=(const Socket &x)
{
	if (this != &x)
	{
		this->fd = x.fd;
		this->addr = x.addr;
	}
	return (*this);
}

Socket::~Socket()
{
	this->close();
}

////////////////////////////////////////////////////////////////////////////////
//                                  methods                                   //
////////////////////////////////////////////////////////////////////////////////

void	Socket::open()
{
	if (this->fd < 0)
	{
		this->fd = socket(AF_INET, SOCK_STREAM, 0);
		if (this->fd == -1)
			throw std::runtime_error("Runtime error: Socket creation failed");
	}
}

void	Socket::close()
{
	if (this->fd != -1)
		::close(this->fd);
}

void	Socket::set(const sockaddr_in &addr)
{
	this->addr = addr;
	if (bind(this->fd, reinterpret_cast<sockaddr *>(&this->addr), sizeof(this->addr)) == -1)
		throw std::runtime_error("Runtime error: Can't bind socket");

	if (listen(this->fd, 128) == -1)
		throw std::runtime_error("Runtime error: Can't listen socket");

	int flags = fcntl(this->fd, F_GETFL);
	if (flags == -1)
		throw std::runtime_error("Runtime error: Can't get socket flags");

	if (fcntl(this->fd, F_SETFL, flags | O_NONBLOCK) == -1)
		throw std::runtime_error("Runtime error: Can't set socket flags");
}

}