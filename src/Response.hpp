#ifndef RESPONSE_HPP
# define RESPONSE_HPP

#include "includes.hpp"
#include "./response/StatusCodes.hpp"
#include "./response/headlines.hpp"
#include "Request.hpp"
#include "Server.hpp"
#include "ConfigFile.hpp"

class Server;

class Response
{
private:

		StatusCodes                         status;
        std::string                         firstLine;
        std::string                         response;
public:
    Server                          *server;
    Response(Request &request);
    Response();
    ~Response();

    Request req;

	std::map<std::string, std::string>  headers;
    void            buildMap();
    void            buildResponse(Server *server);
//    void            protocol(Request &req);
    std::string     getFirstLine();
    std::string     getResponse();
};

#endif