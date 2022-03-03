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
//int         StatusCodes::BadRequest() {
//    setCode(400);
//}
//

// Если сообщение получено без Transfer-Encoding и либо с несколькими полями
// заголовка Content-Length , имеющими разные значения полей, либо с одним
// полем заголовка Content-Length, имеющим недопустимое значение,
// то кадрирование сообщения является недействительным, и получатель
// ДОЛЖЕН рассматривать его как неисправимая ошибка. Если это сообщение
// запроса, сервер ДОЛЖЕН ответить кодом состояния 400 (Bad Request)
// **короче, в случае чего, буду всегда кидать бэд реквест, хе-хе**

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