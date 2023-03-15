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
        Request(const std::vector<ft::Server> & servers);
        Request (const Request & src);

        //Destructor
        ~Request(void);


        //Getters
        std::string getMethod(void){return _method;};
        std::string getUrl(void){return _url;};
        std::string getProtVersion(void){return _protocolVersion;};
        std::string getRequestLine(void){return _requestLine;};

        std::string requestStarter(int readBytes, char *buffer);

        void fillRequest(char *buffer);
        void parseRequest(ft::Response *response, int readBytes);

        void getRequestLine(std::string line);
        void checkMethodAllowed(ft::Response *response, std::string method);
        std::map<std::string, std::string> _rawRequest;


        bool Directory(std::string url);
        void getCorrectUrl(void);
        std::string createAutoIndexHtmlPage(const std::string& directoryPath, const std::string & tmp_loc);
        std::string checkIndexVector(std::vector<std::string> Index);

        int server_start();

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
        std::string _index;
//        int _code;
        std::string _autoIndexBody;
        bool _autoIndex;

        //Parser
	std::vector<ft::Server>	servParsing;

};

}

#endif
