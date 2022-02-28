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

    int         getCode() const;
    void        setCode(int newCode) const;

//    int         OK();
//    int         PartialContent();
//    int         MovedPermanently();
//    int         Forbidden();
//    int         NotFound();
//    int         IamTeapot();
//    int         InternalServerError();
//    int         BadGateway();
};


#endif