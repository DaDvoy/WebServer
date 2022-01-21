#ifndef RESPONCE_HPP
# define RESPONCE_HPP

#include "includes.hpp"

class Responce
{
	private:

		std::map<std::string, std::string> headers;
		std::string	body;
		unsigned int status;
	public:
};

#endif