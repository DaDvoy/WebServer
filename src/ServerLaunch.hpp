#ifndef SERVERLAUNCH_HPP
# define SERVERLAUNCH_HPP

#include "ConfigFile.hpp"
#include <list>
#include "includes.hpp"
#include "Response.hpp"
#include "ConfigParser.hpp"
#include "RequestParser.hpp"
#include "Listener.hpp"
#include <sys/select.h>
#include "CommonGatewayInterface.hpp"
#define OPERATION_TIMEOUT 10

class ServerLaunch
{
	public:
		ServerLaunch(list<ConfigFile> &config);
		~ServerLaunch();
		bool	ExecuteServers();

	private:
		void	closeClientConnection(Listener &listener, vector<Client *>::iterator &clientIter);
		void	InitializeListener();
		list<ConfigFile> config;
		vector<Listener> listener;
    	timeval timeoutMaster;
		fd_set	fdRecv;
		fd_set	fdSend;
		int		maxFd;
};

#endif