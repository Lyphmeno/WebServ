/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlevi <hlevi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:37:50 by hlevi             #+#    #+#             */
/*   Updated: 2023/02/06 15:56:13 by hlevi            ###   ########.fr       */
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