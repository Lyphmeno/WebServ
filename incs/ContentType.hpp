/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ContentType.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:05:03 by avarnier          #+#    #+#             */
/*   Updated: 2023/05/07 17:05:05 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTENTTYPE_HPP
#define CONTENTTYPE_HPP

#include <iostream>
#include <map>

typedef struct s_data{
        std::string _ext;
        std::string _type;
}               t_data;

namespace ft{

////////////////////////////////////////////////////////////////////////////////
//                                  REQUEST                                   //
////////////////////////////////////////////////////////////////////////////////

class ContentType{

public:
        //Constructors
        ContentType();

        //Destructor
        ~ContentType(void);


        //Getters
        const std::string & getType(std::string extension);

        void initMime(std::string ext, std::string type);
		void	clear();
private:

       std::map<std::string, t_data> _mimeType;

};

}

#endif
