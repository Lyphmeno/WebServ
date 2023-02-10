#ifndef STATUSCODE_HPP
#define STATUSCODE_HPP

#include <iostream>
#include <map>

#define COLOR_START "\033[1;100m"
#define COLOR_RED "\033[31m" 
#define COLOR_GREEN "\033[32m" 
#define COLOR_YELLOW "\033[33m"
#define COLOR_END "\033[0m"

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
private:

       std::map<std::string, t_status> _statusCode;

};

}

#endif