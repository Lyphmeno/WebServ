/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:17:09 by hlevi             #+#    #+#             */
/*   Updated: 2023/02/10 19:44:40 by avarnier         ###   ########.fr       */
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
	size_t	serv_nb = this->servers.size();

	this->epfd = epoll_create(serv_nb);
	if (this->epfd == -1)
		throw std::runtime_error("Epoll initialization failed");

	for (size_t x = 0; x < serv_nb; x++)
	{
		if (sockinit(this->servers[x]) == -1)
		{
			this->close();
			throw std::runtime_error("Socket initialization failed");
		}
	}
}

int	Webserv::sockinit(Server &serv)
{
	serv.sock = socket(AF_INET, SOCK_STREAM, 0);
	if (serv.sock == -1)
		return (-1);

	int flags = fcntl(serv.sock, F_GETFL);
	if (flags == -1)
		return (-1);

	if (fcntl(serv.sock, F_SETFL, flags | O_NONBLOCK) == -1)
		return (-1);

	if (bind(serv.sock, (sockaddr *)&serv.addr, sizeof(serv.addr)) == -1)
		return (-1);

	if (listen(serv.sock, 128) == -1)
		return (-1);

	serv.epev.events = EPOLLIN | EPOLLET;
	if (epoll_ctl(this->epfd, EPOLL_CTL_ADD, serv.sock, &serv.epev) == -1)
		return (-1);

	return (0);
}

void	Webserv::close()
{
	if (this->epfd != -1)
	{
		::close(this->epfd);
		this->epfd = -1;
	}
	for (size_t x = 0, serv_nb = this->servers.size(); x < serv_nb; x++)
	{
		if (this->servers[x].sock != -1)
		{
			::close(this->servers[x].sock);
			this->servers[x].sock = -1;
		}
	}
}

/////////////////////////////
// Exceptions              //
/////////////////////////////

}
