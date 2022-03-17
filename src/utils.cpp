#include <algorithm>
#include "includes.hpp"
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

int     file_put_contents(string filename, int fd, int rights)
{
	int        index;
	int             target;
	int             count;
	unsigned char   buf[10240] = {0};

	if (filename.empty())
		return -1;
	filename = abs_path(filename);
	if (!is_file(filename)) {
		if (is_dir(filename))
			return -1;
		index = filename.find_last_of('/');
		if (index != -1)
			if (create_dir(filename.substr(0, index)) == -1)
				return pError("mkdir");
	}
	target = open(filename.c_str(), O_CREAT | O_WRONLY | O_TRUNC, rights);
	if (target == -1)
		return pError("open");

	do {
		count = read(fd, buf, 10239);
		if (count == -1)
			unlink(filename.c_str());
		if (!count)
			continue;
		if (write(target, buf, count) == -1)
		{
			pError("write");
			if (unlink(filename.c_str()) < 0)
				pError("unlink");

			close(target);
			return -1;
		}
		memset(buf, 0, 10240);
	} while (count != 0);
	close(target);
	return 0;
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

bool exists(string const&path)
{
	struct stat buf;
	bzero(&buf, sizeof(struct stat));
	if (stat(path.c_str(), &buf) == -1)
		return false;
	return true;
}

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

std::string& LeftTrim(std::string& str, const std::string& chars)
{
    str.erase(0, str.find_first_not_of(chars));
    return str;
}

std::string& RightTrim(std::string& str, const std::string& chars)
{
    str.erase(str.find_last_not_of(chars) + 1);
    return str;
}

std::string& ft_trimmer(std::string& str, const std::string& chars)
{
    return LeftTrim(RightTrim(str, chars), chars);
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

std::vector<std::string>	ft_split(char symb_split, std::string &string_split)
{
	int	end = 0;
	int	start = 0;
	std::vector<std::string> vector_split;

	for (int i = 0; i < (int)string_split.length(); i++)
	{
		if (string_split[i] == symb_split)
		{
			end = i;
			vector_split.push_back(string_split.substr(start, end - start));
			start = end;
		}
	}
	return (vector_split);
}

std::vector<std::string> split(std::string &strToSplit, char delimeter)
{
    std::stringstream ss(strToSplit);
    std::string item;
    std::vector<std::string> splittedStrings;

    while (std::getline(ss, item, delimeter))
        splittedStrings.push_back(item);

    return splittedStrings;
}

std::vector<std::string> split_one(std::string stringToBeSplitted, std::string delimeter)
{
	std::vector<std::string> splittedString;
	int index;

	index = stringToBeSplitted.find_first_of(delimeter, 0);
	splittedString.push_back(stringToBeSplitted.substr(0, index));
	splittedString.push_back(stringToBeSplitted.substr(index + 2, stringToBeSplitted.size() - 1));
	return (splittedString);
}

std::string	ToupperStr(std::string const &strToUpper)
{
	std::string newStr;

	for (int i = 0; i < (int)strToUpper.size(); i++)
	{
		newStr.push_back((char)std::toupper(strToUpper[i]));
	}
	
	return (newStr);
}

string  abs_path(string path)
{
	string  result;
	string  tmp;
	char    buf[512] = {};
	vector<string> folders;

	if (path[0] == '/')
		return path;
	getcwd(buf, sizeof(buf));
	result = buf;
	folders = split("/", path);

	for (unsigned i = 0; i < folders.size(); i++) {
		tmp = folders[i];
		if (tmp == "..")
			result.erase(result.find_last_of('/'), result.size());
		else if (tmp == "." || tmp.empty())
			continue ;
		else
			result += "/" + tmp;
	}
	return result;
}

int pError(string const&program)
{
	std::cerr << program << ": " << strerror(errno) << std::endl;
	return -1;
}

bool is_file(string const&path)
{
	struct stat buf;
	bzero(&buf, sizeof(struct stat));
	if (stat(path.c_str(), &buf) == -1)
		return false;
	return S_ISREG(buf.st_mode);
}

bool is_dir(string const&path)
{
	struct stat buf;
	bzero(&buf, sizeof(struct stat));
	if (stat(path.c_str(), &buf) == -1)
		return false;
	return S_ISDIR(buf.st_mode);
}
