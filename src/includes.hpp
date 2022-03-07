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
#include <fstream>
#include <algorithm>
#define READ_BUFFER 32768


using namespace std;

std::vector<std::string>	ft_split(char symb_split, std::string &string_split);
std::vector<std::string>	split(std::string &strToSplit, char delimeter);
std::vector<std::string>	split_one(std::string stringToBeSplitted, std::string delimeter);
std::string					&ft_trimmer(std::string const &symbs, std::string &string_trim);
std::string					&LeftTrim(std::string& str, std::string const &symbs);
std::string					&RightTrim(std::string& str, std::string const &symbs);
std::string					ToupperStr(std::string const &strToUpper);
string  					FileGetContent(const string& path);
vector<string> 				split(string needle, string str);

string& 					ltrim(string& str, const string& chars = "\t\n\v\f\r ");
string& 					rtrim(string& str, const string& chars = "\t\n\v\f\r ");
string& 					trim(string& str, const string& chars = "\t\n\v\f\r ");

int 						match(const char *s1, const char *s2);
bool						isEmptySpace(int c);
bool						isContain(string str);


#endif
