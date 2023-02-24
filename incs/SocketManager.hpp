/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:02:22 by avarnier          #+#    #+#             */
/*   Updated: 2023/02/24 09:23:58 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include <vector>
#include <stdexcept>
#include <sys/epoll.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include "../incs/Socket.hpp"

#define MAXEVENTS 10
#define MAXQUEU 10

namespace ft {

class SocketManager
{
public:
	SocketManager();
	~SocketManager();

	void	addServer(const sockaddr_in &addr);
	void	addClient(const int &sfd, const Socket &sock);
	void	addEp(const int &fd);
	void	setNoBlock(const int &fd);
	bool	isServer(const int &fd);
	void	close(const int &fd);

private:
	SocketManager(const SocketManager &x);
	SocketManager	&operator=(const SocketManager &x);
	void	closeServer(const int &fd);
	void	closeClient(const int &fd);

public:
	int									epfd;
	epoll_event							epev[MAXEVENTS];
	std::vector<Socket>					servers;
	std::map<int, std::vector<Socket> >	clients;
};

}