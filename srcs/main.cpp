/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlevi <hlevi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:11:25 by hlevi             #+#    #+#             */
/*   Updated: 2023/02/15 10:10:07 by hlevi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Parser.hpp"
#include <exception>


int main(int ac, char **av)
{
	ft::Parser		base;

	if (ac != 2)
		return (-1);
	try {
		base.parsing(av[1]);
	} catch (std::exception &e) {
		std::cout << "\033[31m" << e.what() << "\033[0m" << "\n";
	}
    return (0);
}
