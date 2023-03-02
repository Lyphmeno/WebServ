#include "../incs/Request.hpp"
#include <dirent.h> 




#define PORT 8080


#include <fstream>
#include "../incs/Request.hpp"
#include "../incs/Response.hpp"
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include "../incs/Request.hpp"
#include <fcntl.h>

////////////////////////////////////////////////////////////////////////////////
//                              CONSTRUCTORS                                  //
////////////////////////////////////////////////////////////////////////////////

ft::Request::Request(void) : _indexON(0), _root(), _index("index.html"){
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
void ft::Request::fillRequest(char *buffer)
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


bool ft::Request::Directory(std::string url){

    DIR* dir = opendir(url.c_str());
    if (dir != NULL)
    {
        closedir(dir);
        return (true);
    }
    return (false);
}

void ft::Request::createAutoIndexHtmlPage(const std::string& directoryPath) {
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



void ft::Request::getCorrectUrl(void){

    if (_url == "/")
    {
        _indexON = 1;
        _url = _root + _url + _index;
        return ;
    }
    _url.erase(0, 1);
    if (Directory(_url)){
        int i = _url.size();
        if (_url.at(i - 1) != '/')
            _url += "/";
        _url = _root + _url + _index;
    
    }
    else{
        _url = _root + _url;
    }

}


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
    getCorrectUrl();
}

/*
    Function that checks if request exists, then parse the request
    and send it to create the response
*/
std::string ft::Request::requestStarter(int readBytes, char *buffer){
    ft::Request requestHTTP;
    ft::Response *responseHTTP = new ft::Response();

    // if (_code == 0)
    // {
        requestHTTP.fillRequest(buffer);
        requestHTTP.parseRequest(responseHTTP, readBytes);
    // }
    responseHTTP->buildFullResponse();
    std::string responseR = responseHTTP->getFullResponse(); 
    // responseR.erase(std::remove(responseR.begin(), responseR.end(), 13), responseR.end());
   
    return responseR;
}





//
//
//SERVER
//
//  


int ft::Request::server_start(std::vector<ft::Server>	server)
{
    int server_fd, new_socket; long valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    ft::Request request;

    std::string hello;

    request.servers = server;
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("In socket");
        exit(EXIT_FAILURE);
    }
    int on = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &on, sizeof(int));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
    
    memset(address.sin_zero, '\0', sizeof address.sin_zero);
    
    
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("In bind");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 10) < 0)
    {
        perror("In listen");
        exit(EXIT_FAILURE);
    }
    while(1)
    {
        printf("\n+++++++ Waiting for new connection ++++++++\n\n");
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
        {
            perror("In accept");
            exit(EXIT_FAILURE);
        }
        
        char buffer[30000] = {0};
        bzero(buffer, 30000);
        valread = read( new_socket , buffer, 30000);
        std::cout << "REQUEST \n\n" << buffer << std::endl;
        std::ofstream ofs("request");

        ofs.write((char *)buffer, sizeof(buffer));
        ofs.close();
        hello = request.requestStarter(valread, buffer);
        // std::cout << hello << std::endl;
        std::ofstream ofs2("response");
        ofs2 << hello;
        write(new_socket , const_cast<char *>(hello.c_str()), hello.size());
        close(new_socket);
    }
    return 0;
}
