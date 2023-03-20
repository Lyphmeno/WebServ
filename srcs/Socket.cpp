
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:12:16 by avarnier          #+#    #+#             */
/*   Updated: 2023/03/19 17:51:14 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Socket.hpp"

namespace ft {

////////////////////////////////////////////////////////////////////////////////
//                                constructor                                 //
////////////////////////////////////////////////////////////////////////////////

Socket::Socket(const Server &config) : fd(-1), addr(), data(config)
{
}

Socket::Socket(const Socket &x) : fd(x.fd), addr(x.addr), data(x.data)
{
}

Socket &Socket::operator=(const Socket &x)
{
	if (this != &x)
	{
		this->fd = x.fd;
		this->addr = x.addr;
		this->data = x.data;
	}
	return (*this);
}

Socket::~Socket()
{
}

}