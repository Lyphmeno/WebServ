#include "../incs/Webserv.hpp"

int main()
{
	try
	{
		ft::Webserv	w;
		w.run();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	return (0);
}