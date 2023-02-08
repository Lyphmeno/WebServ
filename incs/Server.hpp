/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 13:08:45 by avarnier          #+#    #+#             */
/*   Updated: 2023/02/08 19:12:07 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <map>
#include <vector>
#include <string.h>
#include <errno.h>
#include <iostream>
#include <netinet/in.h>

namespace ft {

////////////////////////////////////////////////////////////////////////////////
//                                   Server                                   //
////////////////////////////////////////////////////////////////////////////////

class Server
{
//Server methods
public:
	//Server constructor
	Server();
	Server(const Server &x);
	//Server assignement operators
	Server	&operator=(const Server &x);
	//Server destructor
	~Server();
	//Server initialization
	int	sockinit();
//Server variables
public:
	// hlevi
	std::string	name;
	std::string	error_path;
	// avarnier
	int			sock;
	sockaddr_in	addr;
};
}
