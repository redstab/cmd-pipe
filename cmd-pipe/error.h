#pragma once

#include <iostream>
#include <string>
#include <locale>
#include <Windows.h>

class windows_error
{

public:
	windows_error(int);
	windows_error(std::string);
	windows_error(const windows_error&);

	int code();
	void code(int);

	std::string message();
	void message(std::string);

	std::string fetch_message(int);
	int fetch_code(std::string);
	
private:
	int error_code = -1;
	std::string error_message;

};

inline std::ostream& operator<<(std::ostream& os, windows_error er)
{
	return os << "[" << er.code() << "] - " << er.message();
}