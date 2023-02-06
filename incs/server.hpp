/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 13:08:45 by avarnier          #+#    #+#             */
/*   Updated: 2023/02/06 14:50:55 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

namespace ft {

#include <string>
#include <map>
#include <vector>

#include "location.hpp"

////////////////////////////////////////////////////////////////////////////////
//                                   server                                   //
////////////////////////////////////////////////////////////////////////////////

class server
{
//server methods
public:
	//server constructor
	server();
	server(const server &x);

	//server assignement operators
	server	&operator=(const server &x);
	
	//server destructor
	~server();

//server variables
private:
	std::map<std::vector<int>, int>	hosts_ports;
	std::string						name;
	std::string						error_path;
	std::vector<ft::location>		locations;
};
}

#endif