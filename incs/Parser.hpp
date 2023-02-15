/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlevi <hlevi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 12:12:56 by hlevi             #+#    #+#             */
/*   Updated: 2023/02/15 11:04:13 by hlevi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include "../incs/Server.hpp"

#define FNUM 10 // Number of functions for the funciton pointer array
#define SERNAMES "abcdefghijklmnopqrstuvwxysABCDEFGHIJKLMNOPQRSTUVWXYZ-_."

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
	int		parsing(std::string);
private:
	void	print_info();
	void	print_tabulation();
	void	semi_colon();
	void	brackets();
	void	print_words(std::string);
	void	print_location(std::string);
	int		openfile();
	int		retrieve_file();
	int		parse_server();
	int		parse_global();
	int		parsing_base();
	typedef void(Parser::*parsePtr)();
	void	p_location();
	void	p_servername();
	void	p_listen();
	void	p_root();
	void	p_index();
	void	p_autoindex();
	void	p_maxclientbodysize();
	void	p_errorpage();
	void	p_cgiext();
	void	p_allowmethods();
	// Exceptions //
};
}
