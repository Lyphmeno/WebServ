/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 13:38:39 by avarnier          #+#    #+#             */
/*   Updated: 2023/02/10 13:57:13 by hlevi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <sys/epoll.h>

#include "../incs/Server.hpp"

namespace ft {

class Webserv
{
private:
	int							epfd;
	std::vector<epoll_event>	epdata;
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
};
}
