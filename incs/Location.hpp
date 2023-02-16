#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

namespace ft {
class Location
{
public:
	std::string	root;
    std::string	err_page;
    std::string	index;
    std::string	auto_index;
    std::string	max_client_body_size;
    std::string	cgi_ext;
public:
	// Coplien //
	Location();
	Location(const Location &cpy);
	~Location();
	Location &operator=(const Location &rhs);
	// Assignation contructors //
	// Operators //
	// Getters //
	// Setters //
	// Methods //
	// Exceptions //
};
}