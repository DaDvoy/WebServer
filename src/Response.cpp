#include "Response.hpp"

Response::Response() {}

Response::~Response()
{

}

void        Response::buildResponse() {
//    std::map<std::string, std::string>::iterator it_beg = this->headers.begin();
//    std::map<std::string, std::string>::iterator it_end = this->headers.end();
    RequestParser requestParser;
    headlines headline;

    firstLine = requestParser.request.query.protocol + status.getStrCode();
    headers["content-encoding: "] = headline.getEncoding();
    headers["content-length: "] = headline.getLenght();
    headers["content-type: "] = headline.getType();
    headers["server: "] = "GuluGulu\r\n";
}

std::string     Response::getFirstLine() {
    return (this->firstLine);
}