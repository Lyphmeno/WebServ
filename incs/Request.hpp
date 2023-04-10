#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "Parser.hpp"
#include "Response.hpp"

#define GET 1
#define POST 2
#define DELETE 3

namespace ft{

////////////////////////////////////////////////////////////////////////////////
//                                  REQUEST                                   //
////////////////////////////////////////////////////////////////////////////////

class Request{

public:
	//Constructors
	Request(const ft::Server& server);
	Request (const Request & src);

	//Destructor
	~Request(void);


	//Getters
	std::string getMethod(void);
	std::string getUrl(void);
	std::string getProtVersion(void);
	std::string getRequestLine(void);
	std::string  getElementsHeader(std::string element);

	std::string requestStarter(const int &fd);

	void parseHeader(void);
	void parseRequest(ft::Response &reponse);

	void getRequestLine(std::string line);
	void checkMethodAllowed(ft::Response &response, std::string method);
	std::map<std::string, std::string> _rawRequest;


	bool Directory(std::string url);
	std::string getCorrectUrl(void);
	std::string createAutoIndexHtmlPage(const std::string& directoryPath, const std::string & tmp_loc);
	std::string checkIndexVector(std::vector<std::string> Index);

	//avarnier
	size_t		getContentLength(void) const;
	void    	addToEnvFromRequest(std::map<std::string, std::string> &env,
				const std::string &name, const std::string &elem);
	void		addToEnv(std::map<std::string, std::string> &env,
				const std::string &name, const std::string &content);
	void    	addToEnvAddr(std::map<std::string, std::string> &env, const int &fd);
	void		fillEnv(std::map<std::string, std::string> &env,
				const int &fd, const std::string &scriptName);
	char    	**allocEnv(std::map<std::string, std::string> &env);
	std::string	execCgi(const int &fd, const std::string &scriptName);

	std::string 				rawHeader;
	std::vector<unsigned char>	rawBody;
	ft::Server	_serverParsing;
	std::string _code;


    ft::Response responseHTTP;

private:

	//Request line
	std::string  _method;
	std::string _url;
	std::string _urlLocation;
	std::string _protocolVersion;

	std::string _tmpLoc;

	std::string _requestLine;

	//Raw
	std::vector<std::string> _requestFull;
	
	//Conf file
	std::string _root;
	std::string _index;
	
	std::string _queryString;
	std::map<std::string, std::string> _dataQuery;
	//int _code;
	std::string _autoIndexBody;
	bool _autoIndex;

	// int isAllowed;

};

}

#endif