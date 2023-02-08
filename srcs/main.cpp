/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlevi <hlevi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:11:25 by hlevi             #+#    #+#             */
/*   Updated: 2023/02/08 14:49:35 by hlevi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Parser.hpp"

int	parsing(ft::Parser base)
{
    if (base.openfile())
        return (-1);
    while (base.file)
    {
        std::getline(base.file, base.line, '\n');
		base.line.erase(std::remove(base.line.begin(), base.line.end(), '\n'), base.line.end());
		if (!base.line.empty())
			base.buffer.push_back(base.line);
		/* PARSING algorithm
		 *	- depends on bracket level
		 *	- if lvl 0 -> check for global tag, if else error 
		 *	- if lvl 1 -> check for server tag only or other
		 *	- if lvl > 1 -> check for location/serevr tag
		 *	- Program should end with brackets lvl of 0 or error is returned 
		 */
    }
	base.printv();
    base.file.close();
	return (0);
}

int main(int ac, char **av)
{
	ft::Parser		base;

	if (ac != 2)
		return (-1);
	base.filename = av[1];
	if (parsing(base))
		return (-1);
    return (0);
}
