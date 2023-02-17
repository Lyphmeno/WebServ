#pragma once

#include <string>

namespace ft {

struct	Location
{
	std::string	root;
    std::string	err_page;
    std::string	index;
    std::string	auto_index;
    std::string	max_client_body_size;
    std::string	cgi_ext;
};

}