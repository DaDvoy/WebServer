#include "RequestParser.hpp"

RequestParser::RequestParser()
{
	saver = "";
	config = nullptr;
	server = nullptr;
	count = 0;
}

RequestParser::RequestParser(int sock)
{
	saver = "";
	count = 0;
	config = nullptr;
	server = nullptr;

	if (ReadRequest(sock) < 0)
	{
		std::cerr << "error read sock in requestparser\n";
		exit(0);
	}
	ParseRequest();
}

RequestParser::~RequestParser()
{

}

int RequestParser::ReadRequest(int sock)
{
	long valread;

	char *buffer = new char[READ_BUFFER + 1];
	bzero(buffer, READ_BUFFER + 1);
	if ((valread = read(sock , buffer, READ_BUFFER)) < 0)
	{
		delete[] buffer;
		return (-1);
	}
	saver += buffer;
	delete[] buffer;
	return 0;
}

void RequestParser::ParseRequest()
{
	parseLines = split(saver, '\n');
	std::vector<std::string>::iterator it = parseLines.begin();
	std::string	str;

	while (it != parseLines.end())
	{
		
		str = ft_trimmer("\t\n\v\f\r ", *it);
		std::cout << str << std::endl;
		it++;
		count++;
	}
}
