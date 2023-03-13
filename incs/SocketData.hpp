/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketData.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 18:25:01 by avarnier          #+#    #+#             */
/*   Updated: 2023/03/07 18:34:29 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>

namespace ft {

struct SocketData
{

public:
	SocketData();
	SocketData(const SocketData &x);
	SocketData	&operator=(const SocketData &x);
	~SocketData();

public:
	std::string			content;
	bool				body;
	unsigned long int	bytes;

};

}