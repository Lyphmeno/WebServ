/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:02:18 by avarnier          #+#    #+#             */
/*   Updated: 2023/05/05 13:25:58 by avarnier         ###   ########.fr       */
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
	Socket	sock;
	sock.addr = configIt->addr;
	sock.conf = *configIt;
	sock.fd = socket(AF_INET, SOCK_STREAM, 0);

	if (sock.fd == -1)
		throw std::runtime_error("Runtime error: Socket creation failed");
	this->setNoBlock(sock.fd);

	if (bind(sock.fd, reinterpret_cast<sockaddr *>(&sock.addr), sizeof(sock.addr)) == -1)
	{
		std::cerr << configIt->listen << ": Can't bind socket" << '\n';
		::close(sock.fd);
		return ;
	}
	std::cerr << configIt->listen << ": Socket successfully bind" << '\n';

	if (listen(sock.fd, MAXQUEU) == -1)
		throw std::runtime_error("Runtime error: Can't listen socket");

	this->addEp(sock.fd);
	this->servers.insert(sock_val(sock.fd, sock));
	this->clients.insert(srv_val(sock.fd, sock_type()));
}

void	SocketManager::addClient(const int &sfd, Socket &sock)
{
	sock.conf = this->servers.find(sfd)->second.conf;
	sock.data.req._serverParsing = sock.conf;
	if (gettimeofday(&sock.time, NULL) == -1)
		throw std::runtime_error("Runetime error: Can't get socket creation time");
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

std::string	SocketManager::getHostname(const std::string &host)
{
	std::string key = " ";
	std::string	strEnd = ":";
	size_t start = host.find_first_not_of(key);
	size_t end = host.find_first_of(strEnd);
	if (start == host.npos)
		return ("");
	return (host.substr(start, end - start));
}

std::string	SocketManager::getHostport(const std::string &host)
{
	if (host.find(":") == host.npos)
		return ("80");
	std::string key = ":";
	std::string	strEnd = " ";
	size_t start = host.find(key) + key.size();
	size_t end = host.find_first_of(strEnd);
	return (host.substr(start, end - start));
}

std::string	SocketManager::getHost(const std::string &header)
{
	std::string key = "Host:";
	std::string	strEnd = "\r\n";
	size_t start = header.find(key);
	size_t end = header.find(strEnd, start);
	if (start == header.npos || end == header.npos)
		return ("");
	return (header.substr(start + key.size(), end - (start + key.size())));
}

int	SocketManager::getConf(Socket &sock)
{
	std::string host = getHost(sock.data.req.rawHeader);
	if (host.empty() == true)
		return (-1);
	std::string hostname = getHostname(host);
	if (hostname.empty() == true)
		return (-1);
	std::string hostport = getHostport(host);
	if (hostport.empty() == true)
		return (-1);
	for (conf_cit conf = this->config.begin(); conf != this->config.end(); conf++)
	{
		if (conf->port == hostport || hostport.empty() == true)
		{
			for (std::vector<std::string>::const_iterator name = conf->server_names.begin();
			name != conf->server_names.end(); name++)
			{
				if (hostname == "localhost" && *name == "127.0.0.1")
					return (0);
 				if (*name == hostname)
				{
					sock.data.req._serverParsing = *conf;
					return (0);
				}
			}
		}
	}
	return (-1);
}

void	SocketManager::handleHeader(Socket &sock, std::vector<unsigned char> &buff)
{
	SocketData &data = sock.data;
	std::string	&header = data.req.rawHeader;
	size_t oldsize = header.size();
	header.insert(header.end(), buff.begin(), buff.end());
	size_t pos = header.find("\r\n\r\n");

	if (pos != header.npos)
	{
		buff.erase(buff.begin(), buff.begin() + (pos + 4 - oldsize));
		header.erase(pos + 4, header.npos);
		if (getConf(sock) == -1)
		{
			data.req._code = "400";
			data.rep = data.req.requestStarter(sock.fd);
			data.step = SENDING;
		}
		else
			data.step = PARSING;
	}
	else
		buff.clear();

	if (data.req.rawHeader.size() > MAXHEADER)
	{
		data.req._code = "431";
		data.rep = data.req.requestStarter(sock.fd);
		data.step = SENDING;
	}
}

void	SocketManager::handleBody(Socket &sock, std::vector<unsigned char> &buff)
{
	SocketData &data = sock.data;
	if (buff.size() + data.req.rawBody.size() <= data.bodysize)
	{
		data.req.rawBody.insert(data.req.rawBody.end(), buff.begin(), buff.end());
		buff.clear();
	}
	else
	{
		size_t pos = data.bodysize - data.req.rawBody.size();
		data.req.rawBody.insert(data.req.rawBody.end(), buff.begin(), buff.begin() + pos);
		buff.erase(buff.begin(), buff.begin() + pos);
	}
	if (data.req.rawBody.size() == data.bodysize)
	{
		data.rep = data.req.requestStarter(sock.fd);
		data.step = SENDING;
	}
}

void	SocketManager::handleParsing(Socket &sock)
{
	SocketData &data = sock.data;
	data.req.parseHeader();
	data.bodysize = data.req.getContentLength();

	if (data.req.getMethod() == "POST" && data.bodysize > 0)
	{
		if (data.bodysize > data.req._serverParsing.getMCBS(data.req.getUrl()))
		{
			data.req._code = "413";
			data.rep = data.req.requestStarter(sock.fd);
			data.step = SENDING_CLOSE;
		}
		else
			data.step = BODY;	
	}
	else
	{
		data.rep = data.req.requestStarter(sock.fd);
		data.step = SENDING;
	}
}

void	SocketManager::handleSending(Socket &sock)
{
	send(sock.fd, sock.data.rep.c_str(), sock.data.rep.size(), 0);
	if (sock.data.step == SENDING_CLOSE)
		this->close(sock.fd);
	else
	{
		sock.data.step = HEADER;
		sock.data.bodysize = 0;
		sock.data.rep.clear();
		sock.data.req.clear();
		sock.data.req._serverParsing = sock.conf;
	}
}

void	SocketManager::getData(const int &fd, std::vector<unsigned char> &buff)
{
	Socket &sock = this->findClient(fd);
	if (gettimeofday(&sock.time, NULL) == -1)
		throw std::runtime_error("Runtime error: Can't get current time");
	SocketData &data = sock.data;
	while (buff.size() > 0)
	{
		if (data.step == HEADER)
		{
			std::cerr << "[" << fd << "]: header\n";
			this->handleHeader(sock, buff);
		}
		if (data.step == PARSING)
		{
			std::cerr << "[" << fd << "]: parsing\n";
			this->handleParsing(sock);
		}
		if (data.step == BODY)
		{
			std::cerr << "[" << fd << "]: body\n";
			this->handleBody(sock, buff);
		}
		if (data.step == SENDING || data.step == SENDING_CLOSE)
		{
			std::cerr << "[" << fd << "]: sending\n";
			if (data.step == SENDING_CLOSE)
				buff.clear();
			this->handleSending(sock);
		}
	}
}

void	SocketManager::checkTimeout()
{
	timeval				now;
	std::vector<int>	timeoutFd;
	if (gettimeofday(&now, NULL) == -1)
		throw std::runtime_error("Runtime error: Can't get current time");
	for (srv_it srv_it = this->clients.begin(); srv_it != this->clients.end(); srv_it++)
	{
		for (sock_it cli_it = srv_it->second.begin();
		cli_it != srv_it->second.end(); cli_it++)
		{
			if (difftime(now.tv_sec, cli_it->second.time.tv_sec) >= SOCK_TIMEOUT)
				timeoutFd.push_back(cli_it->second.fd);
		}
	}
	while (timeoutFd.empty() == false)
	{
		std::cerr << "[" << timeoutFd[0] << "]" << "socket timeout" << '\n';
		this->close(timeoutFd[0]);
		timeoutFd.erase(timeoutFd.begin());
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