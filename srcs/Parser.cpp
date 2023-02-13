/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlevi <hlevi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 12:12:58 by hlevi             #+#    #+#             */
/*   Updated: 2023/02/13 15:37:45 by hlevi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Parser.hpp"
#include <sstream>

namespace ft {
/////////////////////////////
// Coplien                 //
/////////////////////////////
Parser::Parser():inbrackets(0)
{
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

void	Parser::p_servername()
{
	std::cout << "Found a SERVERNAME" << std::endl;
}

void	Parser::p_listen()
{
	std::cout << "Found a LISTEN" << std::endl;
}

void	Parser::p_root()
{
	std::cout << "Found a ROOT" << std::endl;
}

void	Parser::p_index()
{
	std::cout << "Found a INDEX" << std::endl;
}

void	Parser::p_autoindex()
{
	std::cout << "Found a AUTOINDEX" << std::endl;
}

void	Parser::p_maxclientbodysize()
{
	std::cout << "Found a MCBS" << std::endl;
}

void	Parser::p_errorpage()
{
	std::cout << "Found a ERRORPAGE" << std::endl;
}

void	Parser::p_cgiext()
{
	std::cout << "Found a CGIEXT" << std::endl;
}

void	Parser::p_allowmethods()
{
	std::cout << "Found a ALLOWMETHOD" << std::endl;
}

int	Parser::parse_server()
{
	std::string	keyword;
	this->line >> keyword;
	std::cout << keyword << "\t-> ";
	parsePtr	parserArray[FNUM] = {
				&Parser::p_servername,
				&Parser::p_listen,
				&Parser::p_root,
				&Parser::p_index,
				&Parser::p_autoindex,
				&Parser::p_maxclientbodysize,
				&Parser::p_errorpage,
				&Parser::p_cgiext,
				&Parser::p_allowmethods,
	};
	std::string	strArray[FNUM] = {
					"server_name",
					"listen",
					"root",
					"index",
					"auto_index",
					"max_client_body_size",
					"error_page",
					"cgi_ext",
					"allow_methods",
	};

	for (int i = 0; i < FNUM; i++)
	{
		if (keyword == strArray[i])
			(this->*parserArray[i])();
		else if (i == FNUM) {
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
			std::cout << "(entering server brackets)" << std::endl;
		}
		else if (this->inbrackets >= SERVER) {
			this->parse_server();
		}
		std::cout << std::endl;;
		this->line.clear();
	}
	if (this->inbrackets) {
		std::cerr << "Error: Bracket not closed: " << this->inbrackets << std::endl;
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
