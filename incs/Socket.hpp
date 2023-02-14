/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 01:00:44 by avarnier          #+#    #+#             */
/*   Updated: 2023/02/14 15:58:41 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <unistd.h>
#include <fcntl.h>
#include <stdexcept>
#include <sys/epoll.h>
#include <netinet/ip.h>
#include <iostream>

#include "EpSocket.hpp"

namespace ft {

class Socket
{
	public:
		Socket(const int &epfd, const int &fd);
		Socket(const int &epfd, const sockaddr_in &addr);
		Socket(const Socket &x);
		Socket	&operator=(const Socket &x);
		~Socket();
		
		void	setNonBlock();
		void	addTo(const int &epfd) const;

	private:
		Socket();
		void	init();

	public:
		int			fd;
		sockaddr_in	addr;
};

}