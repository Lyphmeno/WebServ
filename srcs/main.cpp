#include "../incs/Webserv.hpp"

int main()
{
	try
	{
		ft::Webserv	webserv;
	}
	catch (std::runtime_error &e)
	{
		std::cout << e.what() << std::endl;
	}
	return (0);
}