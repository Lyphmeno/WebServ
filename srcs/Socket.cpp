/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:13:30 by avarnier          #+#    #+#             */
/*   Updated: 2023/02/16 12:39:44 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Socket.hpp"

namespace ft {

/////////////////////////////
// Constructor             //
/////////////////////////////

Socket::Socket() : fd(-1), addr()
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
}

/////////////////////////////
// Methods                 //
/////////////////////////////

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

void	Socket::set()
{
	if (bind(this->fd, (sockaddr *)&addr, sizeof(addr)) == -1)
		throw std::runtime_error("Runtime error: Can't bind socket");

	if (listen(this->fd, 128) == -1)
		throw std::runtime_error("Runtime error: Can't listen socket");

	int flags = fcntl(this->fd, F_GETFL);
	if (flags == -1)
		throw std::runtime_error("Runtime error: Can't get socket flags");

	if (fcntl(this->fd, F_SETFL, flags | O_NONBLOCK) == -1)
		throw std::runtime_error("Runtime error: Can't set socket flags");
}

void	Socket::add(const int &epfd)
{
	epoll_event	ev;
	ev.events = EPOLLIN | EPOLLET;
	if (epoll_ctl(epfd, EPOLL_CTL_ADD, this->fd, &ev) == -1)
		throw std::runtime_error("Runtime error: Can't add socket to epoll");
}

}