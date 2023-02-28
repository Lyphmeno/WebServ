/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:02:22 by avarnier          #+#    #+#             */
/*   Updated: 2023/02/28 23:45:14 by avarnier         ###   ########.fr       */
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
#define MAXHEADER 8192

namespace ft {

class SocketManager
{
private:
	typedef	std::map<int, Socket>::iterator							srv_it;
	typedef	std::map<int, Socket>::const_iterator					srv_cit;
	typedef	std::map<int, Socket>::value_type						srv_val;
	typedef std::map<int, std::map<int, Socket> >::iterator			scli_it;
	typedef std::map<int, std::map<int, Socket> >::const_iterator	scli_cit;
	typedef std::map<int, std::map<int, Socket> >::value_type		scli_val;
	typedef std::map<int, Socket>::iterator							cli_it;
	typedef std::map<int, Socket>::const_iterator					cli_cit;
	typedef std::map<int, Socket>::value_type						cli_val;

public:
	SocketManager();
	~SocketManager();

	void	addServer(const sockaddr_in &addr);
	void	addClient(const int &sfd, const Socket &sock);
	void	addEp(const int &fd) const;
	void	setNoBlock(const int &fd) const;
	bool	isServer(const int &fd) const;
	void	close(const int &fd);
	void	getData(const int &fd, const char *data);

private:
	SocketManager(const SocketManager &x);
	SocketManager	&operator=(const SocketManager &x);
	void	closeServer(const int &fd);
	void	closeClient(const int &fd);

public:
	int										epfd;
	epoll_event								epev[MAXEVENTS];
	std::map<int, Socket>					servers;
	std::map<int, std::map<int, Socket> >	clients;
};

}