/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlevi <hlevi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 12:12:56 by hlevi             #+#    #+#             */
/*   Updated: 2023/02/24 10:27:14 by hlevi            ###   ########.fr       */
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

#define FNUM 10
#define SERALL "abcdefghijklmnopqrstuvwxysABCDEFGHIJKLMNOPQRSTUVWXYZ-_.1234567890"
#define SERALPHA "abcdefghijklmnopqrstuvwxysABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define LISTEN ":.1234567890"

#define GLOBAL 0
#define SERVER 1
#define SLOC 2

#define PRINT_INFO 1

	// Colors //
#define NC   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"


namespace ft {
class Parser
{
public:
	std::fstream    			file;
	std::string     			filename;
    std::stringstream 			line;
	std::vector<std::string>	buffer;
	std::vector<int>			hostint;
	int							portint;
	int							inbrackets;
	int							tablvl;
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
	// ---------Print-------------
	void	print(std::string, std::string);
	void	print_tabulation();
	void	print_servernames(std::vector<Server>&, int);
	void	print_listen(std::vector<Server>&, int);
	void	print_allowmethods(std::vector<Server>&, int, int);
	void	print_index(std::vector<Server>&, int, int);
	void	print_errpage(std::vector<Server>&, int, int);
	void	print_root(std::vector<Server>&, int, int);
	void	print_autoindex(std::vector<Server>&, int, int);
	void	print_mcbs(std::vector<Server>&, int, int);
	void	print_cgidir(std::vector<Server>&, int, int);
	void	print_location(std::vector<Server>&, int);
	void	print_all(std::vector<Server>&);
	// ---------------------------
	void	semi_colon();
	void	brackets();
	int		nbr_words();
	int		openfile();
	int		retrieve_file();
	void	dlt_first();
	int		parse_global();
	int		parse_server(std::vector<Server>&);
	void	parse_mandatory(std::vector<Server>&);
	int		parsing_base(std::vector<Server>&);
	typedef void(Parser::*parsePtr)(std::vector<Server>&);
	void	p_listen_hp_addint(std::string);
	void	p_listen_hp(std::string);
	void	p_location(std::vector<Server>&);
	void	p_servername(std::vector<Server>&);
	void	p_listen(std::vector<Server>&);
	void	p_root(std::vector<Server>&);
	void	p_index(std::vector<Server>&);
	void	p_autoindex(std::vector<Server>&);
	void	p_maxclientbodysize(std::vector<Server>&);
	void	p_errorpage(std::vector<Server>&);
	void	p_cgidir(std::vector<Server>&);
	void	p_allowmethods(std::vector<Server>&);
	// Exceptions //
};
}
