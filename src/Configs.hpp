#ifndef CONFIGS_HPP
# define CONFIGS_HPP

#include <map>
#include <string>
#include <iostream>

class Configs
{
	public:
		Configs();
		Configs(Configs const &other);
		Configs &operator=(Configs const &other);
		~Configs();

		int			port;
		int			auto_index;
		int			client_max_body_size;
		bool		is_location;
		std::string	server_name;
		std::string	autoindex;
		std::string	index;
		std::string	root;
		std::string	error_page;
		std::string cgi_path;
	private:
};

#endif
