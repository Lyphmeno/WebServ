#include "../incs/Request.hpp"
#include <fstream>

////////////////////////////////////////////////////////////////////////////////
//                              CONSTRUCTORS                                  //
////////////////////////////////////////////////////////////////////////////////

ft::Request::Request(void) : _indexON(0){

}

ft::Request::Request(const Request & src){
    *this = src;
}



////////////////////////////////////////////////////////////////////////////////
//                               DESTRUCTOR                                   //
////////////////////////////////////////////////////////////////////////////////

ft::Request::~Request(void){
}



////////////////////////////////////////////////////////////////////////////////
//                                OPERATORS                                   //
////////////////////////////////////////////////////////////////////////////////

ft::Request & ft::Request::operator=(Request const & value) {
    if (&value != this)
    {
       this->_method = value._method;
       this->_url = value._url;
       this->_protocolVersion = value._protocolVersion;
    }
    return *this;
}

void ft::Request::fillRequest(std::string line)
{
    this->_requestFull.push_back(line);
}

void ft::Request::checkMethodAllowed(ft::Response *response, std::string method)
{
    if (method != "GET" && method != "POST" && method != "DELETE")
        response->setAllowedMethod(1);
}

void ft::Request::parseRequest(ft::Response *response){
    
    std::vector<std::string>::iterator it = this->_requestFull.begin();
    _requestLine = (*it);
    getRequestLine(_requestLine);
    checkMethodAllowed(response, _method);
    response->setProtVersion(_protocolVersion);
    response->setURL(_url);
}

void ft::Request::getRequestLine(std::string line)
{
    size_t found = line.find(" ");
    this->_method.insert(0, line, 0, found);
    line.erase(0, _method.size() + 1);
    found = line.find(" ");
    this->_url.insert(0, line, 0, found);
    line.erase(0, _url.size() + 1);
    found = line.find(" ");
    this->_protocolVersion.insert(0, line, 0, found);
    if (_url == "/")
    {
        _indexON = 1;
        _url = "index.html"; //rajouter le root
    }
    else
        _url.erase(0, 1);
}

const std::string & ft::Request::requestStarter(){
    std::string line;
    std::ifstream ifs("request");
    ft::Request requestHTTP;
    ft::Response *responseHTTP = new ft::Response();

    if (!ifs.is_open())
    {
        responseHTTP->setContentType("HTTP/1.1");
        responseHTTP->setError("500");
    }
    else
    { 
        while (std::getline(ifs, line) != 0)
        {
            requestHTTP.fillRequest(line);
        }
        requestHTTP.parseRequest(responseHTTP);
        responseHTTP->createBody(requestHTTP.getUrl());
    }
    responseHTTP->buildFullResponse();
    return responseHTTP->getFullResponse();
}