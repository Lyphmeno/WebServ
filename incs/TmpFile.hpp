/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TmpFile.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 17:52:38 by avarnier          #+#    #+#             */
/*   Updated: 2023/04/29 18:25:23 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstdio>
#include <stdexcept>

namespace ft {

class TmpFile
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