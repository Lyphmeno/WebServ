/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlevi <hlevi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 12:40:48 by hlevi             #+#    #+#             */
/*   Updated: 2023/02/24 10:17:59 by hlevi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../incs/Location.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>

namespace ft {
class Server
{
public:
	std::vector<Location>		location;
	std::vector<std::string>	server_names;
	std::vector<std::string>	allow_methods;
	std::vector<std::string>	index;
	std::vector<std::string>	err_page;
	std::string					listen;
	std::string					root;
    std::string					auto_index;
    std::string					cgi_dir;
	int							max_client_body_size;
	// avarnier
	sockaddr_in					addr;
public:
	// Coplien //
	Server();
	Server(const Server &cpy);
	~Server();
	Server &operator=(const Server &rhs);
	// Assignation contructors //
	// Operators //
	// Getters //
	int		getId(std::string);
	// Setters //
	// Methods //
	// Exceptions //
};
}
