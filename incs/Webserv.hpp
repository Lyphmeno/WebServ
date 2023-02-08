/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 13:38:39 by avarnier          #+#    #+#             */
/*   Updated: 2023/02/09 00:47:27 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <vector>
#include <sys/epoll.h>

#include "../incs/Server.hpp"

namespace ft {

////////////////////////////////////////////////////////////////////////////////
//                                  webserv                                   //
////////////////////////////////////////////////////////////////////////////////

class Webserv
{
//Webserv methods
public:
	//Webserv constructor
	Webserv();
	Webserv(const Webserv &x);
	//Webserv assignement operators
	Webserv	&operator=(const Webserv &x);
	//Webserv destructor
	~Webserv();
private:
	int		epinit();
	void	clear();
//Webserv variables
private:
	int							epfd;
	std::vector<epoll_event>	epdata;
	std::vector<ft::Server>		servers;
};
}