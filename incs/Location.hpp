/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlevi <hlevi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 14:55:36 by hlevi             #+#    #+#             */
/*   Updated: 2023/02/20 18:15:47 by hlevi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <string>

namespace ft {
struct	Location
{
	std::vector<std::string>	allow_methods;
	std::vector<std::string>	index;
	std::vector<std::string>	err_page;
	std::string					path;
	std::string					root;
    std::string					auto_index;
    std::string					max_client_body_size;
    std::string					cgi_dir;
};
}
