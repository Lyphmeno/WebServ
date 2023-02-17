#include "../incs/epSocket.hpp"

namespace ft {

////////////////////////////////////////////////////////////////////////////////
//                                constructor                                 //
////////////////////////////////////////////////////////////////////////////////

epSocket::epSocket() : fd(-1)
{
	std::memset(this->ev, 0, sizeof(this->ev));
}

epSocket::epSocket(const epSocket &x) : fd(x.fd)
{
}

epSocket	&epSocket::operator=(const epSocket &x)
{
	if (this != &x)
		this->fd = x.fd;
	return (*this);
}

epSocket::~epSocket()
{
	this->close();
}

////////////////////////////////////////////////////////////////////////////////
//                                  methods                                   //
////////////////////////////////////////////////////////////////////////////////

void	epSocket::open()
{
	this->fd = epoll_create(1);
	if (this->fd == -1)
		throw std::runtime_error("Runtime error: Epoll creation failed");
}

void	epSocket::close()
{
	if (this->fd != -1)
		::close(this->fd);
}

void	epSocket::add(const int &fd)
{
	epoll_event	ev;
	ev.events = EPOLLIN | EPOLLET;
	if (epoll_ctl(this->fd, EPOLL_CTL_ADD, fd, &ev) == -1)
		throw std::runtime_error("Runtime error: Can't add socket to epoll");
}

}
