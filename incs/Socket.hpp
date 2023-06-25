/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:04:19 by avarnier          #+#    #+#             */
/*   Updated: 2023/05/07 17:05:09 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include "../incs/SocketData.hpp"

namespace ft {

struct Socket
{
public:
	Socket();
	Socket(const Socket &x);
	Socket	&operator=(const Socket &x);
	~Socket();

public:
	int			fd;
	sockaddr_in	addr;
	SocketData	data;
	timeval		time;
	Server		conf;
};

}