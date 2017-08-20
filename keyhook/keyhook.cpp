// keyhook.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "KeyboardHook.h"
#include <iostream>
//#define _WIN32_WINNT 0x050



int main()
{
	MSG msg;
	BOOL bRet;
	KeyboardHook::getInstance().registerHook();

	

	while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
	{
			if (bRet == -1)
			{
				// handle the error and possibly exit
				int a = 1;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
	}
	KeyboardHook::getInstance().unregisterHook();


	std::cout << "Done" << std::endl;
	system("pause");
	// Return the exit code to the system. 

	return msg.wParam;
	//return(0);
}