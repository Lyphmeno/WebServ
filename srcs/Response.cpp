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

void ft::Response::setContentLenght(int valread){
    this->_contentLenght = valread;
}

void ft::Response::setRawRequest(std::vector<std::string> rawRequest){
    this->_raw = rawRequest;
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

typedef void(ft::Response::*fPtr)(std::string body);

void ft::Response::urlencoded(std::string body){
    size_t pos = 0;
    std::string token;
    std::string value;

    while ((pos = body.find("=")) != std::string::npos) {
        token = body.substr(0, pos);
        body.erase(0, pos + 1);
        if ((pos = body.find("&")) != std::string::npos)
        {
            value = body.substr(0, pos);
            value.erase(std::remove(value.begin(), value.end(), 13), value.end());
        }
        body.erase(0, pos + 1);
        // std::cout << "[token = " << token << "] [value = " << value << "]" << std::endl; 
        _formValues[token] = value;
    }
}

void ft::Response::multi(std::string body){
    std::cout << "multi" << std::endl;
    (void)body;

}


void ft::Response::plain(std::string body){
    size_t pos = 0;
    std::string token;
    std::string value;

    std::cout << "plain" << std::endl;
    while ((pos = body.find("=")) != std::string::npos) {
        token = body.substr(0, pos);
        body.erase(0, pos + 1);
        if ((pos = body.find("\n")) != std::string::npos)
        {
            value = body.substr(0, pos);
            value.erase(std::remove(value.begin(), value.end(), 13), value.end());
        }
        body.erase(0, pos + 1);
        _formValues[token] = value;
    }

}

void ft::Response::POST_method(const std::string & url){
    
    std::ifstream ifs(url.c_str());
    std::string raw;
    std::string body;
    std::string enctype;


    if (!ifs.is_open())
    {
        setError("404");
        return ;
    }
    _code = "200";
    _status = _codeStatus.getStatus("200");
    for (std::vector<std::string>::iterator it = _raw.begin(); it != _raw.end(); ++it){
        raw += (*it);
        raw += "\n";
        if ((raw.find("Content-Type: ") != std::string::npos) && enctype.empty())
        {
            enctype = raw.substr(raw.find("Content-Type: "));
            enctype.erase(0, 14);
            if (enctype.find("multipart/form-data;") != std::string::npos)
                enctype = "multipart/form-data";
        }

    }
    std::cout << enctype << std::endl;
    if (raw.find("\r\n\r\n") != std::string::npos)
    {
    
       body = raw.substr(raw.find("\r\n\r\n"));
       body.erase(0, 4);
    }
    enctype.erase(std::remove(enctype.begin(), enctype.end(), 13), enctype.end());
    enctype.erase(std::remove(enctype.begin(), enctype.end(), '\n'), enctype.end());

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
            (this->*enc[i])(body);
    }
    if (i > 3)
        (this->*enc[1])(body);
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