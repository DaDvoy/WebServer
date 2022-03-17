#include "Response.hpp"

Response::Response(Request &request) {
    this->firstLine = "";
    this->response = "";
    req = request;
}

Response::Response() {
    this->firstLine = "";
    this->response = "";
}

Response::~Response()
{

}
//
//void        Response::protocol(Request &req) {
//    this->firstLine = req.query.protocol;
//    this->firstLine.append(" ");
//    //status.getStr
//    firstLine.append(status.getStrCode());
//}

void        Response::buildMap() {
    headlines headline;

    headline.searchKey(req);
    firstLine = req.query.protocol + status.getStrCode() + " " + "OK\r\n";
    if (!headline.getRange().empty())
        headers["content-range: "] = headline.getRange() + "\r\n";
    headers["content-encoding: "] = headline.getEncoding() + "\r\n";
    headers["content-length: "] = headline.getLenght() + "\r\n";
    headers["content-type: "] = headline.getType() + "\r\n";
    headers["expires: "] = headline.getExpires() + "\r\n";
    headers["server: "] = "Gulu-Gulu/2.0\r\n";

}

void        Response::buildResponse() {
    buildMap();
    std::map<std::string, std::string>::iterator it_beg = headers.begin();
    std::map<std::string, std::string>::iterator it_end = headers.end();

    response = firstLine;
    while (it_beg != it_end) {
        response.append(it_beg->first);
        response.append(it_beg->second);
        it_beg++;
    }
    std::cout << response;
}

std::string     Response::getFirstLine() {
    return (this->firstLine);
}

std::string     Response::getResponse() {
    return  (this->response);
}