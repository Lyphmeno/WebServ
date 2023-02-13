/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlevi <hlevi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 12:12:58 by hlevi             #+#    #+#             */
/*   Updated: 2023/02/13 19:10:17 by hlevi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Parser.hpp"
#include <stdexcept>
#include <string>

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

void	Parser::print_tabulation()
{
	for (int i = 0; i < this->inbrackets; i++)
		std::cout << "\t";
}

int		Parser::semi_colon()
{
	std::string	tmp;
	if (this->line.str().at(this->line.str().size() - 1) != ';')
		throw std::invalid_argument("Invalid Argument: semi-colon missing");
	tmp = this->line.str();
	tmp.erase(tmp.size() - 1);
	this->line.str(tmp);
	return (0);
}

void	Parser::print_words(std::string str)
{
	std::string	words;
	this->print_tabulation();
	std::cout << "[" << str << "]";
	this->line >> words;
	while (this->line >> words)
		std::cout << " " << words;
	std::cout << ";";
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

void	Parser::p_location()
{
	std::string	words;
	std::string	tmp;
	this->print_tabulation();
	if (this->line.str().at(this->line.str().size() - 1) != '{')
		throw std::invalid_argument("Invalid Argument: Bracket missing after location");
	tmp = this->line.str();
	tmp.erase(tmp.size() - 1);
	this->line.str(tmp);
	std::cout << "[location]";
	this->line >> words;
	while (this->line >> words)
		std::cout << " " << words;
	std::cout << " {";
	this->inbrackets++;
}
void	Parser::p_servername()
{
	this->semi_colon();
	this->print_words("server_name");
}

void	Parser::p_listen()
{
	this->semi_colon();
	this->print_words("listen");
}

void	Parser::p_root()
{
	this->semi_colon();
	this->print_words("root");
}

void	Parser::p_index()
{
	this->semi_colon();
	this->print_words("index");
}

void	Parser::p_autoindex()
{
	this->semi_colon();
	this->print_words("auto_index");
}

void	Parser::p_maxclientbodysize()
{
	this->semi_colon();
	this->print_words("max_client_body_size");
}

void	Parser::p_errorpage()
{
	this->semi_colon();
	this->print_words("error_page");
}

void	Parser::p_cgiext()
{
	this->semi_colon();
	this->print_words("cgi_ext");
}

void	Parser::p_allowmethods()
{
	this->semi_colon();
	this->print_words("allow_methods");
}

int	Parser::parse_server()
{
	int			i;
	std::string	keyword;
	parsePtr	parserArray[FNUM] = {
				&Parser::p_location,
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
					"location",
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

	this->line >> keyword;
	for (i = 0; i < FNUM; i++) {
		if (keyword == strArray[i]) {
			(this->*parserArray[i])();
			break ;
		}
	}
	if (i == FNUM) {
		throw std::invalid_argument("Invalid Argument: Wrong TAG");
	}
	return (0);
}

int	Parser::parse_global()
{
	std::string	word;
	while (this->line >> word) {
		if (this->inbrackets == GLOBAL) {
			if (!word.compare("server")) {
				this->inbrackets = SERVER;
				std::cout << "[server] {";
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
		else if (this->inbrackets >= SERVER) {
			if (!this->line.str().compare("}")) {
				for (int i = 0; i < this->inbrackets - 1; i++)
					std::cout << "\t";
				std::cout << "}";
				this->inbrackets--;
			}
			else
				this->parse_server();
		}
		std::cout << std::endl;;
		this->line.clear();
	}
	std::cerr << "Bracket: " << this->inbrackets << std::endl;
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
