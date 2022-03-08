#include "Response.hpp"

Response::Response() {
    this->firstLine = "";
}

Response::~Response()
{

}

void        Response::protocol(Request &req) {
    this->firstLine = req.query.protocol;
    this->firstLine.append(" :");
//    firstLine.append(status.getStrCode());
}

void        Response::buildResponse(Request &req) {
//    std::map<std::string, std::string>::iterator it_beg = this->headers.begin();
//    std::map<std::string, std::string>::iterator it_end = this->headers.end();
    headlines headline;
//    firstLine.append(status.get

//    std::cout << "print in response: " << req.head["Accept-Encoding"] << std::endl;
    headline.searchKey(req);
    protocol(req);
//    firstLine = req.query.protocol;// + " " + status.getStrCode()+ " " + "OK\r\n";
    headers["content-encoding: "] = headline.getEncoding() + "\r\n";
    headers["content-length: "] = headline.getLenght() + "\r\n";
    headers["content-type: "] = headline.getType() + "\r\n";
    headers["server: "] = "Gulu-Gulu/2.0\r\n";

}

std::string     Response::getFirstLine() {
    return (this->firstLine);
}

std::string     Response::getTMP() {
    return  (this->tmp);
}