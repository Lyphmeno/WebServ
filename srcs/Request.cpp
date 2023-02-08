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

void ft::Request::parseRequest(void){
    std::vector<std::string>::iterator it = this->_requestFull.begin();
    _requestLine = (*it);
    getRequestLine(_requestLine);
    
}

void ft::Request::getRequestLine(std::string line)
{
    size_t found = line.find(" ");
    this->_method.insert(0, line, 0, found);
    this->_url.insert(0, line, found + 1, line.find(" ", found+1) - found);
    found = line.find(" ", found+1);
    this->_protocolVersion.insert(0, line, found + 1, line.find(" ", found+1) - found);
    
    std::cout << "method = " << this->_method << " | URL = " << this->_url << " | protocol = " << this->_protocolVersion << std::endl;
}