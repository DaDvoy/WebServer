#include "Server.hpp"

Server	&Server::operator=(const Server &other)
{
	this->configServer = other.configServer;
	this->locations = other.locations;
	this->name = other.name;
	return (*this);
}

bool Server::operator==(Server other)
{
	return (this->name == other.name);
}

Server::Server()
{

}

Server::Server(ConfigFile config) : configServer(config)
{
	name = config.domain;

	std::vector<Location>::iterator it = config.locations.begin();
	std::vector<Location>::iterator itEnd = config.locations.end();

	while (it != itEnd)
	{
		Location &location = *it;
		locations[location] = Server(*location.config);
		it++;
	}
}

std::string	&Server::getName()
{
	return (name);
}

Server::~Server()
{

}
