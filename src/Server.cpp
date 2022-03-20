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

Server &Server::GetLocationServer(string &uri)
{
    map<Location, Server>::iterator     locationsIter = locations.begin();
	map<Location, Server>::iterator     coincidence = locations.end();
	int maxExtLength = -1;

	while (locationsIter != locations.end())
    {
    	if (locationsIter->first.path == uri)
	    {
		    coincidence = locationsIter;
		    break;
	    }
    	string path = locationsIter->first.path;
    	if (path.substr(path.length() - 2) == "/*")
	    {
			if (path.substr(0, path.length() - 2) == uri)
			{
				coincidence = locationsIter;
				break;
			}
	    }
        if (match(uri.c_str() ,path.c_str()))
        {
        	int tmp = locationsIter->first.path.length() - locationsIter->first.path.find_last_of('*');
        	if (tmp > maxExtLength || maxExtLength == -1 || (tmp == maxExtLength && coincidence->first.path.length() < locationsIter->first.path.length())) {
		        coincidence = locationsIter;
		        maxExtLength = tmp;
	        }
        }
        locationsIter++;
    }
	if (coincidence != locations.end()) {
		string path = coincidence->first.path;
		int lastDirIndex = path.find_last_of('/');

		if (lastDirIndex > 0) {
			uri.erase(0, lastDirIndex);
		}
		return coincidence->second;
	}
    return *this;
}
