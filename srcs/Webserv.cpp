/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:17:09 by hlevi             #+#    #+#             */
/*   Updated: 2023/02/09 00:52:13 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Webserv.hpp"

namespace ft {

/////////////////////////////
// Coplien                 //
/////////////////////////////
Webserv::Webserv()
{
}

Webserv::Webserv(const Webserv &cpy)
{
	*this = cpy;
}

Webserv::~Webserv()
{
}

Webserv &Webserv::operator=(const Webserv &rhs)
{
	if (this != &rhs)
	{
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
	size_t	size = this->servers.size();
	if (size == 0)
		return (-1);

	for (size_t x = 0; x < size; x++)
		this->epdata[x].events = EPOLLIN | EPOLLET;

	this->epfd = epoll_create(size);
	if (this->epfd == -1)
	{
		this->clear();
		return (-1);
	}

	for (size_t x = 0; x < size; x++)
	{
		epoll_ctl(this->epfd, EPOLL_CTL_ADD,
		this->servers[x].sock, &(this->epdata[x]));
	}
}

void	Webserv::clear()
{
	close(epfd);
	epfd = -1;
}
/////////////////////////////
// Exceptions              //
/////////////////////////////

}