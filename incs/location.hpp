/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlevi <hlevi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 13:38:39 by avarnier          #+#    #+#             */
/*   Updated: 2023/02/06 15:31:56 by hlevi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft {

////////////////////////////////////////////////////////////////////////////////
//                                   route                                    //
////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>

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

#endif