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
	command_prompt.initilize_custom("C:\\Users\\legit.kms\\source\\repos\\cmd-pipe\\Release\\nc.exe", "C:\\Users\\legit.kms\\source\\repos\\cmd-pipe\\Release", ": ", true);
	while (command_prompt.alive()) {
		string command;
		getline(cin, command);
		cout << command << endl;
		command_prompt.command(command);
		command_prompt.endme();
	}
}