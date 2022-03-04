#ifndef HELPER_HPP
#define HELPER_HPP

#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

string  FileGetContent(const string& path);
vector<string> split(string needle, string str);

string& ltrim(string& str, const string& chars = "\t\n\v\f\r ");
string& rtrim(string& str, const string& chars = "\t\n\v\f\r ");
string& trim(string& str, const string& chars = "\t\n\v\f\r ");

int match(const char *s1, const char *s2);
bool isEmptySpace(int c);
bool isContain(string str);

#endif
