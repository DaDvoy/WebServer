#ifndef LISTENER_HPP
#define LISTENER_HPP

#include "includes.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Server.hpp"
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

class Client;

class Listener
{
	private:
		int					port;
		int					sock;
		std::string			tempHost;
		std::list<Server>	serverList;
	public:
		std::vector<Client*> clients;

		Listener(int port);
		Listener(const Listener &other);
		Listener	&operator=(const Listener &other);
		Client	*AcceptClient();
		// Server	&FindServer(const std::string host);
		bool BindServer(Server &server);
        Server &FindServerByHost(std::string host);
		bool InitializePort();
		int	getPort() const;
		int getSock();
		~Listener();
};

#endif