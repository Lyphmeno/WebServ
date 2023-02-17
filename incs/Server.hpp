#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include <vector>

#include "Location.hpp"

namespace ft {

struct  Server
{
	std::string				server_name;
	std::string				listen;
	std::vector<Location>	locations;
	sockaddr_in				addr;
};

}