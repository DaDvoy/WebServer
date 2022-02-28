#include "includes.hpp"

std::string& ltrim(std::string& str, std::string const &symbs)
{
    str.erase(0, str.find_first_not_of(symbs));
    return str;
}

std::string& rtrim(std::string& str, std::string const &symbs)
{
    str.erase(str.find_last_not_of(symbs) + 1);
    return str;
}

std::string					&ft_trimmer(std::string const &symbs, std::string &string_trim)
{
    return ltrim(rtrim(string_trim, symbs), symbs);
}

std::vector<std::string>	ft_split(char symb_split, std::string string_split)
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

std::vector<std::string> split(std::string strToSplit, char delimeter)
{
    std::stringstream ss(strToSplit);
    std::string item;
    std::vector<std::string> splittedStrings;

    while (std::getline(ss, item, delimeter))
	{
		// if (item == "")
		// {
		// 	continue;
		// }
        splittedStrings.push_back(item);
	}
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
