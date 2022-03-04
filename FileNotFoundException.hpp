#ifndef FILE_NOT_FOUND_EXCEPTION_HPP
#define FILE_NOT_FOUND_EXCEPTION_HPP

#include <exception>
#include <string>

using namespace std;

class FileNotFoundException: public exception
{

public:

	FileNotFoundException();
	~FileNotFoundException() throw();

	const char * what() const throw();

};


#endif
