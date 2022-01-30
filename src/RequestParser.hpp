#ifndef REQUESTPARSER_HPP
# define REQUESTPARSER_HPP

#include "Configs.hpp"
#include "Server.hpp"
#include "Response.hpp"
#include "Request.hpp"
#include <sys/socket.h>
#include <sys/types.h>
#include <map>

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
		std::string saver;

		int ReadRequest(int sock);
		void ParseRequest();
		void ParseQuery(std::string &query);
};

#endif