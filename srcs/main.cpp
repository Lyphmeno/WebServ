/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlevi <hlevi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:11:25 by hlevi             #+#    #+#             */
/*   Updated: 2023/02/07 16:48:14 by hlevi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Webserv.hpp"
#include <algorithm>

int	parsing(ft::Webserv base)
{
    if (base.open_file())
        return (-1);
    while (base._file)
    {
        std::getline(base._file, base._line, '\n');
		base._line.erase(std::remove(base._line.begin(), base._line.end(), '\n'), base._line.end());
		if (!base._line.empty())
			std::cout << base._line << std::endl;
    }
    base._file.close();
	return (0);
}

int main(int ac, char **av)
{
	ft::Webserv		base;

	if (ac != 2)
		return (-1);
	base._filename = av[1];
	if (parsing(base))
		return (-1);
    return (0);
}
