#ifndef REQUEST_HPP
#define REQUEST_HPP

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

class Request{

public:
        //Constructors
        Request();
        Request (const Request & src);

        //Destructor
        ~Request(void);

        //Operators
        Request & operator=(Request const & value);

        //Getters
        std::string getMethod(void){return _method;};
        std::string getUrl(void){return _url;};
        std::string getProtVersion(void){return _protocolVersion;};
        std::string getRequestLine(void){return _requestLine;};

        void fillRequest(std::string line);
        void parseRequest(void);

        void getRequestLine(std::string line);
private:
       std::string  _method;
       std::string _url;
       std::string _protocolVersion;

       std::string _requestLine;

       std::vector<std::string> _requestFull;

};

}

#endif
