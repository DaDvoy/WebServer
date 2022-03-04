#include "Utils.hpp"
#include <algorithm>
#include "FileNotFoundException.hpp"

string FileGetContent(const string& path)
{
    std::ifstream t(path);
    if (!t)
        throw FileNotFoundException();
    std::string str((std::istreambuf_iterator<char>(t)),
                    std::istreambuf_iterator<char>());
    return str;
}

vector<string> split(string needle, string str)
{
	size_t len = str.length();
	vector<string> result;
	size_t start = 0;
	size_t end = 0;

	while (start < len)
	{
		end = str.find(needle, start);
		if (end == string::npos)
			end = len;
		result.push_back(str.substr(start, end - start));
		start = end + needle.length();
	}
	return result;
};


bool isContain(string str)
{
	for (string::iterator it = str.begin(); it != str.end(); it++)
	{
		if (*it == ' ' || *it == '\n' || *it == '\t' || *it == '\r')
			return true;
	}
	return false;
}

bool isEmptySpace(int c)
{
	return (c == ' ' || c == '\n' || c == '\t' || c == '\r');
}

std::string& ltrim(std::string& str, const std::string& chars)
{
    str.erase(0, str.find_first_not_of(chars));
    return str;
}

std::string& rtrim(std::string& str, const std::string& chars)
{
    str.erase(str.find_last_not_of(chars) + 1);
    return str;
}

std::string& trim(std::string& str, const std::string& chars)
{
    return ltrim(rtrim(str, chars), chars);
}

int		match(const char *s1, const char *s2)
{
	if (*s1 != '\0' && *s2 == '*')
		return (match(s1 + 1, s2) || match(s1, s2 + 1));
	if (*s1 == '\0' && *s2 == '*')
		return (match(s1, s2 + 1));
	if (*s1 == *s2 && *s1 != '\0' && *s2 != '\0')
		return (match(s1 + 1, s2 + 1));
	if (*s1 == '\0' && *s2 == '\0')
		return (1);
	return (0);
}
