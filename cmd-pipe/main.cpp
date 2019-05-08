#include "pch.h"
#include "process.h"

int main()
{

	console_properties prop;

	prop.console_application = "C:\\Windows\\System32\\cmd.exe";
	prop.working_directory = "C:\\Windows";

	console_process cmd(prop);

	cmd.open();

	auto [written, result] = cmd.write("ping google.com /n 5\n");

	bool more = true;
	while (more) {
		auto [a, b] = cmd.read();
		more = b;
		if (!a.empty()) {
			std::cout << a;
		}
	}
}
