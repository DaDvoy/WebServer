#include "StatusCodes.hpp"

StatusCodes::StatusCodes() {
    this->intCode = 0;
    this->strCode = "";
}
StatusCodes::~StatusCodes() {}


void        StatusCodes::setCode(int newCode) {
    this->intCode = newCode;
}

int         StatusCodes::getIntCode() {
    return (this->intCode);
}

std::string StatusCodes::getStrCode() {
    intToStr();
    return (this->strCode);
}

void        StatusCodes::intToStr() {
    std::stringstream ss;
    ss << this->intCode;
    strCode = ss.str();
}


void         StatusCodes::OK() {
    setCode(200);
}

void         StatusCodes::PartialContent() { // Does it necessary?
    setCode(206);;
}

void         StatusCodes::MovedPermanently(){
    setCode(301);
}

void         StatusCodes::BadRequest() {
    setCode(400);
}


// Если сообщение получено без Transfer-Encoding и либо с несколькими полями
// заголовка Content-Length , имеющими разные значения полей, либо с одним
// полем заголовка Content-Length, имеющим недопустимое значение,
// то кадрирование сообщения является недействительным, и получатель
// ДОЛЖЕН рассматривать его как неисправимая ошибка. Если это сообщение
// запроса, сервер ДОЛЖЕН ответить кодом состояния 400 (Bad Request)
// **короче, в случае чего, буду всегда кидать бэд реквест, хе-хе**

void         StatusCodes::NotFound() {
    setCode(404);
}

void         StatusCodes::IamTeapot() {
    setCode(418);
}

void         StatusCodes::InternalServerError() {
    setCode(500);
}

void         StatusCodes::BadGateway() {
    setCode(502);
}