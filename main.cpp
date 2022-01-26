#include "./src/includes.hpp"
#include "./src/ConfigParser.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Params error!\n";
		return (-1);
	}	
	ConfigParser pars(argv[1]);
}
