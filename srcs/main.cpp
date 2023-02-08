/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlevi <hlevi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:11:25 by hlevi             #+#    #+#             */
/*   Updated: 2023/02/08 12:17:57 by hlevi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/parser.hpp"

int	parsing(ft::parser base)
{
    if (base.open_file())
        return (-1);
    while (base._file)
    {
        std::getline(base._file, base._line, '\n');
		base._line.erase(std::remove(base._line.begin(), base._line.end(), '\n'), base._line.end());
		if (!base._line.empty())
			base._buffer.push_back(base._line);
		/* PARSING algorithm
		 *	- depends on bracket level
		 *	- if lvl 0 -> check for global tag, if else error 
		 *	- if lvl 1 -> check for server tag only or other
		 *	- if lvl > 1 -> check for location/serevr tag
		 *	- Program should end with brackets lvl of 0 or error is returned 
		 */
    }
	base.printv();
    base._file.close();
	return (0);
}

int main(int ac, char **av)
{
	ft::parser		base;

	if (ac != 2)
		return (-1);
	base._filename = av[1];
	if (parsing(base))
		return (-1);
    return (0);
}
