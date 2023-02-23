/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:41:02 by hlevi             #+#    #+#             */
/*   Updated: 2023/02/23 08:02:40 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Webserv.hpp"
namespace ft {

////////////////////////////////////////////////////////////////////////////////
//                                constructor                                 //
////////////////////////////////////////////////////////////////////////////////

Webserv::Webserv(std::string filename)
{
	try {
		this->parser.parsing(filename, this->servers);
	} catch (std::exception &e) {
		std::cout << "\033[31m" << e.what() << "\033[0m" << "\n";
	}
	/*for (std::vector<Server>::const_iterator it = this->servers.begin();
	it != this->servers.end(); it++)
	{
		this->manager.addServer(it->addr);
	}*/
}

Webserv::~Webserv()
{
}

////////////////////////////////////////////////////////////////////////////////
//                                  methods                                   //
////////////////////////////////////////////////////////////////////////////////

void	Webserv::run()
{
	int n = epoll_wait(this->manager.epfd, this->manager.epev, MAXEVENTS, -1);
	for (int i = 0; i < n; i++)
	{
	}
}

}