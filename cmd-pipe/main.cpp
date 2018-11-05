#include <iostream>
#include <Windows.h>
#include <string>
#include "cmd-interface.h"
using namespace std;

//					Inspiration:
//https://www.mpgh.net/forum/showthread.php?t=1101356

int main()
{
	cmd command_prompt;
	while (command_prompt.alive()) {
		string command;
		getline(cin, command);
		command_prompt.command(command);
		command_prompt.endme();
	}
	cin.get();
}