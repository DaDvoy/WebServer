#ifndef CONFIGPARSER_HPP
#define CONFIGPARSER_HPP

#include <list>
#include <algorithm>
#include "ConfigFile.hpp"

using namespace std;

class ConfigParser
{

public:

    ConfigParser();
    ~ConfigParser();

    std::list<ConfigFile> GetServerConfigs(const std::string &configFileName);

private:

    int iter;
    vector<string> configLines;
    vector<string> GetKeyValue(string line);
    ConfigFile ConfigParse();
    void ParseOptionIntoConfig(ConfigFile &config);
    void ParseLocationIntoConfig(ConfigFile &config, vector<string> &words);
    void ParseWordsInMap(vector<string> words, map<string, string> &map, int i);
    void ParseError();

};

#endif
