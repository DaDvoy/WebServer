#include "ConfigParser.hpp"
#include <map>
int main(int argc, char const *argv[])
{
    ConfigParser parser;

    string config = "default_conf.conf";
    list<ConfigFile> Configs = parser.GetServerConfigs(config);

}
