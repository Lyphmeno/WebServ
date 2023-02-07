/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlevi <hlevi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:11:25 by hlevi             #+#    #+#             */
/*   Updated: 2023/02/07 15:00:38 by hlevi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Webserv.hpp"

int main(int ac, char **av)
{
	ft::Webserv		base;

	if (ac != 2)
		return (-1);
	base._filename = av[1];
    if (base.open_file())
        return (-1);
    while (base._file)
    {
        std::getline(base._file, base._line, ';');
        std::cout << "| " << base._line << " |" << std::endl;
    }
    base._file.close();
    return (0);
}
