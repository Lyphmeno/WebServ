#include "../incs/Server.hpp"
#include <sys/socket.h>

namespace ft {
/////////////////////////////
// Coplien                 //
/////////////////////////////
Server::Server()
{
	this->addr.sin_family = AF_INET;
}

Server::Server(const Server &cpy)
{
	*this = cpy;
}

Server::~Server()
{
}

Server &Server::operator=(const Server &rhs)
{
	if (this != &rhs)
	{
		this->location = rhs.location;
		this->server_names = rhs.server_names;
		this->allow_methods = rhs.allow_methods;
		this->addr = rhs.addr;
		this->index = rhs.index;
		this->err_page = rhs.err_page;
		this->listen = rhs.listen;
		this->root = rhs.root;
		this->auto_index = rhs.auto_index;
		this->max_client_body_size = rhs.max_client_body_size;
		this->cgi_dir = rhs.cgi_dir;
	}
	return (*this);
}

/////////////////////////////
// Assignation contructors //
/////////////////////////////
/////////////////////////////
// Getters                 //
/////////////////////////////
int	Server::getId(std::string path)
{
	int	i = 0;
	if (this->location.empty())
		return (-1);
	for (std::vector<Location>::const_iterator it = this->location.begin(); it != this->location.end(); it++) {
		if (it->path == path)
			return (i);
		i++;
	}
	return (-1);
}
/////////////////////////////
// Setters                 //
/////////////////////////////
/////////////////////////////
// Operators               //
/////////////////////////////
/////////////////////////////
// Methods                 //
/////////////////////////////
/////////////////////////////
// Exceptions              //
/////////////////////////////
}
