#include "../incs/Response.hpp"
#include <fstream>

////////////////////////////////////////////////////////////////////////////////
//                              CONSTRUCTORS                                  //
////////////////////////////////////////////////////////////////////////////////

ft::Response::Response(void) {

}

ft::Response::Response(const Response & src){
    *this = src;
}



////////////////////////////////////////////////////////////////////////////////
//                               DESTRUCTOR                                   //
////////////////////////////////////////////////////////////////////////////////

ft::Response::~Response(void){
}



////////////////////////////////////////////////////////////////////////////////
//                                OPERATORS                                   //
////////////////////////////////////////////////////////////////////////////////

ft::Response & ft::Response::operator=(Response const & value) {
    if (&value != this)
    {
    }
    return *this;
}

////////////////////////////////////////////////////////////////////////////////
//                                GETTERS                                     //
////////////////////////////////////////////////////////////////////////////////

const std::string & ft::Response::getProtVersion(void){
    return this->_protVersion;
}

const std::string & ft::Response::getContentType(void){
    return this->_contentType;
    
}

const std::string & ft::Response::getURL(void){
    return this->_url;
}


////////////////////////////////////////////////////////////////////////////////
//                                 SETTERS                                    //
////////////////////////////////////////////////////////////////////////////////


void ft::Response::setProtVersion(std::string version){
    this->_protVersion = version;
}

void ft::Response::setContentType(std::string contentType){
    this->_contentType = contentType;
}

void ft::Response::setURL(std::string url){
    this->_url = url;
}

void ft::Response::handleErrors(){
    if (_code == "404"){
        _body = "<html>\n"
        "<head><title>404 Not Found</title></head>\n"
        "<center><h1>404 Not Found</h1></center>\n"
        "</body>\n"
        "</html>\n";
    }
}

void ft::Response::createBody(const std::string & url){

    std::ifstream ifs(url.c_str());
    std::string buff;

    if (!ifs.is_open())
    {
        _code = "404";
        _status = _codeStatus.getStatus("404");
        handleErrors();
        return ;
    }
    _code = "200";
    _status = _codeStatus.getStatus("200");
    while (std::getline(ifs, buff) != 0)
    {
        _body += buff;
        _body += "\n";
    }
}

void ft::Response::buildFullResponse(){
    std::string full;

    full = _protVersion + " " + _code + " " + _status;
    full += "\n";
    full += "Content-type: " + _contentType;
    full += "\n\n";
    full += _body;

    std::cout << full << std::endl;
}