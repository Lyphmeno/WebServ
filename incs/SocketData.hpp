/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketData.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 18:25:01 by avarnier          #+#    #+#             */
/*   Updated: 2023/03/19 04:52:53 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include "../incs/Request.hpp"

#define HEADER 0
#define PARSING 1
#define BODY 2
#define SENDING 3

namespace ft {

struct SocketData
{

public:
	SocketData(const Server &config);
	SocketData(const SocketData &x);
	SocketData	&operator=(const SocketData &x);
	~SocketData();
	void	clear();
private:
	SocketData();

public:
	char		step;
	size_t		bodysize;
	Request		req;
	std::string	rep;

};

}
