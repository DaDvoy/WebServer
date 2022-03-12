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
	char *what = (char *)strstr(saver.c_str(), "\n\n");
	if (what)
		request.body = what;
	else
		request.body = "";
	ParseRequest();
}

RequestParser::~RequestParser()
{

}

int RequestParser::ReadRequest(int sock)
{
	long valueRead;

	char *buffer = new char[READ_BUFFER + 1];
	bzero(buffer, READ_BUFFER + 1);
	valueRead = read(sock , buffer, READ_BUFFER);
	if (valueRead < 0 || valueRead > READ_BUFFER + 1)
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
	query = query.substr(0, query.find_first_of("\r\n"));
	std::cout << "query: " << query << std::endl;
	std::vector<std::string> query_split = split(query, ' ');
	std::cout << query_split.size() << std::endl;
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
	std::vector<std::string>::iterator	it;

	parseLines = split(saver, '\n');
	it = parseLines.begin();
	ParseQuery(*it); // строка запроса

	std::vector<std::string> head_split;
	while (++it != parseLines.end()) // заголовки запроса
	{
		if (*it == "")
			break;
		head_split = split_one(*it, ": ");
		if (head_split[0] == "" || head_split[1] == "")
			break;
		request.head.insert(std::pair<std::string, std::string>(head_split[0], head_split[1].substr(0, head_split[1].find_first_of("\r\n"))));
		++count;
	}
	if (!request.body.empty())
		request.body = ft_trimmer(request.body);
	else 
		request.body = "";
}
