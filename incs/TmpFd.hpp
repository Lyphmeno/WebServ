/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TmpFd.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 18:10:36 by avarnier          #+#    #+#             */
/*   Updated: 2023/04/29 19:04:16 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <unistd.h>
#include "../incs/TmpFile.hpp"

namespace ft {

class TmpFd
{
public:
    TmpFd();
    ~TmpFd();
private:
    TmpFd(const TmpFd &x);
    TmpFd   &operator=(const TmpFd &x);

public:
    int     fd;
    TmpFile tmpFile;
};

}