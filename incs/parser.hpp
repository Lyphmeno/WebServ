/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlevi <hlevi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 12:12:56 by hlevi             #+#    #+#             */
/*   Updated: 2023/02/08 12:28:05 by hlevi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

#define GLOB 1
#define SERV 2
#define SLOC 3

namespace ft {
class parser
{
public:
	std::fstream    			_file;
	std::string     			_filename;
    std::string     			_line;
	std::vector<std::string>	_buffer;
	int							_inbrackets;
public:
	// Coplien //
	parser();
	parser(const parser &cpy);
	~parser();
	parser &operator=(const parser &rhs);
	// Assignation contructors //
	// Operators //
	// Getters //
	// Setters //
	// Methods //
	int	open_file();
	void	printv();
	// Exceptions //
};
}
