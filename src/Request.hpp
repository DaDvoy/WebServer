#ifndef REQUEST_HPP
#define REQUEST_HPP

#include "includes.hpp"

struct query_str
{
	std::string  query_string;
	std::string  method;
	std::string  address;
	std::string  protocol;
}

class Request
{
	public:
		Request();
		~Request();
		query_str	query;
		std::string	body
		std::map<std::string, std::string>	head;
};

#endif