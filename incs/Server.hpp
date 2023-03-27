/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlevi <hlevi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 12:40:48 by hlevi             #+#    #+#             */
/*   Updated: 2023/03/27 10:55:50 by hlevi            ###   ########.fr       */
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
// #include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// Bool
#define BS_NAME 0
#define BS_METHODS 1
#define BS_INDEX 2
#define BS_ERR 3
#define BS_LISTEN 4
#define BS_ROOT 5
#define BS_AUTOINDEX 6
#define BS_CGI 7
#define BS_MCBS 8

#define BL_METHODS 0
#define BL_INDEX 1
#define BL_ERR 2
#define BL_ROOT 3
#define BL_AUTOINDEX 4
#define BL_CGI 5
#define BL_MCBS 6

namespace ft {
class Server
{
public:
	std::vector<bool>			id;
	std::vector<Location>		location;
	std::vector<std::string>	server_names;
	std::vector<std::string>	allow_methods;
	std::vector<std::string>	index;
	std::vector<std::string>	err_page;
	std::string					listen;
	std::string					root;
    std::string					auto_index;
    std::string					cgi_dir;
	size_t						max_client_body_size;
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
	int							getLoc(std::string);
	int							getMethods(std::string, std::string);
	size_t						getMCBS(std::string);
	bool						getAutoIndex(std::string);
	std::string					getRoot(std::string);
	std::vector<std::string>	getIndex(std::string);
	// Setters //
	// Methods //
	// Exceptions //
};
}
