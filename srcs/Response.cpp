#include "../incs/Response.hpp"
#include <dirent.h> 
#include <algorithm>


static std::string itostring(int toConvert){
    std::ostringstream tm;
    tm << toConvert;
    return tm.str();
}

////////////////////////////////////////////////////////////////////////////////
//                              CONSTRUCTORS                                  //
////////////////////////////////////////////////////////////////////////////////

ft::Response::Response(void) : _allowedMethod(0), _body(""){


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

void ft::Response::setProtVersion(ft::Server server){
    this->_serverParsing = server;
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

void ft::Response::setRawBody(std::vector<unsigned char> body){
    this->_rawBody = body;
}

void ft::Response::setBody(std::string newBody){
    this->_body = newBody;
}

void ft::Response::setContentLenght(int valread){
    this->_contentLenght = valread;
}

void ft::Response::setCode(std::string code){
    this->_code = code;
}

void ft::Response::setAutoIndex(bool autoIndex){
    this->_autoIndex = autoIndex;
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

    pageName = _serverParsing.getErrorPage(tmp)

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
    std::cout << extension << std::endl;
    return (_Mime.getType(extension));
}

void ft::Response::createAutoIndexHtmlPage(const std::string& directoryPath) {
    // Get the list of HTML files in the directory
    std::vector<std::string> htmlFiles;

    DIR* dir = opendir(directoryPath.c_str());
    struct dirent* entry;
    while ((entry = readdir(dir))) {
        std::string filename = entry->d_name;
        if (filename.find(".html") != std::string::npos) {
            htmlFiles.push_back(filename);
        }
    }
    closedir(dir);

    // Sort the list of HTML files
    sort(htmlFiles.begin(), htmlFiles.end());

    // Create the autoindex HTML page
    std::ofstream outputFile((directoryPath + "/index.html").c_str());
    outputFile << "<!DOCTYPE html>\n";
    outputFile << "<html>\n";
    outputFile << "  <head>\n";
    outputFile << "    <title>Autoindex</title>\n";
    outputFile << "  </head>\n";
    outputFile << "  <body>\n";
    outputFile << "    <h1>Index of " << directoryPath << "</h1>\n";
    outputFile << "    <ul>\n";
    for (std::vector<std::string>::const_iterator it = htmlFiles.begin(); it != htmlFiles.end(); ++it) {
        outputFile << "      <li><a href=\"" << *it << "\">" << *it << "</a></li>\n";
    }
    outputFile << "    </ul>\n";
    outputFile << "  </body>\n";
    outputFile << "</html>\n";
}



/*..............................................................................
..                                 METHODS                                    ..
..............................................................................*/

/* get */
void ft::Response::getM(const std::string & url){
    
    std::ifstream ifs(url.c_str());
    std::string buff;

    // if (!ifs.is_open() && _autoIndex == false)
    // {
    //     setError("404");
    //     return ;
    // }
    _code = "200";
    _status = _codeStatus.getStatus("200");
    if (_body == "")
    {
        while (std::getline(ifs, buff) != 0)
        {
            _body += buff;
            _body += "\n";
        }
        _body.erase(_body.size() - 1,1);
    }
}

/* post */

typedef void(ft::Response::*fPtr)(void);

void ft::Response::urlencoded(void){
    std::vector<unsigned char>::iterator pos;
    std::string token;
    std::string value;

    std::map<std::string, std::string> _formValues;

    while ((pos = std::find(_rawBody.begin(), _rawBody.end(), '=')) != _rawBody.end()) {
        token.assign(_rawBody.begin(), pos);
        _rawBody.erase(_rawBody.begin(), pos + 1);
        if ((pos = std::find(_rawBody.begin(), _rawBody.end(), '&')) != _rawBody.end()) {
            value.assign(_rawBody.begin(), pos);
            value.erase(std::remove(value.begin(), value.end(), '\r'), value.end());
            _rawBody.erase(_rawBody.begin(), pos + 1);
            _formValues[token] = value;
        }
    }
    _formValues[token] = std::string(_rawBody.begin(), _rawBody.end());

}

void ft::Response::initPostStruct(std::vector<unsigned char> fullBody){

    std::vector<unsigned char>::iterator it;
    std::string limiter = "\r\n\r\n";
    std::string headers;
    size_t pos = 0;
    std::string token;

    if ((it = std::search(fullBody.begin(), fullBody.end(), limiter.begin(), limiter.end())) != fullBody.end()){
        headers.assign(fullBody.begin(), it);
        fullBody.erase(fullBody.begin(), it + limiter.size());
    }
    while ((pos = headers.find(": ")) != std::string::npos) {
        token = headers.substr(0, pos);
        headers.erase(0, pos + 2);
        if (token == "Content-Disposition")
        {
            if ((pos = headers.find("name=\"")) != std::string::npos) {
                headers.erase(0, pos + 6);
                if ((pos = headers.find("\"")) != std::string::npos)
                    token = headers.substr(0, pos);
            }
            if ((pos = headers.find("filename=\"")) != std::string::npos) {
                headers.erase(0, pos + 10);
                if ((pos = headers.find("\"")) != std::string::npos)
                {
                    std::string filename = headers.substr(0, pos);
                    _multipartForm[token].filename = filename; 
                }
            }
            _multipartForm[token].name = token;
            std::cout << token << " = "   <<  _multipartForm[token].name << std::endl;
            tmpName = token;
        }
    }
    _multipartForm[tmpName].value = fullBody;
    filename = "html/uploads/" + _multipartForm[tmpName].filename;//add root
    std::ofstream ofs(filename.c_str());
    if (ofs.is_open()){
        for (size_t i = 0; i < fullBody.size(); ++i) {
            ofs << fullBody[i];
        }
    }

}

std::vector<unsigned char> getOnlyBody(std::vector<unsigned char> &body, std::string tmp){
    std::vector<unsigned char> fullBody;

    std::string boundary = "------" + tmp;
    std::vector<unsigned char> boundaryVec(boundary.begin(), boundary.end());
    std::vector<unsigned char>::iterator it;

    if ((it = std::search(body.begin(), body.end(), boundaryVec.begin(), boundaryVec.end())) != body.end()) {
        if (it != body.end()) {
            fullBody.assign(body.begin(), it);
        } else {
            fullBody.assign(body.begin(), it + 2);
        }
    }
    body.erase(body.begin(), body.begin() + fullBody.size());
    return fullBody;
}

void ft::Response::multi(void){
    size_t pos = 0;
    std::string tmp = _rawResponse["Content-Type"];
    std::vector<unsigned char> tmpRawBody = _rawBody;
    std::vector<unsigned char> ret;


    if ((pos = tmp.find(" boundary=----")) != std::string::npos) {
        tmp.erase(0, pos + 14);
    }
    std::string boundary(tmp.begin(), tmp.end());

    std::vector<unsigned char>::iterator it;
    while ((it = std::search(tmpRawBody.begin(), tmpRawBody.end(), boundary.begin(), boundary.end())) != tmpRawBody.end()) {
        tmpRawBody.erase(tmpRawBody.begin(), it + boundary.size() + 2);
        initPostStruct(getOnlyBody(tmpRawBody, boundary));
        if (tmpRawBody.size() == boundary.size() + 10)
            break;
    }
}


void ft::Response::plain(void){
    size_t pos = 0;
    std::vector<unsigned char> token;
    std::vector<unsigned char> value;
    std::string tokenStr;
    std::string valueStr;

    while ((pos = std::find(_rawBody.begin(), _rawBody.end(), '=') - _rawBody.begin()) != _rawBody.size()) {
        token = std::vector<unsigned char>(_rawBody.begin(), _rawBody.begin() + pos);
        _rawBody.erase(_rawBody.begin(), _rawBody.begin() + pos + 1);
        if ((pos = std::find(_rawBody.begin(), _rawBody.end(), '\n') - _rawBody.begin()) != _rawBody.size()) {
            value = std::vector<unsigned char>(_rawBody.begin(), _rawBody.begin() + pos);
            value.erase(std::remove(value.begin(), value.end(), 13), value.end());
            _rawBody.erase(_rawBody.begin(), _rawBody.begin() + pos + 1);
        }
        tokenStr = std::string(token.begin(), token.end());
        valueStr = std::string(value.begin(), value.end());
        _formValues[tokenStr] = valueStr;
    }
}

void ft::Response::postM(const std::string & url){
    
    std::ifstream ifs(url.c_str());
    std::string enctype;


    if (!ifs.is_open())
    {
        setError("404");
        return ;
    }
    _code = "200";
    _status = _codeStatus.getStatus("200");
    if (_rawResponse["Content-Type"].find("multipart/form-data;") != std::string::npos)
        enctype = "multipart/form-data";
    else
        enctype = _rawResponse["Content-Type"];

    std::cout << "enctype = " << enctype << std::endl;
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

void ft::Response::deleteM(const std::string & url){
    
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

    if (_allowedMethod != 0)
    {
        if (_method == "GET")
            getM(url);
        else if (_method == "POST")
            postM(url);
        else if (_method == "DELETE")
            deleteM(url);
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

    if (_code != "200")
        setError(_code);
    
    full = _protVersion + " " + _code + " " + _status;
    full += "\n";
    full += "Date: ";
    full += date_time;
    full += "Content-type: " + _contentType;
    full += "\nContent-Lenght: " + itostring(_body.size()); 
    full += "\n\n";
    full += _body;

    std::cout << _url << std::endl;
    _responseFull = full;
    // std::cout << "FULL RESPONSE = " << _responseFull << std::endl;

}