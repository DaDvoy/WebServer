#include "Configs.hpp"

Configs::Configs()
{
	port = 0;
	auto_index = 0;
	client_max_body_size = 0;
	server_name = "";
	index = "";
	root = "";
	error_page = "";
	is_location = false;
	cgi_path = "";
}

Configs::Configs(Configs const &other)
{
	port = other.port;
	auto_index = other.auto_index;
	client_max_body_size = other.client_max_body_size;
	server_name = other.server_name;
	index = other.index;
	root = other.root;
	error_page = other.error_page;
	cgi_path = other.cgi_path;
	is_location = other.is_location;
}

Configs &Configs::operator=(Configs const &other)
{
	port = other.port;
	auto_index = other.auto_index;
	client_max_body_size = other.client_max_body_size;
	server_name = other.server_name;
	index = other.index;
	root = other.root;
	error_page = other.error_page;
	cgi_path = other.cgi_path;
	is_location = other.is_location;
	return (*this);
}

Configs::~Configs()
{

}
