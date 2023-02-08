/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:58:13 by avarnier          #+#    #+#             */
/*   Updated: 2023/02/09 00:46:42 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Server.hpp"

namespace ft {

////////////////////////////////////////////////////////////////////////////////
//                             server constructor                             //
////////////////////////////////////////////////////////////////////////////////

Server::Server() : sock(), addr()
{
}

Server::Server(const Server &x) : sock(x.sock), addr(x.addr)
{
}

////////////////////////////////////////////////////////////////////////////////
//                        server assignement operator                         //
////////////////////////////////////////////////////////////////////////////////

Server	&Server::operator=(const Server &x)
{
	if (this != &x)
	{
	}
	return (*this);
}

////////////////////////////////////////////////////////////////////////////////
//                             server destructor                              //
////////////////////////////////////////////////////////////////////////////////

Server::~Server()
{
}

////////////////////////////////////////////////////////////////////////////////
//                           server initialization                            //
////////////////////////////////////////////////////////////////////////////////

int	Server::sockinit()
{
	this->sock = socket(AF_INET, SOCK_STREAM, 0);
	if (this->sock == -1)
	{
		this->clear();
		return (-1);
	}

	int flags = fcntl(this->sock, F_GETFL);
	if (flags == -1)
	{
		this->clear();
		return (-1);
	}

	if (fcntl(this->sock, F_SETFL, flags | O_NONBLOCK) == -1)
	{
		this->clear();
		return (-1);
	}

	if (bind(this->sock, (sockaddr *)&addr, sizeof(addr)) == -1)
	{
		this->clear();
		return (-1);
	}

	if (listen(sock, 128) == -1)
	{
		this->clear();
		return (-1);
	}

	return (this->sock);
}

////////////////////////////////////////////////////////////////////////////////
//                                server clear                                //
////////////////////////////////////////////////////////////////////////////////

void	Server::clear()
{
	close(this->sock);
	this->sock = -1;
}
}