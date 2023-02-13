/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 01:00:44 by avarnier          #+#    #+#             */
/*   Updated: 2023/02/13 01:43:22 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <unistd.h>
#include <fcntl.h>
#include <stdexcept>
#include <sys/epoll.h>

#include "Server.hpp"

namespace ft {

class Socket
{
	public:
		Socket(int epfd);
		Socket(const Socket &x);
		Socket	&operator=(const Socket &x);
		~Socket();

	private:
		Socket();
		void	init();

	public:
		int			fd;
		ft::Server	conf;
};

}