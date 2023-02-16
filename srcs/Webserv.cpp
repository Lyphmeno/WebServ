#include "../incs/Webserv.hpp"

namespace ft {

////////////////////////////////////////////////////////////////////////////////
//                                constructor                                 //
////////////////////////////////////////////////////////////////////////////////

Webserv::Webserv()
{
	//Parsing
	ep.open();
	for (std::vector<Server>::const_iterator it; it != this->servers.end(); it++)
	{
		Socket	s;
		s.open();
		s.set(it->addr);
		ep.add(s.fd);
		this->sockets.push_back(s);
	}
}

Webserv::Webserv(const Webserv &x) : epfd(x.epfd)
{
}

Webserv &Webserv::operator=(const Webserv &x)
{
	if (this != &x)
		this->epfd = x.epfd;
	return (*this);
}

Webserv::~Webserv()
{
}

////////////////////////////////////////////////////////////////////////////////
//                                  methods                                   //
////////////////////////////////////////////////////////////////////////////////

}