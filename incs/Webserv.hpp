/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:35:33 by hlevi             #+#    #+#             */
/*   Updated: 2023/02/21 17:32:12 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "../incs/Parser.hpp"
#include "../incs/Socket.hpp"
#include "../incs/Server.hpp"
#include "../incs/SocketManager.hpp"

#define MAXBUFF 1024

namespace ft {

class Webserv
{
public:
	Webserv();
	~Webserv();

	void	run();

private:
	Webserv(const Webserv &x);
	Webserv	&operator=(const Webserv &x);

public:
	SocketManager			manager;
	Parser					parser;
	std::vector<ft::Server>	servers;
};

}
