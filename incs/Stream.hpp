/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stream.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 02:56:32 by avarnier          #+#    #+#             */
/*   Updated: 2023/04/21 04:13:38 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../incs/TmpFile.hpp"
#include <unistd.h>
#include <cstdio>

namespace ft {

class Stream
{
public:
    Stream();
    ~Stream();
private:
    Stream(const Stream &x);
    Stream &operator=(const Stream &x);

public:
    TmpFile tmpfile;
    int     fd;
};

}