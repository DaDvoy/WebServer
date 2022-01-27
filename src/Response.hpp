#ifndef RESPONSE_HPP
# define RESPONSE_HPP

#include "includes.hpp"

class Response
{
	private:

		std::map<std::string, std::string> headers;
		std::string	body;
		unsigned int status;
	public:
		Response();
		~Response();
};

#endif