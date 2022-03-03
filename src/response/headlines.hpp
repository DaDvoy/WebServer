#ifndef HEADLINES_HPP
# define HEADLINES_HPP

#include "../includes.hpp"
#include "../Response.hpp"
#include "../RequestParser.hpp"

class headlines
{
private:
    std::string     contentType;
    std::string     contentEncoding;
    std::string     contentLenght;
    std::string     lenght;
    int             intLenght;
public:


    void            searchKey();
    std::string     getType();
    std::string     getEncoding();
    int             getLenght();
};


#endif