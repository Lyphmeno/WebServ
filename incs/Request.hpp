#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include "Parser.hpp"
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
        Request(const ft::Server& server);
        Request (const Request & src);

        //Destructor
        ~Request(void);


        //Getters
        std::string getMethod(void);
        std::string getUrl(void);
        std::string getProtVersion(void);
        std::string getRequestLine(void);
        std::string  getElementsHeader(std::string element);

        std::string requestStarter(int readBytes, std::string buffer);

        void parseHeader(void);
        void parseRequest(ft::Response *reponse, int readBytes);

        void getRequestLine(std::string line);
        void checkMethodAllowed(ft::Response *response, std::string method);
        std::map<std::string, std::string> _rawRequest;


        bool Directory(std::string url);
        void getCorrectUrl(void);
        std::string createAutoIndexHtmlPage(const std::string& directoryPath, const std::string & tmp_loc);
        std::string checkIndexVector(std::vector<std::string> Index);


        std::string rawHeader;
        std::string rawBody;

private:

        //Request line
        std::string  _method;
        std::string _url;
        std::string _protocolVersion;

        std::string _tmpLoc;

        std::string _requestLine;

        //Raw
        std::vector<std::string> _requestFull;
        
        //Conf file
        int _indexON;
        std::string _root;
        std::string _index;
//        int _code;
        std::string _autoIndexBody;
        bool _autoIndex;

        //Parser
	ft::Server	_serverParsing;

};

}

#endif
