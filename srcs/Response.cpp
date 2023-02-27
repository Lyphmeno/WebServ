#include "../incs/Response.hpp"
#include <algorithm>

static std::string itostring(int toConvert){
    std::ostringstream tm;
    tm << toConvert;
    return tm.str();
}

////////////////////////////////////////////////////////////////////////////////
//                              CONSTRUCTORS                                  //
////////////////////////////////////////////////////////////////////////////////

ft::Response::Response(void) : _allowedMethod(0){

}

////////////////////////////////////////////////////////////////////////////////
//                               DESTRUCTOR                                   //
////////////////////////////////////////////////////////////////////////////////

ft::Response::~Response(void){
}

////////////////////////////////////////////////////////////////////////////////
//                                OPERATORS                                   //
////////////////////////////////////////////////////////////////////////////////


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

const std::string & ft::Response::getFullResponse(void){
    return _responseFull;
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

void ft::Response::setMethod(std::string method){
    this->_method = method;
}

void ft::Response::setRawBody(std::string body){
    this->_rawBody = body;
}

void ft::Response::setContentLenght(int valread){
    this->_contentLenght = valread;
}

void ft::Response::setRawResponse(std::map<std::string, std::string> rr){
    this->_rawResponse = rr;
}

////////////////////////////////////////////////////////////////////////////////
//                                 FUNCTIONS                                  //
////////////////////////////////////////////////////////////////////////////////

/*
    Body for errors
*/
void ft::Response::handleErrors(){
    std::string pageName;

    pageName = "html/errors_pages/" + _code;
    pageName.append(".html");
    std::ifstream ifs(pageName.c_str());
    std::string buff;

    while (std::getline(ifs, buff) != 0)
    {
        _body += buff;
        _body += "\n";
    }
}

/*
    Set error status and code
*/
void ft::Response::setError(std::string code)
{
    _code = code;
    _status = _codeStatus.getStatus(code);
    _contentType = "text/html";
    handleErrors();
}

/*
    Check extension to add the content type
*/
const std::string & ft::Response::addContentType(void){

    std::string extension = "";
    
    size_t found = _url.find(".");
    extension.insert(0, _url, found + 1);
    return (_Mime.getType(extension));
}

/*..............................................................................
..                                 METHODS                                    ..
..............................................................................*/

/* get */

void ft::Response::GET_method(const std::string & url){
    
    std::ifstream ifs(url.c_str());
    std::string buff;

    std::cout << url<< std::endl;
    if (!ifs.is_open())
    {
        setError("404");
        return ;
    }
    _code = "200";
    _status = _codeStatus.getStatus("200");
    while (std::getline(ifs, buff) != 0)
    {
        _body += buff;
        _body += "\n";
    }
    _body.erase(_body.size() - 1,1);
}

/* post */

typedef void(ft::Response::*fPtr)(void);

void ft::Response::urlencoded(void){
    size_t pos = 0;
    std::string token;
    std::string value;

    while ((pos = _rawBody.find("=")) != std::string::npos) {
        token = _rawBody.substr(0, pos);
        _rawBody.erase(0, pos + 1);
        if ((pos = _rawBody.find("&")) != std::string::npos)
        {
            value = _rawBody.substr(0, pos);
            value.erase(std::remove(value.begin(), value.end(), 13), value.end());
        }
        _rawBody.erase(0, pos + 1);
        _formValues[token] = value;
    }
    _formValues[token] = _rawBody;
}

void ft::Response::multi(void){
    std::cout << "multi" << std::endl;
    (void)_rawBody;

}


void ft::Response::plain(void){
    size_t pos = 0;
    std::string token;
    std::string value;

    while ((pos = _rawBody.find("=")) != std::string::npos) {
        token = _rawBody.substr(0, pos);
        _rawBody.erase(0, pos + 1);
        if ((pos = _rawBody.find("\n")) != std::string::npos)
        {
            value = _rawBody.substr(0, pos);
            value.erase(std::remove(value.begin(), value.end(), 13), value.end());
        }
        _rawBody.erase(0, pos + 1);
        _formValues[token] = value;
    }

}

void ft::Response::POST_method(const std::string & url){
    
    std::ifstream ifs(url.c_str());
    std::string enctype;


    if (!ifs.is_open())
    {
        setError("404");
        return ;
    }
    _code = "200";
    _status = _codeStatus.getStatus("200");
    enctype = _rawResponse["Content-Type"];

    fPtr enc[3] = {
        &ft::Response::urlencoded,
        &ft::Response::multi,
        &ft::Response::plain,
    };

    const std::string type[3] = {"application/x-www-form-urlencoded", "multipart/form-data", "text/plain"};
    int i = 0;
    for (; i < 3; i++)
    {
        if (type[i] == enctype)
            (this->*enc[i])();
    }
    if (i > 3)
        (this->*enc[1])();
    return ;
}

/* delete */

void ft::Response::DELETE_method(const std::string & url){
    
    int status;

    if (url.find("..") != std::string::npos)
    {
        _code = "400";
        _status = _codeStatus.getStatus("400");
        return;
    }
    status = std::remove(url.c_str());
    if (status != 0)
    {
         _code = "404";
        _status = _codeStatus.getStatus("404");
        return;
    }
    _code = "200";
    _status = _codeStatus.getStatus("200");
}

/*
    Create the body according to the good method
*/
void ft::Response::createBody(const std::string & url){

    if (_allowedMethod == 0)
    {
        if (_method == "GET")
            GET_method(url);
        else if (_method == "POST")
            POST_method(url);
        else if (_method == "DELETE")
            DELETE_method(url);
        return ;
    }
    setError("405");
    return ;
}

/*
    Final response for the client
*/
void ft::Response::buildFullResponse(){
    std::string full;
    time_t now = std::time(0);

    std::string lenght = itostring(_contentLenght);
    char* date_time = std::ctime(&now);

    full = _protVersion + " " + _code + " " + _status;
    full += "\n";
    full += "Date: ";
    full += date_time;
    full += "Content-type: " + _contentType;
    full += "\nContent-Lenght: " + lenght; 
    full += "\n\n";
    full += _body;

    _responseFull = full;
}