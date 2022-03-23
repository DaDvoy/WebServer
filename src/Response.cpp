#include "Response.hpp"

Response::Response(Request &request) {
    this->firstLine = "";
    this->response = "";
    req = request;
    this->config = nullptr;
    this->server = nullptr;
    this->status = "";
    isAutoIndex = false;
    body = "";
    isPathExist = false;
}

Response::Response() {
    this->firstLine = "";
    this->response = "";
}

Response::~Response()
{

}

std::string Response::SetupAutoIndex()
{
    pathLocation = config->getIndexPath(req.query.address);

    vector<string> *dirs = get_dir_content(pathLocation);
    std::string body;
    
    if (dirs == nullptr){
        response += FileGetContent("./public/error");
        return "";
    }
    std::string webPath = "<a href=\"" + req.query.address;

    if (*(--req.query.address.end()) != '/')
        webPath += '/';

    for (unsigned i = 0; i < dirs->size(); i++) {
        body += webPath + (*dirs)[i] + "\">" + (*dirs)[i] + "</a><br>" ;
    }
    headers["content-type: "] = "text/html\r\n\r\n";
    delete dirs;
    return (body);
}

std::string Response::ResponseStatusCode()
{
    StatusCodes status;
	int limitBody;

    if (isPathExist)
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

    isCGI = config->cgiPath.empty();
    isAutoIndex = false;
    if (req.query.address == "/")
    {
        pathLocation = config->rootDirectory + config->index;
        // std::cout << exists(req.query.address) << std::endl;
        if (config->autoindex)
        {
            std::cout << "pass1" << std::endl;
            body = SetupAutoIndex();
            isAutoIndex = true;
        }
    }
    else
        pathLocation = config->rootDirectory + req.query.address;

    // std::cout << isAutoIndex << std::endl;

    isPathExist = exists(pathLocation);
    status = ResponseStatusCode();

    if (code < 200 || code >= 300)
        pathLocation = config->errorPage;  //убрать заглушку

    isPathExist = exists(pathLocation);


    firstLine = req.query.protocol + " " + status + "\r\n";

    if (req.query.method == "POST")
    {
        if (file_put_contents(config->rootDirectory + req.query.address, req.body, 0666) != -1)
            pathLocation = config->rootDirectory + req.query.address;
		headers["content-location: "] = req.query.address + "\r\n";
    }
    else if (req.query.method == "DELETE")
    {
        if (remove(pathLocation.c_str()) != 0)
            std::cerr << "DELETE error\n";
    }
    headline.searchKey(req, pathLocation);
    isPathExist = exists(pathLocation);

    if (!headline.getRange().empty())
        headers["content-range: "] = headline.getRange() + "\r\n";
    headers["content-length: "] =  std::to_string(FileGetContent(pathLocation).length()) + "\r\n";
    if (!body.empty())
        headers["content-length: "] = std::to_string(body.size()) + "\r\n";
    headers["content-type: "] = headline.getType() + "\r\n";
    if (!headline.getExpires().empty())
        headers["expires: "] = headline.getExpires() + "\r\n";
    headers["server: "] = "GuluGulu/v2.0\r\n\r\n";
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

    // std::cout << req.query.method << std::endl;
    // std::cout << body.empty() << std::endl;
    if (!body.empty())
    {
        response += body;
        return;
    }

    // std::cout << pathLocation << std::endl;
    if (isPathExist)
        response += FileGetContent(pathLocation);
}

std::string     Response::getFirstLine() {
    return (this->firstLine);
}

std::string     Response::getResponse() {
    return  (this->response);
}
