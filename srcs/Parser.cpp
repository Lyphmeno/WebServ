/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 12:12:58 by hlevi             #+#    #+#             */
/*   Updated: 2023/03/13 15:37:40 by hlevi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Parser.hpp"
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <netinet/in.h>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace ft {
/////////////////////////////
// Coplien                 //
/////////////////////////////
Parser::Parser():inbrackets(0),tablvl(0)
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
		this->tablvl = rhs.tablvl;
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

int		Parser::nbr_words()
{
	int			count = 0;
	std::string	tmp;

	while (this->line >> tmp)
		count++;
	this->line.clear();
	this->line.seekg(0);
	return (count);
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
	tmp.erase(0, tmp.find_first_of(" \t") + 1);
	if (tmp.empty())
		throw std::invalid_argument("Error: Argument missing after tag");
	this->line.str(tmp);
}

/////////////////////////////
// Print                   //
/////////////////////////////
void	Parser::print(std::string color, std::string str)
{
	std::cout << color << str << NC;
}

void	Parser::print_tabulation()
{
	for (int i = 0; i < this->tablvl; i++)
		std::cout << "\t";
}

void	Parser::print_servernames(std::vector<Server>& servers, int i)
{
	if (servers.at(i).server_names.empty())
		return ;
	this->print_tabulation();
	print(MAGENTA, "[server_name]");
	for (std::vector<std::string>::const_iterator it = servers.at(i).server_names.begin(); it != servers.at(i).server_names.end(); it++)
		print(BLUE, " " + *it);
	print(YELLOW, ";\n");
}

void	Parser::print_listen(std::vector<Server>& servers, int i)
{
	std::stringstream	iss;
	std::string			addr;
	std::string			port;

	if (servers.at(i).listen.empty())
		return ;
	this->print_tabulation();
	iss << servers.at(i).addr.sin_addr.s_addr;
	iss >> addr;
	iss.clear();
	iss << servers.at(i).addr.sin_port;
	iss >> port;
	print(MAGENTA, "[listen]");
	print(BLUE, " " + servers.at(i).listen + " (" + addr + ":" + port + ")");
	print(YELLOW, ";\n");
}

void	Parser::print_allowmethods(std::vector<Server>& servers, int i, int y)
{
	if (y >= 0) {
		if (servers.at(i).location.at(y).allow_methods.empty())
			return ;
		this->print_tabulation();
		print(MAGENTA, "[allow_methods]");
		for (std::vector<std::string>::const_iterator it = servers.at(i).location.at(y).allow_methods.begin(); it != servers.at(i).location.at(y).allow_methods.end(); it++)
			print(BLUE, " " + *it);
		print(YELLOW, ";\n");
	}
	else {
		if (servers.at(i).allow_methods.empty())
			return ;
		this->print_tabulation();
		print(MAGENTA, "[allow_methods]");
		for (std::vector<std::string>::const_iterator it = servers.at(i).allow_methods.begin(); it != servers.at(i).allow_methods.end(); it++)
			print(BLUE, " " + *it);
		print(YELLOW, ";\n");
	}
}

void	Parser::print_index(std::vector<Server>& servers, int i, int y)
{
	if (y >= 0) {
		if (servers.at(i).location.at(y).index.empty())
			return ;
		this->print_tabulation();
		print(MAGENTA, "[index]");
		for (std::vector<std::string>::const_iterator it = servers.at(i).location.at(y).index.begin(); it != servers.at(i).location.at(y).index.end(); it++)
			print(BLUE, " " + *it);
		print(YELLOW, ";\n");
	}
	else {
		if (servers.at(i).index.empty())
			return ;
		this->print_tabulation();
		print(MAGENTA, "[index]");
		for (std::vector<std::string>::const_iterator it = servers.at(i).index.begin(); it != servers.at(i).index.end(); it++)
			print(BLUE, " " + *it);
		print(YELLOW, ";\n");
	}
}

void	Parser::print_errpage(std::vector<Server>& servers, int i, int y)
{
	if (y >= 0) {
		if (servers.at(i).location.at(y).err_page.empty())
			return ;
		this->print_tabulation();
		print(MAGENTA, "[error_page]");
		for (std::vector<std::string>::const_iterator it = servers.at(i).err_page.begin(); it != servers.at(i).err_page.end(); it++)
			print(BLUE, " " + *it);
		print(YELLOW, ";\n");
	}
	else {
		if (servers.at(i).err_page.empty())
			return ;
		this->print_tabulation();
		print(MAGENTA, "[error_page]");
		for (std::vector<std::string>::const_iterator it = servers.at(i).err_page.begin(); it != servers.at(i).err_page.end(); it++)
			print(BLUE, " " + *it);
		print(YELLOW, ";\n");
	}
}

void	Parser::print_root(std::vector<Server>& servers, int i, int y)
{
	if (y >= 0) {
		if (servers.at(i).location.at(y).root.empty())
			return ;
		this->print_tabulation();
		print(MAGENTA, "[root]");
		print(BLUE, " " + servers.at(i).location.at(y).root);
		print(YELLOW, ";\n");
	}
	else {
		if (servers.at(i).root.empty())
			return ;
		this->print_tabulation();
		print(MAGENTA, "[root]");
		print(BLUE, " " + servers.at(i).root);
		print(YELLOW, ";\n");
	}
}

void	Parser::print_autoindex(std::vector<Server>& servers, int i, int y)
{
	if (y >= 0) {
		if (servers.at(i).location.at(y).auto_index.empty())
			return ;
		this->print_tabulation();
		print(MAGENTA, "[auto_index]");
		print(BLUE, " " + servers.at(i).location.at(y).auto_index);
		print(YELLOW, ";\n");
	}
	else {
		if (servers.at(i).auto_index.empty())
			return ;
		this->print_tabulation();
		print(MAGENTA, "[auto_index]");
		print(BLUE, " " + servers.at(i).auto_index);
		print(YELLOW, ";\n");
	}
}

void	Parser::print_mcbs(std::vector<Server>& servers, int i, int y)
{
	std::stringstream	iss;
	std::string			tmp;	

	if (y >= 0) {
		iss << servers.at(i).location.at(y).max_client_body_size;
		iss >> tmp;
		this->print_tabulation();
		print(MAGENTA, "[max_client_body_size]");
		print(BLUE, " " + tmp + " octets");
		print(YELLOW, ";\n");
	}
	else {
		iss << servers.at(i).max_client_body_size;
		iss >> tmp;
		this->print_tabulation();
		print(MAGENTA, "[max_client_body_size]");
		print(BLUE, " " + tmp + " octets");
		print(YELLOW, ";\n");
	}
}

void	Parser::print_cgidir(std::vector<Server>& servers, int i, int y)
{
	if (y >= 0){
		if (servers.at(i).location.at(y).cgi_dir.empty())
			return ;
		this->print_tabulation();
		print(MAGENTA, "[cgi_dir]");
		print(BLUE, " " + servers.at(i).location.at(y).cgi_dir);
		print(YELLOW, ";\n");
	}
	else {
		if (servers.at(i).cgi_dir.empty())
			return ;
		this->print_tabulation();
		print(MAGENTA, "[cgi_dir]");
		print(BLUE, " " + servers.at(i).cgi_dir);
		print(YELLOW, ";\n");
	}
}

void	Parser::print_location(std::vector<Server>& servers, int i)
{
	int	y = 0;

	if (servers.at(i).location.empty())
		return ;
	for (std::vector<ft::Location>::const_iterator it = servers.at(i).location.begin(); it != servers.at(i).location.end(); it++) {
		this->tablvl = 1;
		this->print_tabulation();
		this->tablvl = 2;
		print(GREEN, "[location]");
		print(BLUE, " " + servers.at(i).location.at(y).path);
		print(YELLOW, " {\n");
		print_root(servers, i, y);
		print_index(servers, i, y);
		print_cgidir(servers, i, y);
		print_autoindex(servers, i, y);
		print_errpage(servers, i, y);
		print_allowmethods(servers, i, y);
		print_mcbs(servers, i, y);
		print(YELLOW, "\t}\n");
		y++;
	}
}

void	Parser::print_all(std::vector<Server>& servers)
{
	int	i = 0;

	print(GREEN, "-----------------------------------------------------------\n");
	for (std::vector<ft::Server>::const_iterator it = servers.begin(); it != servers.end(); it++) {
		print(GREEN, "[server] ");
		print(YELLOW, " {\n");
		this->tablvl = 1;
		print_servernames(servers, i);
		print_listen(servers, i);
		print_root(servers, i, -1);
		print_index(servers, i, -1);
		print_cgidir(servers, i, -1);
		print_autoindex(servers, i, -1);
		print_errpage(servers, i, -1);
		print_allowmethods(servers, i, -1);
		print_mcbs(servers, i, -1);
		print_location(servers, i);
		print(YELLOW, "}\n");
		i++;
	}
	print(GREEN, "-----------------------------------------------------------\n");
}
/////////////////////////////
// Full Parsing            //
/////////////////////////////
void	Parser::p_location(std::vector<Server> &servers)
{
	std::string	tmp;

	this->brackets();
	this->dlt_first();
	if (nbr_words() != 1)
		throw std::invalid_argument("Invalid argument: <location> must/can only have one argument");
	this->inbrackets++;
	if (this->inbrackets >= 3)
		throw std::invalid_argument("Invalid argument: <location> cannot have <location>");
	this->line >> tmp;
	if (servers.back().getLoc(tmp) >= 0)
		throw std::invalid_argument("Invalid argument: <location> must not be the same");
	servers.back().location.push_back(ft::Location());
	for (int i = 0; i <= 6; i++)
		servers.back().location.back().id.push_back(false);
	servers.back().location.back().path = tmp;
}

void	Parser::p_servername(std::vector<Server> &servers)
{
	std::string	tmp;

	if (servers.back().id.at(BS_NAME) == true)
		throw std::invalid_argument("Invalid argument: multiple <server_name> tag not allowed");
	servers.back().id.at(BS_NAME) = true;
	this->semi_colon();
	this->dlt_first();
	while (this->line >> tmp)
		if (static_cast<int>(tmp.find_first_not_of(SERALL)) != -1)
			throw std::invalid_argument("Invalid Argument: <server name> can only contain (letter/digit/-_.)");
	this->line.clear();
	this->line.seekg(0);
	while (this->line >> tmp)
		servers.back().server_names.push_back(tmp);
}

void	Parser::p_listen_hp_addint(std::string tmpnum)
{
	int					tmpint;
	std::stringstream	tmpintiss;

	if (tmpnum.empty())
		throw std::invalid_argument("Invalid Argument: 1 <listen'HOST:PORT'> invalid");
	tmpintiss.clear();
	tmpintiss.seekg(0);
	tmpintiss.str(tmpnum);
	tmpintiss >> tmpint;
	this->hostint.push_back(tmpint);
}

void	Parser::p_listen_hp(std::string tmp)
{
	size_t				pos;
	std::stringstream	tmpiss;
	std::string			hostmp(tmp.substr(0, tmp.find_first_of(":")));
	std::string			portmp(tmp.substr(tmp.find_first_of(":") + 1, tmp.size()));

	if (hostmp.empty() || portmp.empty() || static_cast<int>(portmp.find_first_not_of("1234567890")) != -1)
		throw std::invalid_argument("Invalid Argument: 2 <listen'HOST:PORT'> invalid");
	while ((pos = hostmp.find(".")) != std::string::npos) {
		p_listen_hp_addint(hostmp.substr(0, pos));
		hostmp.erase(0, pos + 1);
	}
	p_listen_hp_addint(hostmp.substr(0, pos));
	if (hostint.size() != 4)
		throw std::invalid_argument("Invalid Argument: 3 <listen'HOST:PORT'> invalid");
	for (std::vector<int>::const_iterator it = hostint.begin(); it != hostint.end(); it++)
		if (*it < 0 || *it > 255)
			throw std::invalid_argument("Invalid Argument: 4 <listen'HOST:PORT'> invalid");
	tmpiss.str(portmp);
	tmpiss >> this->portint;
}

void	Parser::p_listen(std::vector<Server> &servers)
{
	std::string	tmp;

	if (servers.back().id.at(BS_LISTEN) == true)
		throw std::invalid_argument("Invalid argument: multiple <listen> tag not allowed");
	servers.back().id.at(BS_LISTEN) = true;
	this->hostint.clear();
	this->portint = 0;
	this->semi_colon();
	this->dlt_first();
	if (nbr_words() != 1)
		throw std::invalid_argument("Invalid argument: 5 <listen> can only have one argument");
	while (this->line >> tmp)
	{
		if (static_cast<int>(tmp.find_first_not_of(LISTEN)) != -1)
			throw std::invalid_argument("Invalid Argument: <listen> Invalid entry");
		if (static_cast<int>(tmp.find_first_not_of("1234567890")) != -1)
			this->p_listen_hp(tmp);
		else {
			if (static_cast<int>(tmp.find_first_not_of("1234567890")) != -1)
				throw std::invalid_argument("Invalid Argument: <listen'PORT'> invalid");
			tmp = "0.0.0.0:" + tmp;
			this->p_listen_hp(tmp);
		}
	}
	servers.back().listen = tmp;
	servers.back().addr.sin_addr.s_addr = htonl((hostint.at(0) << 24) + (hostint.at(1) << 16) + (hostint.at(2) << 8) + (hostint.at(3)));
	servers.back().addr.sin_port = htons(this->portint);
}

void	Parser::p_root(std::vector<Server> &servers)
{
	std::string	tmp;

	this->semi_colon();
	this->dlt_first();
	if (nbr_words() != 1)
		throw std::invalid_argument("Invalid argument: <root> can only have one argument");
	if (this->inbrackets == 1) {
		if (servers.back().id.at(BS_ROOT) == true)
			throw std::invalid_argument("Invalid argument: multiple <root> tag not allowed");
		servers.back().id.at(BS_ROOT) = true;
		while (this->line >> tmp)
			servers.back().root = tmp;
	}
	else {
		if (servers.back().location.back().id.at(BL_ROOT) == true)
			throw std::invalid_argument("Invalid argument: multiple <root> tag not allowed");
		servers.back().location.back().id.at(BL_ROOT) = true;
		while (this->line >> tmp)
			servers.back().location.back().root = tmp;
	}
}

void	Parser::p_index(std::vector<Server> &servers)
{
	std::string	tmp;

	this->semi_colon();
	this->dlt_first();
	if (this->inbrackets == 1) {
		if (servers.back().id.at(BS_INDEX) == true)
			throw std::invalid_argument("Invalid argument: multiple <index> tag not allowed");
		servers.back().id.at(BS_INDEX) = true;
		while (this->line >> tmp)
			servers.back().index.push_back(tmp);
	}
	else {
		if (servers.back().location.back().id.at(BL_INDEX) == true)
			throw std::invalid_argument("Invalid argument: multiple <index> tag not allowed");
		servers.back().location.back().id.at(BL_INDEX) = true;
		while (this->line >> tmp)
			servers.back().location.back().index.push_back(tmp);
	}
}

void	Parser::p_autoindex(std::vector<Server> &servers)
{
	std::string	tmp;

	this->semi_colon();
	this->dlt_first();
	if (nbr_words() != 1)
		throw std::invalid_argument("Invalid argument: <autoindex> can only have one argument");
	while (this->line >> tmp)
		if (tmp.compare("on") && tmp.compare("off"))
			throw std::invalid_argument("Invalid Argument: Invalid method");
	this->line.clear();
	this->line.seekg(0);
	if (this->inbrackets == 1) {
		if (servers.back().id.at(BS_AUTOINDEX) == true)
			throw std::invalid_argument("Invalid argument: multiple <auto_index> tag not allowed");
		servers.back().id.at(BS_AUTOINDEX) = true;
		while (this->line >> tmp)
			servers.back().auto_index = tmp;
	}
	else {
		if (servers.back().location.back().id.at(BL_AUTOINDEX) == true)
			throw std::invalid_argument("Invalid argument: multiple <auto_index> tag not allowed");
		servers.back().location.back().id.at(BL_AUTOINDEX) = true;
		while (this->line >> tmp)
			servers.back().location.back().auto_index = tmp;
	}
}

unsigned long int	Parser::p_convert_mcbs(std::string tmp)
{
	char				unit;
	unsigned long int	tmpint;

	unit = tmp.at(tmp.size() - 1);
	tmp.erase(tmp.size() - 1);
	this->line.str(tmp);
	this->line >> tmpint;
	if (unit == 'G')
		tmpint *= 1073741824;
	else if (unit == 'M')
		tmpint *= 1048576;
	else if (unit == 'K')
		tmpint *= 1024;
	if (tmpint > 2147483648)
		throw std::invalid_argument("Invalid argument: <max_client_body_size> is limited to 2Go");
	return (tmpint);
}

void	Parser::p_maxclientbodysize(std::vector<Server> &servers)
{
	std::string			tmp;
	int					tmpint;

	this->semi_colon();
	this->dlt_first();
	if (nbr_words() != 1)
		throw std::invalid_argument("Invalid argument: <max_client_body_size> can only have one argument");
	tmp = this->line.str();
	if (this->line.str().at(this->line.str().size() - 1) != 'o' &&
			this->line.str().at(this->line.str().size() - 1) != 'K' &&
			this->line.str().at(this->line.str().size() - 1) != 'M' &&
			this->line.str().at(this->line.str().size() - 1) != 'G')
		throw std::invalid_argument("Invalid argument: <max_client_body_size> invalid unit");
	tmpint = this->p_convert_mcbs(tmp);
	if (this->inbrackets == 1) {
		if (servers.back().id.at(BS_MCBS) == true)
			throw std::invalid_argument("Invalid argument: multiple <max_client_body_size> tag not allowed");
		servers.back().id.at(BS_MCBS) = true;
		servers.back().max_client_body_size = tmpint;
	}
	else {
		if (servers.back().location.back().id.at(BL_MCBS) == true)
			throw std::invalid_argument("Invalid argument: multiple <max_client_body_size> tag not allowed");
		servers.back().location.back().id.at(BL_MCBS) = true;
		servers.back().location.back().max_client_body_size = tmpint;
	}
}

void	Parser::p_errorpage(std::vector<Server> &servers)
{
	std::string	tmp;

	this->semi_colon();
	this->dlt_first();
	if (nbr_words() <= 1)
		throw std::invalid_argument("Invalid argument: <error_page> need at least 2 arguments");
	if (this->inbrackets == 1) {
		if (servers.back().id.at(BS_ERR) == true)
			throw std::invalid_argument("Invalid argument: multiple <error_page> tag not allowed");
		servers.back().id.at(BS_ERR) = true;
		while (this->line >> tmp)
			servers.back().err_page.push_back(tmp);
	}
	else {
		if (servers.back().location.back().id.at(BL_ERR) == true)
			throw std::invalid_argument("Invalid argument: multiple <error_page> tag not allowed");
		servers.back().location.back().id.at(BL_ERR) = true;
		while (this->line >> tmp)
			servers.back().location.back().err_page.push_back(tmp);
	}
}

void	Parser::p_cgidir(std::vector<Server> &servers)
{
	std::string	tmp;

	this->semi_colon();
	this->dlt_first();
	if (nbr_words() != 1)
		throw std::invalid_argument("Invalid argument: <cgidir> can only have one argument");
	if (this->inbrackets == 1) {
		if (servers.back().id.at(BS_CGI) == true)
			throw std::invalid_argument("Invalid argument: multiple <cgi_dir> tag not allowed");
		servers.back().id.at(BS_CGI) = true;
		while (this->line >> tmp)
			servers.back().cgi_dir = tmp;
		}
	else {
		if (servers.back().location.back().id.at(BL_CGI) == true)
			throw std::invalid_argument("Invalid argument: multiple <cgi_dir> tag not allowed");
		servers.back().location.back().id.at(BL_CGI) = true;
		while (this->line >> tmp)
			servers.back().location.back().cgi_dir = tmp;
	}
}

void	Parser::p_allowmethods(std::vector<Server> &servers)
{
	std::string	tmp;

	this->semi_colon();
	this->dlt_first();
	while (this->line >> tmp)
		if (tmp.compare("GET") && tmp.compare("POST"))
			throw std::invalid_argument("Invalid Argument: Invalid method");
	this->line.clear();
	this->line.seekg(0);
	if (this->inbrackets == 1) {
		if (servers.back().id.at(BS_METHODS) == true)
			throw std::invalid_argument("Invalid argument: multiple <allow_methods> tag not allowed");
		servers.back().id.at(BS_METHODS) = true;
		while (this->line >> tmp)
			servers.back().allow_methods.push_back(tmp);
	}
	else {
		if (servers.back().location.back().id.at(BL_METHODS) == true)
			throw std::invalid_argument("Invalid argument: multiple <allow_methods> tag not allowed");
		servers.back().location.back().id.at(BL_METHODS) = true;
		while (this->line >> tmp)
			servers.back().location.back().allow_methods.push_back(tmp);
	}
}

int	Parser::parse_server(std::vector<Server> &servers)
{
	int			i;
	std::string	keyword;
	parsePtr	parserArray[FNUM] = {
				&Parser::p_servername,
				&Parser::p_listen,
				&Parser::p_root,
				&Parser::p_index,
				&Parser::p_autoindex,
				&Parser::p_maxclientbodysize,
				&Parser::p_errorpage,
				&Parser::p_cgidir,
				&Parser::p_allowmethods,
				&Parser::p_location,
	};
	std::string	strArray[FNUM] = {
					"server_name",
					"listen",
					"root",
					"index",
					"auto_index",
					"max_client_body_size",
					"error_page",
					"cgi_dir",
					"allow_methods",
					"location",
	};

	this->line >> keyword;
	for (i = 0; i < FNUM; i++) {
		if (keyword == strArray[i]) {
			(this->*parserArray[i])(servers);
			break ;
		}
	}
	if (i >= FNUM) 
		throw std::invalid_argument("Invalid Argument: Wrong tag OR Bracket not closed");
	return (0);
}

int	Parser::parse_global()
{
	std::string	word;
	while (this->line >> word) {
		if (this->inbrackets == GLOBAL) {
			if (!word.compare("server"))
				this->inbrackets = SERVER;
		}
		else
			if (word.compare("{"))
				return (-1);
	}
	return (0);
}

void	Parser::parse_mandatory(std::vector<Server> &servers)
{
	if (servers.empty())
		throw std::invalid_argument("Invalid argument: no servers");
	for (std::vector<Server>::iterator it = servers.begin(); it != servers.end(); it++) {
		if (!it->id.at(BS_LISTEN))
			throw std::invalid_argument("Invalid argument: <listen> is mandatory");
		if (!it->id.at(BS_ROOT))
			throw std::invalid_argument("Invalid argument: <root> is mandatory");
		if (!it->id.at(BS_MCBS))
			it->max_client_body_size = 1048576;
		if (!it->location.empty()) {
			for (std::vector<Location>::iterator itl = it->location.begin(); itl != it->location.end(); itl++) {
				if (!itl->id.at(BL_MCBS))
					itl->max_client_body_size = it->max_client_body_size;
				if (!itl->id.at(BL_ROOT))
					itl->root = it->root;
				if (!itl->id.at(BL_AUTOINDEX))
					itl->auto_index = it->auto_index;
			}
		}
	}
}

int	Parser::parsing_base(std::vector<Server> &servers)
{
	for (std::vector<std::string>::const_iterator it = this->buffer.begin(); it != this->buffer.end(); it++) {
		this->line.str(*it);
		if (this->inbrackets == GLOBAL) {
			if (this->parse_global())
				return (-1);
			servers.push_back(ft::Server());
		}
		else if (this->inbrackets >= SERVER) {
			if (!this->line.str().compare("}"))
				this->inbrackets--;
			else
				this->parse_server(servers);
		}
		this->line.clear();
	}
	this->parse_mandatory(servers);
	if (PRINT_INFO == 1)
		this->print_all(servers);
	if (this->inbrackets)
		throw std::invalid_argument("Invalid Argument: Brackets not closed");
	return (0);
}

void	Parser::parsing(std::string arg, std::vector<Server> &servers)
{
	this->filename = arg;
	if (this->retrieve_file())
		throw std::invalid_argument("Invalid Argument: Invalid File");
	if (this->parsing_base(servers))
		throw std::invalid_argument("Invalid Argument: Invalid File");
}
/////////////////////////////
// Exceptions              //
/////////////////////////////
}
