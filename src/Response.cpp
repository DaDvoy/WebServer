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
	int limitBody;

    if (req.query.address == "/") {
        pathLocation = config->rootDirectory + config->index;
        if (!access(pathLocation.c_str(), 0))
            status.OK();
        else
            status.NotFound();
    }

    if (!access(pathLocation.c_str(), 0))
        status.OK();
    else
        status.NotFound();

	if (!config->allowedFunctions.empty() && config->allowedFunctions.find(req.query.method) == string::npos)
		status.setCode(405, "Method Not Allowed");

    limitBody = config->limitClientBodySize;

    if (req.head.count("Content-Length"))
    {
        if (limitBody != 0 && stoi(req.head["Content-Length"]) > limitBody)
            status.setCode(413, "Request Entity Too Large");
    }
    code = status.getIntCode();
    return (status.getStrCode());
}

void        Response::buildMap() {
    Headlines   headline;

    pathLocation = config->rootDirectory + req.query.address;
    status = ResponseStatusCode();
    if (code < 200 || code >= 300)
        pathLocation = "./public/error.html";  //убрать заглушку
    headline.searchKey(req, pathLocation);
    firstLine = req.query.protocol + " " + status + "\r\n";
    if (!headline.getRange().empty())
        headers["content-range: "] = headline.getRange() + "\r\n";
//    if (!headline.getEncoding().empty())
//        headers["content-encoding: "] = headline.getEncoding() + "\r\n";
    headers["content-length: "] = headline.getLenght() + "\r\n";
    headers["content-type: "] = headline.getType() + "\r\n";//"; charset=UTF-8\r\n";
    headers["expires: "] = headline.getExpires() + "\r\n";
    headers["server: "] = "gulugulu/v2.0\r\n";
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

    response += "\n";
    if (req.query.address == "/") {
        pathLocation = config->rootDirectory + config->index;
        if (!access(pathLocation.c_str(), 0))
        {
            response += FileGetContent(pathLocation.c_str());
            response += "\r\n\r\n";
        }
        else
        {
            response += FileGetContent(pathLocation);
            response += "\r\n\r\n";
        }
    }
    else if (!access(pathLocation.c_str(), 0))
    {
        response += FileGetContent(pathLocation.c_str());
        response += "\r\n\r\n";
    }
    else
    {
        response += FileGetContent(pathLocation);
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
