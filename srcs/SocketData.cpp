/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketData.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:12:04 by avarnier          #+#    #+#             */
/*   Updated: 2023/03/03 20:10:00 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/SocketData.hpp"

namespace ft {

////////////////////////////////////////////////////////////////////////////////
//                                constructor                                 //
////////////////////////////////////////////////////////////////////////////////

SocketData::SocketData()
	:	post(false),
		header(false),
		hlen(0),
		blen(0),
		request(),
		response()
{
}

SocketData::SocketData(const SocketData &x)
	:	post(x.post),
		header(x.header),
		hlen(x.hlen),
		blen(x.blen),
		request(x.request),
		response(x.response)
{
}

SocketData	&SocketData::operator=(const SocketData &x)
{
	if (this == &x)
	{
		this->post = x.post;
		this->header = x.header;
		this->hlen = x.hlen;
		this->blen = x.blen;
		this->request = x.request;
		this->response = x.response;
	}
	return (*this);
}

SocketData::~SocketData()
{
}

}