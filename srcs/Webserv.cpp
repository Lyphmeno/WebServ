/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:41:02 by hlevi             #+#    #+#             */
/*   Updated: 2023/03/04 10:23:16 by hlevi            ###   ########.fr       */
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
	this->request.server_start(this->servers);
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

// void	Webserv::run()
// {
// 	for (;;)
// 	{
// 		int n = epoll_wait(this->manager.epfd, this->manager.epev, MAXEVENTS, -1);
// 		if (n == -1)
// 			throw std::runtime_error("Runtime error: epoll_wait failed");
// 		for (int i = 0; i < n; i++)
// 		{
// 			if ((this->manager.epev[i].events & EPOLLERR)
// 			|| (this->manager.epev[i].events & EPOLLHUP)
// 			|| (!(this->manager.epev[i].events & EPOLLIN)))
// 				this->manager.close(this->manager.epev[i].data.fd);
			
// 			if (this->manager.isServer(this->manager.epev[i].data.fd) == true)
// 			{
// 				Socket		sock;
// 				socklen_t	len;
// 				sock.fd = accept(this->manager.epev[i].data.fd,
// 				reinterpret_cast<sockaddr *>(&sock.addr), &len);
// 				if (sock.fd != -1)
// 					this->manager.addClient(this->manager.epev[i].data.fd, sock);
// 			}
// 			else
// 			{
// 				char buff[MAXBUFF + 1];
// 				ssize_t bytes = recv(this->manager.epev[i].data.fd, buff, MAXBUFF, 0);
// 				if (bytes > 0)
// 				{
// 					buff[bytes] = '\0';
// 					std::cerr << bytes << '\n';
// 					this->manager.getData(this->manager.epev[i].data.fd, buff);
// 				}
// 				else
// 				{
// 					this->manager.close(this->manager.epev[i].data.fd);
// 					std::cout << "close connection" << '\n';
// 				}
// 			}
// 		}
// 	}
// }

 }
