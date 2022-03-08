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
        std::string                         tmp;
public:
		Response();
		~Response();

		std::map<std::string, std::string>  headers;
    void            buildResponse(Request &req);
    void            protocol(Request &req);
    std::string     getFirstLine();
    std::string     getTMP();
};

#endif