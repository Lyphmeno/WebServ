/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:02:18 by avarnier          #+#    #+#             */
/*   Updated: 2023/03/02 16:23:20 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/SocketManager.hpp"
#include <iostream>

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
	while (this->servers.size() > 0)
		this->close(this->servers.begin()->first);
	if (this->epfd > -1)
	{
		::close(this->epfd);
		this->epfd = -1;
	}
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
	this->servers.insert(sock_val(sock.fd, sock));
	this->clients.insert(srv_val(sock.fd, sock_type()));
}

void	SocketManager::addClient(const int &sfd, const Socket &sock)
{
	this->setNoBlock(sock.fd);
	this->addEp(sock.fd);
	this->clients.find(sfd)->second.insert(sock_val(sock.fd, sock));
	this->linker.insert(link_val(sock.fd, sfd));
}

void	SocketManager::addEp(const int &fd) const
{
	epoll_event	ev;
	ev.events = EPOLLIN;
	ev.data.fd = fd;
	if (epoll_ctl(this->epfd, EPOLL_CTL_ADD, fd, &ev) == -1)
		throw std::runtime_error("Runtime error: Can't add socket to epoll");
}

void	SocketManager::setNoBlock(const int &fd) const
{
	int flags = fcntl(fd, F_GETFL);

	if (flags == -1)
		throw std::runtime_error("Runtime error: Can't get socket flags");

	if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1)
		throw std::runtime_error("Runtime error: Can't set socket flags");
}

bool	SocketManager::isServer(const int &fd) const
{
	if (this->servers.find(fd) != this->servers.end())
		return (true);
	return (false);
}

void	SocketManager::getData(const int &fd, const char *s)
{
	sock_it sock = this->clients.find((this->linker.find(fd)->second))->second.find(fd);
	std::string	data(s);

	if (data.find("\r\n") != data.npos)
	{
		sock->second.hlen += data.find("\r\n") + 1;
		sock->second.blen += data.size() - (data.find("\r\n") + 1);
	}
	else if (sock->second.request.find("\r\n") != sock->second.request.find("\r\n"))
		sock->second.blen += data.size();
	else
		sock->second.hlen += data.size();

	//if (sock->second.hlen > MAXHEADER)
	//	sock->second.response = 431;
	//if (sock->second.blen > this->getMaxBody())
	// 	sock->second.response = 413;
}

void	SocketManager::close(const int &fd)
{
	if (this->isServer(fd) == true)
	{
		srv_it sit = this->clients.find(fd);
		for (sock_it it = sit->second.begin(); it != sit->second.end(); it++)
		{
			this->linker.erase(it->second.fd);
			::close(it->second.fd);
		}
		::close(fd);
		this->clients.erase(fd);
		this->servers.erase(fd);
	}
	else
	{
		::close(fd);
		this->clients.find((this->linker.find(fd)->second))->second.erase(fd);
		this->linker.erase(fd);
	}
}

}
