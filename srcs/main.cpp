/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlevi <hlevi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:11:25 by hlevi             #+#    #+#             */
/*   Updated: 2023/02/17 14:44:57 by hlevi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Webserv.hpp"
#include <exception>


int main(int ac, char **av)
{
	ft::Webserv		base;

	if (ac != 2)
		return (-1);
	try {
		base.parser.parsing(av[1]);
	} catch (std::exception &e) {
		std::cout << "\033[31m" << e.what() << "\033[0m" << "\n";
	}
    return (0);
}
