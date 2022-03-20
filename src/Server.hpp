#ifndef SERVER_HPP
#define SERVER_HPP

#include "RequestParser.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "Location.hpp"
#include "ConfigFile.hpp"

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
        Server &GetLocationServer(string &uri); //если есть локейшины, попробует найти его по uri

		ConfigFile	configServer;
};

#endif