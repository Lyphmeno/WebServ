/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 13:08:45 by avarnier          #+#    #+#             */
/*   Updated: 2023/02/17 14:35:49 by hlevi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include <vector>
#include "../incs/Location.hpp"

#include "Location.hpp"

namespace ft {
struct  Server
{
	// hlevi
	std::vector<std::string>	server_names;
	std::string					listen;
	std::string					root;
    std::string					err_page;
    std::string					index;
    std::string					auto_index;
    std::string					max_client_body_size;
    std::string					cgi_ext;
	std::vector<Location>		location;
	// avarnier
	sockaddr_in	addr;
};
}
