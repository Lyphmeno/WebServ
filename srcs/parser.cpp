/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlevi <hlevi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 12:12:58 by hlevi             #+#    #+#             */
/*   Updated: 2023/02/08 12:25:50 by hlevi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/parser.hpp"

/////////////////////////////
// Coplien                 //
/////////////////////////////
ft::parser::parser()
{
	this->_inbrackets = 0;
	this->_filename = "";
	this->_line = "";
}

ft::parser::parser(const parser &cpy)
{
	*this = cpy;
}

ft::parser::~parser()
{
}

ft::parser &ft::parser::operator=(const parser &rhs)
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
int	ft::parser::open_file()
{
	this->_file.open(this->_filename.c_str());
	if (!this->_file.is_open())
		return (-1);
	return (0);
}

void	ft::parser::printv()
{
	for (std::vector<std::string>::iterator it = this->_buffer.begin(); it != this->_buffer.end(); it++) {
        std::cout << "| " << *it << " |" << std::endl;;
    }
}
/////////////////////////////
// Exceptions              //
/////////////////////////////
