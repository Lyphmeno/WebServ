/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:41:02 by hlevi             #+#    #+#             */
/*   Updated: 2023/03/20 16:48:54 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Webserv.hpp"

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
				Socket		sock(this->manager.findConfig(fd));
				socklen_t	len = 0;
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
					this->manager.close(fd);
			}
		}
	}
	std::cerr << "end\n";
}

}
