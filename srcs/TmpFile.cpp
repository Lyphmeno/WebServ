/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TmpFile.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 03:41:32 by avarnier          #+#    #+#             */
/*   Updated: 2023/04/21 04:06:54 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/TmpFile.hpp"

namespace ft {

TmpFile::TmpFile()
{
    this->file = tmpfile();
    if (this->file == NULL)
        throw std::runtime_error("TmpFile(Runtime error): failed to open FILE");
}

TmpFile::~TmpFile()
{
    fclose(this->file);
}

}