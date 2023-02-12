/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 13:38:39 by avarnier          #+#    #+#             */
/*   Updated: 2023/02/12 00:19:34 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>

#include "Server.hpp"

#define MAXEV 10

namespace ft {

class Webserv
{
private:
	int							epfd;
	epoll_event					epev[MAXEV];
	std::vector<int>			sockets;
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
	// Exceptions //

private:
	//Webserv initialization
	void	epinit();
	int	sockinit(sockaddr_in addr);

	//Webserv clear
	void	close();
};
}
