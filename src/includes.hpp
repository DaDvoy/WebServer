#ifndef INCLUDES_HPP
# define INCLUDES_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib> // For exit() and EXIT_FAILURE
#include <unistd.h> // For read

std::vector<std::string>	ft_split(char symb_split, std::string string_split);
std::string					&ft_trimmer(char symb_trim, std::string &string_trim);
std::string					&ltrim(std::string& str, const std::string& chars);
std::string					&rtrim(std::string& str, const std::string& chars);

#endif
