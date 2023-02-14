/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 13:38:39 by avarnier          #+#    #+#             */
/*   Updated: 2023/02/14 20:35:32 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "Server.hpp"
#include "Socket.hpp"
#include "EpSocket.hpp"
#incldue "defines.hpp"

#define MAXEV 10

namespace ft {

class Webserv
{
private:
	ft::EpSocket				ep;
	std::vector<ft::Socket>		sockets;
	std::vector<ft::Server>		servers;

public:
	// Coplien //
	Webserv();
	Webserv(const Webserv &x);
	Webserv	&operator=(const Webserv &x);
	~Webserv();
	
	// Assignation contructors //
	// Operators //
	// Getters //
	// Setters //

	// Methods //
	void	run();

	// Exceptions //

private:
	// Methods //
	void	init();
	bool	isSock(int fd);
	void	removeSock(int fd);
};
}