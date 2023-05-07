/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:03:55 by avarnier          #+#    #+#             */
/*   Updated: 2023/05/07 17:05:10 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Request.hpp"

static int stringtoint(std::string toConvert){
    std::istringstream is(toConvert);
    int i = 0;

    is >> i;
    return i;
}

////////////////////////////////////////////////////////////////////////////////
//                              CONSTRUCTORS                                  //
////////////////////////////////////////////////////////////////////////////////


ft::Request::Request() : _serverParsing(), _code("0"), _root(), _index("index.html"), _autoIndex(false){
}

ft::Request::Request(const Request & src){
    *this = src;
}

////////////////////////////////////////////////////////////////////////////////
//                               DESTRUCTOR                                   //
////////////////////////////////////////////////////////////////////////////////

ft::Request::~Request(void){
}

std::string ft::Request::getMethod(void){return _method;}
std::string ft::Request::getUrl(void){return _url;}
std::string ft::Request::getProtVersion(void){return _protocolVersion;}
std::string ft::Request::getRequestLine(void){return _requestLine;}

std::string ft::Request::getElementsHeader(std::string element){
    return _rawRequest[element];
}

void ft::Request::parseHeader(){
    std::string newbuffer;
    std::string value;
    newbuffer = rawHeader;

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

    getRequestLine(_requestLine);
    if (this->_serverParsing.getMethods(_urlLocation, _method) == 1){
        responseHTTP.setAllowedMethod(1);
    }
    else
        _code = "405";
    responseHTTP.setMethod(_method);
}

void ft::Request::getRequestLine(std::string line){

    size_t found = line.find(" ");
    this->_method.insert(0, line, 0, found);
    line.erase(0, _method.size() + 1);
    found = line.find(" ");
    this->_url.insert(0, line, 0, found);
    line.erase(0, _url.size() + 1);
    found = line.find("\n");
    this->_protocolVersion.insert(0, line, 0, found);
    _protocolVersion.erase(_protocolVersion.size(), 1);
    responseHTTP.setProtVersion(_protocolVersion);
	_code = getCorrectUrl();
}

std::string ft::Request::requestStarter(const int &fd){
    responseHTTP.setServerParsing(_serverParsing);
    std::string responseR;
    std::string url = this->_urlLocation;
    if (url.empty() == true)
        url = this->_url;
    if (this->_url.find(CGI_EXTENSION) != this->_url.npos)
    {
		if (this->_method != "POST" && this->_method != "GET")
			this->_code = "405";
        else
		{
			std::string cgidir = this->_serverParsing.getCgiDir(url);
        	FILE *check = fopen(this->_url.c_str(), "r");
            if (check == NULL)
                this->_code = "404";
            else
            {
                fclose(check);
                if (cgidir.empty() == false)
        	        responseR = execCgi(fd, cgidir);
        	    if (responseR.empty() == true)
        	        this->_code = "500";
        	    else
        	        responseR = responseHTTP.buildCgiResponse(responseR);
            }
        }
	}

    if (responseR.empty() == true)
    {
        responseHTTP.setCode(_code);
        if (_code == "200")
            parseRequest(responseHTTP);

        responseHTTP.buildFullResponse();
        responseR = responseHTTP.getFullResponse();
    }
    return responseR;
}

void ft::Request::parseRequest(ft::Response &response){
    response.setRawResponse(_rawRequest);
    response.setRawBody(rawBody);
    response.setAutoIndex(_autoIndex);
    response.setContentType(_rawRequest["Content-Type"]);
    response.setContentLenght(stringtoint(_rawRequest["Content-Length"]));
    if (_autoIndex)
        response.setBody(_autoIndexBody);
    response.createBody(_url);
}

bool ft::Request::Directory(std::string url){

    DIR* dir = opendir(url.c_str());
    if (dir != NULL)
    {
        closedir(dir);
        return (true);
    }
    return (false);
}

std::string ft::Request::createAutoIndexHtmlPage(const std::string& directoryPath, const std::string & tmp_loc) {
    // Get the list of HTML files in the directory
    std::vector<std::string> htmlFiles;

    DIR* dir = opendir(directoryPath.c_str());
    struct dirent* entry;
    while ((entry = readdir(dir))) {
        std::string filename = entry->d_name;
        htmlFiles.push_back(filename);
    }
    closedir(dir);

    // Sort the list of HTML files
    sort(htmlFiles.begin(), htmlFiles.end());

    // Create the autoindex HTML page
    std::string autoIndexPage;
    autoIndexPage += "<!DOCTYPE html>\n";
    autoIndexPage += "<html>\n";
    autoIndexPage += "  <head>\n";
    autoIndexPage += "    <title>Autoindex</title>\n";
    autoIndexPage += "<head>\n";
	autoIndexPage += "<title>AAH Webserv</title>\n";
	autoIndexPage += "<style>\n";
	autoIndexPage += 	"body {\n";
    autoIndexPage +=        "background-color: #f6ffff;\n";
    autoIndexPage +=        "background-image: url(\"data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' width='260' height='260' viewBox='0 0 260 260'%3E%3Cg fill-rule='evenodd'%3E%3Cg fill='%23ce23cd' fill-opacity='0.37'%3E%3Cpath d='M24.37 16c.2.65.39 1.32.54 2H21.17l1.17 2.34.45.9-.24.11V28a5 5 0 0 1-2.23 8.94l-.02.06a8 8 0 0 1-7.75 6h-20a8 8 0 0 1-7.74-6l-.02-.06A5 5 0 0 1-17.45 28v-6.76l-.79-1.58-.44-.9.9-.44.63-.32H-20a23.01 23.01 0 0 1 44.37-2zm-36.82 2a1 1 0 0 0-.44.1l-3.1 1.56.89 1.79 1.31-.66a3 3 0 0 1 2.69 0l2.2 1.1a1 1 0 0 0 .9 0l2.21-1.1a3 3 0 0 1 2.69 0l2.2 1.1a1 1 0 0 0 .9 0l2.21-1.1a3 3 0 0 1 2.69 0l2.2 1.1a1 1 0 0 0 .86.02l2.88-1.27a3 3 0 0 1 2.43 0l2.88 1.27a1 1 0 0 0 .85-.02l3.1-1.55-.89-1.79-1.42.71a3 3 0 0 1-2.56.06l-2.77-1.23a1 1 0 0 0-.4-.09h-.01a1 1 0 0 0-.4.09l-2.78 1.23a3 3 0 0 1-2.56-.06l-2.3-1.15a1 1 0 0 0-.45-.11h-.01a1 1 0 0 0-.44.1L.9 19.22a3 3 0 0 1-2.69 0l-2.2-1.1a1 1 0 0 0-.45-.11h-.01a1 1 0 0 0-.44.1l-2.21 1.11a3 3 0 0 1-2.69 0l-2.2-1.1a1 1 0 0 0-.45-.11h-.01zm0-2h-4.9a21.01 21.01 0 0 1 39.61 0h-2.09l-.06-.13-.26.13h-32.31zm30.35 7.68l1.36-.68h1.3v2h-36v-1.15l.34-.17 1.36-.68h2.59l1.36.68a3 3 0 0 0 2.69 0l1.36-.68h2.59l1.36.68a3 3 0 0 0 2.69 0L2.26 23h2.59l1.36.68a3 3 0 0 0 2.56.06l1.67-.74h3.23l1.67.74a3 3 0 0 0 2.56-.06zM-13.82 27l16.37 4.91L18.93 27h-32.75zm-.63 2h.34l16.66 5 16.67-5h.33a3 3 0 1 1 0 6h-34a3 3 0 1 1 0-6zm1.35 8a6 6 0 0 0 5.65 4h20a6 6 0 0 0 5.66-4H-13.1z'/%3E%3Cpath id='path6_fill-copy' d='M284.37 16c.2.65.39 1.32.54 2H281.17l1.17 2.34.45.9-.24.11V28a5 5 0 0 1-2.23 8.94l-.02.06a8 8 0 0 1-7.75 6h-20a8 8 0 0 1-7.74-6l-.02-.06a5 5 0 0 1-2.24-8.94v-6.76l-.79-1.58-.44-.9.9-.44.63-.32H240a23.01 23.01 0 0 1 44.37-2zm-36.82 2a1 1 0 0 0-.44.1l-3.1 1.56.89 1.79 1.31-.66a3 3 0 0 1 2.69 0l2.2 1.1a1 1 0 0 0 .9 0l2.21-1.1a3 3 0 0 1 2.69 0l2.2 1.1a1 1 0 0 0 .9 0l2.21-1.1a3 3 0 0 1 2.69 0l2.2 1.1a1 1 0 0 0 .86.02l2.88-1.27a3 3 0 0 1 2.43 0l2.88 1.27a1 1 0 0 0 .85-.02l3.1-1.55-.89-1.79-1.42.71a3 3 0 0 1-2.56.06l-2.77-1.23a1 1 0 0 0-.4-.09h-.01a1 1 0 0 0-.4.09l-2.78 1.23a3 3 0 0 1-2.56-.06l-2.3-1.15a1 1 0 0 0-.45-.11h-.01a1 1 0 0 0-.44.1l-2.21 1.11a3 3 0 0 1-2.69 0l-2.2-1.1a1 1 0 0 0-.45-.11h-.01a1 1 0 0 0-.44.1l-2.21 1.11a3 3 0 0 1-2.69 0l-2.2-1.1a1 1 0 0 0-.45-.11h-.01zm0-2h-4.9a21.01 21.01 0 0 1 39.61 0h-2.09l-.06-.13-.26.13h-32.31zm30.35 7.68l1.36-.68h1.3v2h-36v-1.15l.34-.17 1.36-.68h2.59l1.36.68a3 3 0 0 0 2.69 0l1.36-.68h2.59l1.36.68a3 3 0 0 0 2.69 0l1.36-.68h2.59l1.36.68a3 3 0 0 0 2.56.06l1.67-.74h3.23l1.67.74a3 3 0 0 0 2.56-.06zM246.18 27l16.37 4.91L278.93 27h-32.75zm-.63 2h.34l16.66 5 16.67-5h.33a3 3 0 1 1 0 6h-34a3 3 0 1 1 0-6zm1.35 8a6 6 0 0 0 5.65 4h20a6 6 0 0 0 5.66-4H246.9z'/%3E%3Cpath d='M159.5 21.02A9 9 0 0 0 151 15h-42a9 9 0 0 0-8.5 6.02 6 6 0 0 0 .02 11.96A8.99 8.99 0 0 0 109 45h42a9 9 0 0 0 8.48-12.02 6 6 0 0 0 .02-11.96zM151 17h-42a7 7 0 0 0-6.33 4h54.66a7 7 0 0 0-6.33-4zm-9.34 26a8.98 8.98 0 0 0 3.34-7h-2a7 7 0 0 1-7 7h-4.34a8.98 8.98 0 0 0 3.34-7h-2a7 7 0 0 1-7 7h-4.34a8.98 8.98 0 0 0 3.34-7h-2a7 7 0 0 1-7 7h-7a7 7 0 1 1 0-14h42a7 7 0 1 1 0 14h-9.34zM109 27a9 9 0 0 0-7.48 4H101a4 4 0 1 1 0-8h58a4 4 0 0 1 0 8h-.52a9 9 0 0 0-7.48-4h-42z'/%3E%3Cpath d='M39 115a8 8 0 1 0 0-16 8 8 0 0 0 0 16zm6-8a6 6 0 1 1-12 0 6 6 0 0 1 12 0zm-3-29v-2h8v-6H40a4 4 0 0 0-4 4v10H22l-1.33 4-.67 2h2.19L26 130h26l3.81-40H58l-.67-2L56 84H42v-6zm-4-4v10h2V74h8v-2h-8a2 2 0 0 0-2 2zm2 12h14.56l.67 2H22.77l.67-2H40zm13.8 4H24.2l3.62 38h22.36l3.62-38z'/%3E%3Cpath d='M129 92h-6v4h-6v4h-6v14h-3l.24 2 3.76 32h36l3.76-32 .24-2h-3v-14h-6v-4h-6v-4h-8zm18 22v-12h-4v4h3v8h1zm-3 0v-6h-4v6h4zm-6 6v-16h-4v19.17c1.6-.7 2.97-1.8 4-3.17zm-6 3.8V100h-4v23.8a10.04 10.04 0 0 0 4 0zm-6-.63V104h-4v16a10.04 10.04 0 0 0 4 3.17zm-6-9.17v-6h-4v6h4zm-6 0v-8h3v-4h-4v12h1zm27-12v-4h-4v4h3v4h1v-4zm-6 0v-8h-4v4h3v4h1zm-6-4v-4h-4v8h1v-4h3zm-6 4v-4h-4v8h1v-4h3zm7 24a12 12 0 0 0 11.83-10h7.92l-3.53 30h-32.44l-3.53-30h7.92A12 12 0 0 0 130 126z'/%3E%3Cpath d='M212 86v2h-4v-2h4zm4 0h-2v2h2v-2zm-20 0v.1a5 5 0 0 0-.56 9.65l.06.25 1.12 4.48a2 2 0 0 0 1.94 1.52h.01l7.02 24.55a2 2 0 0 0 1.92 1.45h4.98a2 2 0 0 0 1.92-1.45l7.02-24.55a2 2 0 0 0 1.95-1.52L224.5 96l.06-.25a5 5 0 0 0-.56-9.65V86a14 14 0 0 0-28 0zm4 0h6v2h-9a3 3 0 1 0 0 6H223a3 3 0 1 0 0-6H220v-2h2a12 12 0 1 0-24 0h2zm-1.44 14l-1-4h24.88l-1 4h-22.88zm8.95 26l-6.86-24h18.7l-6.86 24h-4.98zM150 242a22 22 0 1 0 0-44 22 22 0 0 0 0 44zm24-22a24 24 0 1 1-48 0 24 24 0 0 1 48 0zm-28.38 17.73l2.04-.87a6 6 0 0 1 4.68 0l2.04.87a2 2 0 0 0 2.5-.82l1.14-1.9a6 6 0 0 1 3.79-2.75l2.15-.5a2 2 0 0 0 1.54-2.12l-.19-2.2a6 6 0 0 1 1.45-4.46l1.45-1.67a2 2 0 0 0 0-2.62l-1.45-1.67a6 6 0 0 1-1.45-4.46l.2-2.2a2 2 0 0 0-1.55-2.13l-2.15-.5a6 6 0 0 1-3.8-2.75l-1.13-1.9a2 2 0 0 0-2.5-.8l-2.04.86a6 6 0 0 1-4.68 0l-2.04-.87a2 2 0 0 0-2.5.82l-1.14 1.9a6 6 0 0 1-3.79 2.75l-2.15.5a2 2 0 0 0-1.54 2.12l.19 2.2a6 6 0 0 1-1.45 4.46l-1.45 1.67a2 2 0 0 0 0 2.62l1.45 1.67a6 6 0 0 1 1.45 4.46l-.2 2.2a2 2 0 0 0 1.55 2.13l2.15.5a6 6 0 0 1 3.8 2.75l1.13 1.9a2 2 0 0 0 2.5.8zm2.82.97a4 4 0 0 1 3.12 0l2.04.87a4 4 0 0 0 4.99-1.62l1.14-1.9a4 4 0 0 1 2.53-1.84l2.15-.5a4 4 0 0 0 3.09-4.24l-.2-2.2a4 4 0 0 1 .97-2.98l1.45-1.67a4 4 0 0 0 0-5.24l-1.45-1.67a4 4 0 0 1-.97-2.97l.2-2.2a4 4 0 0 0-3.09-4.25l-2.15-.5a4 4 0 0 1-2.53-1.84l-1.14-1.9a4 4 0 0 0-5-1.62l-2.03.87a4 4 0 0 1-3.12 0l-2.04-.87a4 4 0 0 0-4.99 1.62l-1.14 1.9a4 4 0 0 1-2.53 1.84l-2.15.5a4 4 0 0 0-3.09 4.24l.2 2.2a4 4 0 0 1-.97 2.98l-1.45 1.67a4 4 0 0 0 0 5.24l1.45 1.67a4 4 0 0 1 .97 2.97l-.2 2.2a4 4 0 0 0 3.09 4.25l2.15.5a4 4 0 0 1 2.53 1.84l1.14 1.9a4 4 0 0 0 5 1.62l2.03-.87zM152 207a1 1 0 1 1 2 0 1 1 0 0 1-2 0zm6 2a1 1 0 1 1 2 0 1 1 0 0 1-2 0zm-11 1a1 1 0 1 1 2 0 1 1 0 0 1-2 0zm-6 0a1 1 0 1 1 2 0 1 1 0 0 1-2 0zm3-5a1 1 0 1 1 2 0 1 1 0 0 1-2 0zm-8 8a1 1 0 1 1 2 0 1 1 0 0 1-2 0zm3 6a1 1 0 1 1 2 0 1 1 0 0 1-2 0zm0 6a1 1 0 1 1 2 0 1 1 0 0 1-2 0zm4 7a1 1 0 1 1 2 0 1 1 0 0 1-2 0zm5-2a1 1 0 1 1 2 0 1 1 0 0 1-2 0zm5 4a1 1 0 1 1 2 0 1 1 0 0 1-2 0zm4-6a1 1 0 1 1 2 0 1 1 0 0 1-2 0zm6-4a1 1 0 1 1 2 0 1 1 0 0 1-2 0zm-4-3a1 1 0 1 1 2 0 1 1 0 0 1-2 0zm4-3a1 1 0 1 1 2 0 1 1 0 0 1-2 0zm-5-4a1 1 0 1 1 2 0 1 1 0 0 1-2 0zm-24 6a1 1 0 1 1 2 0 1 1 0 0 1-2 0zm16 5a5 5 0 1 0 0-10 5 5 0 0 0 0 10zm7-5a7 7 0 1 1-14 0 7 7 0 0 1 14 0zm86-29a1 1 0 0 0 0 2h2a1 1 0 0 0 0-2h-2zm19 9a1 1 0 0 1 1-1h2a1 1 0 0 1 0 2h-2a1 1 0 0 1-1-1zm-14 5a1 1 0 0 0 0 2h2a1 1 0 0 0 0-2h-2zm-25 1a1 1 0 0 0 0 2h2a1 1 0 0 0 0-2h-2zm5 4a1 1 0 0 0 0 2h2a1 1 0 0 0 0-2h-2zm9 0a1 1 0 0 1 1-1h2a1 1 0 0 1 0 2h-2a1 1 0 0 1-1-1zm15 1a1 1 0 0 1 1-1h2a1 1 0 0 1 0 2h-2a1 1 0 0 1-1-1zm12-2a1 1 0 0 0 0 2h2a1 1 0 0 0 0-2h-2zm-11-14a1 1 0 0 1 1-1h2a1 1 0 0 1 0 2h-2a1 1 0 0 1-1-1zm-19 0a1 1 0 0 0 0 2h2a1 1 0 0 0 0-2h-2zm6 5a1 1 0 0 1 1-1h2a1 1 0 0 1 0 2h-2a1 1 0 0 1-1-1zm-25 15c0-.47.01-.94.03-1.4a5 5 0 0 1-1.7-8 3.99 3.99 0 0 1 1.88-5.18 5 5 0 0 1 3.4-6.22 3 3 0 0 1 1.46-1.05 5 5 0 0 1 7.76-3.27A30.86 30.86 0 0 1 246 184c6.79 0 13.06 2.18 18.17 5.88a5 5 0 0 1 7.76 3.27 3 3 0 0 1 1.47 1.05 5 5 0 0 1 3.4 6.22 4 4 0 0 1 1.87 5.18 4.98 4.98 0 0 1-1.7 8c.02.46.03.93.03 1.4v1h-62v-1zm.83-7.17a30.9 30.9 0 0 0-.62 3.57 3 3 0 0 1-.61-4.2c.37.28.78.49 1.23.63zm1.49-4.61c-.36.87-.68 1.76-.96 2.68a2 2 0 0 1-.21-3.71c.33.4.73.75 1.17 1.03zm2.32-4.54c-.54.86-1.03 1.76-1.49 2.68a3 3 0 0 1-.07-4.67 3 3 0 0 0 1.56 1.99zm1.14-1.7c.35-.5.72-.98 1.1-1.46a1 1 0 1 0-1.1 1.45zm5.34-5.77c-1.03.86-2 1.79-2.9 2.77a3 3 0 0 0-1.11-.77 3 3 0 0 1 4-2zm42.66 2.77c-.9-.98-1.87-1.9-2.9-2.77a3 3 0 0 1 4.01 2 3 3 0 0 0-1.1.77zm1.34 1.54c.38.48.75.96 1.1 1.45a1 1 0 1 0-1.1-1.45zm3.73 5.84c-.46-.92-.95-1.82-1.5-2.68a3 3 0 0 0 1.57-1.99 3 3 0 0 1-.07 4.67zm1.8 4.53c-.29-.9-.6-1.8-.97-2.67.44-.28.84-.63 1.17-1.03a2 2 0 0 1-.2 3.7zm1.14 5.51c-.14-1.21-.35-2.4-.62-3.57.45-.14.86-.35 1.23-.63a2.99 2.99 0 0 1-.6 4.2zM275 214a29 29 0 0 0-57.97 0h57.96zM72.33 198.12c-.21-.32-.34-.7-.34-1.12v-12h-2v12a4.01 4.01 0 0 0 7.09 2.54c.57-.69.91-1.57.91-2.54v-12h-2v12a1.99 1.99 0 0 1-2 2 2 2 0 0 1-1.66-.88zM75 176c.38 0 .74-.04 1.1-.12a4 4 0 0 0 6.19 2.4A13.94 13.94 0 0 1 84 185v24a6 6 0 0 1-6 6h-3v9a5 5 0 1 1-10 0v-9h-3a6 6 0 0 1-6-6v-24a14 14 0 0 1 14-14 5 5 0 0 0 5 5zm-17 15v12a1.99 1.99 0 0 0 1.22 1.84 2 2 0 0 0 2.44-.72c.21-.32.34-.7.34-1.12v-12h2v12a3.98 3.98 0 0 1-5.35 3.77 3.98 3.98 0 0 1-.65-.3V209a4 4 0 0 0 4 4h16a4 4 0 0 0 4-4v-24c.01-1.53-.23-2.88-.72-4.17-.43.1-.87.16-1.28.17a6 6 0 0 1-5.2-3 7 7 0 0 1-6.47-4.88A12 12 0 0 0 58 185v6zm9 24v9a3 3 0 1 0 6 0v-9h-6z'/%3E%3Cpath d='M-17 191a1 1 0 0 0 0 2h2a1 1 0 0 0 0-2h-2zm19 9a1 1 0 0 1 1-1h2a1 1 0 0 1 0 2H3a1 1 0 0 1-1-1zm-14 5a1 1 0 0 0 0 2h2a1 1 0 0 0 0-2h-2zm-25 1a1 1 0 0 0 0 2h2a1 1 0 0 0 0-2h-2zm5 4a1 1 0 0 0 0 2h2a1 1 0 0 0 0-2h-2zm9 0a1 1 0 0 1 1-1h2a1 1 0 0 1 0 2h-2a1 1 0 0 1-1-1zm15 1a1 1 0 0 1 1-1h2a1 1 0 0 1 0 2h-2a1 1 0 0 1-1-1zm12-2a1 1 0 0 0 0 2h2a1 1 0 0 0 0-2H4zm-11-14a1 1 0 0 1 1-1h2a1 1 0 0 1 0 2h-2a1 1 0 0 1-1-1zm-19 0a1 1 0 0 0 0 2h2a1 1 0 0 0 0-2h-2zm6 5a1 1 0 0 1 1-1h2a1 1 0 0 1 0 2h-2a1 1 0 0 1-1-1zm-25 15c0-.47.01-.94.03-1.4a5 5 0 0 1-1.7-8 3.99 3.99 0 0 1 1.88-5.18 5 5 0 0 1 3.4-6.22 3 3 0 0 1 1.46-1.05 5 5 0 0 1 7.76-3.27A30.86 30.86 0 0 1-14 184c6.79 0 13.06 2.18 18.17 5.88a5 5 0 0 1 7.76 3.27 3 3 0 0 1 1.47 1.05 5 5 0 0 1 3.4 6.22 4 4 0 0 1 1.87 5.18 4.98 4.98 0 0 1-1.7 8c.02.46.03.93.03 1.4v1h-62v-1zm.83-7.17a30.9 30.9 0 0 0-.62 3.57 3 3 0 0 1-.61-4.2c.37.28.78.49 1.23.63zm1.49-4.61c-.36.87-.68 1.76-.96 2.68a2 2 0 0 1-.21-3.71c.33.4.73.75 1.17 1.03zm2.32-4.54c-.54.86-1.03 1.76-1.49 2.68a3 3 0 0 1-.07-4.67 3 3 0 0 0 1.56 1.99zm1.14-1.7c.35-.5.72-.98 1.1-1.46a1 1 0 1 0-1.1 1.45zm5.34-5.77c-1.03.86-2 1.79-2.9 2.77a3 3 0 0 0-1.11-.77 3 3 0 0 1 4-2zm42.66 2.77c-.9-.98-1.87-1.9-2.9-2.77a3 3 0 0 1 4.01 2 3 3 0 0 0-1.1.77zm1.34 1.54c.38.48.75.96 1.1 1.45a1 1 0 1 0-1.1-1.45zm3.73 5.84c-.46-.92-.95-1.82-1.5-2.68a3 3 0 0 0 1.57-1.99 3 3 0 0 1-.07 4.67zm1.8 4.53c-.29-.9-.6-1.8-.97-2.67.44-.28.84-.63 1.17-1.03a2 2 0 0 1-.2 3.7zm1.14 5.51c-.14-1.21-.35-2.4-.62-3.57.45-.14.86-.35 1.23-.63a2.99 2.99 0 0 1-.6 4.2zM15 214a29 29 0 0 0-57.97 0h57.96z'/%3E%3C/g%3E%3C/g%3E%3C/svg%3E\");\n";
    autoIndexPage +=     "}\n";
	autoIndexPage += 	"h1 {\n";
	autoIndexPage += 		"font-size: 3em;\n";
    autoIndexPage +=         "font-family:Impact, Haettenschweiler, 'Arial Narrow Bold', sans-serif;\n";
	autoIndexPage += 		"color: #581cd9;\n";
	autoIndexPage += 		"text-align: center;\n";
	autoIndexPage += 		"margin-top: 50px;\n";
	autoIndexPage += 	"}\n";
    autoIndexPage +=     "h1>span{\n";
    autoIndexPage +=         "background-color: rgb(232, 190, 242);\n";
    autoIndexPage +=        " box-shadow: 10px 0 0px 0px rgb(232, 190, 242), -10px 0 0px 0px rgb(232, 190, 242);\n";
    autoIndexPage +=     "}\n";
    autoIndexPage +=     "img{\n";
    autoIndexPage +=         "text-align: center;\n";
    autoIndexPage +=         "display: block;\n";
    autoIndexPage +=         "margin-left: auto;\n";
    autoIndexPage +=         "margin-right: auto;\n";
    autoIndexPage +=     "}\n";
    autoIndexPage += "        .card>form{\n";
    autoIndexPage +=         "text-align: center;\n";
    autoIndexPage +=         "display: block;\n";
    autoIndexPage +=         "padding-bottom: 20px;\n";
    autoIndexPage +=     "}\n";
    autoIndexPage +=      ".card>h3{display: block;text-align: center;font-family:Impact, Haettenschweiler, 'Arial Narrow Bold', sans-serif;}\n";
    autoIndexPage +=     ".card {\n";
    autoIndexPage +=         "margin-left: auto;\n";
    autoIndexPage +=         "margin-right: auto;\n";
    autoIndexPage +=         "margin-top: 50px;";
    autoIndexPage +=         "display: block;\n";
    autoIndexPage +=         "border: 1px solid rgb(232, 190, 242);;\n";
    autoIndexPage +=         "border-radius: 15px;\n";
    autoIndexPage +=         "box-shadow:\n";
    autoIndexPage +=             "0 2.8px 2.2px rgba(0, 0, 0, 0.034),\n";
    autoIndexPage +=             "0 6.7px 5.3px rgba(0, 0, 0, 0.048),\n";
    autoIndexPage +=             "0 12.5px 10px rgba(0, 0, 0, 0.06),\n";
    autoIndexPage +=             "0 22.3px 17.9px rgba(0, 0, 0, 0.072),\n";
    autoIndexPage +=             "0 41.8px 33.4px rgba(0, 0, 0, 0.086),\n";
    autoIndexPage +=             "0 100px 80px rgba(0, 0, 0, 0.12);\n";
    autoIndexPage +=         "width: 500px;\n";
    autoIndexPage +=         "background-color: rgb(232, 190, 242);\n";
    autoIndexPage +=         "}\n";
	autoIndexPage += "</style>\n";
    autoIndexPage += "  </head>\n";
    autoIndexPage += "  <body>\n";
    autoIndexPage += "<div class=\"card\">\n";
    autoIndexPage += "    <h1>Index of " + directoryPath + "</h1>\n";
    for (std::vector<std::string>::const_iterator it = htmlFiles.begin(); it != htmlFiles.end(); ++it) {
        autoIndexPage += "      <h3><a href=\"" + tmp_loc + *it + "\">" + *it + "</a></h3>\n";
    }
    autoIndexPage += "    </div>\n";

    autoIndexPage += "  </body>\n";
    autoIndexPage += "</html>\n";
    return autoIndexPage;
}

std::string ft::Request::checkIndexVector(std::vector<std::string> Index)
{
    std::vector<std::string> tmp = Index;
    for (std::vector<std::string>::iterator it = tmp.begin(); it != tmp.end(); ++it)
    {
        if (*it != "")
            return (*it);
    }
    return ("");
}

std::string ft::Request::getCorrectUrl(void){
    std::string tmpQuery = this->_queryString;
    _tmpLoc = _url;
    size_t pos;

    _url = this->_serverParsing.getRoot(_url) + _url;
    _urlLocation =  _serverParsing.isLoc(_url);
    if ((pos = _url.find("?")) != std::string::npos){
        tmpQuery = _url.substr(pos + 1);
        std::string token;
        std::string value;

        while ((pos = tmpQuery.find("=")) != std::string::npos) {
            token = tmpQuery.substr(0, pos);
            tmpQuery.erase(0, pos + 1);
            if ((pos = tmpQuery.find("&")) != std::string::npos)
            {
                value = tmpQuery.substr(0, pos);
                value.erase(std::remove(value.begin(), value.end(), 13), value.end());
            }
            tmpQuery.erase(0, pos + 1);
            _dataQuery[token] = value;
        }
        _dataQuery[token] = tmpQuery;
    }
    if (Directory(_url))
    {
        std::string::iterator ite = _url.end();
		if (*(--ite) != '/')
            _url += "/";
        std::string::iterator it = _tmpLoc.end();
        if (*(--it) != '/')
            _tmpLoc += "/";
        _urlLocation =  _serverParsing.isLoc(_url);
        if (this->_serverParsing.getAutoIndex(_urlLocation))
        {
            _autoIndex = true;
            _autoIndexBody += createAutoIndexHtmlPage(_url, _tmpLoc);
        }
        else
            _url = _url + checkIndexVector(this->_serverParsing.getIndex(_url));
    }
    std::ifstream ifs(_url.c_str());

    responseHTTP.setURL(_url);
    responseHTTP.setLocation(_urlLocation);
    if (!ifs.is_open())
        return ("404");
    return ("200");
}

//avarnier
void    ft::Request::clear()
{
	this->_rawRequest.clear();
	this->rawHeader.clear();
	this->rawBody.clear();
	this->_code.clear();
    this->responseHTTP.clear();
	this->_method.clear();
	this->_url.clear();
	this->_urlLocation.clear();
	this->_protocolVersion.clear();
	this->_tmpLoc.clear();
	this->_requestLine.clear();
	this->_requestFull.clear();
	this->_root.clear();
	this->_index.clear();
	this->_queryString.clear();
	this->_dataQuery.clear();
	this->_autoIndexBody.clear();
	this->_autoIndex = false;
}

size_t	ft::Request::getContentLength(void) const
{
	size_t ret = 0;
	std::map<std::string, std::string>::const_iterator cit = this->_rawRequest.find("Content-Length");
	if (cit != this->_rawRequest.end())
		std::istringstream(cit->second) >> ret;
	return ret;
}

std::string ft::Request::getScriptName(const std::string &url)
{
    size_t end = url.find(CGI_EXTENSION);
    if (end == url.npos)
        return ("");
    size_t begin = url.rfind("/", end);
    if (begin == url.npos)
        return (url.substr(0, end + 4));
    return (url.substr(begin + 1, end + 4));
}

std::string	ft::Request::getScriptFilename(const std::string &url)
{
    size_t end = url.find(CGI_EXTENSION);
    if (end == url.npos)
        return ("");
    return (url.substr(0, end + 4));
}

std::string ft::Request::getPathInfo(const std::string &path)
{
    std::string extension(CGI_EXTENSION);
    size_t pos = path.find(extension + "/");
    if (pos == path.npos)
        return (std::string());
    std::string pathInfo = path.substr(pos + 5, path.npos);
        return (pathInfo);
}

void    ft::Request::addToEnvFromRequest(std::map<std::string, std::string> &env,
const std::string &name, const std::string &content)
{

    std::string requestContent;
    if (content.size() != 0)
        requestContent = getElementsHeader(content);
    this->addToEnv(env, name, requestContent);
}

void    ft::Request::addToEnv(std::map<std::string, std::string> &env,
const std::string &name, const std::string &content)
{
    env.insert(env.begin(), std::map<std::string, std::string>::value_type(name, content));
}

void    ft::Request::addToEnvAddr(std::map<std::string, std::string> &env, const int &fd)
{
    sockaddr_in addr;
    socklen_t   addrlen = 0;
    getsockname(fd, reinterpret_cast<sockaddr *>(&addr), &addrlen);
    std::string addr_string = inet_ntoa(addr.sin_addr);
    this->addToEnv(env, "REMOTE_ADDR", addr_string);
}



void    ft::Request::fillEnv(std::map<std::string, std::string> &env,
const int &fd)
{
    this->addToEnv(env, "REDIRECT_STATUS", "CGI");
	this->addToEnvFromRequest(env, "CONTENT_TYPE", "Content-Type");
    this->addToEnvFromRequest(env, "CONTENT_LENGTH", "Content-Length");
    this->addToEnv(env, "GATEWAY_INTERFACE", "CGI/1.1");
    this->addToEnv(env, "PATH_INFO", this->getPathInfo(this->_url));
    this->addToEnvAddr(env, fd);
    this->addToEnv(env, "QUERY_STRING", this->_queryString);
    this->addToEnv(env, "REQUEST_METHOD", this->getMethod());
    this->addToEnv(env, "SCRIPT_FILENAME", this->getScriptFilename(this->_url));
    this->addToEnv(env, "SCRIPT_NAME", this->getScriptName(this->_url));
    this->addToEnv(env, "SERVER_NAME", this->_serverParsing.getServerName());
    this->addToEnv(env, "SERVER_PORT", this->_serverParsing.getServerPort());
    this->addToEnv(env, "SERVER_PROTOCOL", "HTTP/1.1");
    this->addToEnv(env, "SERVER_SOFTWARE", "WEBSERV/1.0");
}

char    **ft::Request::allocEnv(std::map<std::string, std::string> &env)
{
    char **c_env = new char*[env.size() + 1];
    int x = 0;

    for (env_cit it = env.begin(); it != env.end(); it++, x++)
    {
        std::string var = it->first + '=' + it->second;
        c_env[x] = new char[var.size() + 1];
        strcpy(c_env[x], var.c_str());
    }
    c_env[x] = NULL;

    return (c_env);
}

char    **ft::Request::allocArg(const std::string &cgiPath, const std::string &scriptName)
{
    char    **c_arg = new char*[3];
    c_arg[0] = new char[cgiPath.size() + 1];
    c_arg[1] = new char[scriptName.size() + 1];
    c_arg[2] = NULL;
    strcpy(c_arg[0], cgiPath.c_str());
    strcpy(c_arg[1], scriptName.c_str());
    return (c_arg);
}

int    ft::Request::cgiAlloc(const int &fd, const std::string &cgiPath, char ***c_env, char ***c_arg)
{
    try
    {
        *c_arg = this->allocArg(cgiPath, this->getScriptFilename(this->_url));
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return (-1);
    }
    try
    {
        env_type    env;
        this->fillEnv(env, fd);
        *c_env = this->allocEnv(env);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return (-1);
    }
    return (0);
}

void    ft::Request::cgiDelete(char **c_env, char **c_arg)
{
    for (size_t x = 0; c_env[x] != NULL; x++)
        delete[] c_env[x];
    delete[] c_env;

    for (size_t x = 0; c_arg[x] != NULL; x++)
        delete[] c_arg[x];
    delete[] c_arg;
}

void    ft::Request::getResponse(const int &fd, std::string &response)
{
    std::vector<unsigned char>  buffer(CGI_BUFFER);
    ssize_t                     bytes = 1;

    while (bytes > 0)
    {
        bytes = read(fd, &buffer[0], CGI_BUFFER);
        if (!(bytes > 0))
            break ;
        buffer.resize(bytes);
        response.insert(response.end(), buffer.begin(), buffer.end());
    }
}

std::string ft::Request::execCgi(const int &fd, const std::string &cgiPath)
{
    std::string response;
	TmpFd		tmpIn;
	TmpFd		tmpOut;
    char        **c_env = NULL;
    char        **c_arg = NULL;

    pid_t timeout = fork();
    if (timeout == -1)
        return("");
    if (timeout == 0)
    {
        sleep(CGI_TIMEOUT);
        exit(0);
    }

    pid_t cgi = fork();
    if (cgi == -1)
        return ("");
    if (cgi == 0)
    {
		if (this->_method == "POST")
		{
			if (write(tmpIn.fd, &this->rawBody[0], this->rawBody.size()) == -1)
				return ("");
			if (lseek(tmpIn.fd, SEEK_SET, 0) == -1)
				return ("");
		}
		if (dup2(tmpIn.fd, STDIN_FILENO) == -1)
            return ("");
        if (dup2(tmpOut.fd, STDOUT_FILENO) == -1)
            return ("");
        if (this->cgiAlloc(fd, cgiPath, &c_env, &c_arg) == -1)
            return ("");
        execve(c_arg[0], c_arg, c_env);
        this->cgiDelete(c_env, c_arg);
        exit(0);
    }

    if (timeout > 0 && cgi > 0)
    {
        pid_t exitChild = wait(NULL);
        if (exitChild == cgi)
            kill(timeout, SIGKILL);
        else
            kill(cgi, SIGKILL);
        wait(NULL);
		if (lseek(tmpOut.fd, SEEK_SET, 0) == -1)
			return ("");
		this->getResponse(tmpOut.fd, response);
    }
    return (response);
}