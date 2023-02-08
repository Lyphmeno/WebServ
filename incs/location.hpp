/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlevi <hlevi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 13:38:39 by avarnier          #+#    #+#             */
/*   Updated: 2023/02/08 12:21:06 by hlevi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once


////////////////////////////////////////////////////////////////////////////////
//                                   route                                    //
////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>

namespace ft {
struct location
{
//route variables
public:
	std::string					path;
	std::vector<std::string>	methods;
	std::string					root;
	bool						autoindex;
	std::string					fileIsDir_error_path;
	std::string					cgi_pass;
	int							client_body_buffer_size;
};
}
