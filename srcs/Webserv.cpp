/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:41:02 by hlevi             #+#    #+#             */
/*   Updated: 2023/05/07 16:03:16 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Webserv.hpp"

extern bool	sig;

namespace ft {

////////////////////////////////////////////////////////////////////////////////
//                                constructor                                 //
////////////////////////////////////////////////////////////////////////////////

Webserv::Webserv(std::string filename)
{
	this->parser.parsing(filename, this->manager.config);
	this->manager.start();
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
		if (this->manager.servers.empty() == true)
			throw std::runtime_error("Closing: No server are running");
		int n = epoll_wait(this->manager.epfd, this->manager.epev, MAXEVENTS, 1);
		if (sig == true)
			throw std::runtime_error("Runtime error: Signal interruption");
		else if (n == -1)
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
				socklen_t	len = 0;
				sock.fd = accept(fd,
				reinterpret_cast<sockaddr *>(&sock.addr), &len);
				if (sock.fd != -1)
					this->manager.addClient(fd, sock);
			}
			else
			{
				std::vector<unsigned char>	buff(MAXBUFF);
				ssize_t bytes = recv(fd, &buff[0], MAXBUFF, 0);
				if (bytes > 0)
				{
					buff.resize(bytes);
					this->manager.getData(fd, buff);
				}
				else
					this->manager.close(fd);
			}
		}
		this->manager.checkTimeout();
	}
}
}
