/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:35:33 by hlevi             #+#    #+#             */
/*   Updated: 2023/03/02 12:28:25 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "../incs/Parser.hpp"
#include "../incs/Socket.hpp"
#include "../incs/Server.hpp"
#include "../incs/SocketManager.hpp"

#define MAXBUFF 1

namespace ft {

class Webserv
{
public:
	Webserv(std::string);
	~Webserv();

	void	run();

private:
	Webserv();
	Webserv(const Webserv &x);
	Webserv	&operator=(const Webserv &x);

public:
	SocketManager			manager;
	Parser					parser;
	std::vector<ft::Server>	servers;
};

}
