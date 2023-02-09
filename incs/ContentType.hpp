#ifndef CONTENTTYPE_HPP
#define CONTENTTYPE_HPP

#include <iostream>
#include <map>

#define COLOR_START "\033[1;100m"
#define COLOR_RED "\033[31m" 
#define COLOR_GREEN "\033[32m" 
#define COLOR_YELLOW "\033[33m"
#define COLOR_END "\033[0m"

typedef struct s_data{
        std::string _ext;
        std::string _type;
}               t_data;

namespace ft{

////////////////////////////////////////////////////////////////////////////////
//                                  REQUEST                                   //
////////////////////////////////////////////////////////////////////////////////

class ContentType{

public:
        //Constructors
        ContentType();
        ContentType (const ContentType & src);

        //Destructor
        ~ContentType(void);

        //Operators
        ContentType & operator=(ContentType const & value);

        //Getters
        const std::string & getType(std::string extension);

        void initMime(std::string ext, std::string type);
        std::map<std::string, t_data> & getMimeType();
private:

       std::map<std::string, t_data> _mimeType;

};

}

#endif