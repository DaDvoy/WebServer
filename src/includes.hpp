#ifndef INCLUDES_HPP
# define INCLUDES_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib> // For exit() and EXIT_FAILURE
#include <unistd.h> // For read



std::vector<std::string>	ft_split(char symb_split, std::string string_split);
std::vector<std::string>	split(std::string strToSplit, char delimeter);
std::string					&ft_trimmer(std::string const &symbs, std::string &string_trim);
std::string					&ltrim(std::string& str, std::string const &symbs);
std::string					&rtrim(std::string& str, std::string const &symbs);

#endif
