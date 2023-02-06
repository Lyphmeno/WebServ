/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlevi <hlevi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:11:25 by hlevi             #+#    #+#             */
/*   Updated: 2023/02/06 18:24:18 by hlevi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Webserv.hpp"
#include <string>
#include <fstream>
#include <iostream>

int main(int ac, char **av)
{
    if (ac != 2)
        return (-1);
    filename = av[1];
    file.open(filename);
    if (!file.is_open())
        return (-1);
    while (file)
    {
        std::getline(file, line, '\n');
        std::cout << line << std::endl;
    }
    file.close();
    return (0);
}