#include "../incs/Webserv.hpp"
#include <iostream>

int main()
{
	try
	{
		ft::Webserv	engine;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << '\n';
	}
	return (0);
}