/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 13:08:45 by avarnier          #+#    #+#             */
/*   Updated: 2023/02/20 19:36:54 by hlevi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include <vector>
#include "../incs/Location.hpp"


namespace ft {
struct  Server
{
	// hlevi
	std::vector<Location>		location;
	std::vector<std::string>	server_names;
	std::vector<std::string>	allow_methods;
	std::vector<std::string>	index;
	std::vector<std::string>	err_page;
	std::string					listen;
	std::string					root;
    std::string					auto_index;
    std::string					max_client_body_size;
    std::string					cgi_dir;
	// avarnier
	sockaddr_in					addr;
};
}
