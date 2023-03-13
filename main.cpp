#include <fstream>
#include "incs/Request.hpp"
#include "incs/Response.hpp"
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include "incs/Request.hpp"
#include "incs/Webserv.hpp"
#include <fcntl.h>

#define PORT 8080


int main(int ac, char **av)
{
	if (ac != 2) {
		std::cerr << "\033[31mError: webserv takes a configuration file as an argument\033[0m\n";
		return (-1);
	}
	try {
		ft::Webserv		base(av[1]);
	} catch (std::exception &e) {
		std::cout << "\033[31m" << e.what() << "\033[0m" << "\n";
	}
    return (0);
}