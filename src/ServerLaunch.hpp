#ifndef SERVERLAUNCH_HPP
# define SERVERLAUNCH_HPP

#include "ConfigFile.hpp"
#include <list>

class ServerLaunch
{
	public:
		ServerLaunch(list<ConfigFile> &config);


	private:
		list<ConfigFile> config;
};

#endif