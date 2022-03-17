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

int Client::readRequest(Listener &listener)
{
    time(&lastOperationTime);
	// usleep(1750);
    int ret = requestParser->ReadRequest(sock, listener);
    
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

int Client::sendResponse() {
    time(&lastOperationTime);


    // if (responseBuffer.empty() && sendBuffer.empty())
    // {
    // 	if (response.headers("Transfer-Encoding") == "chunked")
	//     {
	// 	    responseIsChunked = true;
	// 	    responseBuffer = response.body();
	// 	    response.body("");
	// 	    sendBuffer = response.toString();
	//     } else {
	// 	    sendBuffer = response.toString();
    // 	}
    // }
    // if (responseIsChunked && sendBuffer.empty())
    // {
	//     int message_size = std::min<int>(responseBuffer.length(), READ_BUFFER);
	//     sendBuffer = itoa(message_size, 16) + "\r\n" + responseBuffer.substr(0, message_size) + "\r\n";
	//     responseBuffer.erase(0, message_size);
	//     if (responseBuffer.empty())
	// 	    sendBuffer += "0\r\n\r\n";
    // }
    sendBuffer =    "HTTP/1.1 200 OK\r\n"
                    "Content-Type: text/plain\r\n"
                    "Transfer-Encoding: chunked\r\n"
                    "\n"
                    "7\r\n"
                    "Mozilla\r\n"
                    "9\r\n"
                    "Developer\r\n"
                    "7\r\n"
                    "Network\r\n"
                    "0\r\n"
                    "\r\n";
    int sended = send(sock, sendBuffer.c_str(), sendBuffer.length(), 0);
    if (sended <= 0)
        return sended;
	// sendBuffer.erase(0, sended);
    if (responseBuffer.empty() && sendBuffer.empty())
        actualState = resetState;
    return 1;
}
