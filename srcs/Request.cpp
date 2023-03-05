#include "../incs/Request.hpp"
#include <fstream>
#include <algorithm>
#include <string>

////////////////////////////////////////////////////////////////////////////////
//                              CONSTRUCTORS                                  //
////////////////////////////////////////////////////////////////////////////////

ft::Request::Request(void) : _indexON(0), _root("/"), _code(0){
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

/*
    Add the raw request to a vector
*/
void ft::Request::fillRequest(std::string buffer)
{
    std::string newbuffer;
    std::string value;
    newbuffer = buffer;


    size_t pos = 0;
    std::string token;
   
    if ((pos = newbuffer.find(13)) != std::string::npos)
    {
        _requestLine = newbuffer.substr(0, pos);
        newbuffer.erase(0, pos + 1);
    }
    while ((pos = newbuffer.find(":")) != std::string::npos) {
        token = newbuffer.substr(0, pos);
        newbuffer.erase(0, pos + 2);
        if ((pos = newbuffer.find(13)) != std::string::npos)
        {
            value = newbuffer.substr(0, pos);
            value.erase(std::remove(value.begin(), value.end(), 13), value.end());
        }
        newbuffer.erase(0, pos + 1);
        token.erase(0, 1);
        _rawRequest[token] = value;
    }
    _rawBody = newbuffer;
    _rawBody.erase(0, 3);
}

/*
    Check if method is allowed
*/
void ft::Request::checkMethodAllowed(ft::Response *response, std::string method)
{
    if (method != "GET" && method != "POST" && method != "DELETE")
        response->setAllowedMethod(1);
    response->setMethod(method);
}


/*
    Parse the request line example GET /index.html HTTP/1.1, to set variables
*/
void ft::Request::parseRequest(ft::Response *response, int readBytes){
    response->setRawResponse(_rawRequest);
    response->setRawBody(_rawBody);
    getRequestLine(_requestLine);
    checkMethodAllowed(response, _method);
    response->setProtVersion(_protocolVersion);
    response->setURL(_url);
    response->setContentType(response->addContentType());
    response->setContentLenght(readBytes);
    response->createBody(_url);

}


/*
    Get the URL, method and protocol
*/
void ft::Request::getRequestLine(std::string line)
{
    size_t found = line.find(" ");
    this->_method.insert(0, line, 0, found);
    line.erase(0, _method.size() + 1);
    found = line.find(" ");
    this->_url.insert(0, line, 0, found);
    line.erase(0, _url.size() + 1);
    found = line.find("\n");
    this->_protocolVersion.insert(0, line, 0, found);
    _protocolVersion.erase(_protocolVersion.size(), 1);
    if (_url == "/")
    {
        _indexON = 1;
        _url = "html/pages/index.html"; //rajouter le root
    }
    else
    {
        if (_root != "/")
            _url = _root + _url;
        else
            _url.erase(0, 1);
    }
}

/*
    Function that checks if request exists, then parse the request
    and send it to create the response
*/
std::string ft::Request::requestStarter(int readBytes, std::string buffer){
    ft::Request requestHTTP;
    ft::Response *responseHTTP = new ft::Response();

    if (_code == 0)
    {
        requestHTTP.fillRequest(buffer);
        requestHTTP.parseRequest(responseHTTP, readBytes);
    }
    responseHTTP->buildFullResponse();
    std::string responseR = responseHTTP->getFullResponse(); 
    // responseR.erase(std::remove(responseR.begin(), responseR.end(), 13), responseR.end());
   
    return responseR;
}
