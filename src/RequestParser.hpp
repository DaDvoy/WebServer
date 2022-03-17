#ifndef REQUESTPARSER_HPP
# define REQUESTPARSER_HPP

#pragma once
#include <map>
#include "ConfigFile.hpp"
#include "Response.hpp"
#include "Request.hpp"
#include "response/StatusCodes.hpp"
#include "Listener.hpp"
#include "Server.hpp"

class Listener;
class Server;

class RequestParser
{
	public:
		RequestParser(const sockaddr_in addr);
		~RequestParser();
		int ReadRequest(int sock, Listener &listener);

		Request 			request;
		ConfigFile			*config;
		const sockaddr_in   addr;
		StatusCodes 		status;

	private:
		std::vector<std::string>	parseLines;
		int							count;
		std::string 				saver;
		Server						server;

		void ParseRequest();
		void ParseQuery(std::string &query);
};

#endif
