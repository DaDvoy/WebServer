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
    std::cout << "addr: " << req.query.address << std::endl;
    while (it_beg != it_end) {
        response.append(it_beg->first);
        response.append(it_beg->second);
        it_beg++;
    }
    if (req.query.address == "/")
    {
        if (access("public/index.html", 0))
        {
            response += FileGetContent("public/index.html");
            response += "\r\n\r\n";
        }
        //else {error 404}
    }
    if (req.query.address == "/put-file")
    {
        if (access("/public/post", 0))
        {
            response += FileGetContent("/public/post");
            response += "\r\n\r\n";
        }
    }
    if (req.query.address == "/error")
    {
        if (access("/public/error.html", 0))
        {
            response += FileGetContent("public/error.html");
            // response = "TEST";
            response += "\r\n\r\n";
        }
    }
    // if (req.query.address == "/favicon.ico")
    // {
    //     if (access("/public/favicon.ico", 0))
    //     {
    //         response += FileGetContent("public/favicon.ico");
    //         response += "\r\n\r\n";
    //     }
    // }
}

std::string     Response::getFirstLine() {
    return (this->firstLine);
}

std::string     Response::getResponse() {
    return  (this->response);
}