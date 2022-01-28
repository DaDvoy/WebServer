#ifndef REQUESTPARSER_HPP
# define REQUESTPARSER_HPP

#include "Configs.hpp"
#include "Server.hpp"
#include "Response.hpp"
#include <sys/socket.h>
#include <sys/types.h>

class RequestParser
{
	public:
		RequestParser();
		RequestParser(int sock);
		~RequestParser();

		Request request;
		Response response;
		Configs	*config;
		Server	*server;
        std::vector<std::string> parseLines;
	private:
		int	count;
		int ReadRequest(int sock);
		void ParseRequest();
		std::string saver;
};

#endif