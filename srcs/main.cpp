/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:11:25 by hlevi             #+#    #+#             */
/*   Updated: 2023/04/28 21:07:25 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Webserv.hpp"
#include <exception>
#include <csignal>

bool	sig = false;

void    signalHandler(int signal)
{
    if (signal == SIGINT)
		sig = true;
}

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr << "\033[31mError: webserv takes a configuration file as an argument\033[0m\n";
		return (-1);
	}

	try 
	{
		std::signal(SIGINT, signalHandler);
		ft::Webserv     engine(av[1]);
		engine.run();
	}
	catch (std::exception &e)
	{ 
		std::cout << "\033[31m" << e.what() << "\033[0m" << "\n";
	}

    return (0);
}