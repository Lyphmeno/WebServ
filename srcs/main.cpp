/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:11:25 by hlevi             #+#    #+#             */
/*   Updated: 2023/02/23 08:01:31 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Webserv.hpp"
#include <exception>


int main(int ac, char **av)
{
	if (ac != 2)
		return (-1);
	ft::Webserv		base(av[1]);
    return (0);
}
