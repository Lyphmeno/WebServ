/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 13:08:45 by avarnier          #+#    #+#             */
/*   Updated: 2023/02/13 18:46:02 by hlevi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <netinet/ip.h> //sockaddr_in
#include <string>
#include "../incs/Location.hpp"

namespace ft {

struct Server
{
	// hlevi
	std::string				server_name;
	std::string				listen;
	std::string				root;
    std::string				err_page;
    std::string				index;
    std::string				auto_index;
    std::string				max_client_body_size;
    std::string				cgi_ext;
	std::vector<Location>	location;
	// avarnier
	int			sock;
	sockaddr_in	addr;
};
}
