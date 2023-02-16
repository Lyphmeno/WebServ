#include <iostream>
#include "../incs/Socket.hpp"

int main()
{
	try
	{
		ft::Socket	s;
		s.open();
		s.set();
		s.add(100);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return (0);
}