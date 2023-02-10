#include "../incs/Request.hpp"

////////////////////////////////////////////////////////////////////////////////
//                              CONSTRUCTORS                                  //
////////////////////////////////////////////////////////////////////////////////

ft::Request::Request(void){

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

void ft::Request::parseRequest(ft::Response *response){


    std::vector<std::string>::iterator it = this->_requestFull.begin();
    _requestLine = (*it);
    getRequestLine(_requestLine);
    response->setProtVersion(_protocolVersion);
    response->setContentType(getContentType());
    response->setURL(_url);
}

void ft::Request::getRequestLine(std::string line)
{
    size_t found = line.find(" ");
    this->_method.insert(0, line, 0, found);
    this->_url.insert(0, line, found + 2, line.find(" ", found + 1) - found - 2);
    found = line.find(" ", found+1);
    this->_protocolVersion.insert(0, line, found + 1, line.find(" ", found+1) - found);
}

const std::string & ft::Request::getContentType(void){
    ft::ContentType Mime;

    std::string extension = "";
    size_t found = _url.find(".");
    extension.insert(0, _url, found + 1);
    return (Mime.getType(extension));
}