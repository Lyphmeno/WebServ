/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stream.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 03:02:15 by avarnier          #+#    #+#             */
/*   Updated: 2023/04/21 04:06:42 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Stream.hpp"

namespace ft {

Stream::Stream()
{
    this->fd = fileno(this->tmpfile.file);
    if (this->fd == -1)
        throw std::runtime_error("Stream(Runtime error): failed to open file descriptor");
}

Stream::~Stream()
{
    close(this->fd);
}

}