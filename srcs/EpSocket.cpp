/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EpSocket.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:24:43 by avarnier          #+#    #+#             */
/*   Updated: 2023/02/14 15:39:27 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/EpSocket.hpp"

namespace ft {

/////////////////////////////
// Coplien                 //
/////////////////////////////

EpSocket::EpSocket() try : fd(-1), ev()
{
	this->init();
}
catch (std::exception &e)
{
	std::cout << e.what() << '\n';
	::close(this->fd);
}

EpSocket::EpSocket(const EpSocket &x) try : fd(x.fd), ev(x.ev)
{
}
catch (std::exception &e)
{
	std::cout << e.what() << '\n';
	::close(this->fd);
}

EpSocket	&EpSocket::operator=(const EpSocket &x)
{
	if (this != &x)
	{
		this->fd = x.fd;
		this->ev = x.ev;
	}
	return (*this);
}

EpSocket::~EpSocket()
{
	::close(this->fd);
}

/////////////////////////////
// Methods                 //
/////////////////////////////

void	EpSocket::init()
{
	this->fd = epoll_create(1);
	if (this->fd == -1)
		throw std::runtime_error("Runtime error: Epoll creation failed");
}

}