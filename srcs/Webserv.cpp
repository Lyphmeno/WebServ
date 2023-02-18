#include "../incs/Webserv.hpp"

namespace ft {

////////////////////////////////////////////////////////////////////////////////
//                                constructor                                 //
////////////////////////////////////////////////////////////////////////////////

Webserv::Webserv()
{
	// --> parsing
	for (std::vector<Server>::const_iterator it = this->servers.begin();
	it != this->servers.end(); it++)
	{
		this->manager.addServer(it->addr);
	}
}

Webserv::Webserv(const Webserv &x) : manager(x.manager), servers(x.servers)
{
}

Webserv	&Webserv::operator=(const Webserv &x)
{
	if (this == &x)
	{
		this->manager = x.manager;
		this->servers = x.servers;
	}
	return (*this);
}

Webserv::~Webserv()
{
}

////////////////////////////////////////////////////////////////////////////////
//                                  methods                                   //
////////////////////////////////////////////////////////////////////////////////

}