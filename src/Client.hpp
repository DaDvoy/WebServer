#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "Response.hpp"
#include "Request.hpp"
#include "RequestParser.hpp"
#include "Server.hpp"

class Client
{
	public:
		Request		request;
		Response	response;
		RequestParser requestParser;
};

#endif