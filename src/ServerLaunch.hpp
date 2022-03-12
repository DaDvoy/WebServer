#ifndef SERVERLAUNCH_HPP
# define SERVERLAUNCH_HPP

#include "ConfigFile.hpp"
#include <list>
#include "includes.hpp"
#include "includes.hpp"
#include "Response.hpp"
#include "ConfigParser.hpp"
#include "RequestParser.hpp"
#include "CommonGatewayInterface.hpp"
#include "ServerLaunch.hpp"

class ServerLaunch
{
	public:
		ServerLaunch(list<ConfigFile> &config);
		~ServerLaunch();
		bool	ExecuteServers();

	private:
		list<ConfigFile> config;
		// fd_set	fd_recv;
		// fd_set	fd_send;
		void	InitializeServers();
};

#endif