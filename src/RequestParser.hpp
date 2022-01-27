#ifndef REQUESTPARSER_HPP
# define REQUESTPARSER_HPP

#include "Configs.hpp"
#include "Server.hpp"
#include "Response.hpp"

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
	private:
		std::vector<std::string> parseLines;
		int	count;
		int ReadRequest(int sock);
		void ParseRequest();
		std::string saver;
};

#endif