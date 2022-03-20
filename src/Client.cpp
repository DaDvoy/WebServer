#include "Client.hpp"

Client::Client(int sock, sockaddr_in addr)
{
	this->sock = sock;
	responseIsChunked = false;
    actualState = requestParsing;
	this->requestParser = new RequestParser(addr);
	this->config = nullptr;
    this->server = nullptr;
    this->addr = addr;
    time(&lastOperationTime);
}

Client::Client(const Client &other)
{
    *this = other;
}

Client &Client::operator=(const Client &other)
{
    if (other.sock == 0)
        return *this;
    if (this != &other)
    {
    	this->responseIsChunked = other.responseIsChunked;
    	delete this->requestParser;
    	this->requestParser = new RequestParser(addr);
        this->sock = other.sock;
        this->request = other.request;
	    this->lastOperationTime = other.lastOperationTime;
        this->readBuffer = other.readBuffer;
        this->sendBuffer = other.sendBuffer;
        this->attachedServer = other.attachedServer;
        this->addr = other.addr;
        this->actualState = other.actualState;
    }
    return *this;
}

Client::~Client()
{

}

Client::Client()
{

}

int Client::readRequest()
{
    time(&lastOperationTime);
	// usleep(1750);
    int ret = requestParser->ReadRequest(sock);
    
    if (ret == -1)
    {
        std::cerr << "request parser error" << std::endl;
        return (-1);
    }
    actualState = sendingResponse;
    response.req = requestParser->request;
    return (ret);    
}

void Client::clear()
{
    Client clearedClient(sock, addr);
    *this = clearedClient;
}

int Client::getSock()
{
    // std::cerr << "pass" << std::endl;
    return (sock);
}

int Client::sendResponse(Listener &listener)
{
    time(&lastOperationTime);
    string host = request.head["Host"];
    server = &listener.FindServerByHost(host);
    server = &server->GetLocationServer(response.req.query.address);
    response.buildResponse(server);
    int sended = send(sock, response.getResponse().c_str(), response.getResponse().size(), 0);
    // std::cout << response.getResponse().c_str() << ": " << sended << std::endl;
    if (sended <= 0)
        return sended;
    return 1;
}
