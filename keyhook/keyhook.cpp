// keyhook.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "KeyboardHook.h"
#include <iostream>
//#define _WIN32_WINNT 0x050
bool isRegistered = false;
void unregister();

BOOL WINAPI ConsoleHandlerRoutine(DWORD dwCtrlType) {
	if (CTRL_CLOSE_EVENT == dwCtrlType) {
		unregister();
		return TRUE;
	}

	return FALSE;
}

int messageLoop() {
	MSG msg;
	BOOL bRet;
	while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
	{
		if (bRet == -1)
		{
			// handle the error and possibly exit
			return bRet;
		}
		else
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}

void setupExitHandler() {
	std::cout << "Setting up exit handler..." << std::endl;
	atexit(unregister);
	if (FALSE == SetConsoleCtrlHandler(ConsoleHandlerRoutine, TRUE)) {
		// Cannot register your handler? Check GetLastError()
		std::cout << "Couldn't set up exit handler." << std::endl;
	}
	else {
		std::cout << "Sucessfully set up exit handler!" << std::endl;
	}
}

void unregister() {
	if (isRegistered) {
		std::cout << "Unregistering Keyboard Hook..." << std::endl;
		KeyboardHook::getInstance().unregisterHook();
		std::cout << "Keyboard Hook Unregistered!" << std::endl;
	}
}
int main()
{
	KeyboardHook::getInstance().registerHook();
	isRegistered = true;

	setupExitHandler();
	std::cout << "Hook Registered." << std::endl;
	
	std::cout << "Starting message loop..." << std::endl;
	int result = messageLoop();
	std::cout << "Message loop ended. Terminating program." << std::endl;
	return result;
	//return(0);
}