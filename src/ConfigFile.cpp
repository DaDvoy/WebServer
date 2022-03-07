#include "ConfigFile.hpp"

ConfigFile::~ConfigFile(){}
ConfigFile::ConfigFile() 
{
    port = 80;
    limitClientBodySize = 0;
    auth = false;
    autoindex = false;
    domain = "localhost";
    ip = "127.0.0.1";
    cgiPath = "";
    index = "index.html";
    auth_file_path = "";
    rootDirectory = "/var/www";
}

void ConfigFile::ParseConfVar()
{
    map<string, string> unusedOptions(confVar);

    parseFieldFromMap(unusedOptions, "listen", port);
    parseFieldFromMap(unusedOptions, "client_max_body_size", limitClientBodySize);
    parseFieldFromMap(unusedOptions, "basic_auth", auth);
    parseFieldFromMap(unusedOptions, "autoindex", autoindex);
    parseFieldFromMap(unusedOptions, "server_name", domain);
    parseFieldFromMap(unusedOptions, "cgi_path", cgiPath);
    parseFieldFromMap(unusedOptions, "index", index);
    parseFieldFromMap(unusedOptions, "error_page", errorPage);
    parseFieldFromMap(unusedOptions, "allowed_functions", allowedFunctions);
    parseFieldFromMap(unusedOptions, "basic_auth_file", auth_file_path);
    parseFieldFromMap(unusedOptions, "root", rootDirectory);

    if (unusedOptions.size() > 0)
    {
        map<string, string>::iterator  iter = unusedOptions.begin();
        while (iter != unusedOptions.end())
        {
            cerr << "Unknown field: " << iter->first << endl;
            iter++;
        }
        throw exception();
    }

    if (auth)
    {
        string auth_file;
        try
        {
            auth_file = FileGetContent(auth_file_path);
        }
        catch (exception)
        {
            cerr << "Invalid auth file\n";
            throw exception();
        }
        auth_file_content = split("\n", auth_file);
    }

    vector<Location>::iterator locationBegin = locations.begin();

    while (locationBegin != locations.end())
    {
        Location &location = *locationBegin;
        ConfigFile configCopy;
        configCopy = *this;
        configCopy.locations = vector<Location>();
        configCopy.confVar = location.confVar;
        configCopy.ParseConfVar();
        location.config = new ConfigFile(configCopy);
        locationBegin++;
    }
}

bool ConfigFile::parseFieldFromMap(map<string, string> &fieldMap, string fieldKey, string &fieldRef)
{
    if (fieldMap.count(fieldKey) == 0)
        return false;

    string value = fieldMap[fieldKey];
    fieldRef = value;
    fieldMap.erase(fieldKey);
    return true;
}

bool ConfigFile::parseFieldFromMap(map<string, string> &fieldMap, string fieldKey, int &fieldRef)
{
    if (fieldMap.count(fieldKey) == 0)
        return false;

    string value = fieldMap[fieldKey];

    try
    {
        fieldRef = stoi(value);
    }
    catch (exception)
    {
        return false;
    }

	if (fieldKey == "client_max_body_size")
    {
		if (value.find('k') != string::npos)
			fieldRef *= 1024;
		else if (value.find('M') != string::npos)
			fieldRef *= 1048576;
	}

    fieldMap.erase(fieldKey);
    return true;
}

bool ConfigFile::parseFieldFromMap(map<string, string> &fieldMap, string fieldKey, bool &fieldRef)
{
    if (fieldMap.count(fieldKey) == 0)
        return false;

    string value = fieldMap[fieldKey];

    if (value == "on")
    {
        fieldRef = true;
    }
    else if (value == "off")
        fieldRef = false;
    else
        return false;

    fieldMap.erase(fieldKey);
    return true;
}

ConfigFile &ConfigFile::operator=(ConfigFile const &copy)
{
	if (this != &copy)
    {
		this->port = copy.port;
		this->limitClientBodySize = copy.limitClientBodySize;
		this->auth = copy.auth;
		this->autoindex = copy.autoindex;
		this->domain = copy.domain;
		this->ip = copy.ip;
		this->cgiPath = copy.cgiPath;
		this->index = copy.index;
		this->errorPage = copy.errorPage;
		this->allowedFunctions = copy.allowedFunctions;
		this->auth_file_path = copy.auth_file_path;
		this->rootDirectory = copy.rootDirectory;
		this->auth_file_content = copy.auth_file_content;
		this->locations = copy.locations;
		this->confVar = copy.confVar;
	}
    return *this;
}