#include "ConfigParser.hpp"//fcarl

void	ConfigParser::parseOneField(std::string &field, Configs &config)
{
	std::cerr << field << "|" << std::endl;
	std::vector<std::string>	str_split = split(field, ' ');
	str_split[1].erase(str_split[1].length());
	if (str_split[0] == "server_name")
		config.server_name = str_split[1].erase(str_split[1].length() - 1);
	else if (str_split[0] == "error_page")
		config.error_page = str_split[1].erase(str_split[1].length() - 1);
	else if (str_split[0] == "listen")
		config.port = std::stoi(str_split[1].erase(str_split[1].length() - 1));
	else if (str_split[0] == "client_max_body_size")
		config.client_max_body_size = std::stoi(str_split[1].erase(str_split[1].length() - 1));
	else if (str_split[0] == "root")
		config.root = str_split[1].erase(str_split[1].length() - 1);
}

void	ConfigParser::parseLocation(Configs &config)
{
	std::cerr << "\nin location==============================\n";
	std::string str;

	config.count_locations++;
	while (it != it_end)
	{
		str = ft_trimmer("\t\n\v\f\r ", *it);
		if (*it == "}")
			break;
		it++;
	}
}


Configs	ConfigParser::parseConfig()
{
	Configs	newConfig;
	std::string str;

	it++;
	*it = ft_trimmer("\t\n\v\f\r ", *it);
	if (*it != "{")
	{
		std::cerr << *it << ": parse error server starter quotes is missing\n";
		exit(-1);
	}
	while (++it != it_end)
	{
		str = ft_trimmer("\t\n\v\f\r ", *it);
		if (*it == "")
			continue;
		if (*it == "}")
			break;

		if (str.substr(0, strlen("location")) == "location")
		{
			it++;
			str = ft_trimmer("\t\n\v\f\r ", *it);
			if (str == "{")
				parseLocation(newConfig);
			else
			{
				std::cerr << str << ": parse error location starter quotes is missing\n";
				exit(0);
			}
		}
		if (str != "{")
			parseOneField(str, newConfig);
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

std::list<Configs> &ConfigParser::GetConfig()
{
	return (config);
}

ConfigParser::ConfigParser()
{

}

ConfigParser::~ConfigParser()
{

}
