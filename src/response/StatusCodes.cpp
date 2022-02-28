#include "StatusCodes.hpp"

StatusCodes::StatusCodes() {
    this->_code = 0;
}

StatusCodes::~StatusCodes() {}



void        StatusCodes::setCode(int newCode) const {
    this->_code = newCode;
}

int         StatusCodes::getCode() const {
    return (this->_code);
}

//int         StatusCodes::OK() {
//    setCode(200);
//}
//
//int         StatusCodes::PartialContent() { // Does it necessary?
//    setCode(206);;
//}
//
//int         StatusCodes::MovedPermanently(){
//    setCode(301);
//}
//
//int         StatusCodes::Forbidden() {
//    setCode(403);
//}
//
//int         StatusCodes::NotFound() {
//    setCode(404);
//}
//
//int         StatusCodes::IamTeapot() {
//    setCode(418);
//}

int         StatusCodes::InternalServerError() {
    setCode(500);
}

int         StatusCodes::BadGateway() {
    setCode(502);
}