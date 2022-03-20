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
    Headlines   headline;
    StatusCodes status;


    std::string path = config.rootDirectory + req.query.address;
    if (req.query.address == "/") {
        path = config.rootDirectory + config.index;
        if (!access(path.c_str(), 0))
            status.OK();
        else
            status.NotFound();
    }
    if (!access(path.c_str(), 0))
        status.OK();
    else
        status.NotFound();
    headline.searchKey(req, path);
    firstLine = req.query.protocol + " " + status.getStrCode() + "\r\n";
    if (!headline.getRange().empty())
        headers["content-range: "] = headline.getRange() + "\r\n";
//    if (!headline.getEncoding().empty())
//        headers["content-encoding: "] = headline.getEncoding() + "\r\n";
    headers["content-length: "] = headline.getLenght() + "\r\n";
    headers["content-type: "] = headline.getType() + "\r\n";//"; charset=UTF-8\r\n";
    headers["expires: "] = headline.getExpires() + "\r\n";
    headers["server: "] = "Gulu-Gulu/2.0\r\n";

}

void        Response::buildResponse(Server *server) {
    config = server->configServer;
    buildMap();
    std::map<std::string, std::string>::iterator it_beg = headers.begin();
    std::map<std::string, std::string>::iterator it_end = headers.end();

    response = firstLine;
//    std::cout << "addr: " << req.query.address << std::endl;
    while (it_beg != it_end) {
        response.append(it_beg->first);
        response.append(it_beg->second);
        it_beg++;
    }

    response += "\n";

    std::string path = config.rootDirectory + req.query.address;
    if (req.query.address == "/") {
        path = config.rootDirectory + config.index;
        if (!access(path.c_str(), 0))
        {
            response += FileGetContent(path.c_str());
            response += "\r\n\r\n";
        }
        else
        {
            response += FileGetContent(config.errorPage);
            response += "\r\n\r\n";
        }
    }
    else if (!access(path.c_str(), 0))
    {
        response += FileGetContent(path.c_str());
        response += "\r\n\r\n";
    }
    else
    {
        response += FileGetContent(config.errorPage);
        response += "\r\n\r\n";
    }
    // std::cout << response;
}

std::string     Response::getFirstLine() {
    return (this->firstLine);
}

std::string     Response::getResponse() {
    return  (this->response);
}
