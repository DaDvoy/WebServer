#ifndef RESPONSE_HPP
# define RESPONSE_HPP

#include "includes.hpp"
#include "./response/StatusCodes.hpp"

class Response
{
	private:

		std::map<std::string, std::string> headers;
//		std::string	body;
		StatusCodes status;
       // std::map<std::string> response;
	public:
		Response();
		~Response();

    void        buildResponse();
};

#endif