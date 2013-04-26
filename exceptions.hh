#ifndef _XT_EXCEPTIONS_HH_
#define _XT_EXCEPTIONS_HH_

#include <exception>
#include <string>

namespace xt {

class RuntimeException: public std::exception {
	std::string data;
public:
	RuntimeException(const std::string& error) : data(error) {};
	virtual ~RuntimeException() throw() {};

	inline virtual const char* what() const throw() {return data.c_str();}; 
};

}

#endif
