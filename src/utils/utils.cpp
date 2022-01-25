#include "../includes.hpp"

std::string& ltrim(std::string& str, char chars)
{
    str.erase(0, str.find_first_not_of(chars));
    return str;
}

std::string& rtrim(std::string& str, char chars)
{
    str.erase(str.find_last_not_of(chars) + 1);
    return str;
}

std::string &ft_trimmer(char symb_trim, std::string& string_trim)
{
    return ltrim(rtrim(string_trim, symb_trim), symb_trim);
}

std::vector<std::string>	ft_split(char symb_split, std::string string_split)
{
	int	end = 0;
	int	start = 0;
	std::vector<std::string> vector_split;

	for (int i = 0; i < string_split.length(); i++)
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
