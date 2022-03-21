#include "Response.hpp"

Response::Response(Request &request) {
    this->firstLine = "";
    this->response = "";
    req = request;
    this->server = nullptr;
    this->status = "";
    isPathLocation = false;
}

Response::Response() {
    this->firstLine = "";
    this->response = "";
}

Response::~Response()
{

}

std::string Response::ResponseStatusCode()
{
    StatusCodes status;

    if (req.query.address == "/") {
        pathLocation = config.rootDirectory + config.index;
        if (!access(pathLocation.c_str(), 0)) {
            status.OK();
            isPathLocation = true;
        }
        else
            status.NotFound();
    }
    if (!access(pathLocation.c_str(), 0)) {
        status.OK();
        isPathLocation = true;
    }
    else
        status.NotFound();

    return (status.getStrCode());
}

void        Response::buildMap() {
    Headlines   headline;

    pathLocation = config.rootDirectory + req.query.address;
    status = ResponseStatusCode();
    headline.searchKey(req, pathLocation);
    firstLine = req.query.protocol + " " + status + "\r\n";
    if (!headline.getRange().empty())
        headers["content-range: "] = headline.getRange() + "\r\n";
   std::cout << "pass\n";
//    if (!headline.getEncoding().empty())
//        headers["content-encoding: "] = headline.getEncoding() + "\r\n";
    headers["content-length: "] = headline.getLenght() + "\r\n";
    headers["content-type: "] = headline.getType() + "\r\n";//"; charset=UTF-8\r\n";
    headers["expires: "] = headline.getExpires() + "\r\n";
    headers["server: "] = req.head["host"] + "\r\n";
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
