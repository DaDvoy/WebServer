#ifndef REQUESTPARSER_HPP
# define REQUESTPARSER_HPP

#include "ConfigFile.hpp"
#include "Server.hpp"
#include "Response.hpp"
#include <map>

class RequestParser
{
	public:
		RequestParser();
		RequestParser(int sock);
		~RequestParser();

		Request request;
		Response response;
		ConfigFile	*config;
		Server	*server;	
	private:
		std::vector<std::string> parseLines;
		int	count;
		std::string saver;

		int ReadRequest(int sock);
		void ParseRequest();
		void ParseQuery(std::string &query);
};

#endif