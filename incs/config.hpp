/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlevi <hlevi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:29:54 by hlevi             #+#    #+#             */
/*   Updated: 2023/02/06 15:30:57 by hlevi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft {

#include <iostream>
#include <string>
#include <vector>

class Config
{
private:
	std::vector<ft::Server>		_servers;
public:
	// Coplien //
	Config();
	Config(const Config &cpy);
	~Config();
	Config &operator=(const Config &rhs);
	// Assignation contructors //
	// Operators //
	// Getters //
	// Setters //
	// Methods //
	// Exceptions //
};
}