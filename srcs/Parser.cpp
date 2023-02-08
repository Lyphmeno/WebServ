/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlevi <hlevi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 12:12:58 by hlevi             #+#    #+#             */
/*   Updated: 2023/02/08 15:03:40 by hlevi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Parser.hpp"

namespace ft {
/////////////////////////////
// Coplien                 //
/////////////////////////////
Parser::Parser()
{
	this->inbrackets = 0;
	this->filename = "";
	this->line = "";
}

Parser::Parser(const Parser &cpy)
{
	*this = cpy;
}

Parser::~Parser()
{
}

Parser &Parser::operator=(const Parser &rhs)
{
	if (this != &rhs)
	{
		this->filename = rhs.filename;
		this->line = rhs.line;
		this->inbrackets = rhs.inbrackets;
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
int	Parser::openfile()
{
	this->file.open(this->filename.c_str());
	if (!this->file.is_open())
		return (-1);
	return (0);
}

void	Parser::printv()
{
	for (std::vector<std::string>::iterator it = this->buffer.begin(); it != this->buffer.end(); it++) {
        std::cout << "| " << *it << " |" << std::endl;;
    }
}
/////////////////////////////
// Exceptions              //
/////////////////////////////
}
