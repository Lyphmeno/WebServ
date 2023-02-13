/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 01:41:29 by avarnier          #+#    #+#             */
/*   Updated: 2023/02/13 01:43:22 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Socket.hpp"

namespace ft {

Socket::Socket() try : fd(-1), conf()
{
}
catch (std::exception &e)
{
	std::cout << e.what() << '\n';
}

Socket::Socket(const Socket &x) try : fd(x.fd), conf(x.conf)
{
}
catch (std::exception &e)
{
	std::cout << e.what() << '\n';
}

Socket::Socket(int epfd) try : fd(-1), conf()
{
	init(epfd);
}
catch (std::exception &e)
{
	std::cout << e.what() << '\n';
}

Socket	&Socket::operator=(const Socket &x)
{
}

Socket::~Socket()
{
	::close(this->fd);
}

void	Socket::init(int epfd)
{
	this->fd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->fd == -1)
		throw std::runtime_error("Runtime error: Socket creation failed");

	int flags = fcntl(this->fd, F_GETFL);
	if (flags == -1)
		throw std::runtime_error("Runtime error: Can't get socket flags");

	if (fcntl(this->fd, F_SETFL, flags | O_NONBLOCK) == -1)
		throw std::runtime_error("Runtime error: Can't set socket flags");

	if (bind(this->fd, (sockaddr *)&this->conf.addr, sizeof(this->conf.addr)) == -1)
		throw std::runtime_error("Runtime error: Can't bind socket");

	if (listen(this->fd, 128) == -1)
		throw std::runtime_error("Runtime error: Can't listen socket");

	epoll_event	ev;
	ev.events = EPOLLIN | EPOLLET;
	if (epoll_ctl(epfd, EPOLL_CTL_ADD, this->fd, &ev) == -1)
		throw std::runtime_error("Runtime error: Can't add socket to epoll");
}

}