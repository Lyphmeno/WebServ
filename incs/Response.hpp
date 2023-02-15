#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <iostream>
#include <vector>
#include "StatusCode.hpp"
#include "ContentType.hpp"

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
        void setAllowedMethod(int allowed);
        void setURL(std::string url);

        const std::string & getProtVersion(void);
        const std::string & getContentType(void);
        const std::string & getURL(void);

        const std::string & addContentType(void);
        void createBody(const std::string & url);
        void buildFullResponse();
        void handleErrors();
        void setError(std::string code);

      
private:
        std::string _protVersion;

        std::string _code;
        std::string _status;

        std::string _contentType;
        std::string _server;
        std::string _body;
        std::string _url;

        ft::StatusCode _codeStatus;

        int _allowedMethod;
        // int _contentLenght;
};

}

#endif
