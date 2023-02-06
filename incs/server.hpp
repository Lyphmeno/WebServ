/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlevi <hlevi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 13:08:45 by avarnier          #+#    #+#             */
/*   Updated: 2023/02/06 15:31:27 by hlevi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft {

#include <string>
#include <map>
#include <vector>

#include "location.hpp"

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

//Server variables
private:
	std::map<int, std::vector<int> >	_ports_hosts;
	std::string							_name;
	std::string							_error_path;
	std::vector<ft::location>			_locations;
};
}

#endif
