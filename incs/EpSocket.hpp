/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EpSocket.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:04:34 by avarnier          #+#    #+#             */
/*   Updated: 2023/02/13 17:44:47 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <sys/epoll.h>
#include <netinet/ip.h>
#include <stdexcept>
#include <unistd.h>
#include <iostream>

namespace ft {

class EpSocket
{
	public:
		EpSocket();
		EpSocket(const EpSocket &x);
		EpSocket	&operator=(const EpSocket &x);
		~EpSocket();

	private:
		void	init();

	public:
		int							fd;
		std::vector<epoll_event>	ev;
};

}