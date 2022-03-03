#ifndef HEADLINES_HPP
# define HEADLINES_HPP

#include "../includes.hpp"
#include "../Response.hpp"
#include "../RequestParser.hpp"

class headlines
{
private:
    std::string contentType;
    std::string contentEncoding;
    std::string contentLenght;
    int intLenght;
public:


    void        searchKey();
};


#endif