/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlevi <hlevi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:17:09 by hlevi             #+#    #+#             */
/*   Updated: 2023/02/07 14:49:37 by hlevi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Webserv.hpp"
#include <fstream>
#include <string>

/////////////////////////////
// Coplien                 //
/////////////////////////////
ft::Webserv::Webserv()
{
	this->_inbrackets = 0;
	this->_filename = "";
	this->_line = "";
}

ft::Webserv::Webserv(const Webserv &cpy)
{
	*this = cpy;
}

ft::Webserv::~Webserv()
{
}

ft::Webserv &ft::Webserv::operator=(const Webserv &rhs)
{
	if (this != &rhs)
	{
		this->_filename = rhs._filename;
		this->_line = rhs._line;
		this->_inbrackets = rhs._inbrackets;
	}
	return (*this);
}
/////////////////////////////
// Assignation contructors //
/////////////////////////////
/////////////////////////////
// Getters                 //
/////////////////////////////
/////////////////////////////
// Setters                 //
/////////////////////////////
/////////////////////////////
// Operators               //
/////////////////////////////
/////////////////////////////
// Methods                 //
/////////////////////////////
int	ft::Webserv::open_file()
{
	this->_file.open(this->_filename.c_str());
	if (!this->_file.is_open())
		return (-1);
	return (0);
}
/////////////////////////////
// Exceptions              //
/////////////////////////////
