/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlevi <hlevi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 12:12:58 by hlevi             #+#    #+#             */
/*   Updated: 2023/02/15 18:21:23 by hlevi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Parser.hpp"
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

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
	for (std::vector<std::string>::const_iterator it = this->buffer.begin(); it != this->buffer.end(); it++) {
        std::cout << *it << std::endl;
    }
}

void	Parser::print_tabulation()
{
	for (int i = 0; i < this->inbrackets; i++)
		std::cout << "\t";
}

void	Parser::semi_colon()
{
	std::string	tmp;
	if (this->line.str().at(this->line.str().size() - 1) != ';')
		throw std::invalid_argument("Invalid Argument: semi-colon missing");
	tmp = this->line.str();
	tmp.erase(tmp.size() - 1);
	this->line.str(tmp);
}

void	Parser::brackets()
{
	std::string	tmp;
	if (this->line.str().at(this->line.str().size() - 1) != '{')
		throw std::invalid_argument("Invalid Argument: Bracket missing after location");
	this->print_tabulation();
	tmp = this->line.str();
	tmp.erase(tmp.size() - 1);
	this->line.str(tmp);
}

void	Parser::print_words(std::string str, std::string color)
{
	std::string	words;
	this->print_tabulation();
	std::cout << "\033[35m[" << str << "]\033[0m";
	this->line >> words;
	while (this->line >> words)
		std::cout << color << " " << words;
	std::cout << "\033[33m" << ";" << "\033[0m";
	this->line.clear();
	this->line.seekg(0);
}

void	Parser::print_location(std::string str)
{
	std::string	words;
	std::cout << "\033[36m[" << str << "]\033[0m";
	this->line >> words;
	while (this->line >> words)
		std::cout << " \033[34m" << words;
	std::cout << "\033[33m" << " {" << "\033[0m";
	this->line.clear();
	this->line.seekg(0);
}

int	Parser::openfile()
{
	this->file.open(this->filename.c_str());
	if (!this->file.is_open())
		return (-1);
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

void	Parser::dlt_first()
{
	std::string	tmp;
	tmp = this->line.str();
	tmp.erase(0, tmp.find_first_of(" ") + 1);
	if (tmp.empty())
		throw std::invalid_argument("Error: Argument missing after tag");
	this->line.str(tmp);
}

void	Parser::p_location()
{
	this->brackets();
	this->print_location("location");
	this->dlt_first();
	this->inbrackets++;
}

void	Parser::p_servername()
{
	std::string	tmp;
	this->semi_colon();
	this->print_words("server_name", "\033[34m");
	this->dlt_first();
	while (this->line >> tmp)
	{
		if (static_cast<int>(tmp.find_first_not_of(SERALL)) != -1)
			throw std::invalid_argument("Invalid Argument: Invalid server name");
	}
}

void	Parser::p_listen()
{
	int			count = 0;
	std::string	tmp;
	this->semi_colon();
	this->print_words("listen", "\033[34m");
	this->dlt_first();
	while (this->line >> tmp)
	{
		if (count == 1)
			throw std::invalid_argument("Invalid Argument: Invalid listen entry");
		if (static_cast<int>(tmp.find_first_not_of(LISTEN)) != -1)
			throw std::invalid_argument("Invalid Argument: Invalid listen entry");
		if (static_cast<int>(tmp.find_first_not_of("1234567890")) != -1)
		{
			size_t				pos;
			std::vector<int>	hostint;
			std::string			tmpnum;
			std::string			hostmp(tmp.substr(0, tmp.find_first_of(":")));
			std::string			portmp(tmp.substr(tmp.find_first_of(":") + 1, tmp.size()));
			std::stringstream	tmpiss;
			if (hostmp.empty() || portmp.empty() || static_cast<int>(portmp.find_first_not_of("1234567890")) != -1)
				throw std::invalid_argument("Invalid Argument: Invalid listen entry");
			while ((pos = hostmp.find(".")) != std::string::npos) {
				tmpnum = hostmp.substr(0, pos);
				std::istringstream	tmpintiss(tmpnum);
				int					tmpint;
				tmpintiss >> tmpint;
				hostint.push_back(tmpint);
				hostmp.erase(0, pos + 1);
			}
			std::istringstream	tmpintiss(tmpnum);
			int					tmpint;
			tmpintiss >> tmpint;
			hostint.push_back(tmpint);
			if (hostint.size() != 4)
				throw std::invalid_argument("Invalid Argument: Invalid listen entry");
			for (std::vector<int>::const_iterator it = hostint.begin(); it != hostint.end(); it++){
				if (*it < 0 || *it > 255)
					throw std::invalid_argument("Invalid Argument: Invalid listen entry");
			}
		}
		else
		{
			if (static_cast<int>(tmp.find_first_not_of("1234567890")) != -1)
				throw std::invalid_argument("Invalid Argument: Invalid listen entry");
		}
		count++;
	}
}

void	Parser::p_root()
{
	this->semi_colon();
	this->print_words("root", "\033[34m");
	this->dlt_first();
}

void	Parser::p_index()
{
	this->semi_colon();
	this->print_words("index", "\033[34m");
	this->dlt_first();
}

void	Parser::p_autoindex()
{
	std::string	tmp;
	this->semi_colon();
	this->print_words("auto_index", "\033[34m");
	this->dlt_first();
	while (this->line >> tmp)
	{
		if (tmp.compare("on") && tmp.compare("off"))
			throw std::invalid_argument("Invalid Argument: Invalid method");
	}
}

void	Parser::p_maxclientbodysize()
{
	this->semi_colon();
	this->print_words("max_client_body_size", "\033[0m");
	this->dlt_first();
}

void	Parser::p_errorpage()
{
	this->semi_colon();
	this->print_words("error_page", "\033[0m");
	this->dlt_first();
}

void	Parser::p_cgidir()
{
	this->semi_colon();
	this->print_words("cgi_dir", "\033[34m");
	this->dlt_first();
}

void	Parser::p_allowmethods()
{
	std::string	tmp;
	this->semi_colon();
	this->print_words("allow_methods", "\033[34m");
	this->dlt_first();
	while (this->line >> tmp)
	{
		if (tmp.compare("GET") && tmp.compare("POST"))
			throw std::invalid_argument("Invalid Argument: Invalid method");
	}
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
				&Parser::p_cgidir,
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
					"cgi_dir",
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
		throw std::invalid_argument("Invalid Argument: Wrong tag OR Bracket not closed");
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
				std::cout << "\033[32m[server" << "] \033[33m{\033[0m";
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
	std::cout << "\033[32m---------------------------------------------------------------------------------" << "\033[0m\n";
	for (std::vector<std::string>::const_iterator it = this->buffer.begin(); it != this->buffer.end(); it++) {
		this->line.str(*it);
		if (this->inbrackets == GLOBAL) {
			if (this->parse_global())
				return (-1);
		}
		else if (this->inbrackets >= SERVER) {
			if (!this->line.str().compare("}")) {
				for (int i = 0; i < this->inbrackets - 1; i++)
					std::cout << "\t";
				std::cout << "\033[33m" << " }" << "\033[0m";
				this->inbrackets--;
			}
			else
				this->parse_server();
		}
		std::cout << std::endl;;
		this->line.clear();
	}
	std::cout << "\033[32m---------------------------------------------------------------------------------" << "\033[0m\n";
	if (this->inbrackets) {
		throw std::invalid_argument("Invalid Argument: Brackets not closed");
	}
	return (0);
}

int	Parser::parsing(std::string arg)
{
	this->filename = arg;
	if (this->retrieve_file())
	{
		throw std::invalid_argument("Invalid Argument: Invalid File");
		return (-1);
	}
	if (this->parsing_base())
		return (-1);
	//this->print_info();
	return (0);
}
/////////////////////////////
// Exceptions              //
/////////////////////////////
}
