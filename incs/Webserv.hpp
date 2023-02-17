/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlevi <hlevi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:35:33 by hlevi             #+#    #+#             */
/*   Updated: 2023/02/17 14:44:16 by hlevi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>

#include "Parser.hpp"
#include "Socket.hpp"
#include "epSocket.hpp"
#include "Server.hpp"

#define MAXEV 100

namespace ft {
class Webserv
{
public:
	Webserv();
	Webserv(const Webserv &x);
	Webserv	&operator=(const Webserv &x);
	~Webserv();

public:
	epSocket				ep;
	Parser					parser;
	std::vector<ft::Socket>	sockets;
	std::vector<ft::Server>	servers;
};
}
