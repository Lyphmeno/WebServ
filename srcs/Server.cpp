/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlevi <hlevi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 10:22:03 by hlevi             #+#    #+#             */
/*   Updated: 2023/03/02 12:13:34 by hlevi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Server.hpp"
#include <sys/socket.h>

namespace ft {
/////////////////////////////
// Coplien                 //
/////////////////////////////
Server::Server()
{
	this->addr.sin_family = AF_INET;
	this->max_client_body_size = -1;
	for (int i = 0; i <= 8; i++)
		this->id.push_back(false);
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
		this->id = rhs.id;
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
int	Server::getLoc(std::string path)
{
	if (this->location.empty())
		return (-2);
	for (std::vector<Location>::const_iterator it = this->location.begin(); it != this->location.end(); it++) {
		if (it->path == path)
			return (it - this->location.begin());
	}
	return (-1);
}

bool	Server::getAutoIndex(std::string path)
{
	if (this->getLoc(path) == -1) {
		if (!this->auto_index.compare("on"))
			return (true);
		else
			return (false);
	}
	if (!this->location.at(this->getLoc(path)).auto_index.compare("on"))
		return (true);
	return (false);
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
