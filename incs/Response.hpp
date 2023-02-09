#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <iostream>
#include <vector>

#define COLOR_START "\033[1;100m"
#define COLOR_RED "\033[31m" 
#define COLOR_GREEN "\033[32m" 
#define COLOR_YELLOW "\033[33m"
#define COLOR_END "\033[0m"

namespace ft{

////////////////////////////////////////////////////////////////////////////////
//                                  REQUEST                                   //
////////////////////////////////////////////////////////////////////////////////

class Response{

public:
        //Constructors
        Response();
        Response (const Response & src);

        //Destructor
        ~Response(void);

        //Operators
        Response & operator=(Response const & value);

        //Getters

        //Setters
        void setProtVersion(std::string version);
        void setContentType(std::string contentType);
        
      
private:
        std::string _protVersion;
        // std::string _status;
        // //int _code;
        std::string _contentType;
        //std::string _contentLenght;
};

}

#endif
