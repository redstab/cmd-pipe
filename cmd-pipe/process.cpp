#include "pch.h"
#include "process.h"

console_process::console_process(console_properties input_properties)
{
	if (input_properties.console_application.empty() || input_properties.working_directory.empty()) {
		throw std::invalid_argument("received no executable or working directory");
	}

	process_properties = input_properties;

	startup_info.dwFlags = process_properties.startup_flags;
	startup_info.wShowWindow = process_properties.show_console;


	security_attrib = { sizeof(SECURITY_ATTRIBUTES), 0, process_properties.inherit_handle };
}

console_process::~console_process()
{
	CloseHandle(input_read);
	CloseHandle(input_write);
	CloseHandle(output_read);
	CloseHandle(output_write);
	CloseHandle(process_info.hThread);
	CloseHandle(process_info.hProcess);
}

std::tuple<HANDLE, HANDLE, HANDLE, HANDLE> console_process::handles()
{
	return std::make_tuple(input_read, input_write, output_read, output_write);
}

bool console_process::open()
{
	open_pipe(input_read, input_write);
	open_pipe(output_read, output_write);


	if (process_properties.capture_output) {
		startup_info.hStdOutput = output_write;
		startup_info.hStdError = output_write;
		startup_info.hStdInput = input_read;
	}

	return CreateProcessA(process_properties.console_application.c_str(), 0, 0, 0, process_properties.inherit_handle, process_properties.console_flags, 0, process_properties.working_directory.c_str(), &startup_info, &process_info);
}

bool console_process::close()
{
	return TerminateProcess(process_info.hProcess, 0);
}

std::tuple<bool, int> console_process::write(std::string input)
{
	DWORD bytes_written;
	return { WriteFile(input_write, input.c_str(), input.length() + 1, &bytes_written, 0), bytes_written };
}

std::tuple<std::string, buffer_result> console_process::read()
{
	// Check if we can write to input
	
	// Peak at buffer for data
	
	DWORD bytes_available;

	if (PeekNamedPipe(output_read, 0, 0, 0, &bytes_available, 0)) {
		if (bytes_available != 0) { // if buffer does not equal 0
			
			DWORD read;

			char* output = new char[bytes_available] {'\0'};
			if (ReadFile(output_read, output, bytes_available, &read, 0)) {

				if (read == bytes_available) {
					std::string out(output);
					delete[] output;
					return {out.substr(0, bytes_available), ((((WaitForSingleObject(input_read, process_properties.timeout) == WAIT_OBJECT_0))) ?  more_data : buffer_empty)};
				}

			}
		}

	}
	return { "", more_data };
	//bool done = false;

	//while (!done) {
	//	done = ((WaitForSingleObject(input_read, 50) != WAIT_OBJECT_0));

	//	DWORD bytes;

	//	if (!PeekNamedPipe(output_read, 0, 0, 0, &bytes, 0)) {
	//		
	//	}
	//	else {
	//		if (bytes != 0) {

	//			char* output = new char[bytes] {'\0'};

	//			DWORD read;

	//			if (!ReadFile(output_read, output, bytes, &read, 0)) {
	//				
	//			}
	//			else {

	//				if (read == bytes) {

	//					std::string out(output);
	//					for (auto chr : out.substr(0, read)) {
	//						std::cout << chr;
	//					}

	//				}
	//				else {
	//					
	//				}

	//			}

	//			delete[] output;

	//		}
	//		else {
	//			
	//		}
	//	}
	//}

	//return { "", buffer_empty };

}

bool console_process::open_pipe(HANDLE& read, HANDLE& write)
{
	return CreatePipe(&read, &write, &security_attrib, 0);
}

