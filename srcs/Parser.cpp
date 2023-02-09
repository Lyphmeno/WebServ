/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 12:12:58 by hlevi             #+#    #+#             */
/*   Updated: 2023/02/09 17:47:54 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Parser.hpp"

/////////////////////////////
// Coplien                 //
/////////////////////////////
ft::Parser::Parser()
{
	this->_inbrackets = 0;
	this->_filename = "";
	this->_line = "";
}

ft::Parser::Parser(const Parser &cpy)
{
	*this = cpy;
}

ft::Parser::~Parser()
{
}

ft::Parser &ft::Parser::operator=(const Parser &rhs)
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
int	ft::Parser::open_file()
{
	this->_file.open(this->_filename.c_str());
	if (!this->_file.is_open())
		return (-1);
	return (0);
}

void	ft::Parser::printv()
{
	for (std::vector<std::string>::iterator it = this->_buffer.begin(); it != this->_buffer.end(); it++) {
        std::cout << "| " << *it << " |" << std::endl;;
    }
}
/////////////////////////////
// Exceptions              //
/////////////////////////////
