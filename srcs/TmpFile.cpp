/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TmpFile.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 17:57:18 by avarnier          #+#    #+#             */
/*   Updated: 2023/04/29 18:22:13 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/TmpFile.hpp"

namespace ft {

TmpFile::TmpFile()
{
    this->file = tmpfile();
    if (this->file == NULL)
        throw std::runtime_error("Runtime error: Can't initialize TmpFile");
}

TmpFile::~TmpFile()
{
    fclose(this->file);
}

}