#include "Response.hpp"

Response::Response(Request &request) {
    this->firstLine = "";
    this->response = "";
    req = request;
    this->server = nullptr;
}

Response::Response() {
    this->firstLine = "";
    this->response = "";
}

Response::~Response()
{

}

void        Response::buildMap() {
    headlines headline;

    headline.searchKey(req);
    firstLine = req.query.protocol + " 200 OK\r\n";
    if (!headline.getRange().empty())
        headers["content-range: "] = headline.getRange() + "\r\n";
//    headers["content-encoding: "] = headline.getEncoding() + "\r\n";
    headers["content-length: "] = headline.getLenght() + "\r\n";
//    headers["content-length: "] = headline.getLenght() + "\r\n";
    headers["content-type: "] = headline.getType() + "; charset=UTF-8\r\n";
    headers["expires: "] = headline.getExpires() + "\r\n";
//    Connection: Closed\n\n
//    headers["date: "] = "Mon, 27 Jul 2009 12:28:53 GMT\r\n";
//    headers["last-modified: "] = "Wed, 22 Jul 2009 19:15:56 GMT\r\n";
//    headers["connection: "] = "Closed\r\n";
    headers["server: "] = "Gulu-Gulu/2.0\r\n";

}

void        Response::buildResponse(Server *server) {
    buildMap();
    std::map<std::string, std::string>::iterator it_beg = headers.begin();
    std::map<std::string, std::string>::iterator it_end = headers.end();
    ConfigFile  config = server->configServer;

    response = firstLine;
//    std::cout << "addr: " << req.query.address << std::endl;
    while (it_beg != it_end) {
        response.append(it_beg->first);
        response.append(it_beg->second);
        it_beg++;
    }

    response += "\n";
    std::string path = config.rootDirectory + req.query.address;
    std::cout << path << std::endl;
    if (!access(path.c_str(), 0))
    {
        response += FileGetContent(path.c_str());
        response += "\r\n\r\n";
    }
    std::cout << response;
}

std::string     Response::getFirstLine() {
    return (this->firstLine);
}

std::string     Response::getResponse() {
    return  (this->response);
}