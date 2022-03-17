#include "Request.hpp"

Request::Request()
{

}

Request::Request(Request &other)
{
	*this = other;
}

Request &Request::operator=(const Request &other)
{
	body = other.body;
	head = other.head;
	query = other.query;
	return (*this);
}

Request::~Request()
{

}

// HTTP/1.1
// status code
//Content-type
// Date (?)
// Connection
// Content-lenght