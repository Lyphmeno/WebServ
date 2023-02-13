/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:17:09 by hlevi             #+#    #+#             */
/*   Updated: 2023/02/13 19:31:19 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Webserv.hpp"

namespace ft {
/////////////////////////////
// Coplien                 //
/////////////////////////////

Webserv::Webserv() try : epfd(), sockets(), servers()
{
	this->init();
}
catch (std::exception &e)
{
	std::cout << e.what() << '\n';
}

Webserv::Webserv(const Webserv &x)
try : epfd(x.epfd), sockets(x.sockets), servers(x.servers)
{
}
catch (std::exception &e)
{
	std::cout << e.what() << '\n';
}

Webserv &Webserv::operator=(const Webserv &rhs)
{
	if (this != &rhs)
	{
		this->epfd = rhs.epfd;
		this->sockets = rhs.sockets;
		this->servers = rhs.servers;
	}
	return (*this);
}

Webserv::~Webserv()
{
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

bool	Webserv::isSock(int sock)
{
	for (std::vector<ft::Socket>::const_iterator it = this->sockets.begin();
	it != this->sockets.end(); it++)
		if (sock == it->fd)
			return (true);
	return (false);
}

void	Webserv::init()
{
	//parsing fill servers
	for (std::vector<ft::Server>::const_iterator it = this->servers.begin();
	it != this->servers.end(); it++)
		this->sockets.push_back(ft::Socket(this->epfd, it->addr));
}

void	Webserv::run()
{
}

/////////////////////////////
// Exceptions              //
/////////////////////////////

}