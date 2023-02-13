/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 01:00:44 by avarnier          #+#    #+#             */
/*   Updated: 2023/02/13 18:33:49 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <unistd.h>
#include <fcntl.h>
#include <stdexcept>
#include <sys/epoll.h>
#include <netinet/ip.h>
#include <iostream>

namespace ft {

class Socket
{
	public:
		Socket(const int &epfd, const int &fd);
		Socket(const int &epfd, const sockaddr_in &addr);
		Socket(const Socket &x);
		Socket	&operator=(const Socket &x);
		~Socket();

	private:
		Socket();
		void	init(const int &epfd);
		void	addTo(const int &epfd) const;

	public:
		int			fd;
		sockaddr_in	addr;
};

}