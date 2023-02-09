#include "../incs/Response.hpp"

////////////////////////////////////////////////////////////////////////////////
//                              CONSTRUCTORS                                  //
////////////////////////////////////////////////////////////////////////////////

ft::Response::Response(void){

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

void ft::Response::setProtVersion(std::string version){
    this->_protVersion = version;
}

void ft::Response::setContentType(std::string contentType){
    this->_contentType = contentType;
    std::cout << "content " << contentType << std::endl;
}
        