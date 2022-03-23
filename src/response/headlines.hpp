#ifndef Headlines_HPP
# define Headlines_HPP

#include <ctime>
#include <iostream>
#include "../includes.hpp"
#include "../RequestParser.hpp"
#include "../Request.hpp"
#include "../ConfigFile.hpp"


class Headlines
{
private:
    StatusCodes     _status;
    std::string     contentType;
    std::string     contentEncoding;
    std::string     typeEncoding;
    std::string     contentLenght;
    std::string     contentRange;
    std::string     transferEncoding;
    std::string     expires;
    std::string     chunked;
    int             intLenght;
public:
    Headlines();
    ~Headlines();

    Request         req;
    ConfigFile      conf;
    void            searchKey(Request &requ, std::string &path);
    void            processingRange();
    void            processingEncoding();
    void            expiresTime();

    std::string     sortData(std::string tmp);
    void            processingChunk(std::string path);

    std::string     getChunked();
    std::string     getType();
    std::string     getEncoding();
    std::string     getLenght();
    std::string     getRange();
    std::string     getExpires();
};


#endif