#include "Response.hpp"

Response::Response()
{
	body = "";
	status = 0;
}

Response::~Response()
{

}


void        Response::buildResponse() {
    std::string firstLine(requestParser.request.query.protocol + status.getCode());
//    std::map<std::string, std::string>::iterator it_beg = this->headers.begin();

}