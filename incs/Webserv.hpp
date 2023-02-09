/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 13:38:39 by avarnier          #+#    #+#             */
/*   Updated: 2023/02/09 19:41:23 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>

#include "../incs/Server.hpp"

namespace ft {

class Webserv
{
//Webserv methods
public:
	//Webserv coplien
	Webserv();
	Webserv(const Webserv &x);
	Webserv	&operator=(const Webserv &x);
	~Webserv();

private:
	//Webserv initialization
	int	epinit();
	int	sockinit(Server &serv);

	//Webserv exception
	class	epInitError : public std::exception
	{
		public:
			virtual const char *what() const throw();
	};
	
	class	sockInitError : public std::exception
	{
		public:
			virtual const char *what() const throw();
	};

//Webserv variables
private:
	int							epfd;
	std::vector<ft::Server>		servers;
};

}