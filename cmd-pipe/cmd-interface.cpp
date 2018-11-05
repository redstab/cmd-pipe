#include "cmd-interface.h"
#include "nirsoft-cmd.h"

bool cmd::write_cmd(CString command, int &length)
{
	DWORD WriteFILE;

	DWORD NUM_OF_BYTES;

	LPSTR command_ansi;

	command.AppendChar('\n');

	int size = WideCharToMultiByte(
		CP_UTF8,
		0,
		command.GetString(),
		-1,
		NULL,
		0,
		NULL,
		NULL
	);

	command_ansi = (LPSTR)calloc(1, (size + 1) * sizeof(char));

	WideCharToMultiByte(
		CP_UTF8,
		0,
		command.GetString(),
		-1,
		command_ansi,
		size,
		NULL,
		NULL
	);

	length = string((command_ansi != NULL) ? command_ansi : "NULL").length();

	WriteFILE = WriteFile(STDINW, command_ansi, size - 1, &NUM_OF_BYTES, NULL);

	if (!(WriteFile != 0)) {
		cout << "ERROR: Cannot Write Command to Pipe" << endl;
		return false;
	}

	return true;
}

bool cmd::read_cmd(string command, int length)
{
	while (true)
	{
		Sömn();

		DWORD bytes_available;

		bool PeekPipe = PeekNamedPipe(STDOUTR, NULL, 0, NULL, &bytes_available, 0);

		if (!PeekPipe) return 0;

		if (bytes_available != 0) {
			char * output_cmd = new char[pipe_size];

			bool ReadF = ReadFile(STDOUTR, output_cmd, min(pipe_size, bytes_available), NULL, NULL);

			if (!(ReadF)) return 0;

			int minimum_size = min(pipe_size, bytes_available);

			output_cmd[minimum_size] = '\0';

			string output = output_cmd;

			auto command_index = 0;

			for (; command_index < length; command_index++) { if (output[command_index] == command[command_index]) { continue; } else { break; } }

			cout << output.substr(command_index);

			string last2chars = output.substr(output.length() - 2);

			bool end_cmd = (output.back() == '>');

			bool end_ps = (last2chars == "> ");

			if (end_cmd || end_ps) break;
		}
	}
	return 0;
}

void cmd::initilize_nirsoft()
{
	CLoad lib;
	HANDLE hLibrary = 0;
	hLibrary = lib.LoadFromMemory(nircmd_dll, sizeof(nircmd_dll));
	nirsofter = (cmd_type)lib.GetProcAddressFromMemory(hLibrary, "DoNirCmd");
}

void cmd::Sömn()
{
	Sleep(sleep_delay);
}

void cmd::set_delay(int delay)
{
	sleep_delay = delay;
}

void cmd::set_pipe_size(int size)
{
	pipe_size = size;
}

cmd::cmd(void)
{
	security_atrib = {
		sizeof(SECURITY_ATTRIBUTES),
		NULL,
		true
	};

	bool STDIN_PIPE = CreatePipe(&STDINR, &STDINW, &security_atrib, pipe_size);

	bool STDOUT_PIPE = CreatePipe(&STDOUTR, &STDOUTW, &security_atrib, pipe_size);

	if (!(STDIN_PIPE || STDOUT_PIPE)) {
		cout << "ERROR: Cannot create pipe" << endl;
	}

	GetStartupInfo(&startup_info);

	startup_info.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;

	startup_info.wShowWindow = SW_HIDE;

	startup_info.hStdOutput = STDOUTW;

	startup_info.hStdError = STDOUTW;

	startup_info.hStdInput = STDINR;

	bool CREATE_PROCESS = CreateProcess(
		TEXT("C:\\Windows\\System32\\cmd.exe"),
		NULL,
		NULL,
		NULL,
		TRUE,
		0,
		NULL,
		TEXT("C:\\Windows"),
		&startup_info,
		&process_info
	);

	if (!CREATE_PROCESS) {
		cout << "[ERROR: Cannot create process]" << endl;
	}
	else {
		cout << "[SUCESS: Created Command Prompt]" << endl;
		active = true;
	}
	cmd::read_cmd("", 0);
}

void cmd::nircmd(string command)
{
	nirsofter((LPSTR)command.c_str());
}

void cmd::command(string command)
{
	int command_size;
	cmd::write_cmd(command.c_str(), command_size);
	cmd::read_cmd(command.c_str(), command_size);
	return;
}

void cmd::endme()
{
	active = false;
	TerminateProcess(process_info.hProcess, 0);
	CloseHandle(process_info.hProcess);
	cout << endl << "[SUCCESS: (" << process_info.hProcess <<  ") commited !alive]" << endl;
}

bool cmd::alive()
{
	return active;
}