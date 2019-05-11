#include "error.h"

windows_error::windows_error(int code)
{
	error_code = code;

	error_message = fetch_message(error_code);
}

windows_error::windows_error(std::string message)
{
	error_message = message;

	error_code = fetch_code(error_message);
}

windows_error::windows_error(const windows_error& er)
{
	error_code = er.error_code;
	error_message = er.error_message;
}

int windows_error::code()
{
	return error_code;
}

void windows_error::code(int code)
{
	error_code = code;
}

std::string windows_error::message()
{
	return error_message;
}

void windows_error::message(std::string message) 
{
	error_message = message;
}

std::string windows_error::fetch_message(int code)
{
	char msg_buf[256]{};

	FormatMessageA(

		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS |
		FORMAT_MESSAGE_MAX_WIDTH_MASK,
		nullptr,
		code,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		msg_buf,
		sizeof(msg_buf),
		nullptr

	);

	return std::string(msg_buf);
}

int windows_error::fetch_code(std::string msg)
{
	for (auto i = 0; i < 16000000; i++) {
		std::string error_ms = fetch_message(i);
		if (!error_ms.empty() && error_ms == msg) {
			return i;
		}
	}

	return -1;
}
