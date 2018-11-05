#pragma once
#pragma once
#include <Windows.h>
#include <stdio.h>
#include <atlstr.h>
#include <string>
#include <conio.h>
#include <iostream>
#include <sstream>
#include "memory-lib.h"
using namespace std;
typedef bool (WINAPI *cmd_type)(LPSTR);

class cmd {

public:
	void Sömn();
	void set_delay(int delay);
	void set_pipe_size(int size);
	void set_custom_esc(string escape);
	bool write_cmd(CString command, int &length);
	bool read_cmd(string command, int length);
	void initilize_nirsoft();
	void initilize_custom(string path, string working_directory, string esc, bool output);
	void initilize_cmd(bool output);
	void initilize_ps(bool output);
	void nircmd(string command);
	void command(string command);
	int get_alive();
	void endme();
	bool alive();
	cmd(int delay, int pipe_size);

private:
	bool initilize_process(string path, string working_directory);
	bool active = false;
	bool force_quit = false;
	bool nirsoft = false;
	STARTUPINFOA startup_info;
	PROCESS_INFORMATION process_info;
	SECURITY_ATTRIBUTES security_atrib;
	cmd_type nirsofter;
	string custom_esc = "";
	HANDLE STDINR;
	HANDLE STDINW;
	HANDLE STDOUTR;
	HANDLE STDOUTW;
	DWORD pipe_size;
	DWORD sleep_delay;
};