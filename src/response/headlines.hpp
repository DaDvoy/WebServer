#ifndef HEADLINES_HPP
# define HEADLINES_HPP

#include <ctime>
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
    std::string     expires;
    int             intLenght;
public:
    headlines();
    ~headlines();

    Request         req;
    void            searchKey(Request &requ);
    void            processingRange();
    void            processingEncoding();
    void            expiresTime();

    std::string     sortData(std::string tmp);

    std::string     getType();
    std::string     getEncoding();
    std::string     getLenght();
    std::string     getRange();
    std::string     getExpires();
};


#endif