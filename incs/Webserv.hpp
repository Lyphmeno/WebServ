/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlevi <hlevi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:37:50 by hlevi             #+#    #+#             */
/*   Updated: 2023/02/06 17:23:52 by hlevi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft {

#include <iostream>
#include <string>
#include <vector>

class Webserv
{
private:
	std::vector<ft::Server>		_servers;
	int							_inbrackets; // Tells me if i am inside a brack or not from 0 (not inside) to x (1 = im in a server bracket and more is else)
	std::string     			_filename;
    std::fstream    			_file;
    std::string     			_line;

public:
	// Coplien //
	Webserv();
	Webserv(const Webserv &cpy);
	~Webserv();
	Webserv &operator=(const Webserv &rhs);
	// Assignation contructors //
	// Operators //
	// Getters //
	// Setters //
	// Methods //
	// Exceptions //
};
}