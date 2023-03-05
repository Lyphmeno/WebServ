/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketData.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 18:25:09 by avarnier          #+#    #+#             */
/*   Updated: 2023/03/03 21:54:11 by avarnier         ###   ########.fr       */
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
	bool				post;
	bool				header;
	unsigned long int	hlen;
	unsigned long int	blen;
	std::string			request;
	std::string			response;
};


}