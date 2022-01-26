#ifndef CONFIGPARSER_HPP//fcarl
# define CONFIGPARSER_HPP

#include <map>
#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include "includes.hpp"
#include "Configs.hpp"

class ConfigParser
{
	public:
		ConfigParser();
		ConfigParser(std::string const &configName);
		~ConfigParser();
		std::list<Configs> &GetConfig();
		
	private:
		std::list<Configs>			config;
		std::vector<std::string>::iterator it;
		std::vector<std::string>::iterator it_end;
		std::vector<std::string>	parseLines;

		Configs						parseConfig();
		void						parseLocation(Configs &config);
		void						parseOneField(std::string &field, Configs &config);

};

#endif