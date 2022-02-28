#ifndef COMMONGATEWAYINTERFACE//fcarl
# define COMMONGATEWAYINTERFACE

#include <map>
#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include "includes.hpp"

class CommonGatewayInterface
{
	public:
		CommonGatewayInterface(std::string const &path, char **env);
		CommonGatewayInterface(CommonGatewayInterface const &other);
		~CommonGatewayInterface();

		CommonGatewayInterface &operator=(CommonGatewayInterface const &other);
		std::string	ExecuteCGI();
	private:

		char		**env;
		std::string cgiPath;
};

#endif