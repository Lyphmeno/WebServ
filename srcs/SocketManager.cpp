/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:02:18 by avarnier          #+#    #+#             */
/*   Updated: 2023/03/23 14:09:22 by avarnier         ###   ########.fr       */
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

void	SocketManager::start()
{
	
	for (conf_cit cit = this->config.begin(); cit != this->config.end(); cit++)
		this->addServer(cit);
	

}

void	SocketManager::addServer(const conf_cit &configIt)
{
	Socket	sock(*configIt);
	sock.addr = configIt->addr;
	sock.fd = socket(AF_INET, SOCK_STREAM, 0);

	if (sock.fd == -1)
		throw std::runtime_error("Runtime error: Socket creation failed");
	int on = 1;
	setsockopt(sock.fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &on, sizeof(int));
	this->setNoBlock(sock.fd);

	if (bind(sock.fd, reinterpret_cast<sockaddr *>(&sock.addr), sizeof(sock.addr)) == -1)
	{
		throw std::runtime_error("Runtime error: Can't bind socket");
	}

	if (listen(sock.fd, MAXQUEU) == -1)
		throw std::runtime_error("Runtime error: Can't listen socket");

	this->addEp(sock.fd);
	this->servers.insert(sock_val(sock.fd, sock));
	this->clients.insert(srv_val(sock.fd, sock_type()));
	this->configLinker.insert(link_val(sock.fd, configIt - this->config.begin()));
}

void	SocketManager::addClient(const int &sfd, const Socket &sock)
{
	this->setNoBlock(sock.fd);
	this->addEp(sock.fd);
	this->clients.find(sfd)->second.insert(sock_val(sock.fd, sock));
	this->clientLinker.insert(link_val(sock.fd, sfd));
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

Socket	&SocketManager::findClient(const int &fd)
{
	return (this->clients.find((this->clientLinker.find(fd)->second))->second.find(fd)->second);
}

Server	&SocketManager::findConfig(const int &fd)
{
	if (this->clientLinker.find(fd) == this->clientLinker.end())
		return (this->config.at(this->configLinker.find(fd)->second));
	return (this->config.at(this->configLinker.find(this->clientLinker.find(fd)->second)->second));
}

void	SocketManager::handleHeader(SocketData &data, std::string &buff)
{
	std::string	&header = data.req.rawHeader;
	header += buff;
	size_t pos = header.find("\r\n\r\n");
	if (pos != header.npos)
	{
		buff = header.substr(pos + 4, header.npos);
		header.erase(pos + 4, header.npos);
		data.step = PARSING;
	}
	else
		buff.clear();

	if (data.req.rawHeader.size() > MAXHEADER)
	{
		data.req._code = "431"; //add by abourdar
		data.rep = data.req.requestStarter();
		data.step = SENDING;
	}
}

void	SocketManager::handleBody(SocketData &data, std::string &buff)
{
	if (buff.size() + data.req.rawBody.size() <= data.bodysize)
	{
		data.req.rawBody += buff;
		buff.clear();
	}
	else
	{
		size_t pos = data.bodysize - data.req.rawBody.size();
		data.req.rawBody += buff.substr(0, pos);
		buff.erase(0, pos);
	}
	if (data.req.rawBody.size() == data.bodysize)
	{
		data.rep = data.req.requestStarter();
		data.step = SENDING;
	}
}

void	SocketManager::getData(const int &fd, std::string buff)
{
	Socket &sock = this->findClient(fd);
	SocketData &data = sock.data;
	while (buff.size() > 0)
	{
		if (data.step == HEADER)
			this->handleHeader(data, buff);
		if (data.step == PARSING)
		{
			data.req.parseHeader();
			data.bodysize = data.req.getContentLength();
			if (data.req.getMethod() == "POST" && data.bodysize > 0)
				data.step = BODY;
			else
			{
				data.rep = data.req.requestStarter();
				data.step = SENDING;
			}
		}
		if (data.step == BODY)
			this->handleBody(data, buff);
		if (data.step == SENDING)
		{
			send(sock.fd, data.rep.c_str(), data.rep.size(), 0);
			this->close(sock.fd);
		}
	}
}

void	SocketManager::close(const int &fd)
{
	if (this->isServer(fd) == true)
	{
		srv_it sit = this->clients.find(fd);
		for (sock_it it = sit->second.begin(); it != sit->second.end(); it++)
		{
			this->clientLinker.erase(it->second.fd);
			::close(it->second.fd);
		}
		::close(fd);
		this->clients.erase(fd);
		this->servers.erase(fd);
	}
	else
	{
		::close(fd);
		this->clients.find((this->clientLinker.find(fd)->second))->second.erase(fd);
		this->clientLinker.erase(fd);
	}
}

}