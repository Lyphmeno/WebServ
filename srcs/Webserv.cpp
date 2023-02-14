/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:17:09 by hlevi             #+#    #+#             */
/*   Updated: 2023/02/14 20:47:43 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Webserv.hpp"

namespace ft {
/////////////////////////////
// Coplien                 //
/////////////////////////////

Webserv::Webserv() try : ep(), sockets(), servers()
{
	this->init();
}
catch (std::exception &e)
{
	std::cout << e.what() << '\n';
}

Webserv::Webserv(const Webserv &x)
try : ep(x.ep), sockets(x.sockets), servers(x.servers)
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
		this->ep = rhs.ep;
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

bool	Webserv::isSock(int fd)
{
	for (std::vector<ft::Socket>::const_iterator it = this->sockets.begin();
	it != this->sockets.end(); it++)
		if (fd == it->fd)
			return (true);
	return (false);
}

void	Webserv::removeSock(int fd)
{
	for (std::vector<ft::Socket>::const_iterator it = this->sockets.begin();
	it != this->sockets.end(); it++)
		if (fd == it->fd)
			this->servers.erase(it);
}

void	Webserv::init()
{
	//parsing fill servers
	for (std::vector<ft::Server>::const_iterator it = this->servers.begin();
	it != this->servers.end(); it++)
		this->sockets.push_back(ft::Socket(this->ep.fd, it->addr));
}

void	Webserv::run()
{
	for (;;)
	{
		int	n = epoll_wait(this->ep->fd, this->ep.ev, MAXEV, -1);
		if (n == -1)
			throw std::system_error(errno, "System error: epoll_wait failed");
		for (int i = 0; i < n; i++)
		{
			if ((this->ep.ev[i].events & EPOLLERR)
			|| (this->ep.ev[i].events & EPOLLHUP)
			|| (this->ep.ev[i].events & EPOLLIN))
			{
				::close(this->ep.ev[i].data.fd);
				std::cerr << "Webserv: epoll_wait bad event returned" << '\n';
			}
			else if (this->isSock(this->ep[i].data.fd) == true)
			{
				ft::Socket	client;
				socklen_t	len = sizeof(sockaddr_in);
				client.fd = accept(this->ep[i].data.fd, &client.addr, len);
				if (client.fd == -1)
				{
					if (errno != EAGAIN && errno != EWOULDBLOCK)
						throw std::system_error(errno, "System error: accept failed");
				}
				else
				{
					client.setNonBlock();
					client.addToEpoll(this->ep.fd);
					this->servers.push_back(client);
				}
			}
			else
			{
				int byte = 0;
				char buff[BUFFSIZE + 1];
				memset(buff, '\0', BUFFSIZE);
				byte = recv(this->ep.ev[i].data.fd, buff, BUFFSIZE, MSG_DONTWAIT);
				if (byte > 0)
					buff[byte] = '\0';
				else
					this->removeSock(this->ep.ev[i].data.fd);
			}
		}	
	}
}

/////////////////////////////
// Exceptions              //
/////////////////////////////

}