#ifndef COMMONGATEWAYINTERFACE//fcarl
# define COMMONGATEWAYINTERFACE

#include <map>
#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include "includes.hpp"
#include "Request.hpp"
#include "ConfigFile.hpp"

class CommonGatewayInterface
{
	public:
		CommonGatewayInterface(std::string const &path, Request &request, sockaddr_in &addr, ConfigFile &config);
		CommonGatewayInterface(CommonGatewayInterface const &other);
		~CommonGatewayInterface();

		CommonGatewayInterface &operator=(CommonGatewayInterface const &other);
		std::string	ExecuteCGI();
	private:

		char		**env;
		std::string cgiPath;
		void	FillEnv(Request &request, sockaddr_in &addr, ConfigFile &config);

};

#endif