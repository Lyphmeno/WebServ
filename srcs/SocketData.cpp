/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketData.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 18:28:32 by avarnier          #+#    #+#             */
/*   Updated: 2023/05/02 12:19:25 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/SocketData.hpp"

namespace ft {

SocketData::SocketData()
: step(0), bodysize(0), req(), rep()
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

}