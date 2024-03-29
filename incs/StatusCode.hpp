/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StatusCode.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:04:12 by avarnier          #+#    #+#             */
/*   Updated: 2023/05/07 17:05:09 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATUSCODE_HPP
#define STATUSCODE_HPP

#include <iostream>
#include <map>



typedef struct s_status{
        std::string _code;
        std::string _status;
}               t_status;

namespace ft{

////////////////////////////////////////////////////////////////////////////////
//                                  REQUEST                                   //
////////////////////////////////////////////////////////////////////////////////

class StatusCode{

public:
        //Constructors
        StatusCode();
        StatusCode (const StatusCode & src);

        //Destructor
        ~StatusCode(void);

        //Operators
        StatusCode & operator=(StatusCode const & value);

        //Getters
        const std::string & getStatus(std::string code);

        void initStruct(std::string code, std::string status);
		void	clear();
private:

       std::map<std::string, t_status> codeStatus;

};

}

#endif
