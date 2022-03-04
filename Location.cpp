#include <vector>
#include "Utils.hpp"
#include "Location.hpp"

Location::Location(std::string path) : path(path) {}

Location::~Location() {}

Location &Location::operator=(const Location &copy)
{
	if (this != &copy)
	{
		this->path = copy.path;
	}
	return *this;
}


bool Location::operator<(const Location copy) const
{
    return this->path < copy.path;
}
