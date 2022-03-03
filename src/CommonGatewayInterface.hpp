#ifndef COMMONGATEWAYINTERFACE//fcarl
# define COMMONGATEWAYINTERFACE

#include <map>
#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include "includes.hpp"
#include "Request.hpp"
#include "Configs.hpp"

class CommonGatewayInterface
{
	public:
		CommonGatewayInterface(std::string const &path, char **env, Request &request, sockaddr_in &addr, Configs &config);
		CommonGatewayInterface(CommonGatewayInterface const &other);
		~CommonGatewayInterface();

		CommonGatewayInterface &operator=(CommonGatewayInterface const &other);
		std::string	ExecuteCGI();
	private:

		char		**env;
		std::string cgiPath;
		void	FillEnv(Request &request, sockaddr_in &addr, Configs &config);

};

#endif