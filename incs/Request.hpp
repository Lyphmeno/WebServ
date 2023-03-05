#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <iostream>
#include <vector>
#include "Response.hpp"



#define GET 1
#define POST 2
#define DELETE 3

namespace ft{

////////////////////////////////////////////////////////////////////////////////
//                                  REQUEST                                   //
////////////////////////////////////////////////////////////////////////////////

class Request{

public:
        //Constructors
        Request();
        Request (const Request & src);

        //Destructor
        ~Request(void);


        //Getters
        std::string getMethod(void){return _method;};
        std::string getUrl(void){return _url;};
        std::string getProtVersion(void){return _protocolVersion;};
        std::string getRequestLine(void){return _requestLine;};

        std::string requestStarter(int readBytes, std::string buffer);

        void fillRequest(std::string buffer);
        void parseRequest(ft::Response *reponse, int readBytes);

        void getRequestLine(std::string line);
        void checkMethodAllowed(ft::Response *response, std::string method);
        std::map<std::string, std::string> _rawRequest;

private:

        //Request line
        std::string  _method;
        std::string _url;
        std::string _protocolVersion;

        std::string _requestLine;

        //Raw
        std::vector<std::string> _requestFull;
        std::string _rawBody;
        
        //Conf file
        int _indexON;
        std::string _root;
       int _code;
};

}

#endif
