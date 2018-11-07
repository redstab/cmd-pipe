#include "cmd-interface.h"
using namespace std;

//					Inspiration:
//https://www.mpgh.net/forum/showthread.php?t=1101356
enum dd { ff = 1, dd = 2, cc = 4 };
void print(int d) {
	if (d & ff) {
		cout << "ff";
	}
	if (d & dd) {
		cout << "dd";
	}
	if (d & cc) {
		cout << "cc";
	}
}
int main()
{
	print(ff | dd | cc);
	cmd command_prompt(CommandPrompt);
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