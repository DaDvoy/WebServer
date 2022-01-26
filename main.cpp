#include "./src/includes.hpp"
#include "./src/ConfigParser.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Params error!\n";
		return (-1);
	}	
	ConfigParser parsing(argv[1]);

	std::cout << "server_name: " << (*parsing.GetConfig().begin()).server_name << std::endl;
	std::cout << "port: " << (*parsing.GetConfig().begin()).port << std::endl;
	std::cout << "error_page: " << (*parsing.GetConfig().begin()).error_page << std::endl;
	std::cout << "root: " << (*parsing.GetConfig().begin()).root << std::endl;
	std::cout << "client_max_body_size: " << (*parsing.GetConfig().begin()).client_max_body_size << std::endl;
}
