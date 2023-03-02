/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:11:25 by hlevi             #+#    #+#             */
/*   Updated: 2023/03/02 12:29:02 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Webserv.hpp"
#include <exception>


int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "Webserv only need one .conf" << '\n';
		return (-1);
	}

	try
	{
		ft::Webserv	engine(av[1]);
		engine.run();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

    return (0);
}
