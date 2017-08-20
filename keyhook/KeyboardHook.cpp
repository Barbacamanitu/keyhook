#include "stdafx.h"
#include "KeyboardHook.h"



void KeyboardHook::Keydown(DWORD virtualKey, DWORD scanCode){
	std::cout << "Keydown!" << std::endl;
}

void KeyboardHook::Keyup(DWORD virtualKey, DWORD scanCode){
	//std::cout << "Keyup!" << std::endl;
	//Iterate through all observers and execute them with the correct key info.
	for (auto f : keyUpObservers) {
		f(virtualKey, scanCode);
	}
}


//Singleton method. Return instance if it exists, and create an instance if not.
KeyboardHook& KeyboardHook::getInstance()
{
	static KeyboardHook instance;
	return instance;
}

//Constructor.
KeyboardHook::KeyboardHook() {
}

//Destructor.
KeyboardHook::~KeyboardHook() {
}

/*
	Low level system callback related methods below this line.
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

LRESULT CALLBACK KeyboardHook::LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode == HC_ACTION)
	{

		PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;
		char theCode = MapVirtualKey(p->vkCode, MAPVK_VK_TO_CHAR);
		switch (wParam)
		{
		case WM_KEYDOWN:
			getInstance().Keydown(p->vkCode, p->scanCode);
			break;
		case WM_SYSKEYDOWN:
			//std::cout << "SysKeydown: " << theCode << std::endl;
			break;
		case WM_KEYUP:
			getInstance().Keyup(p->vkCode, p->scanCode);
			break;
		case WM_SYSKEYUP:

			break;
		default:
			break;
		}
	}
	return (CallNextHookEx(NULL, nCode, wParam, lParam));
}


void KeyboardHook::registerHook()
{
	// Install the low-level keyboard hook
	hhkLowLevelKybd = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardHook::LowLevelKeyboardProc, 0, 0);
}

void KeyboardHook::unregisterHook()
{
	//Unhook keyboard
	UnhookWindowsHookEx(hhkLowLevelKybd);
}