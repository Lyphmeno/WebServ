/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:17:09 by hlevi             #+#    #+#             */
/*   Updated: 2023/02/12 22:35:05 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Webserv.hpp"

namespace ft {
/////////////////////////////
// Coplien                 //
/////////////////////////////

Webserv::Webserv() : epfd(-1), epev(), sockets(), servers()
{
}

Webserv::Webserv(const Webserv &cpy)
: epfd(cpy.epfd), servers(cpy.servers)
{
}

Webserv::~Webserv()
{
	this->close();
}

Webserv &Webserv::operator=(const Webserv &rhs)
{
	if (this != &rhs)
	{
		this->epfd = rhs.epfd;
		this->servers = rhs.servers;
	}
	return (*this);
}

/////////////////////////////
// Assignation contructors //
/////////////////////////////

/////////////////////////////
// Getters                 //
/////////////////////////////

/////////////////////////////
// Setters                 //
/////////////////////////////

/////////////////////////////
// Operators               //
/////////////////////////////

/////////////////////////////
// Methods                 //
/////////////////////////////

void	Webserv::start()
{
	try
	{
//		init();
//		run();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}

void	Webserv::init()
{
	this->epinit();
}

void	Webserv::epinit()
{
	this->epfd = epoll_create(this->servers.size());
	if (this->epfd == -1)
		throw std::runtime_error("Runtime error: Epoll creation failed");

	for (std::vector<ft::Server>::const_iterator it = this->servers.begin();
	it != this->servers.end(); it++)
		sockinit(it->addr);
}

void	Webserv::sockinit(sockaddr_in addr)
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
		throw std::runtime_error("Runtime error: Socket creation failed");

	int flags = fcntl(sock, F_GETFL);
	if (flags == -1)
		throw std::runtime_error("Runtime error: Can't get socket flags");

	if (fcntl(sock, F_SETFL, flags | O_NONBLOCK) == -1)
		throw std::runtime_error("Runtime error: Can't set socket flags");

	if (bind(sock, (sockaddr *)&addr, sizeof(addr)) == -1)
		throw std::runtime_error("Runtime error: Can't bind socket");

	if (listen(sock, 128) == -1)
		throw std::runtime_error("Runtime error: Can't listen socket");

	epoll_event	ev;
	ev.events = EPOLLIN | EPOLLET;
	if (epoll_ctl(this->epfd, EPOLL_CTL_ADD, sock, &ev) == -1)
		throw std::runtime_error("Runtime error: Can't add socket to epoll");

	this->sockets.push_back(sock);
}

void	Webserv::close()
{
	if (this->epfd != -1)
	{
		::close(this->epfd);
		this->epfd = -1;
	}
	while (this->sockets.size() != 0)
	{
		::close(*this->sockets.begin());
		this->sockets.erase(this->sockets.begin());
	}
}

void Webserv::run()
{
	for (;;)
	{
		int n = epoll_wait(epoll_fd, this->epev, MAXEV, -1);
		if (n == -1)
			return (-1);
		for (int i = 0; i < n; i++)
		{
			if ((this->epev[i].events & EPOLLERR)
			|| (this->epev[i].events & EPOLLHUP)
			|| !(this->epev[i].events & EPOLLIN))
				::close(this->epev[i].data.fd);
			else if (this->isSock(this->epev[i].data.fd) == true)
			{
			}
			else ()
			{
			}
		}
	}
}

bool	Webserv::isSock(int sock)
{
	for (std::vector<int>::const_iterator it = this->sockets.begin();
	it != this->sockets.end(); it++)
	{
		if (sock == *it)
			return (true);
	}
	return (false);
}

/////////////////////////////
// Exceptions              //
/////////////////////////////

}