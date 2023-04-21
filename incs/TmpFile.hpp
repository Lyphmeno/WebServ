/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TmpFile.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 03:08:34 by avarnier          #+#    #+#             */
/*   Updated: 2023/04/21 03:55:22 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstdio>
#include <stdexcept>

namespace ft {

struct TmpFile
{
public:
    TmpFile();
    ~TmpFile();
private:
    TmpFile(const TmpFile &x);
    TmpFile &operator=(const TmpFile &x);

public:
    FILE    *file;
};

}