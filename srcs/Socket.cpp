/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 01:41:29 by avarnier          #+#    #+#             */
/*   Updated: 2023/02/13 19:31:15 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Socket.hpp"

namespace ft {

/////////////////////////////
// Coplien                 //
/////////////////////////////

Socket::Socket() try : fd(-1)
{
}
catch (std::exception &e)
{
	std::cout << e.what() << '\n';
}

Socket::Socket(const Socket &x) try : fd(x.fd)
{
}
catch (std::exception &e)
{
	std::cout << e.what() << '\n';
}

Socket	&Socket::operator=(const Socket &x)
{
	if (this != &x)
		this->fd = x.fd;
	return (*this);
}

Socket::~Socket()
{
	::close(this->fd);
}

/////////////////////////////
// Constructor             //
/////////////////////////////

Socket::Socket(const ft::EpSocket &epfd, const int &fd) try : fd(fd)
{
	this->addTo(epfd);
}
catch (std::exception &e)
{
	std::cout << e.what() << '\n';
}

Socket::Socket(const ft::EpSocket &epfd, const sockaddr_in &addr) try : fd(-1), addr(addr)
{
	this->init();
	this->addTo(epfd);
}
catch (std::exception &e)
{
	std::cout << e.what() << '\n';
}

/////////////////////////////
// Methods                 //
/////////////////////////////

void	Socket::init()
{
	this->fd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->fd == -1)
		throw std::runtime_error("Runtime error: Socket creation failed");

	int flags = fcntl(this->fd, F_GETFL);
	if (flags == -1)
		throw std::runtime_error("Runtime error: Can't get socket flags");

	if (fcntl(this->fd, F_SETFL, flags | O_NONBLOCK) == -1)
		throw std::runtime_error("Runtime error: Can't set socket flags");

	if (bind(this->fd, (sockaddr *)&addr, sizeof(addr)) == -1)
		throw std::runtime_error("Runtime error: Can't bind socket");

	if (listen(this->fd, 128) == -1)
		throw std::runtime_error("Runtime error: Can't listen socket");
}

void	Socket::addTo(const ft::EpSocket &epfd) const
{
	epoll_event	ev;
	ev.events = EPOLLIN | EPOLLET;
	if (epoll_ctl(epfd.fd, EPOLL_CTL_ADD, this->fd, &ev) == -1)
		throw std::runtime_error("Runtime error: Can't add socket to epoll");
}

}