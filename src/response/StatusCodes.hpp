#ifndef STATUSCODES_HPP
#define STATUSCODES_HPP

#include "iostream"
#include "../includes.hpp"

class StatusCodes
{
private:
    int             intCode;
    std::string     strCode;
public:
    StatusCodes();
    ~StatusCodes();

    int             getIntCode();
    std::string     getStrCode();
    void            setCode(int newCode, std::string clarification);
    void            intToStr();

    void             OK();
    void             PartialContent();
    void             MovedPermanently();
    void             BadRequest();
    void             NotFound();
    void             IamTeapot();
    void             InternalServerError();
    void             BadGateway();
};


#endif