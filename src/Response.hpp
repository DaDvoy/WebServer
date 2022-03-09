#ifndef RESPONSE_HPP
# define RESPONSE_HPP

#include "includes.hpp"
#include "./response/StatusCodes.hpp"
#include "./response/headlines.hpp"
#include "Request.hpp"

class Response
{
private:

		StatusCodes                         status;
        std::string                         firstLine;
        std::string                         response;
public:
    Response(Request &request);
    ~Response();

    Request req;

	std::map<std::string, std::string>  headers;
    void            buildMap();
    void            buildResponse();
//    void            protocol(Request &req);
    std::string     getFirstLine();
    std::string     getResponse();
};

#endif