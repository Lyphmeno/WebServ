/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:17:09 by hlevi             #+#    #+#             */
/*   Updated: 2023/02/09 19:53:47 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Webserv.hpp"

namespace ft {

/////////////////////////////
// Coplien                 //
/////////////////////////////

Webserv::Webserv() : epfd(-1), servers()
{
}

Webserv::Webserv(const Webserv &cpy)
: epfd(cpy.epfd), servers(cpy.servers)
{
}

Webserv::~Webserv()
{
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

int	Webserv::epinit()
{
	size_t	serv_nb = this->servers.size();

	this->epfd = epoll_create(serv_nb);
	if (this->epfd == -1)
		return (-1);

	for (size_t x = 0; x < serv_nb; x++)
	{
		if (sockinit(this->servers[x]) == -1)
			return (-1);
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

/////////////////////////////
// Exceptions              //
/////////////////////////////


const char *Webserv::epInitError::what() const throw()
{
	return ("Epoll failed to initialize");
}

const char *Webserv::sockInitError::what() const throw()
{
	return ("Sockets failed to initialize");
}

}