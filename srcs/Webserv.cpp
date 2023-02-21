/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:41:02 by hlevi             #+#    #+#             */
/*   Updated: 2023/02/21 17:38:27 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Webserv.hpp"
namespace ft {

////////////////////////////////////////////////////////////////////////////////
//                                constructor                                 //
////////////////////////////////////////////////////////////////////////////////

Webserv::Webserv()
{
	// --> parsing
	sockaddr_in	a;
	a.sin_family = AF_INET;
	a.sin_addr.s_addr = INADDR_ANY;
	a.sin_port = htons(8080);
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
	int n = epoll_wait(this->manager.epfd, this->manager.epev, MAXEVENTS, -1);
	for (int i = 0; i < n; i++)
	{
		if (this->manager.isServer(this->manager.epev[i].data.fd) == true)
		{
			Socket		sock;
			socklen_t	len;
			sock.fd = accept(this->manager.epev[i].data.fd,
			reinterpret_cast<sockaddr *>(&sock.addr), &len);
			if (sock.fd != -1)
				this->manager.addClient(this->manager.epev[i].data.fd, sock);
		}
		else
		{
			char 	buff[MAXBUFF];
			ssize_t	bytes = recv(this->manager.epev[i].data.fd, buff, MAXBUFF, 0);
			std::cout << "message: " << buff << '\n';
			if (bytes == 0)
				close(this->manager.epev[i].data.fd);
		}
	}
}

}