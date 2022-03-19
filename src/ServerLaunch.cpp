#include "ServerLaunch.hpp"

ServerLaunch::~ServerLaunch()
{
}

ServerLaunch::ServerLaunch(list<ConfigFile> &config)
{
	this->config = config;

    timeoutMaster.tv_usec = 0;
    timeoutMaster.tv_sec = 2;
    maxFd = -1;

    FD_ZERO(&fdRecv);
    FD_ZERO(&fdSend);
}

void	ServerLaunch::InitializeListener()
{
    list<ConfigFile>::iterator  configIter = config.begin();
    while (configIter != config.end())
    {
        Server newServer(*configIter);

        vector<Listener>::iterator listenerIter = listener.begin();

        while (listenerIter != listener.end())
        {
            if (listenerIter->getPort() == configIter->port)
                break;
            listenerIter++;
        }

        if (listenerIter == listener.end())
        {
            Listener newListener(configIter->port);
            newListener.BindServer(newServer);
            listener.push_back(newListener);
        }
        else
            listenerIter->BindServer(newServer);
        configIter++;
    }
}

bool	ServerLaunch::ExecuteServers()
{	
    if (listener.size() > 0)
    {
        cerr << "Server already started\n";
        exit(1);
    }

	if (config.size() == 0)
		return false;

	InitializeListener();

    vector<Listener>::iterator listenerIter = listener.begin();
    vector<Listener>::iterator listenerIterEnd = listener.end();
    while (listenerIter != listenerIterEnd) {
        if (!listenerIter->InitializePort()) {
            exit(1);
        }
        FD_SET(listenerIter->getSock(), &fdRecv);
        if (listenerIter->getSock() > maxFd)
            maxFd = listenerIter->getSock();
        listenerIter++;
    }

    vector<Client*>::iterator clientIter;

    while(true)
    {
        timeval timeout = timeoutMaster;
        fd_set recvSet;
        fd_set sendSet;
        FD_COPY(&fdRecv, &recvSet);
        FD_COPY(&fdSend, &sendSet);

        int ret = select(maxFd + 1, &recvSet, &sendSet, nullptr, &timeout);

        // std::cout << "select value: " << ret << std::endl;
        if (ret <= 0)
            continue;

        listenerIter = listener.begin();
        listenerIterEnd = listener.end();
        while (listenerIter != listenerIterEnd)
        {
            // std::cout << "pass\n";
            if (FD_ISSET(listenerIter->getSock(), &recvSet))
            {
                try
                {
                    Client *newClient = listenerIter->AcceptClient();

                    if (newClient->getSock() > maxFd)
                        maxFd = newClient->getSock();

                    listenerIter->clients.push_back(newClient);
                    // std::cout << "test2: " << listenerIter->clients.size() << std::endl;
                    FD_SET(newClient->getSock(), &fdRecv);
                    FD_SET(newClient->getSock(), &fdSend);
                }
                catch (exception)
                {
                    cerr << "Accept error: " << strerror(errno) << endl;
                }
            }
            time_t currentTime;
            time(&currentTime);

            clientIter = listenerIter->clients.begin();
            // std::cout << "test1: " << listenerIter->clients.size() << std::endl;
            while (clientIter != listenerIter->clients.end())
            {
                // std::cerr << "pass" << std::endl;
                // std::cout << "test" << (*clientIter)->getSock() << std::endl;
                if ((*clientIter)->actualState == sendingResponse && FD_ISSET((*clientIter)->getSock(), &sendSet))
                {
                    int res = (*clientIter)->sendResponse();
                    (*clientIter)->actualState = resetState;
                    if (res <= 0)
                    {
                        closeClientConnection(*listenerIter, clientIter);
                        continue;
                    }
                }
                // std::cerr << "pass2" << std::endl;
                if ((*clientIter)->actualState == requestParsing && FD_ISSET((*clientIter)->getSock(), &recvSet))
                {
                    int res = (*clientIter)->readRequest();
                    // std::cout << res << std::endl;
                    if (res <= 0) {
                        closeClientConnection(*listenerIter, clientIter);
                        continue;
                    }
                }
                // std::cerr << "pass3" << std::endl;

                if ((*clientIter)->actualState == resetState)
                {
                    (*clientIter)->clear();
                    continue;
                }

                if (difftime(currentTime, (*clientIter)->lastOperationTime) > OPERATION_TIMEOUT)
                {
                    closeClientConnection(*listenerIter, clientIter);
                    continue;
                }

                clientIter++;
            }
            // std::cerr << "pass4" << std::endl;

            listenerIter++;
        }
    }
}

void ServerLaunch::closeClientConnection(Listener &listener, vector<Client *>::iterator &clientIter)
{
    FD_CLR((*clientIter)->getSock(), &fdSend);
    FD_CLR((*clientIter)->getSock(), &fdRecv);
    close((*clientIter)->getSock());
    delete *clientIter;
    listener.clients.erase(clientIter);
}