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
	std::map<std::string, std::string>::iterator it = request.head.begin();
	while (it != request.head.end())
	{
		if ((*it).first != "")
			std::cout << (*it).first << ": " << (*it).second << std::endl;
		it++;
	}
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

void RequestParser::ParseQuery(std::string &query)
{
	request.query.query_string = query;
	std::vector<std::string> query_split = split(query, ' ');

	request.query.method = query_split[0];
	request.query.address = query_split[1];
	request.query.protocol = query_split[2];
}

void RequestParser::ParseRequest()
{
	parseLines = split(saver, '\n');
	std::vector<std::string>::iterator it = parseLines.begin();
	std::string	str;

	ParseQuery(*it);
	std::vector<std::string> head_split;
	while (++it != parseLines.end())	
	{
		std::cout << *it << std::endl;
		head_split = split_str(*it, ": ");
		if (*it == "")
			break;
		request.head.insert(std::pair<std::string, std::string>(head_split[0], head_split[1]));
		++count;
	}
	if (*it == "")
		std::cout << "body parsing\n";
}
