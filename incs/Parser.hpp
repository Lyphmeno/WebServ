/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlevi <hlevi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 12:12:56 by hlevi             #+#    #+#             */
/*   Updated: 2023/02/13 15:34:33 by hlevi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include "../incs/Server.hpp"

#define FNUM 9 // Number of functions for the funciton pointer array

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
	void	print_info();
	int		openfile();
	int		retrieve_file();
	int		parse_server();
	int		parse_global();
	int		parsing_base();
	int		parsing(std::string);

private:
	typedef void(Parser::*parsePtr)();
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

#endif
