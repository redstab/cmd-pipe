#include "pch.h"

int main()
{
	STARTUPINFOA startup_info{};
	PROCESS_INFORMATION process_info{};
	SECURITY_ATTRIBUTES security_attrib{};
	HANDLE STDINR;
	HANDLE STDINW;
	HANDLE STDOUTR;
	HANDLE STDOUTW;

	security_attrib = {
		sizeof(SECURITY_ATTRIBUTES),
		0,
		true
	};

	if (!(CreatePipe(&STDINR, &STDINW, &security_attrib, 0) && CreatePipe(&STDOUTR, &STDOUTW, &security_attrib, 0))) {
		return -12;
	}

	GetStartupInfoA(&startup_info);

	startup_info.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;

	startup_info.wShowWindow = SW_HIDE;

	startup_info.hStdOutput = STDOUTW;

	startup_info.hStdError = STDOUTW;

	startup_info.hStdInput = STDINR;
	PWSTR buffer;
	SHGetKnownFolderPath(FOLDERID_System, 0, 0, &buffer);
	std::wstring system32(buffer);
	CoTaskMemFree(static_cast<void*>(buffer));
	if (!CreateProcessA(std::string(std::string(system32.begin(), system32.end()) + "\\cmd.exe").c_str(), 0, 0, 0, true, CREATE_NEW_CONSOLE, 0, "C:\\Windows", &startup_info, &process_info)) {
		return -13;
	}

	DWORD written;

	std::string command("ping google.com /n 10\n");

	if (WriteFile(STDINW, command.c_str(), command.length() + 1, &written, 0) == 0) {
		return -14;
	}

	bool done = false;

	while (!done) {

		done = ((WaitForSingleObject(STDINR, 50) != WAIT_OBJECT_0));

		DWORD bytes;

		if (!PeekNamedPipe(STDOUTR, 0, 0, 0, &bytes, 0)) {
			return -15;
		}
		else {
			if (bytes != 0) {

				char* output = new char[bytes] {'\0'};

				DWORD read;

				if (!ReadFile(STDOUTR, output, bytes, &read, 0)) {
					return -16;
				}
				else {

					if (read == bytes) {

						std::string out(output);
						for (auto chr : out.substr(0, read)) {
							std::cout << chr;
						}

					}

				}

				delete[] output;

			}
		}
	}

	CloseHandle(process_info.hProcess);
	CloseHandle(process_info.hThread);
	CloseHandle(STDOUTR);
	CloseHandle(STDINW);
	CloseHandle(STDOUTW);
	CloseHandle(STDINR);
	std::cin.get();
}
