/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlevi <hlevi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:37:50 by hlevi             #+#    #+#             */
/*   Updated: 2023/02/07 14:49:15 by hlevi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once


#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "../incs/server.hpp"

namespace ft {
class Webserv
{
private:
	//std::vector<ft::Server>		_servers;

public:
//---------------PARSING----------------//
	std::fstream    			_file;
	std::string     			_filename;
    std::string     			_line;
	int							_inbrackets; // 0 (not inside) to x (1 = im in a server bracket and more is else)
//-------------------------------------//

public:
	// Coplien //
	Webserv();
	Webserv(const Webserv &cpy);
	~Webserv();
	Webserv &operator=(const Webserv &rhs);
	// Assignation contructors //
	// Operators //
	// Getters //
	std::fstream&	get_file();
	std::string&	get_line();
	std::string		get_filename();
	int				get_inbrackets();
	// Setters //
	void	set_filename(std::string);
	void	set_line(std::string);
	// Methods //
	int	open_file();
	// Exceptions //
};
}
