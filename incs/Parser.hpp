/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlevi <hlevi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 12:12:56 by hlevi             #+#    #+#             */
/*   Updated: 2023/02/17 16:24:21 by hlevi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <locale>
#include "../incs/Server.hpp"

#define FNUM 10
#define SERALL "abcdefghijklmnopqrstuvwxysABCDEFGHIJKLMNOPQRSTUVWXYZ-_.1234567890"
#define SERALPHA "abcdefghijklmnopqrstuvwxysABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define LISTEN ":.1234567890"

#define GLOBAL 0
#define SERVER 1
#define SLOC 2

namespace ft {
class Parser
{
public:
	std::fstream    			file;
	std::string     			filename;
    std::stringstream 			line;
	std::vector<std::string>	buffer;
	std::vector<int>			hostint;
	int							inbrackets;
public:
	// Coplien //
	Parser();
	Parser(const Parser &cpy);
	~Parser();
	Parser &operator=(const Parser &rhs);
	// Assignation contructors //
	// Operators //
	// Getters //
	// Setters //
	// Methods //
	void	parsing(std::string, std::vector<Server>&);
private:
	void	print_info();
	void	print_tabulation();
	void	semi_colon();
	void	brackets();
	int		nbr_words();
	void	print_words(std::string, std::string);
	void	print_location(std::string);
	int		openfile();
	int		retrieve_file();
	void	dlt_first();
	int		parse_server();
	int		parse_global();
	int		parsing_base();
	typedef void(Parser::*parsePtr)();
	void	p_listen_hp_addint(std::string);
	void	p_listen_hp(std::string);
	void	p_location();
	void	p_servername();
	void	p_listen();
	void	p_root();
	void	p_index();
	void	p_autoindex();
	void	p_maxclientbodysize();
	void	p_errorpage();
	void	p_cgidir();
	void	p_allowmethods();
	// Exceptions //
};
}
