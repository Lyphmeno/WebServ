/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:02:22 by avarnier          #+#    #+#             */
/*   Updated: 2023/05/07 19:26:15 by avarnier         ###   ########.fr       */
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
#include <sys/time.h>
#include <string>
#include "../incs/Socket.hpp"
#include "../incs/Request.hpp"
#include "../incs/Server.hpp"

#define MAXEVENTS 128
#define MAXQUEU 128
#define MAXHEADER 8192
#define MAXBUFF 1024
#define SOCK_TIMEOUT 60

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

	typedef std::map<int, int>										link_type;
	typedef	std::map<int, int>::iterator							link_it;
	typedef	std::map<int, int>::const_iterator						link_cit;
	typedef	std::map<int, int>::value_type							link_val;

	typedef std::vector<Server>										conf_type;
	typedef std::vector<Server>::iterator							conf_it;
	typedef std::vector<Server>::const_iterator						conf_cit;
	typedef std::vector<Server>::value_type							conf_val;

public:
	SocketManager();
	~SocketManager();

	void		start();
	void		addServer(const conf_cit &configIt);
	void		addClient(const int &sfd, Socket &sock);
	void		addEp(const int &fd) const;
	void		setNoBlock(const int &fd) const;
	bool		isServer(const int &fd) const;
	Socket		&findClient(const int &fd);
	Server		&findConfig(const int &fd);
	void		handleHeader(Socket &sock, std::vector<unsigned char> &buff);
	void		handleBody(Socket &sock, std::vector<unsigned char> &buff);
	void		handleParsing(Socket &sock);
	void		handleSending(Socket &sock);
	std::string	getHostport(const std::string &header);
	std::string	getHostname(const std::string &header);
	std::string	getHost(const std::string &header);
	int			getConf(Socket &sock);
	void		getData(const int &fd, std::vector<unsigned char> &buff);
	void		checkTimeout();
	void		eraseClient(const int &fd);
	void		close(const int &fd);

private:
	SocketManager(const SocketManager &x);
	SocketManager	&operator=(const SocketManager &x);

public:
	int			epfd;
	epoll_event	epev[MAXEVENTS];
	link_type	clientLinker;
	sock_type	servers;
	srv_type	clients;
	conf_type	config;
};

}
