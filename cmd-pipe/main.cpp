#include "cmd-interface.h"
using namespace std;

//					Inspiration:
//https://www.mpgh.net/forum/showthread.php?t=1101356
//https://stackoverflow.com/a/1874109/4363773
//https://stackoverflow.com/questions/13054401/how-does-condition-statement-work-with-bit-wise-operators

int main()
{
	cmd command_prompt(PowerShell|CommandPrompt); 
	//command_prompt.initilize_custom("C:\\path\\to\\file.exe", "C:\\path\\to\\working-directory", ": ", true);
	//command_prompt.initilize_ps(true);
	//command_prompt.initilize_nirsoft();
	//command_prompt.initilize_cmd();
	
	while (command_prompt.alive()) {
		string command;
		getline(cin, command);
		command_prompt.command(command);
		//command_prompt.endme();
	}
}