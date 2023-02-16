#include "../incs/Response.hpp"
#include <fstream>
#include <ctime>

////////////////////////////////////////////////////////////////////////////////
//                              CONSTRUCTORS                                  //
////////////////////////////////////////////////////////////////////////////////

ft::Response::Response(void) : _allowedMethod(0){

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

void ft::Response::setAllowedMethod(int allowed){
    this->_allowedMethod = allowed;
}

void ft::Response::handleErrors(){
    if (_code == "404"){
        _body = "<html>\n"
        "<head><title>404 Not Found</title></head>\n"
        "<center><h1>404 Not Found</h1></center>\n"
        "</body>\n"
        "</html>\n";
    }
    if (_code == "405"){
        _body = "<html>\n"
        "<head><title>405 Method Not Allowed</title></head>\n"
        "<center><h1>405 Method Not Allowed</h1></center>\n"
        "</body>\n"
        "</html>\n";
    }
    if (_code == "500"){
        _body = "<html>\n"
        "<head><title>500 Internal Server Error</title></head>\n"
        "<center><h1>500 Internal Server Error</h1></center>\n"
        "</body>\n"
        "</html>\n";
    }
}

void ft::Response::setError(std::string code)
{
    _code = code;
    _status = _codeStatus.getStatus(code);
    _contentType = "text/html";
    handleErrors();
}

const std::string & ft::Response::addContentType(void){

    std::string extension = "";
    
    size_t found = _url.find(".");
    extension.insert(0, _url, found + 1);
    return (_Mime.getType(extension));
}

void ft::Response::createBody(const std::string & url){

    std::ifstream ifs(url.c_str());
    std::string buff;


    if (_allowedMethod == 0)
    {
        if (!ifs.is_open())
        {
            setError("404");
            return ;
        }
        _code = "200";
        _status = _codeStatus.getStatus("200");
        setContentType(addContentType());
        while (std::getline(ifs, buff) != 0)
        {
            _body += buff;
            _body += "\n";
        }
        _body.erase(_body.size() - 1,1);
        return ;
    }
    setError("405");
    return ;
}

void ft::Response::buildFullResponse(){
    std::string full;
    time_t now = std::time(0);

    char* date_time = std::ctime(&now);

    full = _protVersion + " " + _code + " " + _status;
    full += "\n";
    full += "Date: ";
    full += date_time;
    full += "Content-type: " + _contentType;
    full += "\n\n";
    full += _body;

    _responseFull = full;

}

const std::string & ft::Response::getFullResponse(void){
    return _responseFull;
}
