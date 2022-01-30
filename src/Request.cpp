#include "Request.hpp"

Request::Request()
{

}

Request::Request(Request &other)
{
	*this = other;
}

Request &Request::operator=(Request &other)
{
	body = other.body;
	head = other.head;
	query = other.query;
	return (*this);
}

Request::~Request()
{

}
