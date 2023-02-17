/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlevi <hlevi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 14:55:36 by hlevi             #+#    #+#             */
/*   Updated: 2023/02/17 14:11:42 by hlevi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

namespace ft {
struct	Location
{
	std::string	root;
    std::string	err_page;
    std::string	index;
    std::string	auto_index;
    std::string	max_client_body_size;
    std::string	cgi_ext;
};
}
