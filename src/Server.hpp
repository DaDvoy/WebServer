#ifndef SERVER_HPP
#define SERVER_HPP

#pragma once
#include "Location.hpp"
#include "Server.hpp"
#include "ConfigFile.hpp"
#include "includes.hpp"
#include "Response.hpp"
#include "Request.hpp"

class Response;

class Server
{
	private:
		std::string name;
        map<Location, Server> locations;

	public:
		Server();
		Server(ConfigFile config);
		Server	&operator=(const Server &other);
		bool operator==(Server other);
		std::string	&getName();
		~Server();
		Server &GetLocationServer(string &uri);
		Response getHttpResponse(const sockaddr_in &addr, Request *request, ConfigFile *config);

		ConfigFile	configServer;
};

#endif