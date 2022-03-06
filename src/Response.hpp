#ifndef RESPONSE_HPP
# define RESPONSE_HPP

#include "includes.hpp"
#include "./response/StatusCodes.hpp"
#include "./response/headlines.hpp"

class Response
{
	private:

		std::map<std::string, std::string> headers;
		StatusCodes status;
        std::string firstLine;
	public:
		Response();
		~Response();

    void            buildResponse();
    std::string     getFirstLine();
};

#endif