#include "pch.h"
#include "process.h"

int main()
{

	console_properties prop;

	prop.console_application = "C:\\Windows\\System32\\cmd.exe";//C:\\Windows\\System32\\WindowsPowerShell\\v1.0\\powershell.exe
	prop.working_directory = "C:\\Windows";

	console_process cmd(prop);

	cmd.open();
	
	cmd.execute("dir", [&](std::string s) {std::cout << s; });
}
