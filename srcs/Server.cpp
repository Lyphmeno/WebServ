/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 10:22:03 by hlevi             #+#    #+#             */
/*   Updated: 2023/03/20 17:07:34 by avarnier         ###   ########.fr       */
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

int	Server::getMethods(std::string path, std::string method)
{
	if (this->getLoc(path) == -1) {
		for (std::vector<std::string>::const_iterator it = this->allow_methods.begin(); it != this->allow_methods.end(); it++)
			if (!(*it).compare(method))
				return (1);
		return (0);
	}
	for (std::vector<std::string>::const_iterator it = this->allow_methods.begin(); it != this->allow_methods.end(); it++)
		if (!(*it).compare(method))
			return (1);
	for (std::vector<std::string>::const_iterator it = this->location.at(this->getLoc(path)).allow_methods.begin(); it != this->location.at(this->getLoc(path)).allow_methods.end(); it++)
		if (!(*it).compare(method))
			return (1);
	return (0);
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

std::string	Server::getRoot(std::string path)
{
	if (this->getLoc(path) < 0)
		return (this->root);
	return (this->location.at(this->getLoc(path)).root);
}

std::vector<std::string>	Server::getIndex(std::string path)
{
	if (this->getLoc(path) == -1) {
		if (!this->index.empty())
			return (this->index);
		else
			return (std::vector<std::string>());
	}
	if (!this->location.at(this->getLoc(path)).index.empty())
		return (this->location.at(this->getLoc(path)).index);
	return (std::vector<std::string>());
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
