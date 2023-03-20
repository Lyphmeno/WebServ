/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketData.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 18:28:32 by avarnier          #+#    #+#             */
/*   Updated: 2023/03/17 22:43:48 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/SocketData.hpp"

namespace ft {

SocketData::SocketData(const Server &config)
: step(0), bodysize(0), req(config), rep()
{
}

SocketData::SocketData(const SocketData &x)
: step(x.step), bodysize(x.bodysize), req(x.req), rep(x.rep)
{
}

SocketData	&SocketData::operator=(const SocketData &x)
{
	if (this != &x)
	{
		this->step = x.step;
		this->bodysize = x.bodysize;
		this->req = x.req;
		this->rep = x.rep;
	}
	return (*this);
}

SocketData::~SocketData()
{
}

void	SocketData::clear()
{
	this->step = 0;
	this->bodysize = 0;
	this->req.clear();
	this->rep.clear();
}

}