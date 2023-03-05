/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:02:22 by avarnier          #+#    #+#             */
/*   Updated: 2023/03/04 02:05:02 by avarnier         ###   ########.fr       */
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
#include "../incs/Request.hpp"

#define MAXEVENTS 128
#define MAXQUEU 128
#define MAXHEADER 8192
#define MAXBUFF 33 // always > 26

#define NOTFD 0
#define CLI 1
#define SRV 2

namespace ft {

class SocketManager
{
public:
	typedef std::map<int, Socket>									sock_type;
	typedef	std::map<int, Socket>::iterator							sock_it;
	typedef	std::map<int, Socket>::const_iterator					sock_cit;
	typedef	std::map<int, Socket>::value_type						sock_val;

	typedef std::map<int, std::map<int, Socket> >					srv_type;
	typedef std::map<int, std::map<int, Socket> >::iterator			srv_it;
	typedef std::map<int, std::map<int, Socket> >::const_iterator	srv_cit;
	typedef std::map<int, std::map<int, Socket> >::value_type		srv_val;

	typedef std::map<int, int>										linker_type;
	typedef	std::map<int, int>::iterator							link_it;
	typedef	std::map<int, int>::const_iterator						link_cit;
	typedef	std::map<int, int>::value_type							link_val;

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
	sock_it	findClient(const int &fd);

private:
	SocketManager(const SocketManager &x);
	SocketManager	&operator=(const SocketManager &x);

public:
	int										epfd;
	epoll_event								epev[MAXEVENTS];
	std::map<int, int>						linker;
	std::map<int, Socket>					servers;
	std::map<int, std::map<int, Socket> >	clients;
};

}
