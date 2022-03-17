#ifndef REQUESTPARSER_HPP
# define REQUESTPARSER_HPP

#include <map>
#include "ConfigFile.hpp"
#include "Server.hpp"
#include "Response.hpp"

class RequestParser
{
	public:
		RequestParser(const sockaddr_in addr);
		~RequestParser();
		int ReadRequest(int sock);

		Request 			request;
		ConfigFile			*config;
		const sockaddr_in   addr;

	private:
		std::vector<std::string> parseLines;
		int	count;
		std::string saver;

		void ParseRequest();
		void ParseQuery(std::string &query);
};

#endif