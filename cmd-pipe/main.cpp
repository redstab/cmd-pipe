#include "cmd-interface.h"
using namespace std;

//					Inspiration:
//https://www.mpgh.net/forum/showthread.php?t=1101356

int main()
{
	cmd command_prompt(10, 1000000);
	//command_prompt.initilize_custom("C:\\Users\\legit.kms\\source\\repos\\cmd-pipe\\Release\\nc.exe", "C:\\Users\\legit.kms\\source\\repos\\cmd-pipe\\Release", ": ", true);
	//command_prompt.initilize_ps(true);
	//command_prompt.initilize_nirsoft();
	command_prompt.initilize_cmd(true);
	while (command_prompt.alive()) {
		string command;
		getline(cin, command);
		command_prompt.command(command);
		command_prompt.endme();
	}
}