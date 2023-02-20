/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlevi <hlevi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:35:33 by hlevi             #+#    #+#             */
/*   Updated: 2023/02/20 14:07:37 by hlevi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <sys/epoll.h>

#include "../incs/Parser.hpp"
#include "../incs/Socket.hpp"
#include "../incs/Server.hpp"
#include "../incs/SocketManager.hpp"

namespace ft {
class Webserv
{
public:
	Webserv(std::string);
	~Webserv();

private:
	Webserv();
	Webserv(const Webserv &x);
	Webserv	&operator=(const Webserv &x);

public:
	SocketManager		manager;
	Parser					parser;
	std::vector<ft::Socket>	sockets;
	std::vector<ft::Server>	servers;
};
}
