#ifndef CONFIGFILE_HPP
#define CONFIGFILE_HPP

#include "Location.hpp"
#include "includes.hpp"
#include <vector>
#include <string>
#include <map>
#include <iostream>

using namespace std;

static string valibleConfVar[10] = {
	"autoindex",
    "index",
    "error_page",
    "client_max_body_size"
};

class ConfigFile
{

public:     

    int                         port;
	int                         limitClientBodySize;
	bool                        auth;
	bool                        autoindex;
	string                      domain;
	string                      ip;
	string                      cgiPath;
	string                      index;
	string                      errorPage;
	string                      allowedFunctions; //	GET/POST		POST/GET		GET		POST
	string                      auth_file_path;
	string                      rootDirectory;
	vector<string>              auth_file_content;
	vector<Location>            locations;
	map<string, string>         confVar;

	ConfigFile();
	~ConfigFile();
	void        	ParseConfVar();
	ConfigFile      &operator=(ConfigFile const& copy);
	string			getIndexPath(string path);

private:

    bool parseFieldFromMap(map<string, string>& fieldMap, string fieldKey, string&   fieldRef);
    bool parseFieldFromMap(map<string, string>& fieldMap, string fieldKey, int&      fieldRef);
    bool parseFieldFromMap(map<string, string>& fieldMap, string fieldKey, bool&     fieldRef);

};

#endif