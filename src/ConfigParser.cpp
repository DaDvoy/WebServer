#include "ConfigParser.hpp"

ConfigParser::ConfigParser() {}
ConfigParser::~ConfigParser() {}

list<ConfigFile> ConfigParser::GetServerConfigs(const string &configFileName)
{
    list<ConfigFile> configs;

    string fileContent = FileGetContent(configFileName);

    configLines = split("\n", fileContent);

    for (iter = 0; iter < (int)configLines.size(); iter++)
    {
        string line = trim(configLines[iter]);
        if (line == "server")
        {
            iter++;
            configs.push_back(ConfigParse());
        }
        else if (line == "")
            continue;
        else
            ParseError();
    }

    list<ConfigFile>::iterator  iter = configs.begin();
    while (iter != configs.end())
    {
        try
        {
            iter->ParseConfVar();
        }
        catch (exception)
        {
            cerr << "Invalid server fields";
            exit(1);
        }
        iter++;
    }

    return configs;
}

void ConfigParser::ParseLocationIntoConfig(ConfigFile &config, vector<string> &words)
{
    string line = trim(configLines[iter]);

    if (*words[1].begin() != '/')
        ParseError();
    Location newLocation(words[1]);

    iter++;

    while (trim(configLines[iter]) == "")
        iter++;

    if (trim(configLines[iter]) != "{")
        ParseError();
    else
        iter++;

    while (line != "}")
    {
        if (line != "")
        {
            string line = trim(configLines[iter]);

            vector<string> words = GetKeyValue(line);

            ParseWordsInMap(words, newLocation.confVar, iter);
        }
        iter++;
        line = trim(configLines[iter]);
    }

    config.locations.push_back(newLocation);
}

bool isContains(string str)
{
	for (string::iterator it = str.begin(); it != str.end(); it++)
	{
		if (*it == ' ' || *it == '\n' || *it == '\t' || *it == '\r')
			return true;
	}
    return false;
}

void ConfigParser::ParseOptionIntoConfig(ConfigFile &config)
{
    string line = trim(configLines[iter]);

    vector<string> words = GetKeyValue(line);

    if (words.size() != 2)
        ParseError();

    if (isContains(words[1]))
        ParseError();

    if (words[0] != "location")
    {
        ParseWordsInMap(words, config.confVar, iter);
    }
    else
    {
        ParseLocationIntoConfig(config, words);
    }
}

ConfigFile ConfigParser::ConfigParse()
{
    while (trim(configLines[iter]) == "")
        iter++;

    if (trim(configLines[iter]) != "{")
        ParseError();
    else
        iter++;

    ConfigFile newConfig;
    string line = trim(configLines[iter]);
    while (line != "}")
    {
        if (line != "")
            ParseOptionIntoConfig(newConfig);
        iter++;
        line = trim(configLines[iter]);
    }
    iter++;
    return newConfig;
}

void ConfigParser::ParseWordsInMap(vector<string> words, map<string, string> &map, int i)
{
    (void)i;
    if (*(words[1].end() - 1) != ';')
        ParseError();
    words[1].erase(words[1].end() - 1);
    map[words[0]] = words[1];
}

vector<string> ConfigParser::GetKeyValue(string line)
{
    vector<string>  words;
    string::iterator endFirstWord = find_if(line.begin(), line.end(), isEmptySpace);
    words.push_back(string(line.begin(), endFirstWord));
    words.push_back(string(find_if_not(endFirstWord, line.end(), isEmptySpace), line.end()));
    return words;
}

void ConfigParser::ParseError()
{
    cerr << "Invalid config: " << iter + 1 << " line";
    exit(1);
}
