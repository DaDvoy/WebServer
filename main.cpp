#include "./src/includes.hpp"
#include "./src/Response.hpp"
#include "./src/ConfigParser.hpp"
#include "./src/RequestParser.hpp"
#include "./src/CommonGatewayInterface.hpp"
#include "./src/ConfigParser.hpp"
#include "./src/ServerLaunch.hpp"
#include <map>

#define PORT 8080

int main(int argc, char  *argv[])
{
		if (argc != 2)
	{
		std::cerr << "Wrong params!\n";
		std::cerr << "help: ./gulugulu src/config/default_conf.conf\n";
		return (-1);
	}
		
	ConfigParser parsing;

    list<ConfigFile> Configs = parsing.GetServerConfigs(argv[1]);

    ServerLaunch    launcher(Configs);
    launcher.ExecuteServers();
	
    return 0;
}
