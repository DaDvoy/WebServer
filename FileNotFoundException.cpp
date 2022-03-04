#include "FileNotFoundException.hpp"

FileNotFoundException::FileNotFoundException() {};

FileNotFoundException::~FileNotFoundException() throw() {};


const char *FileNotFoundException::what() const throw()
{
	return "File not found";
};