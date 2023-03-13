/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketData.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 18:28:32 by avarnier          #+#    #+#             */
/*   Updated: 2023/03/07 18:35:02 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/SocketData.hpp"

namespace ft {

SocketData::SocketData() : content(), body(false), bytes(0)
{
}

SocketData::SocketData(const SocketData &x) : content(x.content), body(x.body), bytes(x.bytes)
{
}

SocketData	&SocketData::operator=(const SocketData &x)
{
	if (this != &x)
	{
		this->content = x.content;
		this->body = x.body;
		this->bytes = x.bytes;
	}
	return (*this);
}

SocketData::~SocketData()
{
}

}