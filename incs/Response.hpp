#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <iostream>
#include <vector>
#include "StatusCode.hpp"
#include "ContentType.hpp"



namespace ft{

////////////////////////////////////////////////////////////////////////////////
//                                  REQUEST                                   //
////////////////////////////////////////////////////////////////////////////////

class Response{

public:
        //Constructors
        Response();

        //Destructor
        ~Response(void);


        //Getters
        const std::string & getProtVersion(void);
        const std::string & getContentType(void);
        const std::string & getURL(void);
        const std::string & getFullResponse(void);


        //Setters
        void setProtVersion(std::string version);
        void setContentType(std::string contentType);
        void setAllowedMethod(int allowed);
        void setURL(std::string url);
        void setMethod(std::string method);
        void setContentLenght(int valread);

        const std::string & addContentType(void);
        void createBody(const std::string & url);
        void buildFullResponse();
        void handleErrors();
        void setError(std::string code);

        //Methods
        void GET_method(const std::string & url);
        void POST_method(const std::string & url);

private:
        //request line
        std::string _protVersion;
        std::string _url;
        std::string _method;

        int _allowedMethod;

        //headers and body
        std::string _contentType;
        std::string _server;
        std::string _body;

        int _contentLenght;
        
        ft::ContentType _Mime;

        //Errors
        std::string _code;
        std::string _status;
        ft::StatusCode _codeStatus;

        //RESPONSE OK
        std::string _responseFull;
};

}

#endif
