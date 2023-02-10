/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 12:12:58 by hlevi             #+#    #+#             */
/*   Updated: 2023/02/10 19:06:56 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Parser.hpp"
#include <pthread.h>

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
void	Parser::print_info()
{
	for (std::vector<std::string>::iterator it = this->buffer.begin(); it != this->buffer.end(); it++) {
        std::cout << *it << std::endl;;
    }
}

int	Parser::openfile()
{
	this->file.open(this->filename.c_str());
	if (!this->file.is_open())
	{
		std::cerr << "Error: Invalid File" << std::endl; 
		return (-1);
	}
	return (0);
}

int	Parser::retrieve_file()
{
    if (this->openfile())
        return (-1);
    while (this->file)
    {
        std::getline(this->file, this->line, '\n');
		this->line.erase(std::remove(this->line.begin(), this->line.end(), '\n'), this->line.end());
		if (!this->line.empty())
		{
			this->line.erase(0, this->line.find_first_not_of(" \t"));
			this->line.erase(this->line.find_last_not_of(" \t") + 1, this->line.size());
			this->buffer.push_back(this->line);
		}
    }
    this->file.close();
	return (0);
}

int	Parser::parsing(std::string arg)
{
	this->filename = arg;
	this->retrieve_file();
	this->print_info();
	return (0);
}
/////////////////////////////
// Exceptions              //
/////////////////////////////
}
