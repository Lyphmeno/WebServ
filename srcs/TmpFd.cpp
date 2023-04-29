/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TmpFd.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 18:20:49 by avarnier          #+#    #+#             */
/*   Updated: 2023/04/29 19:04:19 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/TmpFd.hpp"

namespace ft {

TmpFd::TmpFd()
{
    this->fd = fileno(this->tmpFile.file);
    if (this->fd == -1)
        throw std::runtime_error("Runtime error: Can't initialize TmpFd");
}

TmpFd::~TmpFd()
{
    close(this->fd);
}

}