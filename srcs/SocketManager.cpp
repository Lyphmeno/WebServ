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

SocketManager::SocketManager(const SocketManager &x)
	: epfd(x.epfd),
	  servers(x.servers),
	  clients(x.clients)
{
}

SocketManager	&SocketManager::operator=(const SocketManager &x)
{
	if (this != &x)
	{
		this->epfd = x.epfd;
		this->servers = x.servers;
		this->clients = x.clients;
	}
	return (*this);
}

SocketManager::~SocketManager()
{
	this->close();
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
}

void	SocketManager::setNoBlock(const int &fd)
{
	int flags = fcntl(fd, F_GETFL);

	if (flags == -1)
		throw std::runtime_error("Runtime error: Can't get socket flags");

	if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1)
		throw std::runtime_error("Runtime error: Can't set socket flags");
}

void	SocketManager::addEp(const int &fd)
{
	epoll_event	ev;
	ev.events = EPOLLIN | EPOLLET;
	if (epoll_ctl(this->epfd, EPOLL_CTL_ADD, fd, &ev) == -1)
		throw std::runtime_error("Runtime error: Can't add socket to epoll");
}

void	SocketManager::close()
{
	if (this->epfd > -1)
		::close(this->epfd);
	for (std::vector<Socket>::const_iterator it = this->servers.begin();
	it != this->servers.end(); it++)
	{
		if (it->fd > -1)
			::close(it->fd);
	}
	for (std::vector<Socket>::const_iterator it = this->clients.begin();
	it != this->clients.end(); it++)
	{
		if (it->fd > -1)
			::close(it->fd);
	}
}

}