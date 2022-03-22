#ifndef INCLUDES_HPP
# define INCLUDES_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <list>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib> // For exit() and EXIT_FAILURE
#include <unistd.h> // For read
#include <fstream>
#include <algorithm>
#include <sys/stat.h>
#include <dirent.h>
#define READ_BUFFER 32768


using namespace std;

vector<string>				ft_split(char symb_split, string &string_split);
vector<string>				split(string &strToSplit, char delimeter);
vector<string>				split_one(string stringToBeSplitted, string delimeter);
string						ToupperStr(string const &strToUpper);
string  					FileGetContent(const string& path);
vector<string> 				split(string needle, string str);

string& 					LeftTrim(string& str, const string& chars = "\t\n\v\f\r ");
string& 					RightTrim(string& str, const string& chars = "\t\n\v\f\r ");
string& 					ft_trimmer(string& str, const string& chars = "\t\n\v\f\r ");

int 						match(const char *s1, const char *s2);
bool						isEmptySpace(int c);
bool						isContain(string str);

string						getIP(unsigned long ip);
string						abs_path(string path);
bool						exists(string const&path);
vector<string>				*get_dir_content(string const &path);
bool						is_file(string const&path);

#endif
