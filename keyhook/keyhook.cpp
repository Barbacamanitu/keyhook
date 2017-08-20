// keyhook.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "KeyboardHook.h"
#include <iostream>
//#define _WIN32_WINNT 0x050

bool isRegistered = false;
void unregister();
int messageLoop();


int main()
{
	KeyboardHook::getInstance().registerHook();
	isRegistered = true;
	std::cout << "Hook Registered." << std::endl;	

	//Add observer to keyboardhook

	auto upObs = [&](DWORD vk, DWORD sc) {
		std::cout << "Up Observer. Pressed key: " << (char)vk << std::endl;
		KeyboardState state = KeyboardHook::getInstance().getModifierState();
		//Dump the modifier keys
		state.Dump();
	};

	auto downObs = [&](DWORD vk, DWORD sc) {
		//std::cout << "I'm an observer! (down) VK: " << vk << ", SC: " << sc << std::endl;
	};
	KeyboardHook::getInstance().AddKeyObserver(KeyEventType::DOWN,downObs);
	KeyboardHook::getInstance().AddKeyObserver(KeyEventType::UP, upObs);




	std::cout << "Starting message loop..." << std::endl;
	int result = messageLoop();
	std::cout << "Message loop ended. Terminating program." << std::endl;
	return result;
	//return(0);
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

void unregister() {
	if (isRegistered) {
		std::cout << "Unregistering Keyboard Hook..." << std::endl;
		KeyboardHook::getInstance().unregisterHook();
		std::cout << "Keyboard Hook Unregistered!" << std::endl;
	}
}