/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 01:00:44 by avarnier          #+#    #+#             */
/*   Updated: 2023/02/13 19:30:44 by avarnier         ###   ########.fr       */
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
		Socket(const ft::EpSocket &epfd, const int &fd);
		Socket(const ft::EpSocket &epfd, const sockaddr_in &addr);
		Socket(const Socket &x);
		Socket	&operator=(const Socket &x);
		~Socket();

	private:
		Socket();
		void	init();
		void	addTo(const ft::EpSocket &epfd) const;

	public:
		int			fd;
		sockaddr_in	addr;
};

}