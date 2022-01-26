#include "ConfigParser.hpp"

void	ConfigParser::parseLocation(Configs &config)
{
	std::cerr << "in location==============================\n";
	config.is_location = true;
	while (it != it_end || *it != "}")
	{
		std::cerr << *it << "|" << std::endl;
		it++;
	}
}


Configs	ConfigParser::parseConfig()
{
	Configs	newConfig;
	it++;
	*it = ft_trimmer('\n', *it);
	if (*it != "{")
	{
		std::cerr << *it << ": parse error server starter quotes is missing\n";
		exit(-1);
	}
	while (it != it_end)
	{
		*it = ft_trimmer('\n', *it);
		// *it = ft_trimmer('\t', *it);
		// *it = ft_trimmer('\v', *it);
		// *it = ft_trimmer('\f', *it);
		// *it = ft_trimmer('\r', *it);
		std::cerr << *it << "|" << std::endl;
		if ((*it).substr(0, strlen("location")) == "location")
		{
			it++;
			newConfig.is_location = true;
			parseLocation(newConfig);
		}
		if (*it == "}")
			break;
		it++;
	}
	return (newConfig);
}

ConfigParser::ConfigParser(std::string const &configName)
{
	std::ifstream config_file(configName);
	if (config_file.fail())
	{
		std::cerr << config_file << ": open error\n";
		exit(0);
	}
	std::string parseString((std::istreambuf_iterator<char>(config_file)), std::istreambuf_iterator<char>());
	parseLines = ft_split('\n', parseString);
	it = parseLines.begin();
	it_end = parseLines.end();
	while (it != it_end)
	{
		if (*it == "server")
			config.push_back(parseConfig());
		else if (*it == "")
			continue;
		it++;
	}
	std::cout << std::endl;
}

ConfigParser::ConfigParser()
{

}

ConfigParser::~ConfigParser()
{

}
