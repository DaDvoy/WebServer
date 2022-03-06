#ifndef HEADLINES_HPP
# define HEADLINES_HPP

//#include "cstring"
#include "../includes.hpp"
#include "../Response.hpp"
#include "../RequestParser.hpp"

class headlines
{
private:
    std::string     contentType;
    std::string     contentEncoding;
    std::string     contentLenght;
    int             intLenght;
//    length
public:
    headlines();
    ~headlines();

    void            searchKey();
    std::string     getType();
    std::string     getEncoding();
    std::string     getLenght();
};


#endif