#pragma once
#include <Windows.h>
#include <iostream>
/*
	This class is a Singleton because it makes use of a system wide callback, so
	only one instance of this class may exist.

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
	void registerHook();
	void unregisterHook();
	bool isActive();
	static KeyboardHook& getInstance();
	
private:
	KeyboardHook();
	~KeyboardHook();
	

	//Higher level Keyup/Keydown methods.
	void Keydown(DWORD virtualKey, DWORD scanCode);
	void Keyup(DWORD virtualKey, DWORD scanCode);

	//Windows Low-level Keyboard hook callback function
	static LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);

	//Private keyboard hook variables.
	HHOOK hhkLowLevelKybd;
	MSG msg;
};

