/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 13:08:45 by avarnier          #+#    #+#             */
/*   Updated: 2023/02/07 15:38:51 by avarnier         ###   ########.fr       */
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

#include "location.hpp"

////////////////////////////////////////////////////////////////////////////////
//                                   server                                   //
////////////////////////////////////////////////////////////////////////////////

class Server
{
//server methods
public:
	//Server constructor
	Server();
	Server(const Server &x);

	//Server assignement operators
	Server	&operator=(const Server &x);

	//Server destructor
	~Server();

	//Server initialization
	void	socket_init();

//Server variables
public:
	int	socket;
};
}