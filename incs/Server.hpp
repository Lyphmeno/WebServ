#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include <vector>
#include "Location.hpp"

namespace ft {

struct Server
{
	std::string				server_name;
	std::vector<Location>	locations;
	sockaddr_in				addr;
};

}