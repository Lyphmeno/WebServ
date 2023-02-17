/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlevi <hlevi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:41:02 by hlevi             #+#    #+#             */
/*   Updated: 2023/02/17 14:41:05 by hlevi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Webserv.hpp"
namespace ft {

////////////////////////////////////////////////////////////////////////////////
//                                constructor                                 //
////////////////////////////////////////////////////////////////////////////////

Webserv::Webserv()
{
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

Webserv::Webserv(const Webserv &x) : ep(x.ep)
{
}

Webserv &Webserv::operator=(const Webserv &x)
{
	if (this != &x)
		this->ep = x.ep;
	return (*this);
}

Webserv::~Webserv()
{
}

////////////////////////////////////////////////////////////////////////////////
//                                  methods                                   //
////////////////////////////////////////////////////////////////////////////////

}
