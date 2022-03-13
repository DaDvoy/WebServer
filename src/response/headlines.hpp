#ifndef HEADLINES_HPP
# define HEADLINES_HPP

//#include "cstring"
#include "../includes.hpp"
#include "../Response.hpp"
#include "../RequestParser.hpp"
#include "../Request.hpp"

class headlines
{
private:
    StatusCodes     _status;
    std::string     contentType;
    std::string     contentEncoding;
    std::string     contentLenght;
    std::string     contentRange;
    int             intLenght;
public:
    headlines();
    ~headlines();

    Request         req;
    void            searchKey(Request &requ);
    void            processingRange();
    void            processingEncoding();

    std::string     getType();
    std::string     getEncoding();
    std::string     getLenght();
    std::string     getRange();
};


#endif