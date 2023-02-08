/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlevi <hlevi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 13:38:39 by avarnier          #+#    #+#             */
/*   Updated: 2023/02/08 15:04:16 by hlevi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <vector>
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
	int	epollinit();
//Webserv variables
private:
	int					epollfd;
	std::vector<Server>	servers;
};
}
