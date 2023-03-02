/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:12:16 by avarnier          #+#    #+#             */
/*   Updated: 2023/03/02 20:00:04 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Socket.hpp"

namespace ft {

Socket::Socket()
	:	fd(-1),
		addr(),
		blen(0),
		request(),
		response()
{
}

Socket::Socket(const Socket &x)
	:	fd(x.fd),
		addr(x.addr),
		hlen(x.hlen),
		blen(x.blen),
		request(x.request),
		response(x.response)
{
}

Socket &Socket::operator=(const Socket &x)
{
	if (this != &x)
	{
		this->fd = x.fd;
		this->addr = x.addr;
		this->hlen = x.hlen;
		this->blen = x.blen;
		this->request = x.request;
		this->response = x.response;
	}
	return (*this);
}

Socket::~Socket()
{
}

}
