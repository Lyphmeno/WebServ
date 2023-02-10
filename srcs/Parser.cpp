/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlevi <hlevi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 12:12:58 by hlevi             #+#    #+#             */
/*   Updated: 2023/02/10 16:27:58 by hlevi            ###   ########.fr       */
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
        std::cout << *it << std::endl;
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
	std::string	tmpline;

    if (this->openfile())
        return (-1);
    while (this->file)
    {
        std::getline(this->file, tmpline, '\n');
		tmpline.erase(std::remove(tmpline.begin(), tmpline.end(), '\n'), tmpline.end());
		if (!tmpline.empty())
		{
			tmpline.erase(0, tmpline.find_first_not_of(" \t"));
			tmpline.erase(tmpline.find_last_not_of(" \t") + 1, tmpline.size());
			this->buffer.push_back(tmpline);
		}
    }
    this->file.close();
	return (0);
}

int	Parser::parse_server()
{
	int	functionNumber = 8;
	std::string	keyword;
	parsePtr	parserArray[functionNumber] = {
				&Parser::p_servername(),
				&Parser::p_listen(),
				&Parser::p_root(),
				&Parser::p_index(),
				&Parser::p_autoindex(),
				&Parser::p_maxclientbodysize(),
				&Parser::p_errorpage(),
				&Parser::p_cgiext(),
	};
	std::string	strArray[functionNumber]{
					"server_name",
					"listen",
					"root",
					"index",
					"auto_index",
					"max_client_body_size",
					"error_page",
					"cgi_ext",
	};

	for (int i = 0; i < functionNumber; i++)
	{
		if (keyword == strArray[i])
			(this->*parserArray[i])();
		else if (i == functionNumber) {
			std::cerr << "Error: Wrong keyword on configuration file\n";
		}
	}
	return (0);
}

int	Parser::parse_global()
{
	std::string	word;
	while (this->line >> word) {
		std::cout << word << " ";
		if (this->inbrackets == GLOBAL) {
			if (!word.compare("server")) {
				this->inbrackets = SERVER;
			}
		}
		else
			if (word.compare("{"))
				return (-1);
	}
	return (0);
}

int	Parser::parsing_base()
{
	for (std::vector<std::string>::iterator it = this->buffer.begin(); it != this->buffer.end(); it++) {
		this->line.str(*it);
		if (this->inbrackets == GLOBAL) {
			if (this->parse_global())
				return (-1);
		}
		if (this->inbrackets >= SERVER) {
			this->parse_server();
		}
		std::cout << std::endl;;
	}
	if (this->inbrackets) {
		std::cerr << "Error: Bracket not closed" << std::endl;
		return (-1);
	}
	return (0);
}

int	Parser::parsing(std::string arg)
{
	this->filename = arg;
	if (this->retrieve_file())
	{
		std::cerr << "Error: Couldn't retrieve file information" << std::endl;
		return (-1);
	}
	if (this->parsing_base())
	{
		std::cerr << "Error: Invalid file" << std::endl;
		return (-1);
	}
	//this->print_info();
	return (0);
}
/////////////////////////////
// Exceptions              //
/////////////////////////////
}
