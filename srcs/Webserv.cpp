/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:17:09 by hlevi             #+#    #+#             */
/*   Updated: 2023/02/12 17:22:44 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Webserv.hpp"

namespace ft {
/////////////////////////////
// Coplien                 //
/////////////////////////////

Webserv::Webserv() : epfd(-1), servers()
{
	this->epinit();
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

void	Webserv::epinit()
{
	size_t	server_nb = this->servers.size();

	this->epfd = epoll_create(server_nb);
	if (this->epfd == -1)
		throw std::runtime_error("Epoll initialization failed");

	for (std::vector<ft::Server>::const_iterator it = this->servers.begin();
	it != this->servers.end(); it++)
	{
		if (sockinit(it->addr) == -1)
		{
			this->close();
			throw std::runtime_error("Socket initialization failed");
		}
	}
}

int	Webserv::sockinit(sockaddr_in addr)
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
		return (-1);

	int flags = fcntl(sock, F_GETFL);
	if (flags == -1)
		return (-1);

	if (fcntl(sock, F_SETFL, flags | O_NONBLOCK) == -1)
		return (-1);

	if (bind(sock, (sockaddr *)addr, sizeof(addr)) == -1)
		return (-1);

	if (listen(sock, 128) == -1)
		return (-1);

	epoll_event	ev;
	ev.events = EPOLLIN | EPOLLET;
	if (epoll_ctl(this->epfd, EPOLL_CTL_ADD, sock, &ev) == -1)
		return (-1);

	this->sockets.push_back(sock);
	return (0);
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

/////////////////////////////
// Exceptions              //
/////////////////////////////

}
