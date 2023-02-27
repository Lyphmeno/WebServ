#include "../incs/StatusCode.hpp"

////////////////////////////////////////////////////////////////////////////////
//                              CONSTRUCTORS                                  //
////////////////////////////////////////////////////////////////////////////////

void ft::StatusCode::initStruct(std::string code, std::string status)
{
    _statusCode[code]._code = code;;
    _statusCode[code]._status = status;
}

ft::StatusCode::StatusCode(void){

    initStruct("200", "OK");
    initStruct("201", "Created");
    initStruct("202", "Accepted");
    initStruct("204", "No Content");
    initStruct("400", "Bad Request");
    initStruct("401", "Unauthorized");
    initStruct("403", "Forbidden");
    initStruct("404", "Not Found");
    initStruct("405", "Method Not Allowed");
    initStruct("500", "Internal Server Error");
}

ft::StatusCode::StatusCode(const StatusCode & src){
    *this = src;
}



////////////////////////////////////////////////////////////////////////////////
//                               DESTRUCTOR                                   //
////////////////////////////////////////////////////////////////////////////////

ft::StatusCode::~StatusCode(void){
}



////////////////////////////////////////////////////////////////////////////////
//                                OPERATORS                                   //
////////////////////////////////////////////////////////////////////////////////

ft::StatusCode & ft::StatusCode::operator=(StatusCode const & value) {
    if (&value != this)
    {
    }
    return *this;
}

const std::string & ft::StatusCode::getStatus(std::string code){
    return _statusCode[code]._status;
}
