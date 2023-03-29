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

void ft::Response::initPostStruct(std::string fullBody){
    size_t pos = 0;
    std::string value;
    std::string token;

    while ((pos = fullBody.find(": ")) != std::string::npos) {
        token = fullBody.substr(0, pos);
        fullBody.erase(0, pos + 2);
        if ((pos = fullBody.find("\n")) != std::string::npos)
        {
            value = fullBody.substr(0, pos);
            value.erase(std::remove(value.begin(), value.end(), 13), value.end());
        }
        fullBody.erase(0, pos + 1);
        if (token == "Content-Disposition")
        {
            if ((pos = value.find("name=\"")) != std::string::npos) {
                value.erase(0, pos + 6);
                if ((pos = value.find("\"")) != std::string::npos)
                    token = value.substr(0, pos);
            }
            if ((pos = value.find("filename=\"")) != std::string::npos) {
                value.erase(0, pos + 10);
                if ((pos = value.find("\"")) != std::string::npos)
                {
                    std::string filename = value.substr(0, pos);
                    _multipartForm[token].filename = filename; 
                }
            }
            _multipartForm[token].name = token;
            tmpName = token;
        }
    }
    _multipartForm[tmpName].value = fullBody.erase(0, 2);
    std::cout << "VALUE FILE = |\n" <<  _multipartForm[tmpName].value << "\n|\n";
    filename = "html/uploads/" + _multipartForm[tmpName].filename;//add root
    std::ofstream ofs(filename.c_str());
    if (ofs.is_open())
        ofs << _multipartForm[tmpName].value;
}

std::string getOnlyBody(std::string *body, std::string tmp){
    size_t pos = 0;
    std::string fullBody;

    tmp = "------" + tmp;
    if ((pos = body->find(tmp)) != std::string::npos){
        if (pos != body->size())
            fullBody = body->substr(0, pos);
        else
            fullBody = body->substr(0, pos + 2);
    }
    body->erase(0, fullBody.size());
    return (fullBody);
}

void ft::Response::multi(void){

    size_t pos = 0;
    std::string tmp = _rawResponse["Content-Type"];
    std::string tmpRawBody = _rawBody;

    
    if ((pos = tmp.find(" boundary=----")) != std::string::npos) {
        tmp.erase(0, pos + 14);
    }
    while ((pos = tmpRawBody.find(tmp)) != std::string::npos){
        tmpRawBody.erase(0, tmp.size() + 8);
        initPostStruct(getOnlyBody(&tmpRawBody, tmp));
        if (tmpRawBody.size() == tmp.size() + 10)
            break;
    }
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

}

void	ft::Response::clear()
{
	_protVersion.clear();
	_url.clear();
	_method.clear();
	_contentType.clear();
	_server.clear();
	_body.clear();
	_code.clear();
	_status.clear();
	_responseFull.clear();
	_rawResponse.clear();
	_formValues.clear();
	_rawBody.clear();

	// _allowedMethod.clear();
	// _contentLenght.clear();
	// _autoIndex.clear();
	// _codeStatus = ;

	//	to be checked:
	//
	// _indexON = 0;
	// _root.clear();
	// _index.clear();
	// _autoIndexBody.clear();
	// _autoIndex = false;
}