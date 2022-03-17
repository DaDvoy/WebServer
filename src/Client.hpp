#ifndef CLIENT_HPP
# define CLIENT_HPP

#pragma once
#include "Response.hpp"
#include "Request.hpp"
#include "RequestParser.hpp"
#include "Server.hpp"
#include "ConfigFile.hpp"
#include "Listener.hpp"

enum state
{
	requestParsing,
	sendingResponse,
	resetState
};

class Listener;

class Client
{
	public:
		Client(int sock, sockaddr_in addr);
		Client();
		Client(const Client &other);
		Client &operator=(const Client &other);
		
    	int readRequest(Listener &listener);
    	int sendResponse();
		int getSock();
		~Client();
		void clear();

		Server *server;
		
		state actualState;
		Request request;
		RequestParser *requestParser;
    	time_t lastOperationTime;
	
	private:

		string responseBuffer;
		Server attachedServer;
		sockaddr_in addr;
		int sock;
		Response response;
		string  readBuffer;
		string  sendBuffer;
		ConfigFile  *config;

		bool    responseIsChunked;

};

#endif