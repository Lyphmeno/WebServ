/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:11:25 by hlevi             #+#    #+#             */
/*   Updated: 2023/03/13 12:06:12 by hlevi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Webserv.hpp"
#include <exception>

int main(int ac, char **av)
{
	if (ac != 2) {
		std::cerr << "\033[31mError: webserv takes a configuration file as an argument\033[0m\n";
		return (-1);
	}
	try {
		ft::Webserv	engine(av[1]);
		engine.run();
	} 
	catch (std::exception &e) { std::cout << "\033[31m" << e.what() << "\033[0m" << "\n"; }
    return (0);
}
