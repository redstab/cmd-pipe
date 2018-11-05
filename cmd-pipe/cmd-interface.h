#pragma once
#pragma once
#include <Windows.h>
#include <stdio.h>
#include <atlstr.h>
#include <string>
#include <conio.h>
#include <iostream>
#include "memory-lib.h"
using namespace std;
typedef bool (WINAPI *cmd_type)(LPSTR);

class cmd {
public:
	void Sömn();
	void set_delay(int delay);
	void set_pipe_size(int size);
	bool write_cmd(CString command, int &length);
	bool read_cmd(string command, int length);
	void initilize_nirsoft();
	void nircmd(string command);
	void command(string command);
	void endme();
	bool alive();
	cmd();
private:
	bool active = false;
	STARTUPINFO startup_info;
	PROCESS_INFORMATION process_info;
	SECURITY_ATTRIBUTES security_atrib;
	cmd_type nirsofter;
	HANDLE STDINR;
	HANDLE STDINW;
	HANDLE STDOUTR;
	HANDLE STDOUTW;
	DWORD pipe_size = 1000000;
	DWORD sleep_delay = 10;
};