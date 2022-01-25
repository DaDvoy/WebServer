#ifndef STATUSCODES_HPP
#define STATUSCODES_HPP

#include "iostream"

class StatusCodes
{
private:
    int         _code;
public:
    StatusCodes();
    ~StatusCodes();


    int
    int         OK();
    int         PartialContent();
    int         MovedPermanently();
    int         Found();
    int         NotModified();
    int         Forbidden();
    int         NotFound();
    int         IamTeapot();
    int         InternalServerError();
    int         BadGateway();
};


#endif