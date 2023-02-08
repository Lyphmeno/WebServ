/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 10:28:20 by avarnier          #+#    #+#             */
/*   Updated: 2023/02/08 10:47:17 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>

#include "Server.hpp"

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
//webserv variables
private:
	int						epollfd;
	std::vector<ft::Server>	servers;
};

}