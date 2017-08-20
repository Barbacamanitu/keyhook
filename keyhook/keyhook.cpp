// keyhook.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "KeyboardHook.h"
#include <iostream>
//#define _WIN32_WINNT 0x050



int main()
{

	while (KeyboardHook::getInstance().isActive()) {

	}

	std::cout << "Done" << std::endl;
	system("pause");
	return(0);
}