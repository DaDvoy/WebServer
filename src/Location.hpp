#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <map>
#include <string>

class ConfigFile;

using namespace std;

class Location
{

public:

    string                  path;
    map<string, string>     confVar;
    ConfigFile*             config;

    Location(string path);
    Location    &operator=(const Location&  copy);
    bool        operator<(const Location   copy) const;
    ~Location();

};

#endif