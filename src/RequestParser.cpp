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
	// std::cout << "all: " << saver << std::endl;
	// std::vector<std::string> tmp_str = split_one(saver, "\n\r\n"); для тела реквеста
	// request.body = tmp_str[1];
	// saver = tmp_str[0];
	// std::cout << tmp_str[1] << std::endl;

	ParseRequest();
	// std::map<std::string, std::string>::iterator it = request.head.begin();
	// while (it != request.head.end())
	// {
	// 	if ((*it).first == "Accept")
	// 		std::cout << (*it).first << ": " << (*it).second << std::endl;
	// 	it++;
	// }
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

void RequestParser::ParseQuery(std::string &query) // строка запроса
{
	std::vector<std::string> query_split = split(query, ' ');
	std::vector<std::string> args;

	request.query.method = query_split[0];
	args = split_one(query_split[1], "?");
	request.query.address = args[0];
	request.query.query_string = args[1];
	if (query_split.size() == 3)
		request.query.protocol = query_split[2];
	else
		request.query.protocol = "1.1";
}

void RequestParser::ParseRequest()
{
	std::vector<std::string>::iterator it;

	parseLines = split(saver, '\n');
	it = parseLines.begin();

	ParseQuery(*it); // строка запроса

	std::vector<std::string> head_split;
	while (++it != parseLines.end()) // заголовки запроса
	{
		if (*it == "")
			break;
		head_split = split_one(*it, ": ");
		if (*it == "")
			break;
		request.head.insert(std::pair<std::string, std::string>(head_split[0], head_split[1]));
		++count;
	}
	// it++;
	// if (*it == "") // тело запроса
	// {
	// 	while (++it != parseLines.end())
	// 	{
	// 		request.body += *it;
	// 		request.body += "\n";
	// 	}
	// 	std::cout << "body start\n";
	// 	std::cout << request.body;
	// }
}
