#include "pch.h"
#include "process.h"

std::string after_string(std::string input, std::string query) {
	auto found = input.find(query);
	if (found != std::string::npos && found == 0) { // must be at start because of 
		return input.substr(query.length());
	}
	else {
		return input;
	}

}

int main()
{

	console_properties prop;

	prop.console_application = "C:\\Windows\\System32\\cmd.exe";
	prop.working_directory = "C:\\Windows";

	console_process cmd(prop);

	cmd.open();

	// Read startup message
	cmd.read([&](std::string partial_output) {std::cout << partial_output; });

	// Start interactive prompt
	std::string command;
	while (cmd.alive() && std::getline(std::cin, command)) {
		cmd.execute(command + "\n", [&](std::string partial_output) {std::cout << after_string(partial_output, command + "\n"); });
	}

}
