/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:02:18 by avarnier          #+#    #+#             */
/*   Updated: 2023/02/24 09:14:29 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/SocketManager.hpp"

namespace ft {

////////////////////////////////////////////////////////////////////////////////
//                                constructor                                 //
////////////////////////////////////////////////////////////////////////////////

SocketManager::SocketManager()
{
	this->epfd = epoll_create(1);
	if (this->epfd == -1)
		throw std::runtime_error("Runtime error: Epoll creation failed");
}

SocketManager::~SocketManager()
{
	if (this->epfd > -1)
	{
		::close(this->epfd);
		this->epfd = -1;
	}
	while (this->servers.size() > 0)
		this->closeServer(this->servers[0].fd);
}

////////////////////////////////////////////////////////////////////////////////
//                                  methods                                   //
////////////////////////////////////////////////////////////////////////////////

void	SocketManager::addServer(const sockaddr_in &addr)
{
	Socket	sock;
	sock.addr = addr;
	sock.fd = socket(AF_INET, SOCK_STREAM, 0);
	if (sock.fd == -1)
		throw std::runtime_error("Runtime error: Socket creation failed");
	
	this->setNoBlock(sock.fd);
	
	if (bind(sock.fd, reinterpret_cast<sockaddr *>(&sock.addr), sizeof(sock.addr)) == -1)
		throw std::runtime_error("Runtime error: Can't bind socket");
	
	if (listen(sock.fd, MAXQUEU) == -1)
		throw std::runtime_error("Runtime error: Can't listen socket");
	
	this->addEp(sock.fd);
	this->servers.push_back(sock);
	this->clients.insert
	(std::map<int, std::vector<Socket> >::value_type(sock.fd, std::vector<Socket>()));
}

void	SocketManager::addClient(const int &sfd, const Socket &sock)
{
	this->setNoBlock(sock.fd);
	this->addEp(sock.fd);
	this->clients[sfd].push_back(sock);
}

void	SocketManager::addEp(const int &fd)
{
	epoll_event	ev;
	ev.events = EPOLLIN;
	ev.data.fd = fd;
	if (epoll_ctl(this->epfd, EPOLL_CTL_ADD, fd, &ev) == -1)
		throw std::runtime_error("Runtime error: Can't add socket to epoll");
}

void	SocketManager::setNoBlock(const int &fd)
{
	int flags = fcntl(fd, F_GETFL);

	if (flags == -1)
		throw std::runtime_error("Runtime error: Can't get socket flags");

	if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1)
		throw std::runtime_error("Runtime error: Can't set socket flags");
}

bool	SocketManager::isServer(const int &fd)
{
	for (std::vector<Socket>::const_iterator it = this->servers.begin();
	it != this->servers.end(); it++)
	{
		if (it->fd == fd)
			return (true);
	}
	return (false);
}

void	SocketManager::closeServer(const int &fd)
{
	if (fd == -1)
		return ;
	for (std::map<int, std::vector<Socket> >::iterator mit = this->clients.begin();
	mit != this->clients.end(); mit++)
	{
		if (mit->first == fd)
		{
			for (std::vector<Socket>::iterator vit = mit->second.begin();
			vit != mit->second.end(); vit++)
				::close(vit->fd);
			mit->second.clear();
			this->clients.erase(mit);
			break;
		}
	}
	for (std::vector<Socket>::iterator it = this->servers.begin();
	it != this->servers.end(); it++)
	{
		if (it->fd == fd)
		{
			::close(fd);
			this->servers.erase(it);
			break;
		}
	}
}

void	SocketManager::close(const int &fd)
{
	if (fd == -1)
		return ;
	if (this->isServer(fd) == true)
		this->closeServer(fd);
	else
	{
		for (std::map<int, std::vector<Socket> >::iterator mit = this->clients.begin();
		mit != this->clients.end(); mit++)
		{
			for (std::vector<Socket>::iterator vit = mit->second.begin();
			vit != mit->second.end(); vit++)
			{
				if (vit->fd == fd)
				{
					::close(fd);
					mit->second.erase(vit);
					return ;
				}
			}
		}
	}
}

}