#include "pch.h"
#include "process.h"

int main()
{

	console_properties prop;

	prop.console_application = "C:\\Windows\\System32\\cmd.exe";//C:\\Windows\\System32\\WindowsPowerShell\\v1.0\\powershell.exe
	prop.working_directory = "C:\\Windows";

	console_process cmd(prop);

	cmd.open();

	std::queue<std::string> shs;

	while (cmd.read(shs)) {
		if (!shs.empty()) {
			std::cout << shs.front();
			shs.pop();
		}
	}

	cmd.write("ping google.com\n");//ping google.com /n 5

	std::queue<std::string> ss;

	while (cmd.read(ss)) {
		if (!ss.empty()) {
			std::cout << ss.front();
			ss.pop();
		}
	}
	std::cout << "done" << std::endl;

	std::cin.get();
}
