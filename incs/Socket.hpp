/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 12:30:41 by avarnier          #+#    #+#             */
/*   Updated: 2023/02/16 12:40:41 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>

namespace ft {

class Socket
{
	public:
		Socket();
		Socket(const Socket &x);
		Socket	&operator=(const Socket &x);
		~Socket();

		void	open();
		void	close();
		void	set();
		void	add();
	
	public:
		int			fd;
		sockaddr_in	addr;
};

}