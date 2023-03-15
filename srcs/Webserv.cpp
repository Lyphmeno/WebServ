/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:41:02 by hlevi             #+#    #+#             */
/*   Updated: 2023/03/07 19:06:22 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Webserv.hpp"

namespace ft {

////////////////////////////////////////////////////////////////////////////////
//                                constructor                                 //
////////////////////////////////////////////////////////////////////////////////

Webserv::Webserv(std::string filename)
{
	this->parser.parsing(filename, this->servers);
	Request myRequest(this->servers);
	myRequest.server_start();
	// for (std::vector<Server>::const_iterator it = this->servers.begin();
	// it != this->servers.end(); it++)
	// {
	// 	this->manager.addServer(it->addr);
	// }

}

Webserv::~Webserv()
{
}

////////////////////////////////////////////////////////////////////////////////
//                                  methods                                   //
////////////////////////////////////////////////////////////////////////////////

void	Webserv::run()
{
	for (;;)
	{
		int n = epoll_wait(this->manager.epfd, this->manager.epev, MAXEVENTS, -1);
		if (n == -1)
			throw std::runtime_error("Runtime error: epoll_wait failed");
		for (int i = 0; i < n; i++)
		{
			int fd = this->manager.epev[i].data.fd;
			uint32_t event = this->manager.epev[i].events;
			if ((event & EPOLLERR) || (event & EPOLLHUP) || (!(event & EPOLLIN)))
				this->manager.close(fd);
			
			if (this->manager.isServer(fd) == true)
			{
				Socket		sock;
				socklen_t	len;
				sock.fd = accept(fd,
				reinterpret_cast<sockaddr *>(&sock.addr), &len);
				if (sock.fd != -1)
					this->manager.addClient(fd, sock);
			}
			else
			{
				char buff[MAXBUFF + 1];
				ssize_t bytes = recv(fd, buff, MAXBUFF, 0);
				if (bytes > 0)
				{
					buff[bytes] = '\0';
					this->manager.getData(fd, buff);
				}
				else
				{
					this->manager.close(fd);
					std::cout << "close connection" << '\n';
				}
			}
		}
	}
}

 }
