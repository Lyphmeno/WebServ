#include <iostream>
#include "../incs/Socket.hpp"
#include "../incs/epSocket.hpp"
#include "../incs/Webserv.hpp"

int main()
{
	try
	{
		ft::Webserv	w;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return (0);
}
