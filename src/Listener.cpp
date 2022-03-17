#include "Listener.hpp"

Listener::Listener(int port) : port(port)
{

}

int	Listener::getPort() const
{
	return (port);
}

int Listener::getSock()
{
	return (sock);
}

Listener::Listener(const Listener &other)
{
	*this = other;
}

Listener	&Listener::operator=(const Listener &other)
{
	this->port = other.port;
	this->sock = other.sock;
	this->serverList = other.serverList;
	return (*this);
}

Client	*Listener::AcceptClient()
{
    sockaddr_in client_addr;
    int addrlen = sizeof(client_addr);
    int client_sock = accept(sock, (struct sockaddr *) &client_addr, (socklen_t*)&addrlen);

    fcntl(client_sock, F_SETFL, O_NONBLOCK);
    Client *newClient = new Client(client_sock, client_addr);

    return newClient;
}

// Server	&Listener::FindServer(const std::string host)
// {
// 	tempHost = host;
// 	list<Server>::iterator serverIterator = find_if(serverList.begin(), serverList.end(), IsServerNameEqualHost);
// 	if (serverIterator == serverList.end())
// 		return *serverList.begin();
// 	else
// 		return *serverIterator;
// }

bool Listener::BindServer(Server &server)
{
    if (find(serverList.begin(), serverList.end(), server) == serverList.end())
    {
        serverList.push_back(server);
        return true;
    }
    else
        return false;
}

bool Listener::InitializePort()
{
	sockaddr_in	address;

	address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
	sock = socket(PF_INET, SOCK_STREAM, 0);

    int opt = 1;
    setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,(const char *)&opt,sizeof(int));

	if (sock < 0)
	{
		perror("Initialize Error");
		return false;
	}

	if (bind(sock, (sockaddr *)&address, sizeof(address))<0)
    {
        perror("Initialize Error in bind...");
		return false;
    }

	if (listen(sock, 200) < 0)
	{
        perror("Initialize Error in bind...");
		return false;
	}
	return true;
}

Listener::~Listener()
{

}